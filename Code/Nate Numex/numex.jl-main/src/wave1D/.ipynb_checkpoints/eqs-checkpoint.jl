
function init_data!(fields)
    nx = fields.grid.nx

    Pi = fields.u[1]
    Phi = fields.u[2]
    x = fields.grid.x

    amp = 1.0
    lambda = 1.0
    x0 = 10.0

    
#     Pi[1] = 0
#     Phi[1] = 0
    for i=1:nx
#         Pi[i] = 3*amp*sin(10*x[i])*exp(-( (x[i]-x0)/lambda )^2)
#         Pi[i] = 3*exp(-(x[i])^2)
#         Phi[i] = -2*x[i]*amp*exp(-( (x[i]-x0)/lambda )^2)
        Pi[i] = 0
        Phi[i] = -2*x[i]*amp*exp(-( (x[i]-x0)/lambda )^2)
#         Phi[i] = 0
#         Phi[i] = amp*exp(-( (lambda*x[i] )^0.5))
    end
#     Pi[nx] = Pi[1]
#     Phi[nx] = Phi[1]

end

function waveEqs!(dtu, u, dxu, x, dx, time)
#     print("dtu: $(dtu)\n\n\n")
#     print("u: $(u)\n\n\n")
#     print("dxu: $(dxu)\n\n\n")
#     print("x: $(x)\n\n\n")
#     print("dx: $(dx)\n\n\n")
#     print("time: $(time)\n\n\n")
    nx = length(x)
    idx = 1.0/dx
    idx_by_2 = 1.0/(2.0*dx)

    dtPi = dtu[1]
    dtPhi = dtu[2]
    Pi = u[1]
    Phi = u[2]
    dxPi = dxu[1]
    dxPhi = dxu[2]
#     dtphi = Pi
#     phi = u[3]

    diff66_x!(dxPi, Pi, dx)
    diff66_x!(dxPhi, Phi, dx)

    dtPi[1] = idx*(Pi[2] - Pi[1])
    dtPhi[1] = idx*(Phi[2] - Phi[1])
#     dtPi[1] = 0
#     dtPhi[1] = 0

    for i = 2:nx-1
        # Note: Changing the cfl to 0.5 gives interesting behavior after some time
        # Note: Why does original not reflect but others do?
        # Original
        dtPi[i] = dxPhi[i]
        dtPhi[i] = dxPi[i] 
        #= Example 1
        a0 = cos(i)
        dtPi[i] = dxPhi[i] + a0*Phi[i]
        dtPhi[i] = dxPi[i] =#
        #= Example 2 - Unstable!!!
        a0 = cos(i)
        a1 = sin(2*i)
        dtPi[i] = dxPhi[i] + a0*Phi[i] + a1*dxPi[i]
        dtPhi[i] = dxPi[i] =#
        #= Example 3
        a0 = cos(i)
        a1 = sin(2*i)
        dtPi[i] = dxPhi[i] + a0*Phi[i] + a1*Pi[i]
        dtPhi[i] = dxPi[i] =#
        #= Example 4
        a0 = cos(i)
        a1 = sin(2*i)
        a2 = sqrt(i)
        dtPi[i] = dxPhi[i] + a0*Phi[i] + a1*Pi[i] + a2*dxPhi[i]
        dtPhi[i] = dxPi[i] =#
        #= Example 5 =#
        #= Example 6 =#
        #= Example 7 =#
        #= Example 8 =#
        #= Example 9 =#
        #= Example 10 =#
        #= Example 11 =#
#         a0 = cos(i)
#         a1 = sin(2*i)
#         a2 = sqrt(i)
        # dtPi[i] = dxPhi[i]
        # dtPhi[i] = dxPi[i]
        # Would need to add phi[i] and dtphi[i]
        # dtPi[i] = dxPhi[i] + a0*phi[i]
        # dtPhi[i] = dxPi[i]
        # dtphi[i] = Pi[i]
    end
    # Original boundary conditions (Sommerfeld)
    dtPi[nx] = -idx*(Pi[nx] - Pi[nx-1])
    dtPhi[nx] = -idx*(Phi[nx] - Phi[nx-1])
    # Example 1
#     dtPi[nx] = 0
#     dtPhi[nx] = 0
    # Example 2
#     dtPi[nx] = dtPi[1]
#     dtPhi[nx] = dtPhi[1]
    
    # Dirichlet
    # Pi[1] = 0
    # Pi[nx] = 0
    
    # Neumann
#     Phi[1] = 0
#     Phi[nx] = 0
    
    # Robin
#     Pi[1] = 0
#     Phi[1] = 0
#     Pi[nx] = 0
#     Phi[nx] = 0
    
    # Periodic
#     Pi[1] = Pi[nx]
#     Phi[nx] = Phi[1]
    
    

end

