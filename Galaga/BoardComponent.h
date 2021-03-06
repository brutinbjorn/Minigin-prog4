#pragma once
#include <Component.h>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "CellComponent.h"
#include <Transform.h>

#include "GameObject.h"
#include "Scene.h"


struct cellPos
{
	glm::ivec2 position;
	std::shared_ptr<dae::GameObject> cell;
};

//https://www.redblobgames.com/grids/hexagons/#size-and-spacing
class BoardComponent :
    public BaseComponent
{
public:
	BoardComponent( dae::Scene& currentScene, const glm::vec3& center, const std::vector<glm::ivec2>& cellHexPosition, std::string texturepath,
	               float radius);
	BoardComponent(std::string path) {};

	~BoardComponent();
	
	void Update(const float ) override {};
	void Render() const override;
	
	std::shared_ptr<dae::GameObject> GetCellFromPos(int x, int y);
	std::shared_ptr<dae::GameObject> GetCellFromPos(glm::ivec2 pos);
	

private:
	std::vector<cellPos> m_cells;
	dae::Transform m_center;



	
};

