import numpy as np
import matplotlib.pyplot as plt

# Matrix sizes
sizes = [20, 40, 80, 160, 320]

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
    if n == 320:
        normalization_factor = 1
    elif n == 160:
        normalization_factor = O**2
    elif n == 80:
        normalization_factor = O**4
    elif n == 40:
        normalization_factor = O**6
    elif n == 20:
        normalization_factor = O**8

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





# Plot the analytic vs. numerical functions visually

# Initialize lists to store x and y values from the .dat file
x_vals = []
y_vals_dat = []

# Read the .dat file
with open('result_320.dat', 'r') as file:
    for line in file:
        # Split each line into x and y values
        x, y = line.split()
        x_vals.append(float(x))
        y_vals_dat.append(float(y))

# Convert x_vals to a NumPy array to use for the analytic function
x_vals_np = np.array(x_vals)

# Define the analytic function (example: y = sin(x))
def analytic_function(x):
    return 2 * np.pi * np.cos(2 * np.pi * x)  # Replace this with your desired function

# def analytic_function(x):
#     cos_term = np.cos(2 * np.pi * x)               # cos(2 * pi * x)
#     cos_squared = cos_term ** 2                    # cos^2(2 * pi * x)
#     exp_term = np.exp(cos_squared)                 # exp(cos^2(2 * pi * x))
#     exp_cubed_root = exp_term ** (1.0 / 3)         # (exp(...))^(1/3)
#     cot_term = 1 / np.tan(exp_cubed_root)          # cot((exp(...))^(1/3))
#     sin_term = np.sin(2 * np.pi * x)               # sin(2 * pi * x)
#     return -(40.0 / 3.0) * exp_cubed_root * np.pi * cos_term * cot_term * sin_term  # Replace this with your desired function

# Compute y values using the analytic function
y_vals_analytic = analytic_function(x_vals_np)

# Plot the .dat file data
plt.plot(x_vals, y_vals_dat, marker='o', linestyle='-', color='b', label='Numerical Approximation')

# Plot the analytic function
plt.plot(x_vals_np, y_vals_analytic, linestyle='--', color='r', label='Analytic Function')

# Set y-axis limits
plt.ylim(-15, 15)  # Set this to your desired y-axis range

# Add labels, title, and legend
plt.xlabel('x')
plt.ylabel('y')
plt.title('Comparison of Numerical and Analytic Results')
plt.legend()

# Show grid
plt.grid(True)

# Display the plot
plt.show()
