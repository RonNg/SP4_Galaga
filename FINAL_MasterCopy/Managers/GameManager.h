#pragma once
#include "Singleton.h"
#include "Vec3D.h"
#include <vector>
#include "irrKlang.h"
using namespace irrklang;



// Lua scripting
extern "C" 
{
#include "LUA\lua.h"
#include "LUA\lualib.h"
#include "LUA\lauxlib.h"
}

class ippEnemySpawner;
class ippEnemyGrid;
class ippBullet;
class ippShip;
class GameUI;

class ippPowerUpManager;
class ippStarManager;

class ippGameManager
	: public ippSingleton<ippGameManager>
{
public:
	enum gameState_t 
	{		
		PLAY= 0,
		SPLASH,
		MENU,
		SHOP,
		PAUSE,
		GAME_OVER
	};
private:

	bool loadFinish; // a boolean that makes sure load level runs only once
	std::vector<ippEnemySpawner*>spawnerList;
	ippEnemyGrid* theGrid;

	float prevTime;
	float attackPrevTime;

	//Enemy Count
	int greenNo;
	int redNo;
	int blueNo;
	int totalNo;

	//FOR RANDOM GENERATION OF LEVELS
	/*
	========================
	
	When spawners spawn enemies, they must deduct from this pool 
	Safeguard in case of over spawning.
	This pool is reset after every wave.

	The number of enemies in this pool available is as follow
	Green = 4;
	Red = 16;
	Blue = 20;

	Total = 50 enemies at any one wave.
	========================
	*/
	int greenPool;
	int redPool;
	int bluePool; 

	bool waveDisplay; // boolean that toggles wave number display
	float prevDisplay;
	int waveNo; // Current wave number
	

	//Garbage collector interval
	float gcPrevTime;

	/*
	========================
	Game User Interface Section
	========================
	*/
	
	GameUI*					theGameUI;
	char*					command;

	ISound*					Sound_ThemeSong;
	ISound*					Sound_BGM;
	ISound*					Sound_EnemyDeath;

	gameState_t				gameState;
	bool playOnce;
	bool startGame;
	bool enableShoot;

	ippShip*				playerShip;
	ippPowerUpManager*		powerupManager;
	ippStarManager*			starManager;



public:
	ippGameManager(void);
	~ippGameManager(void);

	void Init ();
	void Init_GameUI ();
	void Init_SaveManager ();
	void Init_Enemies();

	void Update();
	void Update_Game();
	void Update_Menu();

	void Render ();

	void IO_Handler();

	void SpawnerLoad ( int index );
	
	void LoadLevel ();
	void LoadPreset_1 ( int difficulty );
	void LoadPreset_2( int difficulty );
	void LoadPreset_3( int difficulty );
	void TestPreset();

	std::vector<ippBullet*> enemyBulletList;
	int bulletIndex, bufferSize;
	void FireBullet ( Vec3D position, Vec3D direction );

	void Reset(); // Reset everything to prepare for next wave
	void Reset_Game();
	void Spawn ();

	void DeleteFlagged();
	void DeleteOutOfScreen();
	void WipeEnemyFromExistence();


	int	highscore; // High score of the current game

	// SHOP STATS
	int shipSpeed;
	int shipEvasion;

	int bulletSpeed;
	int bulletLevel;
	bool startgame;
	int missileSpeed;
	int missileTurnSpeed;

	int droneFireRate;


};

