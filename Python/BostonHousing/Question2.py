import pandas as pd

# Load the dataset from the Excel file
df = pd.read_excel('BostonHousing.xlsx', sheet_name='BostonHousing')

# Extract the necessary columns
X = df[['CRIM', 'CHAS', 'RM']]
y = df['MEDV']
from sklearn.model_selection import train_test_split

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=0)
from sklearn.linear_model import LinearRegression

# Fit the multiple linear regression model
model = LinearRegression()
model.fit(X_train, y_train)
# Get the coefficients and intercept of the model
coefficients = model.coef_
intercept = model.intercept_

print(coefficients)
print(intercept)

#Equation:
#MEDV = X*CRIM + Y*CHAS + Z*RM + Intercept
#with
#CRIM: per capita crime rate by town
#CHAS: Charles River dummy variable (= 1 if tract bounds river; 0 otherwise)
#RM: average number of rooms per dwelling
#Coefficients = [X Y Z]
#Intercept: 4.012
