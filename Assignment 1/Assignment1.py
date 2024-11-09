import matplotlib.pyplot as plt
import numpy as np

# Store the three vertices of the trianngle
A = np.array([0, 0])
B = np.array([3, 1])
C = np.array([4, 2])

# Store the vertices in a matrix
vertices = np.array([A, B, C])

# Apply scaling transformation on the triangle
def scale(vertices, factor):
    scaling_matrix = np.array([[factor, 0], 
                               [0, factor]])
    scaled_vertices = np.dot(vertices, scaling_matrix)

    return scaled_vertices

# Apply rotation transformation on the triangle
def rotate(vertices, angle):
    rotation_matrix = np.array([[np.cos(angle), -np.sin(angle)], 
                                [np.sin(angle), np.cos(angle)]])
    rotated_vertices = np.dot(vertices, rotation_matrix)

    return rotated_vertices

# Scale the triangle by a factor of 2
scaled_vertices = scale(vertices, 2)

# Rotate the triangle by 45 degrees
rotated_vertices = rotate(vertices, np.pi/4)

# Plot the original triangle
plt.plot(np.append(vertices[:, 0], vertices[0, 0]), 
         np.append(vertices[:, 1], vertices[0, 1]), 'r', linewidth=2.5)

# Plot the scaled triangle
plt.plot(np.append(scaled_vertices[:, 0], scaled_vertices[0, 0]), 
         np.append(scaled_vertices[:, 1], scaled_vertices[0, 1]), 'g')

# Plot the rotated triangle
plt.plot(np.append(rotated_vertices[:, 0], rotated_vertices[0, 0]), 
         np.append(rotated_vertices[:, 1], rotated_vertices[0, 1]), 'b')

plt.show()