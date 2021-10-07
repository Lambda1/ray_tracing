#ifndef MY_BALL_H
#define MY_BALL_H

#include "./Shape.h"

#include "../glm/glm/glm.hpp"

namespace my
{
	class Ball : public Shape
	{
	public:
		explicit Ball(const float &x, const float &y, const float &z, const float &r);
		virtual ~Ball();

	private:
		glm::vec3 m_center;
		float m_radius;
	};
}

#endif
