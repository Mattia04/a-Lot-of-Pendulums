# A lot of Pendulums

Boia deh ci piacciono i pendoli.

## TODOs

- Add documentation to the classes
- Make the visualization (in c++)
- Complete this file

## Project overview

### video example

### photo fractal

### Project tree structure

## Mathematical Description

### Hamiltonian system

### Wolfram Mathematica Calculations

## Classes defined

### `MyFunctor`

### `MyODEIntegrator`

I have made different ODE integrators to test their performance.

Here is a list of what classes I have defined:

- RK4
- RK5
- RK6
- RK7 
- RK8
- RKF45 (todo)
- RKDP45 (todo)

NOTE: the Butcher tables for all of them (except for RK4) are generated using 
ChatGPT so they could be wrong, but from eye I don't see an error.

The child classes of `MyODEIntegrator` calculates the next step of the 
integration using the `.step()` method, which takes the current time `t`, 
the step size `h`, the current generalized coordinates `x` and the functor 
to integrate `f` (in this case the `MyDoublePendulum` class).

### `MySimpleDoublePendulum`

### `MyDoublePendulum`