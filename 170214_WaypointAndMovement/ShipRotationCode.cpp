
//Implement these functions

// bool stopRotation = true
// everytime you set a waypoint


Rotation ()
{
	Vec3D targetDir = waypoint.position - position;
	Vec3D result = targetDir.crossVec3D(currentDir);
	result.Normalize();
	targetDir.Normalize();

	if ( !stopRotation )
	{
		if (result.z < 0)
		{
			//cw
			rotVal += turnSpeed;
			currentDir.Rotate2D(turnSpeed, true);
			Vec3D newResult = targetDir.crossVec3D(currentDir);
			if ( newResult.z > 0 )
			{
				//Code must be present, prevents direction from misaligning
				oldDir = currentDir;
				currentDir = targetDir;

				rotVal -= oldDir.AngleBetweenTwoVector(currentDir);
				stopRotation = true;
			}
		}
		else if ( result.z > 0)
		{
			rotVal -= turnSpeed;
			currentDir.Rotate2D(-turnSpeed, true);
			Vec3D newResult = targetDir.crossVec3D(currentDir);
			if ( newResult.z < 0 )
			{
				//Code must be present, prevents direction from misaligning
				oldDir = currentDir;
				currentDir = targetDir;

				rotVal += oldDir.AngleBetweenTwoVector(currentDir);
				stopRotation = true;
			}
		}
	}
}

Waypoint_MoveTo ()
{
	float distance = (waypointPos - position).GetMagnitude();
	
	if ( distance > waypoint.range &&
			 waypoint.isActivated() )
	{ 
		Rotation();

		Vec3D velocity = currentDir * moveSpeed;
		position.Set( position.x + velocity.x,
			position.y + velocity.y, 0);

	}

}
}