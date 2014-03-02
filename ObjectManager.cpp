#include "ObjectManager.h"
#include <algorithm>


#include "Entities\GameObject.h"
#include "Entities\AI\Enemy.h"

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

void ippObjectManager::Init()
{
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
		(*itr)->Debug_RenderCollider2D();
	}
}

ippGameObject* ippObjectManager::GetRandomObjByTag ( std::string tag )
{
	if ( tag == "Enemy" )
	{
		//Runs through to check if there is an Enemy in the entire vector list first ( safety )
		if ( GetNumberOfEnemy() > 0 )
		{
			while ( true )
			{
				int randomNo =  rand () %  ( objects.size() );
				if ( objects[randomNo]->GetTag() == "Enemy" )
				{
					return objects[randomNo];
				}
			}
		}
		else
		{
			return NULL;
		}
	}
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