# Meetings with Dr.Hirschmann

## 4/30/2024
Today we started working on learning from numex.jl. Take 1D wave equation and modify it to learn how the solve works. Then move on to bigger crazier things.

Items worked on today:
 * numex.jl - 1D Wave equation
 * Github repository created for students that work with Dr. Hirschmann


## 5/2/2024
Today, we explored how the boundary conditions of the 1D wave equation are coded in the Numex wave equation solver, and we talked about how to modify the code to test different boundary conditions. The mesh points in the "middle" of the grid are coded with a 2nd order scheme, while the mesh points on the boundaries of the grid are coded with a 1st order scheme (the scheme is relying on a point to the left and right, and on the boundaries, one of those doesn't exist). We clarified some confusion about how to translate the 1D wave equation into a system of equations if we add additional terms to the RHS (with more unknowns, more equations are needed in the system). The Numex code is using a 2nd-order Runge-Kutta (rk2) method, and the 4th-order Runge-Kutta (rk4) method is commonly used and pretty accurate, so we should learn more about how that method is used.

Items worked on today:
 * Coding boundary conditions
 * Translating 2nd-order DEs into systems of 1st-order DEs
 * Runge-Kutta methods (rk2 and rk4)


## 5/7/2024
Today, we first talked about some more boundary conditions to try to code up in the Numex 1D wave equation solver. We want to look at Dirichlet (reflecting), periodic, Neumann, Robin, and outgoing boundary conditions with the linear wave equation, and we want to see what happens with stability when applying different boundary conditions to nonlinear wave equations. The original Numex solver is using finite difference approximations (FDAs) that are 2nd order in t and x. We want to try adjusting the code to use an FDA that is 4th order in x but still 2nd order in t, then we want to adjust it to use the rk4 scheme (4th order in t) but still 2nd order in x, and then we want to combine the two approaches to have 4th order in t and x.

The discussion on using difference FDA stencils led to a discussion on compact finite difference approximations (CFDAs). With normal FDAs, if you have a stencil that uses 3 points, then the order of accuracy is $O(h^2)$. You can obtain higher accuracy, such as $O(h^4)$ by using more points (5 in that case), but that is more costly and can cause problems around boundaries. CFDAs seek to obtain higher-order accuracy using the same number of points in the stencil. The major cost that is introduced is matrix inversion, but there are some unique things about the matrices involved (Toeplitz matrices).

We worked with a particular scheme, using Taylor expansions to find unknown coefficients in our discretized equation. We did a review of Fourier/Neumann stability analysis (semi-discretizing a function, taking the Fourier and inverse Fourier transforms, seeing if the end result is stable) for a simple case, and then we did a similar analysis using the chosen CFDA scheme. It was much more complicated, but it is possible to show for the first few specific cases that the scheme is stable. One future goal/project is to develop Mathematica scripting tools to solve and test the stability of different CFDA schemes, with an end goal of finding a stable analytic solution with error $O(h^6)$.

Items worked on today:
 * Different boundary conditions to test with 1D wave equation
 * Different FDA stencils to test with 1D wave equation
 * Future plans of coding 2D wave equation or Maxwell's equations
 * Idea behind cost/benefit tradeoff using compact finite differences
 * Review of proving stability for a scheme using simple wave equation
 * Pseudo-proof of stability for the basic CFDA scheme


## 5/14/2024
Today, we worked on trying to figure out how to implement the boundary conditions in the Numex code for a while, which is surprisingly different for a system of first-order equations than for a single second-order equation. We were finally able to figure out how to include Dirichlet, Neumann, and periodic boundary conditions in the code, and we suspect that the original implemented boundary conditions were Sommerfeld conditions.

We discussed our Mathematica module that takes as an input a discretized scheme and outputs the function after a Fourier transform to see if it is a stable scheme (related to dispersion), and we also discussed a function we have to compute the entries of the $C_{ij}$ matrix for the tridiagonal matrix CFDA scheme. If the eigenvalues of this matrix are all positive (the matrix is positive definite), then the scheme is stable, so this code is helpful. We are going to start looking at doing the same thing for the pentadiagonal matrix.

Items worked on today:
 * Coding boundary conditions
 * Mathematica Fourier analysis module
 * Find entries for the $C_{ij}$ matrix for the CFDA scheme


## 5/21/2024
Today, we walked through solving the 1D Wave equation (system) using the method of characteristics rather than the method of separation of variables. Now having an analytic solution to the Wave equation (system), we are able to plot the analytic and numeric solutions together, as well as subtract or take the L2 norm to find the error of our numeric solutions.

We spent some time talking about the determinants of pentadiagonal matrices, and our Mathematica code to compute the determinant using the analytic expression and compare it with the determinant found using the built-in function was showing that the determinant had an imaginary component, so it seems that there was either some serious roundoff error or the previously found analytic expression had some small errors. We were able to find another expression that matches the built-in determinant function exactly, so we just need to compare it to find where the error in the first analytic solution was.

Items worked on today:
 * Analytic solutions with the method of characteristics
 * Pentadiagonal matrix determinants


## 5/28/2024
Today, we talked about strategies to find the cofactor matrix recurrence relation for the pentadiagonal matrix. We found a relation for entries along the main diagonal, and our next goals are to find them for outgoing superdiagonals until we can find a pattern that works for all entries in the cofactor matrix. Once we are able to find this, we can use the cofactor matrix, along with the determinant, to find the analytic inverse.

We also talked about a stencil for the tridiagonal CFD scheme that differs on the boundaries (left-shifted or right-shifted, depending on the corresponding boundary). Dr. Hirschmann found an analytic determinant for that matrix, and he is now working on finding the cofactor matrix for that version of the tridiagonal matrix.

Items worked on today:
 * Cofactor matrix for purely pentadiagonal system
 * Inversion of tridiagonal system with shifted boundaries


## 6/4/2024
Today, we talked with Dr. Hirschmann about our progress on the cofactors for the pentadiagonal matrix. We are a little bit stumped, so we are going to shift gears and work on inverses for the tridiagonal matrix with some different (Dirichlet) boundary conditions. We got access to the GR Google Drive folder that has many helpful and relevant papers, so we are going to be able to read through some of those now.

Items worked on today:
 * Determinants and cofactors (for inversion) of tridiagonal matrices with Dirichlet boundary conditions


## 6/11/2024
Today, we showed Dr. Hirschmann our progress with reparameterizing the determinants for the different tridiagonal matrices and finding the cofactor matrices. We talked about the different cases for the cofactor matrices and some possibilities for bounding them or simplifying the cases. We briefly talked about our progress in creating a Mathematica module that allows us to solve a system of equations to solve a boundary scheme for the variable parameters for any desired order of accuracy.

Items worked on today:
 * Showed progress on boundary tridiagonal determinant reparameterization
 * Showed progress on boundary tridiagonal cofactor matrices
 * Showed progress on boundary tridiagonal system of equations coefficient solver

To-do items:
 * Write formulas for the inverse of boundary tridiagonal matrices
 * Test the inverse formula for large enough matrices ($k>20$) in Mathematica
 * Compare the accuracy of our analytic formula with Mathematica's solution
 * Get set up to use numerical linear algebra solvers (LAPACK)
 * Compare the timing of our analytic formula with numerical solvers (the goal is to get $O(k)$ accuracy, rather than $O(k^2)$ accuracy)


## 6/18/2024
Today, we showed Dr. Hirschmann the inverses that we had coded up in Mathematica. We are going to work on writing out the inverses with all cases in the reparameterized forms. We talked about possible approaches to solving for the matrix $C=A^{-1}B$ in the CFD schemes. We still want to look at stability with a Fourier-like stability approach, or, seeing if the matrix $C$ is positive-definite. Dr. Hirschmann is thinking of a perturbation approach where we express $A^{-1}$ as a combination of the purely tridiagonal inverse and a perturbative term. The idea is that the new factors on the boundary have a limited impact on the inverse.

Items worked on today:
 * Showed progress on boundary tridiagonal inverses
 * Talked about timing tests for the matrix inversion
 * Stability analysis approaches for the matrix $C$

To-do items:
 * Write inverses in analytic, reparameterized form
 * Perform timing tests in C++ code
 * Work on finding the matrix $C$ and testing to see if it's positive-definite


## 6/25/2024 - 8/6/2024
Undocumented meetings.


## 8/13/2024
Today, we met with Dr. Hirschmann and Dr. Neilsen to discuss Kim's latest paper and his technique of extrapolating a polynomial on the boundary of a CFD scheme to determine coefficients that lead to better stability and accuracy on the boundaries. We got a little stuck when trying to catalogue all of the equations that form a system to solve for the coefficients, but we are going to keep exploring this technique in the future.

Items worked on today:
 * Talked about extrapolation polynomial in Kim's paper

To-do items:
 * Read Kim's latest paper and his previous one that is frequently referenced


## ?/??/2024
