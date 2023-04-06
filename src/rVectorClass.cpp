#include "rVectorClass.hpp"

rVector::rVector(std::vector<glm::vec3>& rVertices) : rVertices(rVertices)
{ }

rVector::rVector()
{
	rVertices = std::vector<glm::vec3>{
        glm::vec3( 1.0f, 1.0f, -1.0f),
        glm::vec3( 0.0f, 1.5f, -1.0f),
        glm::vec3(-1.0f, 1.0f, -1.0f),
        glm::vec3( 1.0f, 1.0f,  0.0f),
        glm::vec3( 0.0f, 2.0f,  0.0f),
        glm::vec3(-1.0f, 1.0f,  0.0f),
        glm::vec3( 1.0f, 1.0f,  1.0f),
        glm::vec3( 0.0f, 1.5f,  1.0f),
        glm::vec3(-1.0f, 1.0f,  1.0f)
    };
}

void rVector::setRVertices(std::vector<glm::vec3>& rVertices)
{
    rVector::rVertices = rVertices;
}

glm::vec3 rVector::getVertex(const float u, const float v)
{

    return r0Vector(v)*(1-u)*(1-u) + 2.0f*r1Vector(v) * (1 - u) * u + r2Vector(v) *u*u;
}

glm::vec3 rVector::r0Vector(const float v)
{
    return rVertices[0]*(1-v)*(1-v)+2.0f* rVertices[1]*(1-v)*v+ rVertices[2]*v*v;
}

glm::vec3 rVector::r1Vector(const float v)
{
    return rVertices[3] * (1 - v) * (1 - v) + 2.0f * rVertices[4] * (1 - v) * v + rVertices[5] * v * v;

}

glm::vec3 rVector::r2Vector(const float v)
{
    return rVertices[6] * (1 - v) * (1 - v) + 2.0f * rVertices[7] * (1 - v) * v + rVertices[8] * v * v;

}
