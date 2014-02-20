#include "ippWeaponClass.h"


ippWeaponClass::ippWeaponClass ( void )
	:speed ( 0 )
	,damage ( 0 )
	,sizeX ( 0 )
	,sizeY ( 0 )
{
	projectile = new ippQuadClass ();
}


ippWeaponClass::~ippWeaponClass ( void )
{
	delete projectile;
}

int ippWeaponClass::GetDamage ( void )
{
	return damage;
}