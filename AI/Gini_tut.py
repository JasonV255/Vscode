import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df = pd.read_csv('./Data/iris.csv')
df = df.dropna()
print(df)

def gini_index (y):
    n= y.sum()
    p_sum = 0
    for key in y.keys():
        p_sum = p_sum  +  (y[key] / n ) * (y[key] / n ) 
    gini = 1 - p_sum
    return gini

class_value_counts = df['variety'].value_counts()
print(f'Number of samples in each class is:\n{class_value_counts}')

gini_class = gini_index(class_value_counts)
print(f'\nGini Impurity of the class is {gini_class:.3f}')

def gini_split(feat_name):
    feat_values= df[feat_name].value_counts()
    gini_A=0
    for key in feat_values.keys():
        df_k = df['variety'][df[feat_name]==key].value_counts()
        n_k = feat_values[key]
        n = df.shape[0]
        gini_A = gini_A + ((n_k/n)*gini_index(df_k))
    return gini_A

gini_feature = {}
feat_names =  ["sepal.length","sepal.width","petal.length","petal.width"]
for key in feat_names:
    gini_feature[key] = gini_split(key)
    print(f'Gini for {key} is {gini_feature[key]:.3f}')

min_value = min(gini_feature.values())
print('The minimum value of Gini Impurity : {0:.3} '.format(min_value))
print('The maximum value of Gini Gain     : {0:.3} '.format(1-min_value))
selected_attribute = min(gini_feature.keys())
print('The selected attiribute is: ', selected_attribute)

class Node:
    def __init__(self, gini, num_samples, num_samples_per_class, predicted_class):
        self.gini = gini
        self.num_samples = num_samples
        self.num_samples_per_class = num_samples_per_class
        self.predicted_class = predicted_class
        self.feature_index = 0
        self.threshold = 0
        self.left = None
        self.right = None

def build_tree(X, y, depth=0):
    num_samples_per_class = [np.sum(y == i) for i in range(n_classes)]
    predicted_class = np.argmax(num_samples_per_class)
    node = Node(
        gini=gini(y),
        num_samples=y.size,
        num_samples_per_class=num_samples_per_class,
        predicted_class=predicted_class,
    )

    if depth < max_depth:
        idx, thr = best_split(X, y)
        if idx is not None:
            indices_left = X[:, idx] < thr
            X_left, y_left = X[indices_left], y[indices_left]
            X_right, y_right = X[~indices_left], y[~indices_left]
            node.feature_index = idx
            node.threshold = thr
            node.left = build_tree(X_left, y_left, depth + 1)
            node.right = build_tree(X_right, y_right, depth + 1)
    return node

def predict(node, x_test):
    if node.left is None and node.right is None:
        return node.predicted_class
    else:
        if x_test[node.feature_index] < node.threshold:
            return predict(node.left, x_test)
        else:
            return predict(node.right, x_test)

# Convert dataframe to numpy arrays and run the code
X = df.drop(columns='variety').to_numpy()
y = df['variety'].to_numpy()
tree = build_tree(X, y)

# Make predictions on the same dataset (just for demonstration purposes)
predictions = [predict(tree, x) for x in X]
print("Predictions:", predictions)
