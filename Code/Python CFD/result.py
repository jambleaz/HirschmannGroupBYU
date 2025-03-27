import numpy as np
import matplotlib.pyplot as plt

# Matrix sizes
sizes = [20, 40, 80, 160]

# Create a new figure for the result plot
plt.figure(figsize=(12, 8))

# Plot each result file on the same graph
for n in sizes:
    # Load the result data
    data = np.loadtxt(f'result_{n}.dat')
    x = data[:, 0]
    result = data[:, 1]

    # Plot the result with a label
    plt.plot(x, result, label=f'Result for n = {n}', marker='o')

# Add titles and labels
plt.title('Result Comparison for Different Matrix Sizes')
plt.xlabel('x')
plt.ylabel('Result')

# Add grid and legend
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.legend()

# Save the plot
plt.savefig('result_comparison.png')  # Save as PNG file

# Display the plot
plt.show()
