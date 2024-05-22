function diff21_x!(dxu, u, dx)
    nx = length(u)
    idx = 1.0/dx
    idx_by_2 = 0.5*idx

    dxu[1] = (-u[1] + u[2])*idx
    for i = 2:nx-1
        dxu[i] = (u[i+1] - u[i-1]) * idx_by_2
    end
    dxu[nx] = (u[nx] - u[nx-1])*idx
end

function diff22_x!(dxu, u, dx)
    nx = length(u)
    idx = 1.0/dx
    idx_by_2 = 0.5*idx

    dxu[1] = (-3.0*u[1] + 4.0*u[2] - u[3]) * idx_by_2
#     dxu[1] = 0
    for i = 2:nx-1
        dxu[i] = (u[i+1] - u[i-1]) * idx_by_2
    end
    dxu[nx] = (u[nx-2] - 4.0*u[nx-1] + 3.0*u[nx]) * idx_by_2
#     dxu[nx] = 0
end

function diff42_x!(dxu, u, dx)
    nx = length(u)
    idx = 1.0/dx
    idx_by_2 = 0.5*idx
    idx_by_12 = idx/12.0

    dxu[1] = (-3.0*u[1] + 4.0*u[2] - u[3]) * idx_by_2
    dxu[2] = (-u[1] + u[3]) * idx_by_2
    for i = 3:nx-2
        dxu[i] = (u[i-2] - 8.0*u[i-1] + 8.0*u[i+1] - u[i+2])*idx_by_12
    end
    dxu[nx-1] = ( - u[nx-2] + u[nx]) * idx_by_2
    dxu[nx] = (u[nx-2] - 4.0*u[nx-1] + 3.0*u[nx]) * idx_by_2
end

function kodiss!(f, u, dx)

    nx = length(f)
    sigma = 0.05
    idx = sigma/dx

    f[1] -= 2.0*(u[3] - 2.0*u[2] + u[1])*idx
    f[2] -= (u[4] - 4.0*u[3] + 5.0*u[2] - 2.0*u[1])*idx
#     f[1] -= 0
#     f[2] -= 0
    for i = 3:nx-2
        f[i] -= (u[i+2] - 4.0*u[i+1] + 6.0*u[i]
                            - 4.0*u[i-1] + u[i-2])*idx
    end
    f[nx-1] -= (u[nx-3] - 4.0*u[nx-2] + 5.0*u[nx-1] - 2.0*u[nx]  ) *idx
    f[nx] -= 2.0 * (u[nx-2] - 2.0*u[nx-1] + u[nx])*idx
#     f[nx-1] -= 0
#     f[nx] -= 0

end










# attempt at 6th order
function diff66_x!(dxu, u, dx)
    nx = length(u)
    idx = 1.00/dx
    idx_by_60 = idx / 60.0
    
    i = 1
    dxu[1] = ( - 147.0 * u[i]     
                    + 360.0 * u[i+1]     
                    - 450.0 * u[i+2]     
                    + 400.0 * u[i+3]     
                    - 225.0 * u[i+4]     
                    +  72.0 * u[i+5]     
                    -  10.0 * u[i+6]     
                  ) * idx_by_60

    i = 2
    dxu[2] = (  -  10.0 * u[i-1]     
                     -  77.0 * u[i]     
                     + 150.0 * u[i+1]     
                     - 100.0 * u[i+2]     
                     +  50.0 * u[i+3]     
                     -  15.0 * u[i+4]     
                     +   2.0 * u[i+5]     
                  ) * idx_by_60

    i = 3
    dxu[3] = (      2.0 * u[i-2]     
                     -  24.0 * u[i-1]     
                     -  35.0 * u[i]     
                     +  80.0 * u[i+1]     
                     -  30.0 * u[i+2]     
                     +   8.0 * u[i+3]     
                     -          u[i+4]     
                  ) * idx_by_60
    
    for i = 4:nx-3
        dxu[i] = ( -         u[i-3]     
                      +  9.0 * u[i-2]     
                      - 45.0 * u[i-1]     
                      + 45.0 * u[i+1]     
                      -  9.0 * u[i+2]     
                      +         u[i+3]     
                    ) * idx_by_60
    end

    i = nx-2
    dxu[nx-2] = (            u[i-4]     
                     -  8.0 * u[i-3]     
                     + 30.0 * u[i-2]     
                     - 80.0 * u[i-1]     
                     + 35.0 * u[i]     
                     + 24.0 * u[i+1]     
                     -  2.0 * u[i+2]     
                  ) * idx_by_60

    i = nx-1
    dxu[nx-1] = (  -   2.0 * u[i-5]     
                     +  15.0 * u[i-4]     
                     -  50.0 * u[i-3]     
                     + 100.0 * u[i-2]     
                     - 150.0 * u[i-1]     
                     +  77.0 * u[i]     
                     +  10.0 * u[i+1]     
                   ) * idx_by_60

    i = nx
    dxu[nx] = (     10.0 * u[i-6]     
                     -  72.0 * u[i-5]     
                     + 225.0 * u[i-4]     
                     - 400.0 * u[i-3]     
                     + 450.0 * u[i-2]     
                     - 360.0 * u[i-1]     
                     + 147.0 * u[i]     
                   ) * idx_by_60

end