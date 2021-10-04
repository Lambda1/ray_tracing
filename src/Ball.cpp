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

	float Ball::RayCast(const glm::vec3& vect, const glm::vec3& eye) const
	{
		const float a = eye.x * eye.x + eye.y * eye.y + eye.z * eye.z;
		const float b = 2.0f * (eye.x * (vect.x - m_center.x) + eye.y * (vect.y - m_center.y) + eye.z * (vect.z - m_center.z));
		const float c = (vect.x - m_center.x) * (vect.x - m_center.x) + (vect.y - m_center.y) * (vect.y - m_center.y) + (vect.z - m_center.z) * (vect.z - m_center.z) - m_r * m_r;
		
		const float d = b * b - 4.0f * a * c;

		if (d >= 0.0f)
		{
			return (-b - std::sqrtf(d))/2.0f;
		}

		return 1e5f;
	}
}
