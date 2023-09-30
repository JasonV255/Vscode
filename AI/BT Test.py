import numpy as np
import pandas as pd
import matplotlib.pyplot as plt



iris_df = pd.read_csv('D:\\CB\\AI\\iris.csv')

setosa_df = iris_df[iris_df['variety'] == 'Iris-setosa']


plt.scatter(setosa_df['sepal_length'], setosa_df['sepal_width'])
plt.title('Sepal Dimensions of Iris-setosa')
plt.xlabel('Sepal Length (cm)')
plt.ylabel('Sepal Width (cm)')
plt.grid(True)
plt.show()