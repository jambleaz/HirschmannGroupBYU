import numpy as np
import matplotlib.pyplot as plt

# Matrix sizes
# sizes = [20, 40, 80, 160, 320]
sizes = 40
# dat_files = ['error_80_explicit4.dat','error_80_compact4.dat','error_80_kim4.dat']
# label_list = ['Explicit Scheme','Compact Scheme','Kim Optimized Scheme']
dat_files = ['error_40_explicit6.dat','error_40_compact6.dat','error_40_bv6.dat']
# dat_files = ['error_80_explicit6.dat','error_80_compact6.dat','error_80_bv6.dat','error_80_kim4.dat']
label_list = ['Explicit Scheme','Compact Scheme','Brady & Livescu (2018)']
# dat_files = ['kim4NOBC.dat','kim4YESBC.dat']
# label_list = ['No BC','Yes BC']


# Order parameter
O = 4.0  # You can set this to any value, here it's set to 2.0 for illustration

# Create a new figure for error plot
plt.figure(figsize=(12, 8))

# Plot each error file on the same graph (absolute error on log scale)
i = 0
while i < len(dat_files):
    # Load the error data
    data = np.loadtxt(dat_files[i])
    x = data[:, 0]
    error = data[:, 1]

    # Plot the error with a label
    plt.plot(x, np.abs(error), label=label_list[i], marker='o')
    i += 1

# Set log scale for the y-axis
plt.yscale('log')

# Add titles and labels
plt.title(f'Error Comparison for Different Order {O} Schemes with n = {sizes}')
plt.xlabel('x')
plt.ylabel('log(Error)')

# Add grid and legend
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.legend()

# Save the plot
plt.savefig('error_scheme_comparison.png')  # Save as PNG file

# Display the plot
plt.show()

# Create a new figure for the convergence test plot
plt.figure(figsize=(12, 8))
