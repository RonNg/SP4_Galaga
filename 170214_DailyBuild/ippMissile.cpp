#include "ippMissile.h"


ippMissile::ippMissile(void)
{
}

ippMissile::ippMissile ( Vec3D position, Vec3D* tPosition, float speed, int damage, float sizeX, float sizeY )
{
	this->position = position;
	this->tPosition = tPosition;
	this->speed = speed;
	this->damage = damage;
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	projectile->SetLW ( sizeX, sizeY );
}

ippMissile::~ippMissile(void)
{
}

void ippMissile::Update ( void )
{
	/*position += direction * speed * Global::timedelta;*/
	projectile->SetXY ( position.x, position.y );
}

void ippMissile::Render ( void )
{
	projectile->DrawQuads ();
}