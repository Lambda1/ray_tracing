#include "Ball.h"

#include <cmath>

#include "../glm/glm/glm.hpp"

namespace my
{
	Ball::Ball(const float& x, const float& y, const float& z, const float& r) :
		m_center{ x, y, z }, m_r{ r },
		m_k_d{0.0f, 0.0f, 0.0f}
	{
	}

	Ball::~Ball()
	{
	}

	float Ball::RayCast(const glm::vec3& vect, const glm::vec3& eye) const
	{
		const float d = (m_r * m_r - vect.x * vect.x - vect.y * vect.y);

		if (d >= 0.0f)
		{
			return m_center.z - std::sqrtf(d);
		}

		return 1e5f;
	}
}
