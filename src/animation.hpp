#pragma once

#include <vector>
#include <iostream>

#include <glm/glm.hpp>

class Curve
{
private:
	glm::vec3 r[3];

public:
	Curve(glm::vec3 r0, glm::vec3 r1, glm::vec3 r2);

	glm::vec3 operator() (const float v) const;
};

class Animation
{
private:
	std::vector<Curve> rPath;
	unsigned int numCurves;

public:
	Animation(std::vector<glm::vec3>& rVectors);
	std::pair<glm::vec3, glm::vec3> getPosDirection(float v);
};