#pragma once

#include <math.h>
#include <iostream>
using namespace std;

#define PI 3.14159265f
#define RADTODEG 180/PI
#define DEGTORAD PI/180


class Vec3D
{
	public:
		float x, y, z; //Stores vector coords
		float dirX, dirY, dirZ; //Stores direction of vectors


		Vec3D();	//Default Constructor
		Vec3D(float x, float y, float z); //User-defined constructor
		~Vec3D(); //Destructor
		Vec3D(const Vec3D &sourceVector); //Copy constructor
		
		Vec3D operator+ (Vec3D &); //Addition of vectors
		Vec3D operator+= (Vec3D &); //+= operator
		Vec3D operator- (Vec3D &); //Subtraction of vectors

		Vec3D operator* (float); //Scalar multiplication
		Vec3D operator/ (float); //Scalar division

		float operator* (Vec3D &); //Dot Product
		Vec3D crossVec3D(const Vec3D &vec);
		Vec3D operator^ (Vec3D &); //Cross product

		Vec3D operator= (Vec3D &); //Asssignment overloads

		//Comparison operator
		bool operator!= ( Vec3D );

		//Angle between two vector 
		float AngleBetweenTwoVector (Vec3D &);

		void DoClamp ( float &a );

		//Set function
		void Set (float x, float y, float z);

		//Function for Magnitude
		float GetMagnitude (void);

		//Function for Normalization
		Vec3D GetNormalize ( void );
		void Normalize (void);

		

		void Rotate2D(const float angle, bool normalize);

		//Print Functions
		void printVect (void);
		void printDir (void);
		void printAll (void); //Prints Vect, Mag and Norm

	
};
