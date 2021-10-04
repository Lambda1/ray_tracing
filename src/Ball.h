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

		float RayCast(const glm::vec3& vect, const glm::vec3 &eye) const;

		inline glm::vec3 GetCenter() const { return m_center; }
		inline float GetR() const { return m_r; }

	private:
		const glm::vec3 m_center;
		const float m_r;
	};
}

#endif
