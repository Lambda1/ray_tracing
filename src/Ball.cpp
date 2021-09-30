#include "Ball.h"

#include <cmath>

#include "../glm/glm/glm.hpp"

namespace my
{
	Ball::Ball(const float& x, const float& y, const float& z, const float& r) :
		m_center{ x, y, z }, m_r{ r }
	{
	}

	Ball::~Ball()
	{
	}

	float Ball::RayCast(const glm::vec3& vect, const glm::vec3& eye)
	{
		const float d = std::sqrtf(m_r * m_r - vect.x * vect.x - vect.y * vect.y);

		if (d >= 0)
		{
			return vect.z - d;
		}

		return 0.0f;
	}
}