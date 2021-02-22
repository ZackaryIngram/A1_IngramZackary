#include "States.h"
#include "StateManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Primitive.h"
#include "GameObject.h"
#include "Engine.h"
#include "Button.h"
#include "EventManager.h"
#include <iostream>

#define WIDTH 1024
#define HEIGHT 768
#define FPS 60
#define BGSCROLL 2 
#define PSPEED 6

using namespace std;


void State::Render()
{
	SDL_RenderPresent(Engine::Instace().GetRenderer());
}

void State::Resume(){}
GameObject* State::GetGameobject(const std::string& s)
{ 
	auto it = std::find_if(m_objects.begin(), m_objects.end(),
		[&](const std::pair<std::string, GameObject*>& element)
		{
			return element.first == s;
		});
	if (it != m_objects.end())
		return it->second;
	else return nullptr;
}

auto State::GetIt(const std::string& s)
{
	auto it = std::find_if(m_objects.begin(), m_objects.end(),
		[&](const std::pair<std::string, GameObject*>& element)
		{
			return element.first == s;
		});
	return it;
}
//Begin TitleState 
TitleState::TitleState(){}

void TitleState::Enter()
{
	TEMA::Load("Img/Start.png", "start");
	TEMA::Load("Img/titleLogo.png", "title");
	TEMA::Load("Img/titleScreen.jpg", "startBackground");
	SOMA::Load("Aud/starWarsTheme.mp3", "music", SOUND_MUSIC);

	m_objects.push_back(pair<string, GameObject*>("startBackground", new Image({ 0, 0, 1920, 1080 }, { 0, 0, 1024, 768 }, "startBackground")));

	m_objects.push_back(pair<string, GameObject*>("startBackground", new Image({ 0, 0, 700, 160 }, { 150, 300, 700, 200}, "title")));

	m_objects.push_back(pair<string, GameObject*>("start", new PlayButton({ 0, 0, 600, 200}, { 350, 600, 300, 100 }, "start")));

	SOMA::AllocateChannels(16);
	SOMA::SetMusicVolume(40);
	SOMA::PlayMusic("music", -1, 2000);
}

void TitleState::Update()
{
	for (auto const& t : m_objects)
	{
		t.second->Update();
		if (STMA::StateChanging()) return;
	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instace().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instace().GetRenderer());
	for (auto const& t : m_objects)
		t.second->Render();
	State::Render();
}

void TitleState::Exit()
{
	
	TEMA::UnLoad("title");
	
	SOMA::StopMusic();
	
	for (auto& t : m_objects)
	{
		delete t.second;
		t.second = nullptr; // ;)
	}
	
}
//End of TitleState 

//Begin GameState
GameState::GameState() = default;

void GameState::Enter()
{
	TEMA::Load("img/pauseButton.png", "pause");
	TEMA::Load("img/rules.jpg", "rules");

	m_objects.push_back(pair<string, GameObject*>("pause", new PauseButton({ 0,0,600,200 }, { 350,600,300,100 }, "pause")));
	m_pTexture = IMG_LoadTexture(Engine::Instace().GetRenderer(), "img/bobaShip.jpg");
	m_pBGTexture = IMG_LoadTexture(Engine::Instace().GetRenderer(), "img/gameBackground.png");
	m_pEnemyTexture = IMG_LoadTexture(Engine::Instace().GetRenderer(), "img/Enemy.png");
	m_pRules = IMG_LoadTexture(Engine::Instace().GetRenderer(), "img/rules.jpg"); 


	m_player = { {150, 300, 300, 200,}, { 120, 300, 400, 500} }; //Not sure why this doesnt work either 

	m_enemy = { {0,m_srcHeight * 3,m_srcWidth,m_srcHeight} };
	m_bg1 = { {0,0,1375,780},{0,0,1375,780} };
	m_bg2 = { {0,0,1375,780},{1365,0,1375,780} };
	m_enemy = { {0,0,95 / 3,96} };
	SOMA::Load("Aud/GameStateMusic.mp3", "gameMusic", SOUND_MUSIC);
	SOMA::AllocateChannels(16);
	SOMA::SetMusicVolume(25);
	SOMA::SetSoundVolume(25);
	SOMA::PlayMusic("gameMusic", -1, 2000);

	
	
	Mix_PlayMusic(m_backgroundMusic, -1); 
	Mix_VolumeMusic(80); 
}

void GameState::Update()
{
	
	if (EVMA::KeyHeld(SDL_SCANCODE_W) && m_player.m_dst.y > 0)
	{
		m_player.m_dst.y -= m_speed;
		m_player.m_playerDst.y -= m_speed;
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_S) && m_player.m_dst.y < HEIGHT - m_player.m_dst.h)
	{
		m_player.m_dst.y += m_speed;
		m_player.m_playerDst.y += m_speed;
	}
	if (EVMA::KeyHeld(SDL_SCANCODE_A) && m_player.m_dst.x > 0)
	{
		m_player.m_dst.x -= m_speed;
		m_player.m_playerDst.x -= m_speed;
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_D) && m_player.m_dst.x < WIDTH - m_player.m_dst.w)
	{
		m_player.m_dst.x += m_speed;
		m_player.m_playerDst.x += m_speed;
	}
	
	if (EVMA::KeyPressed(SDL_SCANCODE_T)) STMA::ChangeState(new TitleState());//Change to TitleState
	else if (EVMA::KeyPressed(SDL_SCANCODE_P)) STMA::PushState(new PauseState());// Change to PauseState

	//Scroll the background
	m_bg1.m_dst.x -= m_speed / 2;
	m_bg2.m_dst.x -= m_speed / 2;
	
	//Wrap Background
	if (m_bg1.m_dst.x <= -m_bg1.m_dst.w)
	{
		m_bg1.m_dst.x = 0;
		m_bg2.m_dst.x = 1000;
	}
	
	//(Also not sure why this idesnt working)
	m_enemyTimer = rand() % 5 + 1;
	if (m_timerE == 200)
	{
		m_enemyNumber.push_back(new Enemy({ 1024,(rand() % 540) }));
		m_enemyNumber.shrink_to_fit();
		cout << " New Enemy vector capacity: " << m_enemyNumber.capacity() << endl;
		m_timerE = 0;
	}
	for (unsigned i = 0; i < m_enemyNumber.size(); i++) 
	{
		m_enemyNumber[i]->UpdateEnemy();
	}

	// Delete Enemy
	for (unsigned i = 0; i < m_enemyNumber.size(); i++) 
	{
		if (m_enemyNumber[i]->GetRekt()->x < -100)
		{
			
			delete m_enemyNumber[i]; 
			m_enemyNumber[i] = nullptr; 
			m_enemyNumber.erase(m_enemyNumber.begin() + i);
			m_enemyNumber.shrink_to_fit();
			cout << " Enemy Deleted..." << endl;

		}
	}
	
	// Enemy obstacles
	m_enemyTimer = rand() % 5 + 1;
	if (m_timerE == 200)
	{
		if (m_enemyTimer > 2)
		{
			m_enemyNumber.push_back(new Enemy({ (rand() % 50 + 1024), 100 }));
			m_enemyNumber.shrink_to_fit();
			cout << " New enemy vector capacity: " << m_enemyNumber.capacity() << endl;
		}
	}
	for (unsigned i = 0; i < m_enemyNumber.size(); i++) 
	{
		m_enemyNumber[i]->UpdateEnemy();
	}
	//Delete Enemy
	for (unsigned i = 0; i < m_enemyNumber.size(); i++) 
	{
		if (m_enemyNumber[i]->GetRekt()->x < -100)
		{
			delete m_enemyNumber[i]; 
			m_enemyNumber[i] = nullptr; 
			m_enemyNumber.erase(m_enemyNumber.begin() + i);
			m_enemyNumber.shrink_to_fit();
			cout << " Enemy Deleted..." << endl;
		}
	}
	
	// Enemy/Player Collision
	for (unsigned i = 0; i < m_enemyNumber.size(); i++)
	{
		if (SDL_HasIntersection(m_enemyNumber[i]->GetEnemycoRekt(), m_player.GetPlayerDst()))
		{
			cout << "Enemy/Player Collision!" << endl;
			m_plose = true;
		}
	}

	if(EVMA::KeyPressed(SDL_SCANCODE_P)) STMA::ChangeState(new PauseState()); // Changes to pause state
	if (EVMA::KeyPressed(SDL_SCANCODE_L)) STMA::ChangeState(new LoseState()); // Changes to lose state
	
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instace().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instace().GetRenderer());

	// Background
	SDL_RenderCopy(Engine::Instace().GetRenderer(), m_pBGTexture, &m_bg2.m_src, &m_bg2.m_dst);
	SDL_RenderCopy(Engine::Instace().GetRenderer(), m_pBGTexture, &m_bg1.m_src, &m_bg1.m_dst);

	// Sprite
	if (m_playerSpawned == true)
	{
		SDL_RenderCopy(Engine::Instace().GetRenderer(), m_pTexture, &m_player.m_src, &m_player.m_dst);
	}
	// Enemy
	for (unsigned i = 0; i < m_enemyNumber.size(); i++)
	{
		m_enemyNumber[i]->Render(Engine::Instace().GetRenderer(), m_pEnemyTexture, &m_enemy.m_src);
	}

	SDL_RenderPresent(Engine::Instace().GetRenderer()); 
	State::Render();

}

void GameState::Resume()
{
	cout << "Resuming GameState... " << endl;
}

void GameState::Exit()
{
	cout << "Cleaning engine..." << endl;

	for (unsigned i = 0; i < m_enemyNumber.size(); i++) 
	{
		delete m_enemyNumber[i]; 
		m_enemyNumber[i] = nullptr; 
	}
	
	for (unsigned i = 0; i < m_enemyNumber.size(); i++) 
	{
		delete m_enemyNumber[i]; 
		m_enemyNumber[i] = nullptr; 
	}

	m_enemyNumber.clear();
	m_enemyNumber.shrink_to_fit(); 

	SDL_DestroyTexture(m_pTexture);
	SDL_DestroyTexture(m_pBGTexture);
	SDL_DestroyTexture(m_pEnemyTexture);
	
	
}
//End GameState 

//Begin Losestate 
LoseState::LoseState() = default;

void LoseState::Enter()
{
	cout << "Lose State" << endl;
	TEMA::Load("Img/gameOverBackground.jpg", "lose");
	SOMA::Load("Aud/loseStateSound.mp3", "loseSound", SOUND_MUSIC);
	m_objects.push_back(pair<string, GameObject*>("lose",
		new Image({ 0, 0, 1920, 1080 }, { 0, 0, 1024, 768 }, "lose")));
}

void LoseState::Update()
{
	
	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}
	if (EVMA::KeyPressed(SDL_SCANCODE_T)) STMA::ChangeState(new TitleState());//Change to TitleState
}

void LoseState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instace().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instace().GetRenderer());
	for (auto const& i : m_objects) i.second->Render();
	State::Render();
}

void LoseState::Exit()
{
	SOMA::Unload("loseSound", SOUND_MUSIC);
}
//End LoseState 

//Begin PauseState 
PauseState::PauseState() = default;

void PauseState::Enter()
{
	cout << "Entering Pause State... " << endl;
	m_pPBGTexture = IMG_LoadTexture(Engine::Instace().GetRenderer(), "img/pausedBg.jpg"); //Not sure why this doesnt work
}

void PauseState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_R)) STMA::PopState(); //Press R to resume, and P to Pause

}

void PauseState::Render()
{

	cout << "Rendering Pause State... " << endl;
	//Render Gamestate
	STMA::GetStates().front()->Render();
	//Render PauseState
	SDL_SetRenderDrawBlendMode(Engine::Instace().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instace().GetRenderer(), 0, 0, 0, 128);
	State::Render();
}

void PauseState::Exit()
{
	cout << "Exiting Pause State... " << endl;
}
//End PauseState 