#ifndef MY_BALL_H
#define MY_BALL_H

#include "./Shape.h"

namespace my
{
	class Ball : public Shape
	{
	public:
		explicit Ball(const float &x, const float &y, const float &z, const float &r);
		virtual ~Ball();

		virtual float RayCast(const glm::vec3& vect, const glm::vec3& eye) const override;
		virtual glm::vec3 Normal(const glm::vec3 &eye, const glm::vec3& eye_v, const float &t) const override;
	private:
	};
}

#endif
