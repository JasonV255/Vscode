import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler

# Load the wine dataset
df = pd.read_csv('./Data/wine.csv')

# Assume the first column is the target and the rest are features
X = df.iloc[:, 1:].values
y = df.iloc[:, 0].values

# Standardize the features to have mean=0 and variance=1
sc = StandardScaler()
X = sc.fit_transform(X)

# Compute the covariance matrix
cov_matrix = np.cov(X.T)

# Compute the eigenvalues and eigenvectors of the covariance matrix
eigenvalues, eigenvectors = np.linalg.eig(cov_matrix)

# Sort the eigenvalues and corresponding eigenvectors in decreasing order
idx = np.argsort(eigenvalues)[::-1]
eigenvalues = eigenvalues[idx]
eigenvectors = eigenvectors[:, idx]

# Take the first 2 principal components
n_components = 2
eigenvectors = eigenvectors[:, :n_components]

# Transform the data
X_pca = np.dot(X, eigenvectors)

print('Explained variation per principal component: {}'.format(eigenvalues[:n_components]/np.sum(eigenvalues)))

# Create a scatter plot of the transformed data
plt.figure(figsize=(8, 6))
plt.scatter(X_pca[:, 0], X_pca[:, 1], c=y)
plt.xlabel('First Principal Component')
plt.ylabel('Second Principal Component')
plt.title('PCA Scatter Plot')
plt.show()
