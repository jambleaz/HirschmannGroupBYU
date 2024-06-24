import numpy as np
import matplotlib.pyplot as plt

# Matrix sizes
sizes = [20, 40, 80, 160]

# Order parameter
O = 4.0  # You can set this to any value, here it's set to 2.0 for illustration

# Create a new figure for error plot
plt.figure(figsize=(12, 8))

# Plot each error file on the same graph (absolute error on log scale)
for n in sizes:
    # Load the error data
    data = np.loadtxt(f'error_{n}.dat')
    x = data[:, 0]
    error = data[:, 1]

    # Plot the error with a label
    plt.plot(x, np.abs(error), label=f'Error for n = {n}', marker='o')

# Set log scale for the y-axis
plt.yscale('log')

# Add titles and labels
plt.title('Error Comparison for Different Matrix Sizes')
plt.xlabel('x')
plt.ylabel('Error (log scale)')

# Add grid and legend
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.legend()

# Save the plot
plt.savefig('error_comparison_log_scale.png')  # Save as PNG file

# Display the plot
plt.show()

# Create a new figure for the convergence test plot
plt.figure(figsize=(12, 8))

# Plot normalized errors (convergence test) on the same graph
for n in sizes:
    # Load the error data
    data = np.loadtxt(f'error_{n}.dat')
    x = data[:, 0]
    error = data[:, 1]

    # Determine the normalization factor based on the size
    if n == 160:
        normalization_factor = 1
    elif n == 80:
        normalization_factor = O**2
    elif n == 40:
        normalization_factor = O**4
    elif n == 20:
        normalization_factor = O**6

    # Normalize the errors
    normalized_error = np.abs(error) / normalization_factor

    # Plot the normalized error with a label
    plt.plot(x, normalized_error, label=f'Normalized Error for n = {n}', marker='o')

# Set log scale for the y-axis
plt.yscale('log')

# Add titles and labels
plt.title('Convergence Test for Different Matrix Sizes')
plt.xlabel('x')
plt.ylabel(f'Normalized Error (log scale) with O = {O}')

# Add grid and legend
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.legend()

# Save the plot
plt.savefig('convergence_test_log_scale.png')  # Save as PNG file

# Display the plot
plt.show()

# Read and print timing information
with open('timing.dat') as f:
    print(f.read())
