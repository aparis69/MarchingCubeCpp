## Marching Cube C++
A public domain header-only marching cube implementation in C/C++ without anything fancy. Only dependencies are cmath 
and vector headers. I could get rid of vector and just use plain arrays, but it is more convenient for my personal 
projects to keep that way, though one could easily modify the implementation.

This work was motivated by this public domain implementation of the marching cube: https://github.com/nsf/mc which gives 
a fully runnable example in OpenGL. I thought it could be simplified and could make a good header-only library.

## Behaviour
Calling Mc::marching_cube will create an indexed mesh with vertices and normals defined in their own std::vector's.
By default, data is allocated for vertices, normals and triangle indices. You can change the default allocated 
space using the function MC::setDefaultArraySizes.

The output mesh represents the zero-isosurface of the input data.

You can optionally enable double precision by defining MC_CPP_USE_DOUBLE_PRECISION before including the header.

## Use
First define MC_CPP_ENABLE and then include MC.h in your project. Example:
```
#define MC_IMPLEM_ENABLE
#include "MC.h"

int main()
{
	// Create a scalarfield with whatever dimension and values you want.
	const int n = 100;
	MC::MC_FLOAT* field = new MC::MC_FLOAT[n * n * n];
	// [...]
	
	// Compute isosurface using marching cube
	MC::mcMesh mesh;
	MC::marching_cube(field, n, n, n, mesh);

	// Dot whatever you want with the mesh
	// [...]

	return 0;
}
```

You may find a complete example in main.cpp file. Running the program in the repository will output an obj file showing 
the isosurface of a single perlin noise octave.

## Licence
Public domain.
