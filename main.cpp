#define MC_IMPLEM_ENABLE
#include "MC.h"

#include "noise.h"
#include <iostream>
#include <fstream>

int main()
{
	// Compute a scalarfield from a single octave of perlin noise
	const int n = 100;
	MC_FLOAT* field = new MC_FLOAT[n * n * n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
				field[(k * n + j) * n + i] = PerlinNoise::GetValue(i * 0.03478, j * 0.03478, k * 0.03478);
		}
	}

	// Compute isosurface using marching cube
	mcMesh mesh;
	marching_cube(field, n, n, n, mesh);

	// Export the result as an .obj file
	std::ofstream out;
	out.open("test.obj");
	if (out.is_open() == false)
		return 0;
	out << "g " << "Obj" << std::endl;
	for (size_t i = 0; i < mesh.vertices.size(); i++)
		out << "v " << mesh.vertices.at(i).x << " " << mesh.vertices.at(i).y << " " << mesh.vertices.at(i).z << '\n';
	for (size_t i = 0; i < mesh.vertices.size(); i++)
		out << "vn " << mesh.normals.at(i).x << " " << mesh.normals.at(i).y << " " << mesh.normals.at(i).z << '\n';
	for (size_t i = 0; i < mesh.indices.size(); i += 3)
	{
		out << "f " << mesh.indices.at(i) + 1 << "//" << mesh.indices.at(i) + 1
			<< " " << mesh.indices.at(i + 1) + 1 << "//" << mesh.indices.at(i + 1) + 1
			<< " " << mesh.indices.at(i + 2) + 1 << "//" << mesh.indices.at(i + 2) + 1
			<< '\n';
	}
	out.close();

	return 0;
}
