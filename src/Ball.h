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

		float RayCast(const glm::vec3& vect, const glm::vec3 &eye) const;

		inline void SetLuminance(const glm::vec3& k) { m_k_d = k; }

		inline glm::vec3 GetLuminance() const { return m_k_d; }
		inline glm::vec3 GetCenter() const { return m_center; }

	private:
		const glm::vec3 m_center;
		const float m_r;

		glm::vec3 m_k_d; // ŠgU”½ËŒW”
	};
}

#endif
