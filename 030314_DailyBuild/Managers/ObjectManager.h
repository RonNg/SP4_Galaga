#pragma once
#include "..\Singleton.h"
#include <list>
#include <string>
#include <vector>

class ippGameObject;


class ippObjectManager
	: public ippSingleton<ippObjectManager>
{
public:
	ippObjectManager(void);
	ippObjectManager( ippObjectManager const&); // Don't implement
	void operator= (ippObjectManager const&); // Don't implement

	//Contains all of the objects in the game world.
	std::vector<ippGameObject*> objects;

	ippGameObject* AddObj ( ippGameObject* obj );
	void DeleteObj ( ippGameObject* obj );

	void Init();
	void Update();
	void Render();


	ippGameObject* GetRandomObjByTag ( std::string tag );

	//Returns the number of enemies currently existing
	int GetNumberOfEnemy ();
	//Returns number of green enemies
	int GetNumberOfEnemyType (int type);

};

