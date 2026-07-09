#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include"Universe.h"
#include"Texture.h"
#include"mesh.h"

struct PlanetTextures
{
	Texture& sun;
	Texture& mercury;
	Texture& venus;
	Texture& earth;
	Texture& mars;
	Texture& jupiter;
	Texture& saturn;
	Texture& uranus;
	Texture& neptune;
};


class SolarSystemFactory {
	public :
		static void CreateSolarSystem(Universe& universe, Mesh& sphereMesh,PlanetTextures& textures);
		static void CreateSun(Universe& universe, Mesh& sphereMesh, Texture& sunTexture);
		static void CreateMercury(Universe& universe, Mesh& sphereMesh, Texture& mercuryTexture);
		static void CreateVenus(Universe& universe, Mesh& sphereMesh, Texture& venusTexture);
		static void CreateEarth(Universe& universe, Mesh& sphereMesh, Texture& earthTexture);
		static void CreateMars(Universe& universe, Mesh& sphereMesh, Texture& marsTexture);
		static void CreateJupiter(Universe& universe, Mesh& sphereMesh, Texture& jupiterTexture);
		static void CreateSaturn(Universe& universe, Mesh& sphereMesh, Texture& saturnTexture);
		static void CreateUranus(Universe& universe, Mesh& sphereMesh, Texture& uranusTexture);
		static void CreateNeptune(Universe& universe, Mesh& sphereMesh, Texture& neptuneTexture);
};

#endif