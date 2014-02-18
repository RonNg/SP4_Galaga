#include "ippBulletClass.h"


ippBulletClass::ippBulletClass ( void )
{
	direction = Vec3D ( 0.0f, -1.0f, 0.0f );
}

ippBulletClass::ippBulletClass ( Vec3D position, Vec3D direction, float speed, int damage, float sizeX, float sizeY )
{
	this->position = position;
	this->direction = direction;
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

void ippBulletClass::Update ( void )
{
	position += direction * speed * Global::timedelta;
	projectile->SetXY ( position.x, position.y );
}

void ippBulletClass::Render ( void )
{
	projectile->DrawQuads ();
}