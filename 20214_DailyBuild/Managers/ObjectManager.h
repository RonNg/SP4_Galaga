#pragma once
#include "..\Singleton.h"
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

	void AddObj ( ippGameObject* obj );
	ippGameObject* DeleteObj ( ippGameObject* obj );

	void Init();
	void Update();
	void Render();
};

