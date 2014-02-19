#include "Vec3D.h"

//Default Constructor
Vec3D::Vec3D()
:x(0),
 y(0),
 z(0)
{
}

//User-defined Constructor
Vec3D::Vec3D(float x, float y, float z)
:x(x),
 y(y),
 z(z)
{
}

Vec3D::~Vec3D()
{
}

Vec3D::Vec3D (const Vec3D & vectorSource)
{
	x = vectorSource.x;
	y = vectorSource.y;
	z = vectorSource.z;
}

Vec3D Vec3D::operator= (Vec3D & vector2)
{
	//Checks for self-assignment
	if (this == &vector2) //If current obj's memory location same as vector2
        return *this;

	x = vector2.x;
	y = vector2.y;
	z = vector2.z;
	
	return *this;
}

Vec3D Vec3D::operator+ (Vec3D & vector2)
{
	Vec3D tempVec;

	tempVec.x = x + vector2.x;
	tempVec.y = y + vector2.y;
	tempVec.z = z + vector2.z;

	return tempVec;
}

Vec3D Vec3D::operator+= (Vec3D & vector2)
{
	*this = *this + vector2;

	return *this;
}

Vec3D Vec3D::operator- (Vec3D & vector2)
{
	Vec3D tempVec;

	tempVec.x = x - vector2.x;
	tempVec.y = y - vector2.y;
	tempVec.z = z - vector2.z;

	return tempVec;
}

//Scalar Multiplication
Vec3D Vec3D::operator* (float scalar)
{
	Vec3D tempVec;

	tempVec.x = x * scalar;
	tempVec.y = y * scalar;
	tempVec.z = z * scalar;

	return tempVec;
}
//Dot product
float Vec3D::operator* (Vec3D & vector2)
{
	float dot_product = x * vector2.x + y * vector2.y + z * vector2.z;
	
	return dot_product;
}

//Scalar division
Vec3D Vec3D::operator/ (float scalar)
{
	Vec3D tempVec;

	tempVec.x = x / scalar;
	tempVec.y = y / scalar;
	tempVec.z = z / scalar;

	return tempVec;
}

//calculate and return cross product
Vec3D Vec3D::crossVec3D(const Vec3D &vec)
{
	//(a)[0] = (b)[1] * (c)[2] - (c)[1] * (b)[2]; \
	//(a)[1] = (b)[2] * (c)[0] - (c)[2] * (b)[0]; \
	//(a)[2] = (b)[0] * (c)[1] - (c)[0] * (b)[1];

	return Vec3D(y * vec.z - vec.y  * z,
				 z * vec.x - vec.z * x,
				 x * vec.y - vec.x * y);
}


//Cross Product
Vec3D Vec3D::operator^ (Vec3D & vector2)
{
	return Vec3D(y * vector2.z - vector2.y  * z,
		z * vector2.x - vector2.z * x,
		x * vector2.y - vector2.x * y);
}

bool Vec3D::operator!= ( Vec3D v)
{

	return (x != v.x || x != v.y || z != v.z);
} 

//Angle between two vectors
float Vec3D::AngleBetweenTwoVector (Vec3D & vector2)
{
	float angle;

	angle = acos(((*this) * vector2)/((*this).GetMagnitude() * vector2.GetMagnitude())) * 180/PI;
	return angle;
}


///////////////////////////////
////	Vector Functions   ////
///////////////////////////////
void Vec3D::Set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vec3D::GetMagnitude(void)
{
	float magnitude;
	magnitude = sqrt(x * x + y * y + z * z);
	return magnitude;
}


Vec3D Vec3D::GetNormalize ( void )
{
	Vec3D tempVec;
	tempVec = *this;

	float d = (sqrt((tempVec.x*tempVec.x) + 
				    (tempVec.y*tempVec.y) + 
					(tempVec.z*tempVec.z)));

	tempVec.x = (tempVec.x / d);
	tempVec.y = (tempVec.y / d);
	tempVec.z = (tempVec.z / d);

	return tempVec;
}

void Vec3D::Normalize (void)
{
	float d = (sqrt((x*x) + (y*y) + (z*z)));
	x = (x / d);
	y = (y / d);
	z = (z / d);
}

void Vec3D::Rotate2D( const float angle, bool normalize )
{
	float px = 0;
	float py = 0;

	px = ( x * cos(angle * PI/180 )) - ( y * sin(angle * PI/180));
	py = ( y * cos(angle * PI/180 )) + ( x * sin(angle * PI/180));

	x = px;
	y = py;

	if ( normalize )
		Normalize();

}

///////////////////////////////
////    Print Functions	   ////
///////////////////////////////

void Vec3D::printVect (void)
{
	cout << "X-coords: " << x << endl;
	cout << "Y-coords: " << y << endl;
	cout << "Z-coords: " << z << endl;
}

void Vec3D::printDir (void)
{
		cout << "Direction of X: " << dirX << " degrees"<< endl;
		cout << "Direction of Y: " << dirY << " degrees"<< endl;
		cout << "Direction of Z: " << dirZ << " degrees"<< endl;
}

void Vec3D::printAll (void)
{
	printVect();
	cout << endl;


	printDir();
	cout << "=============================================\n";
}