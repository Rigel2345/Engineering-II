#pragma config(Sensor, dgtl1,  floor1LED,      sensorLEDtoVCC)
#pragma config(Sensor, dgtl2,  floor2LED,      sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,  floor3LED,      sensorLEDtoVCC)
#pragma config(Sensor, dgtl7,  quadEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl10, floor1Button,   sensorTouch)
#pragma config(Sensor, dgtl11, floor3Button,   sensorTouch)
#pragma config(Sensor, dgtl12, floor2Button,   sensorTouch)
#pragma config(Motor,  port2,           elevatorMotor, tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//const float PI = 3.14159;

float floor1R = 0;
float floor2R = 980;
float floor3R = 1560;
float waitTime_ms = 10_000;
int elevatorState = 1;
void Init()
{
	clearTimer(T1);
}

void StopElevator()
{
	stopMotor(elevatorMotor);
}

void MoveElevator(int state)
{
	elevatorState = state;
	int targetFloor = 0;

	if (state == 1)
	{
		targetFloor = floor1R;
	}
	else if (state == 2)
	{
		targetFloor = floor2R;
	}
	else if (state == 3)
	{
		targetFloor = floor3R;
	}

	while (true)
	{
		if (SensorValue[quadEncoder] < targetFloor)
		{
			if (abs(SensorValue[quadEncoder] - targetFloor) > 100)
			{
				startMotor(elevatorMotor, 25);
			}
			else
			{
				startMotor(elevatorMotor, 15);
			}
		}
		else if (SensorValue[quadEncoder] > targetFloor)
		{
			if (abs(SensorValue[quadEncoder] - targetFloor) > 100)
			{
				startMotor(elevatorMotor, -15);
			}
			else
			{
				startMotor(elevatorMotor, -12);
			}
		}


		if (abs(SensorValue[quadEncoder] - targetFloor) < 5)
		{
			StopElevator();
			break;
		}
	}
}

void UpdateLights()
{
	if (elevatorState == 1)
	{
		turnLEDOn(floor1LED);
		turnLEDOff(floor2LED);
		turnLEDOff(floor3LED);
	}
	else if (elevatorState == 2)
	{
		turnLEDOff(floor1LED);
		turnLEDOn(floor2LED);
		turnLEDOff(floor3LED);
	}
	else if (elevatorState == 3)
	{
		turnLEDOff(floor1LED);
		turnLEDOff(floor2LED);
		turnLEDOn(floor3LED);
	}
}




task main()
{
	Init();
	while (true)
	{
		UpdateLights();
		if (SensorValue[floor1Button] == 1)
		{
			clearTimer(T1);
			MoveElevator(1);
		}
		if (SensorValue[floor2Button] == 1)
		{
			clearTimer(T1);
			MoveElevator(2);
		}
			if (SensorValue[floor3Button] == 1)
		{
			clearTimer(T1);
			MoveElevator(3);
		}
		if (time1[T1] > waitTime_ms && elevatorState != 1)
		{
			clearTimer(T1);
			MoveElevator(1);
		}
	}
}

	
