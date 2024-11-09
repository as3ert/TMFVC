import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

# Own colors
color_cyan = '#D6F2FD'
color_red = '#FF5733'

# Define vertices of the tetrahedron
p = np.array([[1, 1, 1],
              [1, 3, 1],
              [1, 2, 3],
              [3, 2, 2]])

# Observer's position
o = np.array([-4, 0, 0])

# Create a new figure
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')

# Set limits for axes
ax.set_xlim([-5, 5])
ax.set_ylim([0, 5])
ax.set_zlim([0, 5])

# Create grid for the plane x=0
y = np.linspace(0, 5, 10)
z = np.linspace(0, 5, 10)
Y, Z = np.meshgrid(y, z)
X = np.zeros_like(Y)

# Plot the plane x=0
ax.plot_surface(X, Y, Z, facecolor='#D6F2FD', edgecolor='none', alpha=0.7)

# Plot the axes
ax.quiver(0, 0, 0, 5, 0, 0, color='black', arrow_length_ratio=0.1)
ax.quiver(0, 0, 0, 0, 5, 0, color='black', arrow_length_ratio=0.1)
ax.quiver(0, 0, 0, 0, 0, 5, color='black', arrow_length_ratio=0.1)

# Add labels to axes
ax.text(5, 0, 0, 'x', color='black', fontsize=12, verticalalignment='bottom', horizontalalignment='right')
ax.text(0, 5, 0, 'y', color='black', fontsize=12, verticalalignment='bottom', horizontalalignment='left')
ax.text(0, 0, 5, 'z', color='black', fontsize=12, verticalalignment='top', horizontalalignment='left')

def projection(p, o):
    x0 = abs(o[0])
    return [0, x0 * p[1] / (x0 + p[0]), x0 * p[2] / (x0 + p[0])]

p_proj = np.array([projection(pi, o) for pi in p])

# Plot the observer position
ax.scatter(*o, color='black', s=50)
ax.text(*o, 'Observer', color='black', fontsize=10, verticalalignment='bottom', horizontalalignment='right')

# Plot the original tetrahedron edges
edges = [(p[0], p[1]), (p[0], p[2]), (p[0], p[3]), (p[1], p[2]), (p[1], p[3]), (p[2], p[3])]
for edge in edges:
    ax.plot(*zip(*edge), color='blue', linewidth=1)

# Plot the projected tetrahedron edges
for edge in edges:
    ax.plot(*zip(*[projection(edge[0], o), projection(edge[1], o)]), color=color_red, linestyle='--', linewidth=1)

# Plot lines from observer to each vertex of the original tetrahedron
for vertex in p:
    ax.plot([o[0], vertex[0]], [o[1], vertex[1]], [o[2], vertex[2]], color='gray', linestyle=':', linewidth=1)

# Draw original and projected vertices with labels
for i, vertex in enumerate(p):
    ax.scatter(*vertex, color='blue', s=50)
    ax.text(*vertex, f'p{i+1}', color='blue', fontsize=10, verticalalignment='bottom', horizontalalignment='right')

for i, vertex_proj in enumerate(p_proj):
    ax.scatter(*vertex_proj, color=color_red, s=50)
    ax.text(*vertex_proj, f'p{i+1}\'', color=color_red, fontsize=10, verticalalignment='bottom', horizontalalignment='right')

# Set labels for axes
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# Set title
ax.set_title('One-Point Perspective Projection')

# Show plot
plt.show()