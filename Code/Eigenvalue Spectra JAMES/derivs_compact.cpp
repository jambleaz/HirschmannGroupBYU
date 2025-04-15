#include "derivatives/derivs_compact.h"

#include <cstddef>
#include <stdexcept>

#include "refel.h"

namespace dendroderivs {

/**
 * @brief This routine builds a matrix for a FD scheme, given the diagonal
 *  and boundary terms. The matrix is stored column-by-column in a single array.
 *  Implemented fully with unsigned integer indices for maximum size possible.
 *
 * @param M       the c-style array to be written to, storing the matrix
 * @param diag    the interior portion of the FD scheme
 * @param bound   the boundary terms for the left side of the FD scheme
 *                (these will be repeated for the right side according to
 * parity)
 * @param parity  the sign by which to multiply @param bound by when mirroring
 * @param n       the number of grid points, aka the size of @param M
 */
void CompactDerivs::buildMatrix(double *M, std::vector<double> &diag,
                                std::vector<std::vector<double>> &bound,
                                double parity, unsigned int n) {
#ifdef DEBUG
    std::cout << "entering buildMatrix method" << std::endl;
#endif
    // build rows corresponding to left side boundary
    for (unsigned int i = 0; i < bound.size(); i++) {
        for (unsigned int j = 0; j < bound[i].size(); j++) {
            M[IDXN(i, j, n)] = bound[i][j];
        }
    }
#ifdef DEBUG
    std::cout << "just built left side boundary in buildMatrix" << std::endl;
#endif

    // build rows corresponding to interior
    unsigned int ku = (((unsigned int)diag.size()) - 1u) /
                      2u;  // number of diagonals below main
    for (unsigned int i = ((unsigned int)bound.size());
         i < n - ((unsigned int)bound.size()); i++) {
        // #ifdef DEBUG
        //         std::cout << "i: " << i << std::endl;
        // #endif
        for (unsigned int j = 0u; j < ((unsigned int)diag.size()); j++) {
            // #ifdef DEBUG
            //             std::cout << "ku: " << ku << " i: " << i << " j: " <<
            //             j << " diag.size() " << diag.size() << " bound.size()
            //             " << bound.size() << " n: " << n << " n^2: " << n*n
            //             << std::endl; std::cout << "IDXN(i, i - ku + j, n) "
            //             << IDXN(i, i - ku + j, n) << std::endl; std::cout <<
            //             "M[IDXN(i, i - ku + j, n)] " << M[IDXN(i, i - ku + j,
            //             n)] << std::endl; std::cout << "about to set M at
            //             this index" << std::endl; M[IDXN(i, i - ku + j, n)] =
            //             -1.0; std::cout << "I just set M at that index" <<
            //             std::endl; std::cout << "diag[j] " << diag[j] <<
            //             std::endl;
            //             // std::cout << "about to set diag at this index" <<
            //             std::endl;
            //             // diag[j] = -1.0;
            //             // std::cout << "I just set diag at that index" <<
            //             std::endl;
            // #endif
            M[IDXN(i, i - ku + j, n)] = diag[j];
            // #ifdef DEBUG
            //         std::cout << "go next iteration in j loop" << std::endl;
            // #endif
        }
        // #ifdef DEBUG
        //     std::cout << "go next iteration in i loop" << std::endl;
        // #endif
    }
#ifdef DEBUG
    std::cout << "just built interior in buildMatrix" << std::endl;
#endif
    // build rows corresponding to right side boundary
    // iterate rows in to out
    for (unsigned int boundRow = bound.size() - 1;
         boundRow != ((unsigned int)0) - 1; boundRow--) {
        unsigned int i            = n - 1 - boundRow;
        unsigned int numBoundCols = bound[boundRow].size();
        // iterate columns in to out
        for (unsigned int boundCol = numBoundCols - 1;
             boundCol != ((unsigned int)0) - 1; boundCol--) {
            unsigned int j   = n - 1 - boundCol;
            M[IDXN(i, j, n)] = parity * bound[boundRow][boundCol];
        }
    }
#ifdef DEBUG
    std::cout << "just built right boundary in buildMatrix" << std::endl;
#endif

#ifdef DEBUG
    std::cout << "exiting buildMatrix method" << std::endl;
#endif
}

// have to define this here so GCC creates the vtable.....
// see this answer https://stackoverflow.com/a/57504289
CompactDerivs::~CompactDerivs() {
#ifdef DEBUG
    std::cout << "in CompactDerivs deconstructor" << std::endl;
#endif
};

std::vector<double> createMatrix(
    const std::vector<std::vector<double>> &diag_boundary,
    const std::vector<std::vector<double>> &diag_boundary_btm,
    const std::vector<double> &diag_interior, const unsigned int n,
    const double parity, const unsigned int boundary_top,
    const unsigned int boundary_bottom) {
    // initialize the matrix, which needs to have top and bottom corners removed
    // depending

    if ((int)n - (int)boundary_top - (int)boundary_bottom <= 0) {
        throw std::invalid_argument(
            "Boundary top and bottom are causing matrix to be too small!");
    }

    const unsigned int n_fill = n - boundary_top - boundary_bottom;

    // TODO: quick checks to make sure we can fit everything in here
    if (!check_size_and_boundary_terms(diag_boundary, n_fill)) {
        throw std::runtime_error(
            "Error, there aren't enough spaces in the matrix to fit the "
            "boundaries! Either increase N or use a different scheme!");
    }
    if (!check_size_and_boundary_terms(diag_boundary_btm, n_fill)) {
        throw std::runtime_error(
            "Error, there aren't enough spaces in the matrix to fit the "
            "boundaries! Either increase N or use a different scheme!");
    }

    if (diag_boundary.size() * 2 >= n_fill) {
        throw std::runtime_error(
            "Error: Cannot fill any rows with interior points with this input "
            "size and scheme!");
    }

    if (diag_interior.size() > n_fill) {
        throw std::runtime_error(
            "Error: the number of points the diagonal terms wants isn't large "
            "enough!");
    }

    std::vector<double> outmat(n_fill * n_fill, 0.0);

    // boundaries
    const size_t last_row = diag_boundary.size() - 1;
    const size_t last_col = n_fill - 1;
    for (int row = 0; row <= last_row; row++) {
        size_t top_i         = row;
        size_t bottom_i      = last_col - row;
        const auto &curr_row = diag_boundary[row];
        size_t n_cols        = curr_row.size();

        for (int col = 0; col < n_cols; col++) {
            size_t top_j                       = col;
            size_t bottom_j                    = last_col - col;

            // top boundary
            outmat[IDXN(top_i, top_j, n_fill)] = curr_row[col];
        }
    }

    const size_t last_row_btm = diag_boundary_btm.size() - 1;
    const size_t last_col_btm = n_fill - 1;
    for (int row = 0; row <= last_row_btm; row++) {
        size_t bottom_i      = last_col - row;
        const auto &curr_row = diag_boundary_btm[row];
        size_t n_cols        = curr_row.size();

        for (int col = 0; col < n_cols; col++) {
            size_t bottom_j                          = last_col - col;

            // bottom boundary, it overwrites anything potential done by top
            outmat[IDXN(bottom_i, bottom_j, n_fill)] = parity * curr_row[col];
        }
    }

    // then we build the number of rows for interior
    size_t ku                = (diag_interior.size() - 1u) / 2u;
    size_t boundary_size     = diag_boundary.size();
    size_t boundary_size_btm = diag_boundary_btm.size();
    size_t interior_size     = diag_interior.size();

    for (size_t i = boundary_size; i < n_fill - boundary_size_btm; i++) {
        for (size_t j = 0; j < interior_size; j++) {
            size_t col                   = i - ku + j;

            // the index we want to work with is i - ku + j
            outmat[IDXN(i, col, n_fill)] = diag_interior[j];
        }
    }

    // if there was no boundary to worrry about, we just return
    if (boundary_top + boundary_bottom == 0) return outmat;

    // otherwise we need our "true" matrix
    std::vector<double> true_mat(n * n, 0.0);

    for (int i = 0; i < n_fill; ++i) {
        for (int j = 0; j < n_fill; ++j) {
            true_mat[IDXN(i + boundary_top, j + boundary_top, n)] =
                outmat[IDXN(i, j, n_fill)];
        }
    }

    for (int i = 0; i < boundary_top; ++i) {
        true_mat[IDXN(i, i, n)] = 1.0;
    }

    for (int i = 0; i < boundary_bottom; ++i) {
        true_mat[IDXN(n - i - 1, n - i - 1, n)] = 1.0;
    }

    return true_mat;
}

std::vector<double> create_P_from_diagonals(
    const MatrixDiagonalEntries &matrixDiagonals, const unsigned int n,
    const double parity, const unsigned int boundary_top,
    const unsigned int boundary_bottom) {
    return createMatrix(matrixDiagonals.PDiagBoundary,
                        matrixDiagonals.PDiagBoundaryLower,
                        matrixDiagonals.PDiagInterior, n, parity, boundary_top,
                        boundary_bottom);
}

std::vector<double> create_Q_from_diagonals(
    const MatrixDiagonalEntries &matrixDiagonals, const unsigned int n,
    const double parity, const unsigned int boundary_top,
    const unsigned int boundary_bottom) {
    return createMatrix(matrixDiagonals.QDiagBoundary,
                        matrixDiagonals.QDiagBoundaryLower,
                        matrixDiagonals.QDiagInterior, n, parity, boundary_top,
                        boundary_bottom);
}

}  // namespace dendroderivs
