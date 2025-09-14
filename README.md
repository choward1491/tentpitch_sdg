# Solver for systems of hyperbolic partial differential equations (Work in process)
## A package for solving hyperbolic PDEs using the spacetime discontinuous galerkin method with tent pitching
The goal of this package is to build a free to use package for solving hyperbolic PDEs, using a spacetime discontinuous approach and the tent pitching technique. This package is based on data structures and algorithms designed in my [masters thesis][1] but makes use of my HPC and software engineering skills picked up over time.

## Goals
- Written in modern C++
- Handles systems of hyperbolic PDEs.
	- Will start with linear PDEs, plan to add in capabilities for nonlinear
	- Extendable for new problems and boundary conditions.
- Fast and parallel, if desired.
	- Tent pitching approach allows for very fast serial solution to solving systems of hyperbolic PDEs
	- Fairly easily parallelizable; have a shared memory implementation built.
	- A distributed implementation using MPI is in the works.
- Adaptive meshing algorithms.
	- Has built in spacetime refinement, smoothing, and edge flip operations to help users get the best results.
	- Has heuristic error indicators to help decide when to refine.
- Allows for specifying reference spatial geometry model using VTK format; this helps with refinement, specifying boundary conditions, etc.
- Built tools for code generation of models.
- Unit tests for everything.

## References
[1]: https://www.ideals.illinois.edu/items/112053 "Masters Thesis on data structures for spacetime discontinuous galerkin method through 3d x time"
