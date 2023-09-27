import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, mean_absolute_percentage_error

# Load the dataset from the Excel file
df = pd.read_excel('BostonHousing.xlsx', sheet_name='BostonHousing')

# Split the data into X (features) and y (target)
X = df.drop('MEDV', axis=1)
y = df['MEDV']

# Compute the correlation matrix
corr_matrix = X.corr().abs()

# Find highly correlated pairs
high_corr = np.where(corr_matrix > 0.7)
high_corr = [(corr_matrix.columns[x], corr_matrix.columns[y]) for x, y in zip(*high_corr)
             if x != y and x < y]
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=0)
X_train = X_train[:, np.argsort(-np.abs(corr_matrix[0, 1:]))[:6]]
# Define a function to compute the performance metrics for a given model
def evaluate_model(model, X, y):
    # Split the data into training and testing sets
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=0)
    # Train the model on the training set
    model.fit(X_train, y_train)
    # Make predictions on the testing set
    y_pred = model.predict(X_test)
    # Compute the performance metrics
    rmse = mean_squared_error(y_test, y_pred, squared=False)
    mape = mean_absolute_percentage_error(y_test, y_pred)
    me = np.mean(y_pred - y_test)
    return rmse, mape, me, y_test, y_pred

# Define a function to perform backward subset selection
def backward_subset_selection(X, y):
    # Start with all features
    remaining_features = list(X.columns)
    selected_features = []
    # Train a model with all features and compute the baseline performance
    baseline_model = LinearRegression()
    baseline_rmse, _, _, _, _ = evaluate_model(baseline_model, X, y)
    best_rmse = baseline_rmse
    # Iterate over the remaining features and remove one at a time
    while len(remaining_features) > 0:
        rmse_list = []
        for feature in remaining_features:
            # Remove the feature and train a model on the remaining features
            temp_features = [f for f in selected_features if f != feature]
            temp_features += [f for f in remaining_features if f not in selected_features and f != feature]
            temp_X = X[temp_features]
            temp_model = LinearRegression()
            temp_rmse, _, _, _, _ = evaluate_model(temp_model, temp_X, y)
            rmse_list.append(temp_rmse)
        # Find the feature that results in the lowest RMSE
        min_rmse = min(rmse_list)
        min_feature = remaining_features[rmse_list.index(min_rmse)]
        # Check if adding this feature improves the performance
        if min_rmse < best_rmse:
            best_rmse = min_rmse
            selected_features.append(min_feature)
            remaining_features.remove(min_feature)
        else:
            break
    # Train a final model on the selected features
    final_model = LinearRegression()
    final_rmse, final_mape, final_me, y_test, y_pred = evaluate_model(final_model, X[selected_features], y)
    return selected_features, final_rmse, final_mape, final_me, y_test, y_pred

# Define a function to perform forward subset selection

def forward_subset_selection(X, y):
    X_train = X_train[:, np.argsort(-np.abs(corr_matrix[0, 1:]))[:6]]
    n_features = X.shape[1]
    selected = []
    cur_err = float("inf")
    for i in range(n_features):
        best_err = float("inf")
        best_feature = None
        for feature in range(n_features):
            if feature in selected:
                continue
            features = selected + [feature]
            model = LinearRegression().fit(X[:, features], y)
            y_pred = model.predict(X[:, features])
            err = rmse(y, y_pred)
            if err < best_err:
                best_err = err
                best_feature = feature
        if best_err < cur_err:
            cur_err = best_err
            selected.append(best_feature)
        else:
            break
    return selected, cur_err


# Stepwise subset selection
def stepwise_subset_selection(X, y):
    # Initialize the list of selected features
    selected_features = []
    # Initialize the minimum error and best feature index
    min_error = float('inf')
    best_feature_index = None
    # Loop over the features
    for i in range(X.shape[1]):
        # Initialize the list of features to consider
        candidate_features = selected_features + [i]
        # Fit the model and evaluate it using cross-validation
        error = evaluate_model(X[:, candidate_features], y)
        # Check if this feature set has the lowest error so far
        if error < min_error:
            min_error = error
            best_feature_index = i
        # Add the best feature to the list of selected features
        selected_features.append(best_feature_index)
    # Fit the final model and return the selected features
    final_features = selected_features[:-1]
    model = LinearRegression()
    model.fit(X[:, final_features], y)
    return model, final_features

# Run the three subset selection algorithms and evaluate their performance

print("Forward Subset Selection:")
model, features = forward_subset_selection(X_train, y_train)
print("Selected Features:", features)
evaluate_model(X_test[:, features], y_test)

print("Backward Subset Selection:")
model, features = backward_subset_selection(X_train, y_train)
print("Selected Features:", features)
evaluate_model(X_test[:, features], y_test)

print("Stepwise Subset Selection:")
model, features = stepwise_subset_selection(X_train, y_train)
print("Selected Features:", features)
evaluate_model(X_test[:, features], y_test)

