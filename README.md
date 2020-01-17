## Marching Cube C++
A public domain header-only marching cube implementation in C++, without anything fancy. Only dependencies are <cmath> and <vector> headers.
I could get rid of vector and just use plain arrays, but it is more convenient for my personal projects to keep that way, though one could 
easily modify the implementation.

Note that calling the main function marching_cube() may allocate a lot memory, depending on the resolution of your data. The function creates
an indexed mesh having vertices, normals and indexes properly defined in their own arrays.

You can optionally enable double precision by defining MC_CPP_USE_DOUBLE_PRECISION before including the header.

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

## Licence
Public domain.
