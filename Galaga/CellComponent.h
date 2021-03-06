#pragma once
#include <Component.h>
#include <SDL_pixels.h>
#include <string>


#include "Transform.h"
#include "RenderComponent.h"

class CellComponent :
    public BaseComponent
{
public:
	
	CellComponent(const glm::vec3& pos, const glm::ivec2& boardPos, RenderComponent* render, float rad);

	void Update(const float ) override {};
	void Render() const override;

	glm::vec2 getSpritePos();
	glm::vec2 GetPosition();

private:
	float m_radius;
	glm::ivec2 m_hexCoordinate;

	dae::Transform m_Transform;

	RenderComponent* nm_pRenderComponent = nullptr;


	
};


