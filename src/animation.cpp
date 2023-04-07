#include "animation.hpp"

Curve::Curve(glm::vec3 r0, glm::vec3 r1, glm::vec3 r2) : r{ r0, r1, r2 }
{ }

glm::vec3 Curve::operator() (const float v) const
{
	return r[0] * (1 - v) * (1 - v) + 2.0f * r[1] * (1 - v) * v + r[2] * v * v;
}


Animation::Animation(std::vector<glm::vec3>& rVectors) : numCurves(rVectors.size()/3)
{
	for (size_t i = 0; i < rVectors.size()/3; i++)
	{
		rPath.push_back(Curve(rVectors[i * 3], rVectors[i * 3 + 1], rVectors[i * 3 + 2]));
	}
}

std::pair<glm::vec3, glm::vec3> Animation::getPosDirection(float v)
{
	float localV = fmodf(v, numCurves);
	glm::vec3 pos = glm::vec3(rPath[static_cast<int>(fmodf(v, numCurves))](localV));
	glm::vec3 direction = glm::normalize(glm::vec3(rPath[static_cast<int>(fmodf(v, numCurves))](localV + 0.01)) - pos);
	return std::pair<glm::vec3, glm::vec3>{ pos, direction };
}

