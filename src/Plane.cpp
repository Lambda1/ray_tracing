#include "Plane.h"

my::Plane::Plane(const float& x, const float& y, const float& z)
{
	m_center = glm::vec3{ x, y, z };
}

my::Plane::~Plane()
{
}

float my::Plane::RayCast(const glm::vec3& vect, const glm::vec3& eye) const
{
	if (eye.y == 0.0f) { return 1e5f; }
	
	const float t = (m_center.y - vect.y) / eye.y;
	if (t >= 0.0f)
	{
		return t;
	}

	return 1e5f;
}

glm::vec3 my::Plane::Normal(const glm::vec3& eye, const glm::vec3& eye_v, const float& t) const
{
	if (eye.y == 0.0f) { return glm::vec3{1e5f, 1e5f, 1e5f}; }
	return glm::vec3{0.0f, 1.0f, 0.0f};
}
