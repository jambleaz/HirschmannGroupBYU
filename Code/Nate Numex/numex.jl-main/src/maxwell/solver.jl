using Printf
using WriteVTK
using ArgParse

include("Maxwell2D.jl")
#import .Maxwell2D

using .Maxwell2D

function parse_commandline()
    s = ArgParseSettings()

    @add_arg_table s begin
        "--nx", "-n"
            help = "number of points in each direction"
            arg_type = Int
            default = 401
       "--vtkfreq", "-f"
            help = "Frequency of VTK output"
            arg_type = Int
            default = 5
         "--cfl", "-c"
            help = "Courant number"
            arg_type = Float64
            default = 0.1
        "nsteps"
            help = "Number of steps"
            arg_type = Int
            required = true
 
    end
    return parse_args(s)
end

function evolve!(fields, nt, vtkOutFreq)
    time = [0.0]
    vtkFileCount::Int64 = 0
    screenOutFreq = vtkOutFreq
    filename = @sprintf("maxwell_%05d",vtkFileCount)
    @printf("Step=%d, time=%g, |Bz|=%g\n",0,time[1],l2norm(fields.u[3]))
    println(typeof(filename))
    println(typeof(fields.grid.x))
    println(typeof(fields.grid.y))
    vtk_grid(filename, fields.grid.x, fields.grid.y) do vtk
        vtk["Ex",VTKPointData()] = fields.u[1]
        vtk["Ey",VTKPointData()] = fields.u[2]
        vtk["Hz",VTKPointData()] = fields.u[3]
        vtk["time",VTKFieldData()] = time[1]
    end
    for i = 1:nt
        rk2_step!(Maxwell2D.maxwell_TE!, fields, time)
        if (mod(i,screenOutFreq)==0)
            @printf("Step=%d, time=%g, |Bz|=%g\n",i,time[1],l2norm(fields.u[3]))
        end
        if (mod(i,vtkOutFreq)==0)
            vtkFileCount += 1
            filename = @sprintf("maxwell_%05d",vtkFileCount)
            vtk_grid(filename, fields.grid.x, fields.grid.y) do vtk
                vtk["Ex",VTKPointData()] = fields.u[1]
                vtk["Ey",VTKPointData()] = fields.u[2]
                vtk["Hz",VTKPointData()] = fields.u[3]
                vtk["time",VTKFieldData()] = time[1]
            end
        end
    end
end

function main()
  
    params = parse_commandline()
    n = params["nx"]
    nt = params["nsteps"]
    cfl = params["cfl"]
    VTKOutFreq = params["vtkfreq"]

    nx = ny = n
    bbox = [-10.0, 10.0, -10.0, 10.0]
    println("main:  nx = ",nx, " ny = ",ny)
    grid = Grid(nx, ny, bbox, cfl)
    println("main grid:  nx = ",grid.nx, " ny = ",grid.ny)

    fields = GridFields(3, grid)
    Maxwell2D.init_data!(fields)
    
    evolve!(fields, nt, VTKOutFreq)
end

main()

