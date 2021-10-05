#ifndef MY_PLANE_H
#define MY_PLANE_H

#include "./Shape.h"

namespace my
{
	class Plane : public Shape
	{
	public:
		explicit Plane(const float &x, const float &y, const float &z);
		~Plane();
		
		virtual float RayCast(const glm::vec3& vect, const glm::vec3& eye) const override;
		virtual glm::vec3 Normal(const glm::vec3 &eye, const glm::vec3& eye_v, const float &t) const override;
	};
}

#endif
