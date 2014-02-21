#include "ObjectManager.h"
#include <algorithm>

#include "Entities\GameObject.h"



ippObjectManager::ippObjectManager(void)
{
}

void ippObjectManager::AddObj ( ippGameObject* obj )
{
	objects.push_back (obj);
}

ippGameObject* ippObjectManager::DeleteObj ( ippGameObject* obj )
{
	std::vector<ippGameObject*>::iterator itr = find(objects.begin(), objects.end(), obj );
	if ( itr != objects.end() )
	{
		delete (*itr);
		objects.erase(itr);
		
		return NULL;
	}
}

void ippObjectManager::Init()
{
	/*for ( int i = 0; i < objects.size(); i ++ )
	{
		objects.at(i)->Init();
	}*/
}

void ippObjectManager::Update()
{
	std::vector<ippGameObject*>::iterator itr;

	for ( itr = objects.begin(); itr != objects.end(); ++ itr )
	{
		(*itr)->Update();
	}
}

void ippObjectManager::Render()
{
	std::vector<ippGameObject*>::iterator itr;

	for ( itr = objects.begin(); itr != objects.end(); ++ itr )
	{
		(*itr)->Render();
	}
}

