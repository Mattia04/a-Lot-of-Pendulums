# A lot of Pendulums

Boia deh ci piacciono i pendoli.

## TODOs

- Add documentation to the classes
- Add Symplectic integrator
- Make the visualization (in c++)
- Complete this file

### Other things I don't know 

Maybe it's better to think a different file structure for the local 
libraries, now it's kind of a complicated structure.

## Project overview

### video example

### photo fractal

### Project tree structure

## Mathematical Description

### Hamiltonian system

### Wolfram Mathematica Calculations

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