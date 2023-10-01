import numpy as np
import pandas as pd
from matplotlib import pyplot as plt



#iris_df = pd.read_csv('D:\\CB\\AI\\iris.csv')

# Define column names
column_names = ['sepal_length', 'sepal_width', 'petal_length', 'petal_width', 'variety']

# Read the CSV file into a pandas DataFrame
iris_df = pd.read_csv('D:\\CB\\AI\\iris.csv', names=column_names)

# Display the first few rows of the dataset to verify it was loaded correctly
print(iris_df.head())

# Visualize the data (scatter plot)
plt.figure(figsize=(10, 6))

# Create separate DataFrames for each variety
setosa_df = iris_df[iris_df['variety'] == 'Iris-setosa']
versicolor_df = iris_df[iris_df['variety'] == 'Iris-versicolor']
virginica_df = iris_df[iris_df['variety'] == 'Iris-virginica']

# Plot sepal length vs. sepal width
plt.plot(setosa_df['sepal_length'], setosa_df['sepal_width'], label='Setosa', marker='.')
plt.plot(versicolor_df['sepal_length'], versicolor_df['sepal_width'], label='Versicolor', marker='s')
plt.plot(virginica_df['sepal_length'], virginica_df['sepal_width'], label='Virginica', marker='^')

# Add labels and a legend
plt.xlabel('Sepal Length (cm)')
plt.ylabel('Sepal Width (cm)')
plt.legend(loc='best')
plt.title('Sepal Length vs. Sepal Width')

# Show the plot
#plt.show()
plt.savefig('petal.png', dpi=300)