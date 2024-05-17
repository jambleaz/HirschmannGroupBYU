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
