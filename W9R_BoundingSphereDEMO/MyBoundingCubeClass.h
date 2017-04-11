#pragma once
#include "RE\ReEng.h"

class MyBoundingCubeClass
{
public:
	float m_fCenter = 0.0f;

	vector3 m_v3Center = vector3(0.0f);

	MyBoundingCubeClass(std::vector<vector3> vertexList);
};