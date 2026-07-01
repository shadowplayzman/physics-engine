#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include"Universe.h"
#include"mesh.h"

class SolarSystemFactory {
	public :
		static void CreateSolarSystem(Universe& universe, Mesh& sphereMesh);
		static void CreateSun(Universe& universe, Mesh& sphereMesh);
		static void CreateMercury(Universe& universe, Mesh& sphereMesh);
		static void CreateVenus(Universe& universe, Mesh& sphereMesh);
		static void CreateEarth(Universe& universe, Mesh& sphereMesh);
		static void CreateMars(Universe& universe, Mesh& sphereMesh);
		static void CreateJupiter(Universe& universe, Mesh& sphereMesh);
		static void CreateSaturn(Universe& universe, Mesh& sphereMesh);
		static void CreateUranus(Universe& universe, Mesh& sphereMesh);
		static void CreateNeptune(Universe& universe, Mesh& sphereMesh);
};

#endif