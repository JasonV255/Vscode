import pandas as pd

# Load the dataset from the Excel file
df = pd.read_excel('BostonHousing.xlsx', sheet_name='BostonHousing')

# Split the data into X (features) and y (target)
X = df.drop(['MEDV', 'CAT. MEDV'], axis=1)
y = df['MEDV']

from sklearn.model_selection import train_test_split

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=0)

from sklearn.linear_model import LinearRegression

# Build a linear regression model
model = LinearRegression()
model.fit(X_train, y_train)

from sklearn.metrics import mean_squared_error

# Evaluate the model
y_pred = model.predict(X_test)
mse = mean_squared_error(y_test, y_pred)

# Load the new data into a Pandas DataFrame
new_data = pd.DataFrame({
    'CRIM': [0.1],
    'ZN': [0.2],
    'INDUS': [6.0],
    'CHAS': [0],
    'NOX': [0.4],
    'RM': [6.0],
    'AGE': [30.0],
    'DIS': [5.0],
    'RAD': [0.3],
    'TAX': [7.0],
    'PTRATIO': [0.2],
    'LSTAT': [10.0],
    'MEDV': [24],
    'CAT. MEDV': [0]
})

# Separate the target variable from the features
new_target = new_data['MEDV']
new_features = new_data.drop(['MEDV', 'CAT. MEDV'], axis=1)

# Use the model to make the prediction
prediction = model.predict(new_features)

print(prediction)




