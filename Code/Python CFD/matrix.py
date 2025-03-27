import numpy as np
import re
import sys

# Function to parse coefficients from the text file
def parse_coefficients(file_path):
    coeff_dict = {}
    with open(file_path, 'r') as file:
        for line in file:
            match = re.match(r'double\s+(\w+)\s*=\s*(.*);', line)
            if match:
                var_name = match.group(1)
                expr = match.group(2)
                try:
                    coeff_dict[var_name] = eval(expr)
                except Exception as e:
                    print(f"Error evaluating expression {expr}: {e}")

    alpha_value = coeff_dict.get('alpha', 0)
    beta_value = coeff_dict.get('beta', 0)
    a1_value = coeff_dict.get('a1', 0)
    a2_value = coeff_dict.get('a2', 0)
    a3_value = coeff_dict.get('a3', 0)
    return coeff_dict, alpha_value, beta_value, a1_value, a2_value, a3_value

# Function to create the P matrix
def create_p_matrix(coeffs, matrix_size, alpha_value, beta_value):
    p = np.zeros((matrix_size, matrix_size))
    np.fill_diagonal(p, 1)  # Identity matrix

    for i in range(1, matrix_size - 1):
        p[i, i - 1] = alpha_value
        p[i, i + 1] = alpha_value
    for i in range(2, matrix_size - 2):  # Adjusting to ensure valid index
        p[i, i - 2] = beta_value
        p[i, i + 2] = beta_value

    for key, value in coeffs.items():
        match = re.match(r'gamma(\d)(\d)', key)
        if match:
            row, col = int(match.group(1)), int(match.group(2))
            if row < matrix_size and col < matrix_size:
                p[row, col] = value
                p[matrix_size - 1 - row, matrix_size - 1 - col] = value

    return p

# Function to create the Q matrix
def create_q_matrix(coeffs, h, matrix_size, a1_value, a2_value, a3_value):
    q = np.zeros((matrix_size, matrix_size))
    middle_index = matrix_size // 2

    
    for i in range(matrix_size):
        for j in range(matrix_size):
            if i == j:
                # Main diagonal
                q[i, j] = 0.0
                # q[i,j] = -2 * ( (a1_value / 1.0) + (a2_value / 4.0) )
            elif i == j - 1:
                # Adjacent diagonals 
                q[i, j] = a1_value/2.0
                # q[i, j] = a1_value / (1.0 * (h ** 0))
            elif i == j + 1:
                # Adjacent diagonals 
                q[i, j] = -a1_value/2.0
                # q[i, j] = -a1_value / (1.0 * (h ** 0))
            elif i == j - 2:
                # Super diagonals 
                q[i, j] = a2_value/4.0
                # q[i, j] = a2_value / (4.0 * (h ** 0))
            elif i == j + 2:
                # Super diagonals 
                q[i, j] = -a2_value/4.0
                # q[i, j] = -a2_value / (4.0 * (h ** 0))
            elif i == j - 3:
                # Super +1 diagonals 
                q[i, j] = a3_value/6.0
            elif i == j + 3:
                # Super +1 diagonals 
                q[i, j] = -a3_value/6.0

    for key, value in coeffs.items():
        match = re.match(r'a(\d)(\d)', key)
        if match:
            row, col = int(match.group(1)), int(match.group(2))
            if row < matrix_size and col < matrix_size:
                q[row, col] = value
                q[matrix_size - 1 - row, matrix_size - 1 - col] = -value
    q *= (1 / (h) )
    # q *= (1 / (h ** 2) )
    return q

if __name__ == "__main__":
    # coeff_file = 'coefficients_explicit4.txt'
    # coeff_file = 'coefficients_compact4.txt'
    # coeff_file = 'coefficients_kim24.txt'
    # coeff_file = 'coefficients_kim24nbc.txt'
    coeff_file = 'kim9_coeffs.txt'
    # coeff_file = 'coefficients_explicit6.txt'
    # coeff_file = 'coefficients_compact6.txt'
    # coeff_file = 'bv_coeffs.txt'
    # coeff_file = 'coefficients_interioronly.txt'
    # coeff_file = 'coefficients_compact8.txt'
    # coeff_file = '2der_tri4.txt'
    # coeff_file = '2der_tri6.txt'
    # coeff_file = 'coeff_usp10.txt'
    # coeff_file = 'coeff_tylerp10.txt'
    coefficients, alpha_value, beta_value, a1_value, a2_value, a3_value = parse_coefficients(coeff_file)

    # Get matrix size from command-line arguments
    if len(sys.argv) != 2:
        print("Usage: python matrix.py <matrix_size>")
        sys.exit(1)

    matrix_size = int(sys.argv[1])
    h = 1.0 / (matrix_size - 1)

    # Create matrices P and Q
    p_matrix = create_p_matrix(coefficients, matrix_size, alpha_value, beta_value)
    q_matrix = create_q_matrix(coefficients, h, matrix_size, a1_value, a2_value, a3_value)
    print(p_matrix)
    print(q_matrix)

    # Save matrices to text files
    np.savetxt(f"P_matrix_{matrix_size}.txt", p_matrix)
    np.savetxt(f"Q_matrix_{matrix_size}.txt", q_matrix)

    print(f"Matrices P and Q saved for size {matrix_size}.")
