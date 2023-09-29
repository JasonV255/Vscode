import numpy as np
import matplotlib.pyplot as plt

# Define the function f(x) and its derivative f'(x)
def f(x):
    return 3 * x**3 - 2 * x - 7

def df(x):
    return 9 * x**2 - 2

# Implement Newton's method to find the root
def newton_method(f, df, x0, tol=0.001, max_iter=1000):
    x = x0
    iterations = 0
    while iterations < max_iter:
        x_new = x - f(x) / df(x)
        if abs(x_new - x) < tol:
            return x_new, iterations
        x = x_new
        iterations += 1
    return None, iterations

# Initial guess for Newton's method
x0 = 1.0

# Find the root using Newton's method
root, iterations = newton_method(f, df, x0)

if root is not None:
    print(f"Root found at x = {root} after {iterations} iterations.")
else:
    print("Newton's method did not converge.")

# Create a graph of the function and Newton's method iterations
x = np.linspace(-2, 2, 400)
y = f(x)
plt.plot(x, y, label='f(x) = 3x^3 - 2x - 7')
plt.axhline(0, color='black', linestyle='-')
plt.axvline(0, color='black', linestyle='-')
plt.scatter(root, 0, color='red', marker='o', label='Root')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.legend()

# Save the graph as a PNG file
plt.savefig('newton_method_graph.png', dpi=300)