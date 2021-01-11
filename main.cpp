#define MC_IMPLEM_ENABLE
#include "MC.h"

#include "noise.h"
#include <iostream>
#include <fstream>
#include <chrono>

void TestPerformances()
{
	// Compute a scalarfield from a single octave of perlin noise
	const int n = 100;
	MC::MC_FLOAT* field = new MC::MC_FLOAT[n * n * n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
				field[(k * n + j) * n + i] = PerlinNoise::GetValue(i * 0.0201f, j * 0.0201f, k * 0.0201f);
		}
	}

	// Measure performance on 100 iterations of marching cubes
	int count = 100;
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	{
		for (int i = 0; i < count; i++)
		{
			MC::mcMesh mesh;
			MC::marching_cube(field, n, n, n, mesh);
		}
	}
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Average time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / count << "[ms]" << std::endl;
}

void TestSimpleMC()
{
	// Compute a scalarfield from a single octave of perlin noise
	const int n = 50;
	float* field = new float[n * n * n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
				field[(k * n + j) * n + i] = PerlinNoise::GetValue(i * 0.0201f, j * 0.0201f, k * 0.0201f);
		}
	}

	// Compute isosurface using marching cube
	MC::mcMesh mesh;
	MC::marching_cube(field, n, n, n, mesh);

	// Export the result as an .obj file
	std::ofstream out;
	out.open("test.obj");
	if (out.is_open() == false)
		return;
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
}

int main()
{
	//TestPerformances();
	TestSimpleMC();
	return 0;
}
