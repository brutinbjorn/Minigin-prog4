#pragma once

//#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
//#pragma warning(pop)

#include "Component.h"

namespace dae
{
	
	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z = 0) noexcept;
		void SetPosition(const glm::vec3& pos) noexcept;

	private:
		glm::vec3 m_Position = glm::vec3();
		
	};
}
