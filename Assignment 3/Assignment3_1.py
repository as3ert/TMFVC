import matplotlib.pyplot as plt
import numpy as np
import sympy as sp

# Define the function f(x, y) = x^6 + y^6 - 3x^2 - 3y^2
def f(x, y):
    return np.power(x, 6) + np.power(y, 6) - 3 * np.power(x, 2) - 3 * np.power(y, 2)

# Define the local minima, local maxima, and saddle points
local_minima = [(1, 1), (1, -1), (-1, 1), (-1, -1)]
local_maxima = [(0, 0)]
saddle_points = [(0, 1), (0, -1), (1, 0), (-1, 0)]

# Define the legend elements
legend_elements = [
    plt.Line2D([0], [0], marker='o', color='w', markerfacecolor='green', markersize=10, label='Local Minima'),
    plt.Line2D([0], [0], marker='o', color='w', markerfacecolor='blue', markersize=10, label='Local Maxima'),
    plt.Line2D([0], [0], marker='o', color='w', markerfacecolor='red', markersize=10, label='Saddle Point')
]

# Make data
X = np.arange(-2, 2, 0.01)
Y = np.arange(-2, 2, 0.01)
X, Y = np.meshgrid(X, Y)
Z = f(X, Y)

# Create a figure
fig = plt.figure(figsize=(14, 6))

# Plot the surface
ax1 = fig.add_subplot(121, projection='3d')
ax1.plot_surface(X, Y, Z, cmap='viridis', alpha=0.8)
ax1.set_title('Surface plot of $f(x,y) = x^6 + y^6 - 3x^2 - 3y^2$')
ax1.set_xlabel('$x$')
ax1.set_ylabel('$y$')
ax1.set_zlabel('$f(x,y)$')
ax1.legend(handles=legend_elements)

# Add critical points to the 3D plot
for x_val, y_val in local_minima:
    ax1.scatter(x_val, y_val, f(x_val, y_val), color='green', s=50, label='Local Minima')
for x_val, y_val in local_maxima:
    ax1.scatter(x_val, y_val, f(x_val, y_val), color='blue', s=50, label='Local Maxima')
for x_val, y_val in saddle_points:
    ax1.scatter(x_val, y_val, f(x_val, y_val), color='red', s=50, label='Saddle Point')

X = np.arange(-1.5, 1.5, 0.01)
Y = np.arange(-1.5, 1.5, 0.01)
X, Y = np.meshgrid(X, Y)
Z = f(X, Y)

# Plot the contour
ax2 = fig.add_subplot(122)
contour = ax2.contour(X, Y, Z, levels=50, cmap='nipy_spectral')
ax2.set_title('Contour plot of $f(x,y) = x^6 + y^6 - 3x^2 - 3y^2$')
ax2.set_xlabel('$x$')
ax2.set_ylabel('$y$')
ax2.set_aspect('equal', 'box')
ax2.legend(handles=legend_elements)
fig.colorbar(contour, ax=ax2, orientation='vertical', shrink=0.9)

# Add critical points to the 2D contour plot
for x_val, y_val in local_minima:
    ax2.scatter(x_val, y_val, color='green', s=50, label='Local Minima')
for x_val, y_val in local_maxima:
    ax2.scatter(x_val, y_val, color='blue', s=50, label='Local Maxima')
for x_val, y_val in saddle_points:
    ax2.scatter(x_val, y_val, color='red', s=50, label='Saddle Point')

plt.tight_layout()
plt.show()