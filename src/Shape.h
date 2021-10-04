#ifndef MY_SHAPE_H
#define MY_SHAPE_H

#include "../glm/glm/glm.hpp"

namespace my
{
	class Shape
	{
	public:
		Shape() : m_k_d{0.0f, 0.0f, 0.0f} {};
		virtual ~Shape() = default;

		inline void SetLuminance(const glm::vec3& k) { m_k_d = k; }

		inline glm::vec3 GetLuminance() const { return m_k_d; }

		virtual float RayCast(const glm::vec3& vect, const glm::vec3& eye) const = 0;

	protected:
		glm::vec3 m_k_d; // ŠgU”½ËŒW”
	};
}

#endif