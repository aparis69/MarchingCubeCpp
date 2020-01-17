## Marching Cube C++
A public domain header-only marching cube implementation in C++ without anything fancy. Only dependencies are cmath and vector headers.
I could get rid of vector and just use plain arrays, but it is more convenient for my personal projects to keep that way, though one could 
easily modify the implementation.

Note that calling the main function marching_cube() may allocate a lot of memory depending on the resolution of your data. The function 
creates an indexed mesh with vertices, normals and indexes defined in their own arrays.

You can optionally enable double precision by defining MC_CPP_USE_DOUBLE_PRECISION before including the header.

This work was motivated by this implementation of the marching cube: https://github.com/nsf/mc
which gives a fully runnable example in OpenGL. I thought it could be heavily simplified and could make a good
header only library.

## Use
First define MC_CPP_ENABLE and then include MC.h in your project. Example:
```
#define MC_IMPLEM_ENABLE
#include "MC.h"

int main()
{
	// Create a scalarfield with whatever dimension and values you want.0
	const int n = 100;
	MC_FLOAT* field = new MC_FLOAT[n * n * n];
	// [...]
	
	// Compute isosurface using marching cube
	mcMesh mesh;
	marching_cube(field, n, n, n, mesh);

	// Dot whatever you want with the mesh
	// [...]

	return 0;
}
```

You may find a complete example in main.cpp file. Running the program in the repository will output an obj file showing the isosurface
of a single perlin noise octave.

## Licence
Public domain
