function rk2_helper1(ynp1, yn, f, dt)
    @. ynp1 = yn + 0.5*dt*f
end
function rk2_helper2(yn, f, dt)
    @. yn += dt[1]*f
end

function rk2_step!(func::Function, fields, t)
    # func calculates the RHS.  The boundary conditions are returned in func.
    neqs = length(fields.u)
    tx = t[1]

    dx = fields.grid.dx
    dt = fields.grid.dt
    x  = fields.grid.x
    yn = fields.u
    ynp1 = fields.u2
    f = fields.wrk
    dxy = fields.dxu
    
    func(f, yn, dxy, x, dx, tx)
    @. kodiss!(f, yn, dx)
    @. rk2_helper1(ynp1, yn, f, dt)
    
    thalf = tx + 0.5*dt
    t[1] += dt
    func(f, ynp1, dxy, x, dx, thalf)
    @. kodiss!(f, yn, dx)
    @. rk2_helper2(yn, f, dt)
end



#------------------------------------RK4------------------------------------



function rk4_helper1(ynp1, yn, f, dt)
    @. ynp1 = yn + dt*f
end

function rk4_helper2(yn, f1, f2, f3, f4, dt)
    t1 = dt / 6.0
    @. yn += t1*(f1 + 2.0*f2 + 2.0*f3 + f4)
end



function rk4_step!(func::Function, fields, t)
    # rk4 Scheme
    neqs = length(fields.u)
    tx = t[1]
    
    dx = fields.grid.dx
    dt = fields.grid.dt
    x  = fields.grid.x
    yn = fields.u
    ynp1 = fields.u2
    f = fields.wrk
    dxy = fields.dxu
    
    f1 = deepcopy(f)
    f2 = deepcopy(f)
    f3 = deepcopy(f)
    f4 = deepcopy(f)
    
    dthalf = 0.5*dt
    thalf = tx + dthalf
    tnp1 = tx + dt
    t[1] = tnp1
#     print("We can at least make it here\n")
    
#     println("f: ", f)
#     println("f1: ", f1)
#     println("f2: ", f2)
    yntemp = yn
    func(f1, yn, dxy, x, dx, tx)
    @. kodiss!(f1, yn, dx)
#     @. rk4_helper1(yntemp, yn, f1, dthalf)
#     print("Finished step 1\n")
    
    yntemp = yn + 0.5*dt*f1
    func(f2, yntemp, dxy, x, dx, thalf)
    @. kodiss!(f2, yn, dx)
#     @. rk4_helper1(yntemp, yn, f2, dthalf)
#     print("Finished step 2\n")
    
    yntemp = yn + 0.5*dt*f2
    func(f3, yntemp, dxy, x, dx, thalf)
    @. kodiss!(f3, yn, dx)
#     @. rk4_helper1(yntemp, yn, f3, dt)
#     print("Finished step 3\n")
    
    yntemp = yn + dt*f3
    func(f4, yntemp, dxy, x, dx, tnp1)
    @. kodiss!(f4, yn, dx)
    @. rk4_helper2(yn, f1, f2, f3, f4, dt)
#     print("Finished step 4\n")
end