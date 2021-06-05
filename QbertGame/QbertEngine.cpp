#include "QbertEngine.h"

#include "CellComponent.h"
#include "BoardComponent.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ObjectConstructors.h"
#include "SpriteComponent.h"

void QbertEngine::LoadGame()
{
	auto scene = dae::SceneManager::GetInstance().CreateScene("Qbert");


	auto obj = std::make_shared<dae::GameObject>();

	//SDL_Color test = SDL_Color{100,100,0,255};
	//auto cell = new CellComponent(glm::vec3(300, 200, 0), glm::ivec2(0, 0), test, 30);	
	//obj->AddComponent(cell);
	//scene->Add(obj);


	auto boardObj = std::make_shared<dae::GameObject>();
	
	std::vector<glm::ivec2> cellposition;
	cellposition.emplace_back(0, 0);
	cellposition.emplace_back(1, 0);
	cellposition.emplace_back(-1, 0);
	cellposition.emplace_back(1, -1);
	cellposition.emplace_back(-1, 1);
	cellposition.emplace_back(0, 1);
	cellposition.emplace_back(0, -1);
	
	auto board = 
		new BoardComponent(*scene,glm::vec3(300,200,0),cellposition,"sprites.png",30);

	boardObj->AddComponent(board);
	scene->Add(boardObj);

	
	auto Qbert = objectConstructors::Qbert(3);// qbert is 16 on 16 big on sprite sheet
	Qbert->GetComponent<RenderComponent>()->SetPosition(300, 200);
	Qbert->GetComponent<RenderComponent>()->SetTexture("sprites.png");
	Qbert->GetComponent<RenderComponent>()->SetSize(30, 30);
	Qbert->GetComponent<RenderComponent>()->SetOffset(-15,-40);
	
	
	auto SpriteManager = new SpriteComponent(Qbert->GetComponent<RenderComponent>(), SDL_Rect{ 0,0,16,16 }, 8, 1);
	SpriteManager->SetXSprite(4);
	SpriteManager->setYSprite(1);
	Qbert->AddComponent(SpriteManager);
	scene->Add(Qbert);



	
}
