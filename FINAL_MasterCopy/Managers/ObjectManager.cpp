#include "ObjectManager.h"
#include <algorithm>


#include "Entities\GameObject.h"
#include "Entities\AI\Enemy.h"

#include "Managers\CollisionManager.h"

ippObjectManager::ippObjectManager(void)
{
	srand(time(NULL));
}

ippGameObject* ippObjectManager::AddObj ( ippGameObject* obj )
{
	objects.push_back (obj);

	return objects.back();
}

void ippObjectManager::DeleteObj ( ippGameObject* obj )
{
	std::vector<ippGameObject*>::iterator itr = find(objects.begin(), objects.end(), obj );
	if ( itr != objects.end() )
	{
   		objects.erase(itr);
		delete obj;
		obj = NULL;
	}

}


ippGameObject* ippObjectManager::GetObj ( int index )
{
	if ( index <= objects.size() )
	{
		return objects.at(index);
	}
	return NULL;
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

ippGameObject* ippObjectManager::GetRandomObjByTag ( std::string tag )
{
	//Runs through to check if there is an Enemy in the entire vector list first ( safety )
	while ( true )
	{
		int randomNo =  rand () %  ( objects.size() );
		if ( objects[randomNo]->GetTag() == tag )
		{
			return objects[randomNo];
		}
	}
	return NULL;
}
int ippObjectManager::GetNumberOfEnemy ()
{
	int enemyNo = 0;
	std::vector<ippGameObject*>::iterator itr;

	for ( itr = objects.begin(); itr != objects.end(); ++ itr ) 
	{
		if ( (*itr)->GetTag().compare ( "Enemy" ) == 0 )
		{
			 enemyNo ++;
		}
	}
	return enemyNo;
}

int ippObjectManager::GetNumberOfEnemyType ( int type )
{
	int enemyNo = 0;

	std::vector<ippGameObject*>::iterator itr;

	for ( itr = objects.begin(); itr != objects.end(); ++ itr )
	{
		ippEnemy* temp = static_cast<ippEnemy*>( (*itr) );
		if ( temp->GetType() == type )
		{
			++ enemyNo;
		}
 	}

	return enemyNo;
}