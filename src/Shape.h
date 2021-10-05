#ifndef MY_SHAPE_H
#define MY_SHAPE_H

#include "../glm/glm/glm.hpp"

namespace my
{
	class Shape
	{
	public:
		Shape() : m_k_d{ 0.0f, 0.0f, 0.0f },
			m_center{}, m_r{}
		{};
		virtual ~Shape() = default;

		inline void SetLuminance(const glm::vec3& k) { m_k_d = k; }

		inline glm::vec3 GetLuminance() const { return m_k_d; }
		inline glm::vec3 GetCenter() const { return m_center; }
		inline float GetR() const { return m_r; }

		virtual float RayCast(const glm::vec3& vect, const glm::vec3& eye) const = 0;
		virtual glm::vec3 Normal(const glm::vec3 &eye, const glm::vec3& eye_v, const float &t) const = 0;

	protected:
		glm::vec3 m_center;
		float m_r;

		glm::vec3 m_k_d; // ŠgU”½ËŒW”
	};
}

#endif