#include "ObjectManager.h"
#include <algorithm>

#include "Entities\GameObject.h"



ippObjectManager::ippObjectManager(void)
{
}

ippGameObject* ippObjectManager::AddObj ( ippGameObject* obj )
{
	objects.push_back (obj);

	return objects.back();
}

void ippObjectManager::DeleteObj ( ippGameObject* obj )
{
	std::list<ippGameObject*>::iterator itr = find(objects.begin(), objects.end(), obj );
	if ( itr != objects.end() )
	{
   		objects.erase(itr);
		delete obj;
		obj = NULL;
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
	std::list<ippGameObject*>::iterator itr;

	for ( itr = objects.begin(); itr != objects.end(); ++ itr )
	{
		(*itr)->Update();
	}
}

void ippObjectManager::Render()
{
	std::list<ippGameObject*>::iterator itr;

	for ( itr = objects.begin(); itr != objects.end(); ++ itr )
	{
		(*itr)->Render();
		(*itr)->Debug_RenderCollider2D();
	}
}

int ippObjectManager::GetNumberOfEnemy ()
{
	int enemyNo = 0;
	std::list<ippGameObject*>::iterator itr;

	for ( itr = objects.begin(); itr != objects.end(); ++ itr ) 
	{
		if ( (*itr)->GetTag().compare ( "Enemy" ) == 0 )
		{
			 enemyNo ++;
		}
	}
	return enemyNo;

}

