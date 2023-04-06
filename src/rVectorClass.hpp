#pragma once

#include <vector>

#include <glm/glm.hpp>

class rVector
{
private:
	std::vector<glm::vec3> rVertices;

public:
	rVector(std::vector<glm::vec3>& rVertices);
	rVector();
	glm::vec3 getVertex(const float u, const float v);
	void setRVertices(std::vector<glm::vec3>& rVertices);


private:
	glm::vec3 r0Vector(const float v);
	glm::vec3 r1Vector(const float v);
	glm::vec3 r2Vector(const float v);


};