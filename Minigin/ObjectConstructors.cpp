#include "MiniginPCH.h"
#include "ObjectConstructors.h"

#include "HealthBarComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "ActorComponent.h"
#include "ScoreComponent.h"

std::shared_ptr<dae::GameObject> objectConstructors::TextObject(const std::string& file, unsigned int size,
                                                                const std::string& text, float Xpos, float Ypos )
{
	auto textObject = std::make_shared<dae::GameObject>();
	RenderComponent* textRenderComp = new RenderComponent;
	textRenderComp->SetPosition(Xpos, Ypos);

	auto font3 = dae::ResourceManager::GetInstance().LoadFont(file, size);
	dae::TextComponent* textComp = new dae::TextComponent(text, font3, textRenderComp);
	textObject->AddComponent(textRenderComp);
	textObject->AddComponent(textComp);
	
	return textObject;
}

std::shared_ptr<dae::GameObject> objectConstructors::RenderObject(const std::string& TexturePath
 ,  float Xpos ,  float Ypos )
{
	auto newObject = std::make_shared<dae::GameObject>();
	RenderComponent* rendercomp = new RenderComponent;
	rendercomp->SetTexture(TexturePath);
	rendercomp->SetPosition(Xpos, Ypos);
	newObject->AddComponent(rendercomp);
	return newObject;
}



std::shared_ptr<dae::GameObject> objectConstructors::LivesBar(const std::string& TexturePath,
	float Xpos, float Ypos,int lives)
{

	auto newObject = std::make_shared<dae::GameObject>();
	HealthComponent* health = new HealthComponent(lives);
	newObject->AddComponent(health);
	
	HealthBarComponent* healthBar = new HealthBarComponent(health);
	healthBar->SetTexture(TexturePath);
	healthBar->SetPosition(Xpos, Ypos);
	newObject->AddComponent(healthBar);
	
	return newObject;
}


//creates HealthComp, ActorComp,RenderComp, and binds render to actor.
std::shared_ptr<dae::GameObject> objectConstructors::BasicActor()
{
	auto newObject = std::make_shared<dae::GameObject>();

	// new qbert
	ActorComponent* qbertcomp = new ActorComponent();
	newObject->AddComponent(qbertcomp);
	// end qbert

	//render
	RenderComponent* renderComp = new RenderComponent();
	newObject->AddComponent(renderComp);
	
	qbertcomp->BindRenderComponent(renderComp);
	// end render
	return newObject;
	
}

std::shared_ptr<dae::GameObject> objectConstructors::Score(const std::string& file, unsigned int size, const std::string& text, float Xpos, float Ypos)
{

	auto newObject = TextObject(file, size, text, Xpos, Ypos);

	auto textcomp = newObject->GetComponent<dae::TextComponent>();

	ScoreComponent* newScore = new ScoreComponent(textcomp);
	newObject->AddComponent(newScore);

	return newObject;
	
}
