#include "ippBulletClass.h"


ippBulletClass::ippBulletClass ( void )
{
	direction = Vec3D ( 0.0f, -1.0f, 0.0f );
}

ippBulletClass::ippBulletClass ( float speed, int damage, float sizeX, float sizeY )
{
	alive = false;
	this->speed = speed;
	this->damage = damage;
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	projectile = new ippQuadClass ();

	projectile->SetLW ( sizeX, sizeY );
}

ippBulletClass::~ippBulletClass ( void )
{
}

void ippBulletClass::SetRendered ( bool alive )
{
	this->alive = alive;
}

void ippBulletClass::SetPosition ( Vec3D position )
{
	this->position = position;
}

void ippBulletClass::SetDirection ( Vec3D direction )
{
	this->direction = direction;
}

void ippBulletClass::Update ( void )
{
	position += direction * speed * Global::timedelta;
	projectile->SetXY ( position.x, position.y );
}

void ippBulletClass::Render ( void )
{
	projectile->DrawQuads ();
}