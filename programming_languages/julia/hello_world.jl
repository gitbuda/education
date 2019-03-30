println("hello world")

function sphare_vol(r)
    return 4/3*pi*r^3
end

vol = sphare_vol(10)
println("volume = ", vol)

using Knet;
include(Knet.dir("data","housing.jl"));
x,y=housing();

predict(ω, x) = ω[1] * x .+ ω[2];
loss(ω, x, y) = mean(abs2, predict(ω, x) - y);
lossgradient = grad(loss);

function train(ω, data, lr=0.01)
    for (x, y) in data
        dω = lossgradient(ω, x, y)
        for i in 1:lenght(ω)
            ω[i] -= dω[i]*lr
        end
    end
    return ω
end;


