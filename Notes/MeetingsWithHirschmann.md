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