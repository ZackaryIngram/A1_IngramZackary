#include "States.h"
#include "StateManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Primitives.h"
#include "GameObject.h"
#include "Engine.h"
#include <iostream>
#include "Button.h"
#include "EventManager.h"
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
GameObject* State::GetGo(const std::string& s)
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
	m_objects.push_back(pair<string, GameObject*>("startBackground",
		new Image({ 0, 0, 1920, 1080 }, { 0, 0, 1024, 768 }, "startBackground")));
	m_objects.push_back(pair<string, GameObject*>("startBackground",
		new Image({ 0, 0, 700, 160 }, { 150, 300, 700, 200}, "title")));
	m_objects.push_back(pair<string, GameObject*>("start",
		new PlayButton({ 0, 0, 600, 200}, { 350, 600, 300, 100 }, "start")));
	SOMA::AllocateChannels(16);
	SOMA::SetMusicVolume(40);
	SOMA::PlayMusic("music", -1, 2000);
}

void TitleState::Update()
{
	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}
	

}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instace().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instace().GetRenderer());
	for (auto const& i : m_objects)
		i.second->Render();
	State::Render();
}

void TitleState::Exit()
{
	TEMA::UnLoad("play");
	TEMA::UnLoad("title");
	TEMA::UnLoad("bg");
	SOMA::StopMusic();
	SOMA::Unload("tbgm", SOUND_MUSIC);
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr; // ;)
	}
	
}//End of TitleState 

//Begin PauseState 
PauseState::PauseState()
{
	
}

void PauseState::Enter()
{
	cout << "Entering Pause State... " << endl;
}

void PauseState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_R))
		STMA::PopState();
	
}

void PauseState::Render()
{
	cout << "Rendering Pause State... " << endl;
	//First render the Gamestate
	STMA::GetStates().front()->Render();//invoke render of GameState
	//Now render rest of Pause state
	SDL_SetRenderDrawBlendMode(Engine::Instace().GetRenderer(),SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instace().GetRenderer(), 0, 0, 0, 128);
	State::Render();
}

void PauseState::Exit()
{
	cout << "Exiting Pause State... " << endl;
}
//End PauseState 

//Begin GameState
GameState::GameState() {}

void GameState::Enter()
{
	TEMA::Load("Img/pauseButton.png", "pause");
	m_objects.push_back(pair<string, GameObject*>("pause", new PauseButton({ 0,0,600,200 }, { 350,600,300,100 }, "pause")));

	m_pTexture = IMG_LoadTexture(Engine::Instace().GetRenderer(), "img/bobaShip.jpg");
	m_pBGTexture = IMG_LoadTexture(Engine::Instace().GetRenderer(), "img/gameBackground.png");
	m_pShootTexture = IMG_LoadTexture(Engine::Instace().GetRenderer(), "img/shoot.jpg");
	m_pEnemyTexture = IMG_LoadTexture(Engine::Instace().GetRenderer(), "img/Enemy.png");
	
	

	SOMA::Load("Aud/Shoot.mp3", "shoot",SOUND_SFX);
	SOMA::Load("Aud/Shoot.mp3", "enemyShoot", SOUND_SFX);
	SOMA::Load("Aud/exp.wav", "explosion", SOUND_SFX);
	SOMA::Load("Aud/GameStateMusic.mp3", "gameMusic", SOUND_MUSIC);
	SOMA::AllocateChannels(16);
	SOMA::SetMusicVolume(25);
	SOMA::SetSoundVolume(25);
	SOMA::PlayMusic("gameMusic", -1, 2000);


	m_player = { {0,m_srcy + m_srcHeight,m_srcWidth,m_srcHeight}, {0,384,m_dstWidth / 5,m_dstHeight / 5},{15,394,m_dstWidth / 5 - 15,m_dstHeight / 5 - 10} }; // First {} is src rectangle, and second {} destination rect
	m_shoot = { {0,0,146,72} };
	

	//srand(time(NULL));
	m_enemy = { {0,m_srcHeight * 3,m_srcWidth,m_srcHeight} };
	m_bg1 = { {0,0,1365,768},{0,0,1365,768} };
	m_bg2 = { {0,0,1365,768},{1365,0,1365,768} };
	m_enemy = { {0,0,95 / 3,96} };
	

	Mix_PlayMusic(m_bgm, -1); // 0-n for # of loops, or -1 for infinite looping.
	Mix_VolumeMusic(80); // 0-128.
	
}

void GameState::Update()
{
	if (EVMA::MousePressed(1))
	{
		m_bullet.push_back(new Bullet({ m_player.m_dst.x + 40, m_player.m_dst.y + 40 }));
		m_bullet.shrink_to_fit();
		cout << " New bullet vector capacity " << m_bullet.capacity() << endl;
		SOMA::PlaySound("shoot", 0, 15);
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_W) && m_player.m_dst.y > 0)
	{
		m_player.m_dst.y -= m_speed;
		m_player.m_playercoDst.y -= m_speed;
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_S) && m_player.m_dst.y < HEIGHT - m_player.m_dst.h)
	{
		m_player.m_dst.y += m_speed;
		m_player.m_playercoDst.y += 2*m_speed;
	}
	if (EVMA::KeyHeld(SDL_SCANCODE_A) && m_player.m_dst.x > 0)
	{
		m_player.m_dst.x -= m_speed;
		m_player.m_playercoDst.x -= m_speed;
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_D) && m_player.m_dst.x < WIDTH / 2 - m_player.m_dst.w)
	{
		m_player.m_dst.x += m_speed;
		m_player.m_playercoDst.x += m_speed;
	}
	
	if (EVMA::KeyPressed(SDL_SCANCODE_T))
		STMA::ChangeState(new TitleState());//Change to new TitleState
	else if (EVMA::KeyPressed(SDL_SCANCODE_P))
		STMA::PushState(new PauseState());

	// Scroll the background
	m_bg1.m_dst.x -= m_speed / 2;
	m_bg2.m_dst.x -= m_speed / 2;

	// Wrap the backgrounds/
	if (m_bg1.m_dst.x <= -m_bg1.m_dst.w)
	{
		m_bg1.m_dst.x = 0;
		m_bg2.m_dst.x = 1000;
	}

	//// Animation
	//m_time++;

	//if (FPS / m_time == 4)
	//{
	//	m_time = 0;
	//	m_player.m_src.x += m_srcWidth;
	//	if (m_player.m_src.x >= m_dstWidth)
	//		m_player.m_src.x = 0;

	//	m_enemy.m_src.x += m_srcWidth;
	//	if (m_enemy.m_src.x >= m_dstWidth)
	//		m_enemy.m_src.x = 0;

	//	m_bird1.m_src.x += 95 / 3;
	//	if (m_bird1.m_src.x >= 95 / 3 * 2)
	//		m_bird1.m_src.x = 0;

	//	m_bird2.m_src.x += 96 / 3;
	//	if (m_bird2.m_src.x >= 96 / 3 * 2)
	//		m_bird2.m_src.x = 0;

	//}

	

	// enemy movement
	m_timerE++;
	m_timerB++;
	if (m_timerE == 500)
	{
		m_enemyNumber.push_back(new Enemy({ 1024,(rand() % 540) }));
		m_enemyNumber.shrink_to_fit();
		cout << " New Enemy vector capacity " << m_enemyNumber.capacity() << endl;
		m_timerE = 0;
	}
	for (unsigned i = 0; i < m_enemyNumber.size(); i++) // size() is actual filled numbers of elements
	{
		m_enemyNumber[i]->UpdateEnemy();
	}

	// Enemy delete
	for (unsigned i = 0; i < m_enemyNumber.size(); i++) // size() is actual filled numbers of elements
	{
		if (m_enemyNumber[i]->GetRekt()->x < -100)
		{
			//m_enemy.m_dst.x = 1024;
			delete m_enemyNumber[i]; // flag for reallocation
			m_enemyNumber[i] = nullptr; // get rid of the dangling pointer
			m_enemyNumber.erase(m_enemyNumber.begin() + i);
			m_enemyNumber.shrink_to_fit();
			cout << " Enemy Deleted \n";

		}
	}
	
	// bird1 obstacles
	m_enemyTimer = rand() % 5 + 1;
	if (m_timerE == 200)
	{
		if (m_enemyTimer > 2)
		{
			m_enemyNumber.push_back(new Enemy({ (rand() % 50 + 1024), 100 }));
			m_enemyNumber.shrink_to_fit();
			cout << " New bird1 vector capacity " << m_enemyNumber.capacity() << endl;
		}
	}
	for (unsigned i = 0; i < m_enemyNumber.size(); i++) // size() is actual filled numbers of elements
	{
		m_enemyNumber[i]->UpdateEnemy();
	}
	for (unsigned i = 0; i < m_enemyNumber.size(); i++) // size() is actual filled numbers of elements
	{
		if (m_enemyNumber[i]->GetRekt()->x < -100)
		{
			//m_enemy.m_dst.x = 1024;
			delete m_enemyNumber[i]; // flag for reallocation
			m_enemyNumber[i] = nullptr; // get rid of the dangling pointer
			m_enemyNumber.erase(m_enemyNumber.begin() + i);
			m_enemyNumber.shrink_to_fit();
			cout << " Bird1 Deleted \n";

		}
	}
	

	// player Bullet
	for (unsigned i = 0; i < m_bullet.size(); i++) // size() is actual filled numbers of elements
	{
		//m_fireball.m_dst.x = m_player.m_dst.x + 40;

		m_bullet[i]->Update();
		//m_fireball.m_dst.x += 6;
	}//	 combines dereference and member accsess
	// check bullets going off screen


	for (unsigned i = 0; i < m_bullet.size(); i++) // size() is actual filled numbers of elements
	{

		if (m_bullet[i]->GetRekt()->x > WIDTH)
		{
			//m_fireball.m_dst.x = m_player.m_dst.x + 40;
			delete m_bullet[i]; // flag for reallocation
			m_bullet[i] = nullptr; // get rid of the dangling pointer
			m_bullet.erase(m_bullet.begin() + i);
			m_bullet.shrink_to_fit();
			cout << " Bullet Deleted \n";

			break;
		}
	}



	// player bullet to enemy collision
	for (unsigned i = 0; i < m_bullet.size(); i++)
	{
		for (unsigned a = 0; a < m_enemyNumber.size(); a++)
			if (SDL_HasIntersection(m_bullet[i]->GetRekt(), m_enemyNumber[a]->GetEnemycoRekt()))
			{
				cout << "Player bullet Collision!" << endl;
				SOMA::PlaySound("explosion", 0, 15);

				delete m_bullet[i]; // flag for reallocation
				m_bullet[i] = nullptr; // get rid of the dangling pointer
				m_bullet.erase(m_bullet.begin() + i);
				m_bullet.shrink_to_fit();
				cout << " Bullet Deleted \n";

				delete m_enemyNumber[a]; // flag for reallocation
				m_enemyNumber[a] = nullptr; // get rid of the dangling pointer
				m_enemyNumber.erase(m_enemyNumber.begin() + a);
				m_enemyNumber.shrink_to_fit();
				cout << " Enemy Deleted \n";
				m_eExploOn = true;
				m_counter++;
			}


	}
	// enemy bullet to player collision

	// enemy and player collision
	for (unsigned i = 0; i < m_enemyNumber.size(); i++)
	{
		if (SDL_HasIntersection(m_enemyNumber[i]->GetEnemycoRekt(), m_player.GetPlayercoDst()))
		{
		
			SOMA::PlaySound("explosion", 0, 15);

			cout << "Enemy and Player Collision!" << endl;


			cout << "Game Over" << endl;
			m_playerOn = false;
		//	m_pExploOn = true;
			m_plose = true;
		}
	}

	// tree collision

	//bird1 collision with player
	for (unsigned i = 0; i < m_enemyNumber.size(); i++)
	{
		if (SDL_HasIntersection(m_enemyNumber[i]->GetEnemycoRekt(), m_player.GetPlayercoDst()))
		{

			cout << "Bird1 Collision!" << endl;
			SOMA::PlaySound("explosion", 0, 15);

			cout << "Game Over" << endl;
			m_playerOn = false;
			m_pExploOn = true;
			m_plose = true;
			
		}
		
	}
	
	//if (m_plose == true )
	//{
	//	m_loseTimer++;

	//	if (m_loseTimer == 90)
	//	{
	//		STMA::ChangeState(new LoseState());//Change to new TitleState
	//		STMA::PopState();
	//	}
	//}


	
	
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instace().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instace().GetRenderer());

	// Background
	SDL_RenderCopy(Engine::Instace().GetRenderer(), m_pBGTexture, &m_bg2.m_src, &m_bg2.m_dst);
	SDL_RenderCopy(Engine::Instace().GetRenderer(), m_pBGTexture, &m_bg1.m_src, &m_bg1.m_dst);



	// Sprite
	if (m_playerOn == true)
	SDL_RenderCopy(Engine::Instace().GetRenderer(), m_pTexture, &m_player.m_src, &m_player.m_dst);

	// Enemy
	for (unsigned i = 0; i < m_enemyNumber.size(); i++) // size() is actual filled numbers of elements
		m_enemyNumber[i]->Render(Engine::Instace().GetRenderer(), m_pEnemyTexture, &m_enemy.m_src);

	//// Enemy
	//for (unsigned i = 0; i < m_enemyNumber.size(); i++) // size() is actual filled numbers of elements
	//	m_enemyNumber[i]->Render(Engine::Instace().GetRenderer(), m_pEnemyTexture, &m_enemy.m_src);

	// Bullet
	for (unsigned i = 0; i < m_bullet.size(); i++) // size() is actual filled numbers of elements
		m_bullet[i]->Render(Engine::Instace().GetRenderer(), m_pShootTexture, &m_shoot.m_src);

	TEMA::Load("Img/pauseButton.png", "pause");
	m_objects.push_back(pair<string, GameObject*>("pause", new PauseButton({ 0,0,600,200 }, { 350,600,300,100 }, "pause")));


	//SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_player.m_src, &m_player.m_dst, 90.0, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(Engine::Instace().GetRenderer()); // Flip buffers - send data to window.
	State::Render();

}

void GameState::Resume()
{
	cout << "Pausing GameState... " << endl;
}

void GameState::Exit()
{
	cout << "Cleaning engine..." << endl;
	for (unsigned i = 0; i < m_bullet.size(); i++) // size() is actual filled numbers of elements
	{
		delete m_bullet[i]; // flag for reallocation
		m_bullet[i] = nullptr; // get rid of the dangling pointer
	}

	for (unsigned i = 0; i < m_enemyNumber.size(); i++) // size() is actual filled numbers of elements
	{
		delete m_enemyNumber[i]; // flag for reallocation
		m_enemyNumber[i] = nullptr; // get rid of the dangling pointer
	}
	
	for (unsigned i = 0; i < m_enemyNumber.size(); i++) // size() is actual filled numbers of elements
	{
		delete m_enemyNumber[i]; // flag for reallocation
		m_enemyNumber[i] = nullptr; // get rid of the dangling pointer
	}


	m_bullet.clear();
	m_bullet.shrink_to_fit(); // reduces the capacity to size

	m_enemyNumber.clear();
	m_enemyNumber.shrink_to_fit(); // reduces the capacity to size

	m_enemyNumber.clear();
	m_enemyNumber.shrink_to_fit(); // reduces the capacity to size



	
	SDL_DestroyTexture(m_pTexture);
	SDL_DestroyTexture(m_pBGTexture);
	SDL_DestroyTexture(m_pEnemyTexture);
	SDL_DestroyTexture(m_pShootTexture);
	SDL_DestroyTexture(m_pEnemyTexture);
	
	SOMA::Unload("shoot",SOUND_SFX);
	SOMA::Unload("Eshoot", SOUND_SFX);
	SOMA::Unload("explosion", SOUND_SFX);
	SOMA::Unload("bgm", SOUND_MUSIC);
	SOMA::StopMusic();
	SOMA::Unload("bgm", SOUND_MUSIC);
	
	
}//End GameState 

//Begin Losestate 
LoseState::LoseState()
{
}

void LoseState::Enter()
{
	
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
}

void LoseState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instace().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instace().GetRenderer());
	for (auto const& i : m_objects)
		i.second->Render();
	State::Render();
}

void LoseState::Exit()
{
	TEMA::UnLoad("gover");
	SOMA::Unload("loseSound", SOUND_MUSIC);
	
}
//End LoseState 
