# How to use CFD Wave and Advection Evolution codes

## CFD Convergence Testing

_This code is for testing first derivative operators on the advection equation._

**How to use:**
1. Run the clear block
2. Run everything in Essential Modules and Initializations
- Defining Coefficients will save all of the coefficients that you want to use later in the code. If you want to add new coefficients, do so here.
- Filter Coefficients is the same but for filtering schemes.
- LHS and RHS Matrix Modules define the modules for how to set up the matrices. If you want to alter the way that the schemes are generated, do so here.
- Advection Equation Setup defines the wave speed and $\Delta t$ for time stepping.
3. Select the operator, initial and boundary conditions
- Pick one of the "Setting Up The Operators" block to run. 
- Dirichlet means that the left side of the solution will be exhibit a homogeneous Dirichlet condition. The DirichletBoundary module changes the matrix to replace the corresponding rows and columns to make that boundary. Params: (Matrix, is LHS, Boundary on Left side, Boundary on Right Side)
- Note that the Dirichlet boundary will sometimes blow up on the left side. If it does, you can change the time-stepping ($Delta t$ or choose a higher order time integrator like RK4).
- Periodic schemes only utilize the interior coefficients of the operator, so it will be very good for testing convergence there.
4. Run the operator by choosing either Euler, Crank-Nicholson, or RK4. Euler is fastest but will occasionally run into error with higher resolutions.
- To change the amount of time steps, just alter the condition in the for loop:
	`i < 10 / \[Delta]t` will be enough time steps for "10 seconds" of the solution to propagate.
	`i < 100` will simply run 100 time steps.
5. Plotting Results
- Automatically shows the animated graphs and the convergence of the scheme.

## Wave Equation CFD

_This code is for testing first and second derivative operators on the 1D Wave Equation._

**How to use:**
1. Run the Clear Block
2. Run everything in Essential Modules and Initializations
- Same rules as CFD Convergence Testing apply here
3. Selecting and Running the operators
- There are more things to pick from here. If you want to test second derivative operators, try them with the normal "Setting Up the Operators (Dirichlet/Periodic)". If you want to test first derivative operators, try the ones labeled as such. Please note, however, that the first derivative solutions with Dirichlet conditions are **still a work in progress**, so they will likely not work as you would hope that they would. (I mean, if you can fix it then that would be amazing). The periodic first derivative schemes should work just fine.
- Be sure to adjust your operators coefficients as well as the correct number of boundary rows (with Dirichlet condition) before generating the operator.
- To run the operator, first run the block of code under your selected conditions that will build the operator, then run the second block to run it. The instructions are similar to the CFD Convergence Testing methods, however, the only time-stepping method here is forward Euler.
4. Animate or Graph Convergence
- Unlike the other notebook, animating the convergence takes two steps: generating the animations, and displaying them. This saves time and allows for faster computation.
- Graphing the convergence is also separate.


## Other things to note:

There are two different types of modules for generating the RHS matrices: "Adjusted" : `RHSMatrixAdjusted` and `PeriodicRHSAdjusted` and the "Non-Adjusted" : `RHSMatrix` and `PeriodicRHS`. The "Adjusted" Matrices are to be used for Kim's and other operators that just use the coefficients straight up without dividing by any factors. The "Non-Adjusted" matrices will divide the bands of coefficients by 2, 4, 6, etc.

Periodic Boundaries are different than the Dirichlet boundaries in a few ways. One significant difference is that the solution is only plotted from $0$ to $1-1/n$ instead of $0$ to $1$, and it has $n-1$ points compared to the corresponding Dirichlet operators

