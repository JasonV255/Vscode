import pandas as pd
import matplotlib.pyplot as plt

# Step 1: Load the iris.csv file into a Pandas DataFrame
iris_df = pd.read_csv('iris.csv')

# a) Plot the relations of the dimensions of Setosa's sepal
setosa_df = iris_df[iris_df['variety'] == 'Setosa']
plt.scatter(setosa_df['sepal_length'], setosa_df['sepal_width'])
plt.xlabel('Sepal Length (cm)')
plt.ylabel('Sepal Width (cm)')
plt.title('Setosa Sepal Dimensions')
plt.show()

# b) Plot the relations of the dimensions of Versicolor's petal
versicolor_df = iris_df[iris_df['variety'] == 'Versicolor']
plt.scatter(versicolor_df['petal_length'], versicolor_df['petal_width'])
plt.xlabel('Petal Length (cm)')
plt.ylabel('Petal Width (cm)')
plt.title('Versicolor Petal Dimensions')
plt.show()

# c) Save the information of the lengths and widths of Versicolor into a versicolor.csv file
versicolor_df[['petal_length', 'petal_width']].to_csv('versicolor.csv', index=False)
