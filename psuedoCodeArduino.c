//psuedo code for Arduino

#includes rplidar, servo

varibles: 

setup{
	setup serial,
	setup 
}

loop{
	//get command mode from pi, and duration of mode
	(mode,count) = GetPiCommand();
	if(mode == 0)
		mode = oldMode; //if 0 or no command repeat mode;
	//check surrounding with lidar, save min val and angle
	(minVal,minAng) = checkLidar();
	//adjust throttle for balanced upper and lower sensor
	equalLevel();
	//check that min value is not inside danger bubble
	if(minVal< dangerVal)
		mode = escapePlan(minAng);//mode for escapePlan or excute right away;

	switch(mode)
	{
		case 1: //moving forward
			moveFoward();
			break;
		case 2: //moving back
			moveBack();
			break;
		case 3: //rotating left
			rotateLeft();
			break;
		case 4: //rotating right
			rotateRight();
			break;
		case 5: //moving away from object
			escapePlan(minAng);
			mode = 0;
			break;
		default: //all other modes idle();
			idle();
			break;
	}
	Serial.write(mode); //return to pi what the last mode was
	if(count > 0)
	{
		oldMode = mode; //return to idle 
		count--;
	}
	else
		oldMode = 0;
	
}

idle()
{
	elivator = 1500;
	aileron = 1500;
	rudder = 1500;
}

moveFoward()
{
	elivator = 1800;
}

moveBack()
{
	elivator = 1200;
}

rotateLeft()
{
	rudder = 1200;
}

rotateRight()
{
	rudder = 1800;
}


checkLidar()
{
	minVal = MaxVal;
	minAng = 0;
	while(!lidar.newScan);
	for(int degree = 0; i <360; i+=2)
	{
		(dist,angle) = lidar.read()
		if(dist < minVal)
		{
			minVal = dist; minAng = angle;
		}
		if(angle == 0)
		{
			front = dist;
		}
		else if(angle == 90)
		{
			right = dist;
		}
		else if(angle == 180)
		{
			back = dist;
		}
		else if (angle == 270)
		{
			left = dist;
		}
	}
}

//function that check the upper and lower ping for balanced
equalLevel()
{
	lower = checkDist(lowerPin);
	upper = checkDist(upperPin);
	if(upper > lower)
		throttleUp();
	else if(lower < upper)
		throttleDown();
	
}

