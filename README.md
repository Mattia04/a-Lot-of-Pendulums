# A lot of Pendulums

> "Boia deh ci piacciono i pendoli."
> 
> -- <cite>M.B.</cite>

I have decided to move the comparison of integrators in another project 
see: [ODE Solvers](https://github.com/Mattia04/ODESolvers), for this 
project I will use only KR4 and/or RK5, the other methods will remain but 
will not be used.

# Note:

This project is now obsolete, the new project can be found on [this repo](https://github.com/Mattia04/ALotOfPendulums2)

## Project overview

Here is a preview of the double pendulum fractal:

The first image (512x512px) produced:

<img src="tests/static_fractal/output_image.png">

Then I changed the color scheme and produced this 128x128px image in 20 
seconds:

<img src="tests/static_fractal/output_image3.png">

Then I left the code running for 1.5 hours and got this 2024x2024px image:

<img src="tests/static_fractal/output_image2.png">

The results show an accurate method of producing the pendulum fractal but 
without the GPU is not feasible to do anything significantly better. 
So this project will remain still until I understand how to use GPUs.

## Mathematical Description

I used the hamiltonian equation of the double pendulum using the lengths 
and masses equal to 1. For more information about the mathematics behind 
this project please refer to: [this pdf](Mathematica.pdf).

## Classes defined

### `MyFunctor`

A simple abstract class to be used as a base for general ODE problems.

Note: there is no time dependence, but it could be added if necessary.

#### `MySimpleDoublePendulum`

A child class of `MyFunctor`, it implements Hamilton equations of the double 
pendulum with rod length of 1 and masses of 1. For the maths behind it see 
`Mathematica.pdf`.

### `MyODEIntegrator`

An abstract class for ODE integrators with **fixed** step size. 

#### `MyRKN`

An abstract class for Runge-Kutta integrators of order $n$.

With this I can create Runge-Kutta integrators by just giving the number of 
steps `N`, and the butcher tableau in the form of 3 arrays: `m_A[N]`, `m_B[N][N]`, 
`m_C[N+1]` which contains the coefficients of the butcher tableau.

List of classes defined:

- `RK4`
- `RK5`
- `RK6`
- `RK7` (NOT TESTED)

### `MyDODEIntegrator`

An abstract class for ODE integrators with **variable** step size. 

#### `MyDRKN`

An abstract class for Runge-Kutta integrators of order $n$.

With this I can create Runge-Kutta integrators by just giving the number of 
steps `N`, and the butcher tableau in the form of 4 arrays: `m_A[N]`, 
`m_B[N][N]`, `m_CH[N+1]`, `m_CT[N+1]` which contains the coefficients of the 
butcher tableau, CH is used for the next step, CT is used for the error 
estimation.

List of classes defined:

- `RKF45` (NOT TESTED): Runge-Kutta-Fehlberg method
- `RKDP45` (NOT TESTED): Runge-Kutta-Dormand-Prince method

### `MySODEIntegrator`

An abstract class for **symplectic** ODE integrators.

List of classes defined:

- `MyVer` (NOT TESTED): Verlet method

Even tho symplectic methods are more stable for physical systems I don't 
think I will update this class since I have described the physical system 
in a different way of how those methods work, so the implementations would 
not be elegant (and I won't change everything just to implement them, I 
think I have enough methods of integration for this project).