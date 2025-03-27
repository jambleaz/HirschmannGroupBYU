import numpy as np
import time
import subprocess
from scipy.linalg import lu_factor, lu_solve, inv
from scipy.linalg.blas import dgemm
# Sizes for the matrices
sizes = [20,40,80,160,320]
timing_file = open("timing.dat", "w")

# Iterate over the different sizes
for n in sizes:
    # Call the script that generates the matrices for the current size
    subprocess.run(["python", "matrix.py", str(n)])  # Pass the size as an argument

    x_min = 0.0
    x_max = 1.0
    h = (x_max - x_min) / (n-1)

    # Measure the execution time
    start = time.time()

    # Load P and Q matrices from text files
    try:
        P = np.loadtxt(f"P_matrix_{n}.txt")  # Load the P matrix from file
        Q = np.loadtxt(f"Q_matrix_{n}.txt")  # Load the Q matrix from file
        #print the matrix:
        # print(f"P matrix for size {n}:\n{P}\n")
        # print(f"Q matrix for size {n}:\n{Q}\n")
         # Compute the LU decomposition of the matrix P
        lu, piv = lu_factor(P)

        # Compute the inverse of the matrix P
        Pinv = inv(P)


        # Perform the matrix operations
        P1 = np.linalg.inv(P)  # Invert the P matrix
        # Compute the product of the inverted matrix Pinv and matrix Q
        R = dgemm(alpha=1.0, a=Pinv, b=Q)

        # Define the input array x and encode sin(2*pi*x)
        x = np.linspace(x_min, x_max, n)
        w = 2.0 * np.pi
        f = np.sin(w * x)

        # Compute the product of the inverted matrix P1 and matrix Q
        result = np.dot(R, f)

        # Calculate the analytical solution and error
        analytical = 2 * np.pi * np.cos(w * x)
        # analytical = - 4 * (np.pi ** 2) * np.sin(w * x)
        # analytical = - 2 * np.sin(w * x)
        error = result - analytical

        # Save the results and errors to data files
        np.savetxt(f"result_{n}.dat", np.column_stack((x, result)))
        np.savetxt(f"error_{n}.dat", np.column_stack((x, error)))

    except np.linalg.LinAlgError as e:
        print(f"Matrix operation failed for size {n}: {e}")
        continue
    except IOError as e:
        print(f"Error loading matrix files for size {n}: {e}")
        continue

    # Measure the end time
    end = time.time()
    elapsed = end - start

    # Print and save the timing information
    print(f"Size {n} took {elapsed:.6f} seconds.")
    timing_file.write(f"Size {n} took {elapsed:.6f} seconds.\n")

timing_file.close()
