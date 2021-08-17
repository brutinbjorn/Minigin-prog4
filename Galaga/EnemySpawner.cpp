#include "EnemySpawner.h"

#include <nlohmann/json.hpp>



#include "ActorComponent.h"
#include "BeeComponent.h"
#include "BezierMoveComponent.h"
#include "GalagaConstructor.h"
#include "JsonManager.h"
#include "Scene.h"


namespace  ns
{
	struct wave
	{
		int id;
		int cells[8];
	};
}


EnemySpawner::EnemySpawner(glm::vec2 startCenterPos, glm::vec2 SizeOfEnemy, glm::vec2 WindowSize, const std::string& file)
	: m_SizeOfEnemy(SizeOfEnemy)
	, m_GameSize(WindowSize)
	, m_RunSpawnLoop(false)
	, m_HasSpawnedCount(0)
	, m_ToSpawn(8)
{
	for (int height = -2; height <= 2; height++) //up to and 2
	{
		for (int witdh = -5; witdh < 5; witdh++) // up to 5
		{
			GridPos ToAdd;

			ToAdd.arrayPos = glm::ivec2(witdh, height);
			ToAdd.screenPos = glm::vec2(
				(SizeOfEnemy.x / 2) + SizeOfEnemy.x * witdh,
				SizeOfEnemy.y * height) + startCenterPos;

			m_Gridpositions.push_back(ToAdd);
		}
	}

	nlohmann::json j = JsonManager::GetInstance().LoadJsonDoc(file);

	nlohmann::json jAr = j["Waves"];
	for (nlohmann::json::iterator it = jAr.begin(); it != jAr.end(); ++it)
	{

		nlohmann::json jPoints = it.value()["Bazier"];
		std::vector<glm::vec2> NewBazierPoints;
		for (nlohmann::json::iterator it2 = jPoints.begin(); it2 != jPoints.end(); ++it2)
		{
			if(it->is_object())
			{
				nlohmann::json ob = it2.value();
				
				glm::vec2 BazierPos;
				BazierPos.x = float(ob["x"].get<int>());// get_to(BazierPos.y);
				BazierPos.y = float(ob["y"].get<int>());// get_to(BazierPos.y);
				NewBazierPoints.push_back(BazierPos);
			}
		}
		m_BaziersPoints.push_back(NewBazierPoints);

		
	// get the Positions where enemy have to go to
		std::vector<int> integerWave;
		std::cout << *it << std::endl;

		nlohmann::json jCells = it.value()["Cells"];
		for (nlohmann::json::iterator it2 = jCells.begin(); it2 != jCells.end(); ++it2)
		{
			integerWave.push_back(it2->get<int>());
		}

		std::vector<GridPos> GridWave;
		for (int i = 0; i < integerWave.size(); i++)
			GridWave.push_back(m_Gridpositions[integerWave[i]]);
		m_Waves.push_back(GridWave);	
	}

	for (int Baziers = 0; Baziers < m_BaziersPoints.size(); Baziers++)
	{
		std::vector<glm::vec2> newPath;
		for (int segments = 0; segments <= 20; segments++)
		{
			
			m_CurrentBridges = m_BaziersPoints[Baziers];
			glm::vec2 newpoint = CalculateBridges(segments, 20);
			
			newPath.push_back(newpoint);
			
		}
		m_BazierPaths.push_back(newPath);
	}
	
}

void EnemySpawner::Update(const float DeltaTime)
{

	if (m_RunSpawnLoop) // if is spawning
	{
		//if not finished spawning enemys of the current wave
		if (m_HasSpawnedCount < m_ToSpawn)
		{
			m_ELapsedSpawnDelay += DeltaTime; // add delay to to spawn;
			if (m_ELapsedSpawnDelay > m_SpawnDelay) // treshhold reached
			{


				auto &pos = m_Waves[m_CurrentWave][m_HasSpawnedCount];
				m_ELapsedSpawnDelay -= m_SpawnDelay;


				
				std::shared_ptr<dae::GameObject> newOb;
				
				if (pos.arrayPos.y == -2)
				{
					 newOb = objectConstructors::BeeEnemy("Galaga/BossGalaga.png", glm::ivec2(m_GameSize.x / 2, 0));
				}
				else if(pos.arrayPos.y <= 0)
				{
					newOb = objectConstructors::BeeEnemy("Galaga/butterfly.png", glm::ivec2(m_GameSize.x / 2, 0));		
				}
				else
				{
					newOb = objectConstructors::BeeEnemy("Galaga/bee.png", glm::ivec2(m_GameSize.x / 2, 0));
				}
				//spawn Enemy

				auto scene = dae::SceneManager::GetInstance().GetActiveScene();

				scene->AddInRun(newOb);
			
				newOb->GetComponent<BeeComponent>()->SetScreenPosition(m_Waves[m_CurrentWave][m_HasSpawnedCount]);
				newOb->GetComponent<BeeComponent>()->BindEnemySpawnerComp(this);
				newOb->GetComponent<BeeComponent>()->SetBazierID(m_CurrentWave);
				// Set Position on the grid7
				m_HasSpawnedCount++;
			}
			
		} 
		else // spawned all of wave
		{
			if (m_CurrentWave == m_Waves.size() - 1) // if al waves spawend: stop
			{
				m_RunSpawnLoop = false;
			}
			
			m_ElapsedNextWave += DeltaTime; // add for delay between spawn.
			if (m_ElapsedNextWave >= m_NextWaveDelay) // reset data and go to next wave;
			{
				m_HasSpawnedCount = 0;
				m_ElapsedNextWave = 0.f;
				m_ELapsedSpawnDelay = 0.f;
				
				m_CurrentWave++; 
			}
		}
		
	}


	
}

void EnemySpawner::SpawnEnemys()
{

	m_RunSpawnLoop = true;
	m_HasSpawnedCount = 0;	
}


glm::vec2 EnemySpawner::CalculateBridges(int currentSegment, int MaxSegments)
{
	if (currentSegment > MaxSegments)
	{
		currentSegment = MaxSegments;
	}
	
	float devision = static_cast<float>(currentSegment) / MaxSegments;
	
	devision = std::clamp(devision, 0.f, 1.f);

	if (m_CurrentBridges.size() == 2)
	{
		glm::vec2 point = (1 - devision) * m_CurrentBridges[0] + devision * m_CurrentBridges[1];
		return point;
	}
	else
	{
		for (int i = 0; i < m_CurrentBridges.size() - 1; i++)
		{
			m_NewBridges.push_back((1 - devision) * m_CurrentBridges[i] + devision * m_CurrentBridges[i + 1]);
		}
		m_CurrentBridges = m_NewBridges;
		m_NewBridges.clear();
		
		return CalculateBridges(currentSegment,MaxSegments);
	}
	
}
