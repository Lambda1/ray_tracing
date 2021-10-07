#include "Ball.h"

namespace my
{
	Ball::Ball(const float& x, const float& y, const float& z, const float& r) :
		m_center{ x, y, z }, m_radius{ r }
	{
	}

	Ball::~Ball()
	{
	}
}
