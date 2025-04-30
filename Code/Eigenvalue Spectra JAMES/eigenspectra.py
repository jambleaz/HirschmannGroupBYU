import numpy as np
import re
import sys
import matplotlib.pyplot as plt

from scipy.linalg import lu_factor, lu_solve, inv
from scipy.linalg.blas import dgemm



def parse_coefficients(file_path):
    coeff_dict = {}
    with open(file_path, 'r') as file:
        for line in file:
            match = re.match(r'(\w+)\s*=\s*(.*)', line)
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


def create_p_matrix(coeffs, matrix_size, alpha_value, beta_value):
    """Creates left hand side CFD matrix p.
    
    Keyword Arguments:
    coeffs      -- list of coefficients parsed from input file
    matrix_size -- number of points on grid
    alpha_value -- coeff value for first off diagonal
    beta_value  -- coeff value for second off diagonal
    """

    p = np.zeros((matrix_size, matrix_size))
    np.fill_diagonal(p, 1)  # Identity matrix

    for i in range(1, matrix_size - 1):
        p[i, i - 1] = alpha_value
        p[i, i + 1] = alpha_value
    for i in range(2, matrix_size - 2):
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



def create_q_matrix(coeffs, h, matrix_size, a1_value, a2_value, a3_value):
    """Creates right hand side CFD matrix q.
    
    Keyword Arguments:
    coeffs      -- list of coefficients parsed from input file
    h           -- grid spacing
    matrix_size -- number of points on grid
    a1_value    -- value of a1 coeff
    a2_value    -- value of a2 coeff
    a3_value    -- value of a3
    """

    q = np.zeros((matrix_size, matrix_size))
    middle_index = matrix_size // 2

    
    for i in range(matrix_size):
        for j in range(matrix_size):
            if i == j:
                # Main diagonal
                q[i, j] = 0.0
            elif i == j - 1:
                # Adjacent diagonals 
                q[i, j] = a1_value/2.0
            elif i == j + 1:
                # Adjacent diagonals 
                q[i, j] = -a1_value/2.0
            elif i == j - 2:
                # Super diagonals 
                q[i, j] = a2_value/4.0
            elif i == j + 2:
                # Super diagonals 
                q[i, j] = -a2_value/4.0
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
    q *= (1 / h)
    return q









coeff_files = ['shu_ccs_t6','tyler_p6','tyler_t4','bradliv_t6','kim24_t6']

def find_eigenvalue_spectra(file, matrix_size):
    coefficients, alpha_value, beta_value, a1_value, a2_value, a3_value = parse_coefficients(f"{file}.txt")
    # matrix_size = 92
    h = 1.0 / (matrix_size - 1)

    p_matrix = create_p_matrix(coefficients, matrix_size, alpha_value, beta_value)
    q_matrix = create_q_matrix(coefficients, h, matrix_size, a1_value, a2_value, a3_value)
    # print(p_matrix)
    # print(q_matrix)

    line1p = np.zeros(matrix_size)
    line1p[0] = 1
    line1q = np.zeros(matrix_size)

    p_new = p_matrix
    p_new[0] = line1p
    q_new = q_matrix
    q_new[0] = line1q

    # lu, piv = lu_factor(p_new)
    pinv_matrix = inv(p_new)

    R = dgemm(alpha=1.0, a=pinv_matrix, b=q_new)
    # R_new = R
    # print(R)
    # print(R_new)


    # eigenvalues, eigenvectors = np.linalg.eig(R)
    eigenvalues2, eigenvectors2 = np.linalg.eig(R)
    # print(eigenvalues)
    # print(eigenvalues2)


    real = -eigenvalues2.real
    imag = eigenvalues2.imag
        # print(real)
        # print(imag)

    re_max = max(real)
    print(f"Max Real for {file}: {re_max}")



    plt.figure(figsize=(6, 4))
    plt.scatter(real, imag, color='blue', marker='o')
    plt.axhline(0, color='gray', linestyle='--', linewidth=0.5)
    plt.axvline(0, color='gray', linestyle='--', linewidth=0.5)
    plt.xlabel("Real")
    plt.ylabel("Imag")
    plt.title(f"Eigenvalue Spectra for {file} with N={matrix_size}")
    plt.grid(True)
    # plt.show()
    plt.savefig(f"{file}.png")
    plt.clf()

for file in coeff_files:
    find_eigenvalue_spectra(file,82)



# coeff_files = ['shu_ccs_t6','tyler_p6','tyler_t4','bradliv_t6','kim24_t6']
# # 'tyler_p10'

# for file in coeff_files:
#     coefficients, alpha_value, beta_value, a1_value, a2_value, a3_value = parse_coefficients(f"{file}.txt")
#     matrix_size = 92
#     h = 1.0 / (matrix_size - 1)
#     # h = 1.0

#     p_matrix = create_p_matrix(coefficients, matrix_size, alpha_value, beta_value)
#     q_matrix = create_q_matrix(coefficients, h, matrix_size, a1_value, a2_value, a3_value)
#     p_matrix_new = p_matrix[1:,1:]
#     q_matrix_new = q_matrix[1:,1:]
#     # print(p_matrix)
#     # print(q_matrix)

#     lu, piv = lu_factor(p_matrix_new)
#     pinv_matrix_new = inv(p_matrix_new)

#     R_new = dgemm(alpha=1.0, a=pinv_matrix_new, b=q_matrix_new)
#     # print(R)
#     # print(R_new)


#     eigenvalues, eigenvectors = np.linalg.eig(R)
#     eigenvalues2, eigenvectors2 = np.linalg.eig(R_new)
#     # print(eigenvalues)
#     # print(eigenvalues2)


#     real = -eigenvalues2.real
#     imag = eigenvalues2.imag
#     # print(real)
#     # print(imag)

#     re_max = max(real)
#     print(f"Max Real for {file}: {re_max}")



#     plt.figure(figsize=(6, 4))
#     plt.scatter(real, imag, color='blue', marker='o')
#     plt.axhline(0, color='gray', linestyle='--', linewidth=0.5)
#     plt.axvline(0, color='gray', linestyle='--', linewidth=0.5)
#     plt.xlabel("Real")
#     plt.ylabel("Imag")
#     plt.title(f"Eigenvalue Spectra for {file} with N={matrix_size}")
#     plt.grid(True)
#     # plt.show()
#     plt.savefig(f"{file}.png")
#     plt.clf()
