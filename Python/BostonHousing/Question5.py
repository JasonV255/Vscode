import pandas as pd

# Load the dataset from the Excel file
df = pd.read_excel('BostonHousing.xlsx', sheet_name='BostonHousing')

# Compute the correlation matrix
corr_matrix = df.corr()

# Print the correlation matrix
print(corr_matrix)