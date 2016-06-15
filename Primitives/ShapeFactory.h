#pragma once
#include <glm.hpp>
#include <vector>
#include "ShapeData.h"

class ShapeFactory
{
public:
	static ShapeData MakeTriangle();
	static ShapeData MakeCube();
	static ShapeData MakeArrow();
	static ShapeData MakePlane(glm::uint dimensions = 10);
	static ShapeData MakeTeaPot(glm::uint tesselation, const glm::mat4& lidTransform);
	static ShapeData GenerateNormalLines(const ShapeData& data);
private :
	static void generatePatches(float * v, float * n, float * tc, unsigned short * el, int grid);
	static void moveLid(int grid, float * v, glm::mat4 lidTransform);
	static void buildPatchReflect(int patchNum, float * B, float * dB, float * v, float * n, float * tc, unsigned short * el, int & index, int & elIndex, int & tcIndex, int grid, bool reflectX, bool reflectY);
	static void getPatch(int patchNum, glm::vec3 patch[][4], bool reverseV);
	static glm::vec3 evaluate(int gridU, int gridV, float * B, glm::vec3 patch[][4]);
	static glm::vec3 evaluateNormal(int gridU, int gridV, float * B, float * dB, glm::vec3 patch[][4]);
	static void buildPatch(glm::vec3 patch[][4], float * B, float * dB, float * v, float * n, float * tc, unsigned short * el, int & index, int & elIndex, int & tcIndex, int grid, glm::mat3 reflect, bool invertNormal);
	static void computeBasisFunctions(float * B, float * dB, int grid);

};

