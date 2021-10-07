#ifndef MY_PLANE_H
#define MY_PLANE_H

#include "./Shape.h"

#include "../glm/glm/glm.hpp"

namespace my
{
	class Plane : public Shape
	{
	public:
		explicit Plane(const float &x, const float &y, const float &z);
		~Plane();
	private:
		glm::vec3 m_center;
	};
}

#endif
