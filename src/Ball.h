#ifndef MY_BALL_H
#define MY_BALL_H

#include "../glm/glm/vec3.hpp"

namespace my
{
	class Ball
	{
	public:
		explicit Ball(const float &x, const float &y, const float &z, const float &r);
		virtual ~Ball();

		float RayCast(const glm::vec3& vect, const glm::vec3 &eye);

	private:
		glm::vec3 m_center;
		float m_r;
	};
}

#endif
