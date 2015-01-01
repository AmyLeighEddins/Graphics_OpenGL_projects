/*

COMP 5400 - Assignment 6
Amy Eddins

Key commands:
Up Arrow - move student forward (student, bus and camera in other modes)
Down Arrow - move student backward (bus and camera in other modes)
Right Arrow - rotate student right (and camera in other mode)
Left Arrow - rotate student left (and camera in other mode)
U - look up (and camera in other mode)
D - look down (and camera in other mode)
Page Up - zoom in
Page Down - zoom out
Home - Toggle topdown and 3d mode
F1 - decrease transparency
F2 - increase transparency 
L - change light mode
+ - increase light intensity
- - decrease light intensity
T - Tour
S - Switch Between Student, bus, and camera
R - toggle run for student
C - toggle collision detection
Q - Quit tour 

Assignment 5 Notes:
White light is attached to student
Purple light is on top of white light post next to tree

Assignment 6 Notes:
Made a toggle for running and collision detection for testing purposes and decided to leave it in.
In the tour the purple street lamp has a "motion sensor" and turns on when the student goes by.
You are not allowed to move the student or switch the controller while on tour. 
You can change light modes during the tour, but that changes the purple light from coming on when the student is close. 
The bus control is a bad angle, but the bus looks ugly from other angles.
While controlling the bus you are only able to move forward and backward.
There is no collision detection for the camera.
There is a white door on the closest wall to the moveable student that the student can go through.

*/
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <windows.h>
using namespace std;

//Global for width and height
GLdouble width, height;

//Globals used for student movement
GLfloat moveX = 0.0;
GLfloat moveY = 0.0;
GLfloat moveZ = 0.0;
GLdouble posX, posY, posZ;
GLfloat rotateStudent = 90.0;
GLfloat zoom = 1.0;
GLboolean topDown = 0;
GLdouble transparency = 1.0;
GLint lightMode = 1;
GLdouble lightIntensity = 0.0;
GLfloat vec1Arr[3] = { 0.0, 0.0, 0.0 };
GLfloat vec2Arr[3] = { 0.0, 0.0, 0.0 };
GLfloat vec3Arr[3] = { 0.0, 0.0, 0.0 };
GLfloat xNormal, yNormal, zNormal, x, y, z;
GLfloat speed = 5.0;
bool speedToggle = false;
bool onTour = false;
bool collisionDetection = true;
GLfloat studentPos1X = 0.0;
GLfloat studentPos1Z = 0.0;
GLfloat studentPos2X = 0.0;
GLfloat studentPos3X = 0.0;
GLfloat studentPos4X = 0.0;
GLfloat studentPos5X = 0.0;
GLfloat studentPos2Z = 0.0;
GLfloat studentPos3Z = 0.0;
GLfloat studentPos4Z = 0.0;
GLfloat studentPos5Z = 0.0;
GLfloat studentPosTourX = 0.0;
GLfloat studentPosTourZ = 0.0;
GLfloat studentRotTour = 90.0;
int tourIncrement = 0;
int switchController = 0;
GLfloat headControl = 0.0;

void takeTour();
bool detectCollision(GLfloat plannedX, GLfloat plannedZ);
void processSpecialKeys(int key, int xdir, int ydir);
void processRegularKeys(unsigned char key, int x, int y);
void drawRectangle(GLfloat bottomLeftX, GLfloat bottomRightX, GLfloat topRightX, GLfloat topLeftX, GLfloat bottomLeftZ, GLfloat bottomRightZ, GLfloat topRightZ, GLfloat topLeftZ);
void drawStudent(bool transform, float rotate, bool girl, int hairColor, bool n3DS, bool shirtLogo, int shirtColor, int shortColor, bool glasses, int skinColor, int shoeColor);
void display();
void drawBus();
void drawStudent(bool transform, float rotate, bool girl, int hairColor, bool n3DS, bool shirtLogo, int shirtColor, int shortColor, bool glasses, int skinColor, int shoeColor);

/*
Calculate Normal
From website: http://support.microsoft.com/kb/131130
*/
void 
CalculateVectorNormal(GLfloat fVert1[], GLfloat fVert2[], GLfloat fVert3[], GLfloat *fNormalX, GLfloat *fNormalY, GLfloat *fNormalZ)
{
	GLfloat Qx, Qy, Qz, Px, Py, Pz;

	Qx = fVert2[0] - fVert1[0];
	Qy = fVert2[1] - fVert1[1];
	Qz = fVert2[2] - fVert1[2];
	Px = fVert3[0] - fVert1[0];
	Py = fVert3[1] - fVert1[1];
	Pz = fVert3[2] - fVert1[2];

	*fNormalX = Py*Qz - Pz*Qy;
	*fNormalY = Pz*Qx - Px*Qz;
	*fNormalZ = Px*Qy - Py*Qx;
}

/*
Tour the student center.
Key "T"
*/
void
takeTour()
{
	if (tourIncrement == 19)
	{
		rotateStudent += 90.0;
	}
	else if (tourIncrement == 46)
	{
		rotateStudent += 45.0;
	}
	else if (tourIncrement == 66)
	{
		rotateStudent += 45.0;
	}
	else if (tourIncrement == 81)
	{
		rotateStudent -= 90.0;
	}
	else if (tourIncrement == 102)
	{
		lightMode = 2;
	}
	else if (tourIncrement == 116)
	{
		rotateStudent += 90.0;
	}
	else if (tourIncrement == 141)
	{
		rotateStudent += 90.0;
	}
	else if (tourIncrement == 211)
	{
		rotateStudent += 90.0;
	}
	if (tourIncrement >= 0 && tourIncrement <= 18)
	{
		moveY = (moveY - 15 * sin(M_PI / 180 * -rotateStudent));
		moveX = (moveX - 15 * cos(M_PI / 180 * -rotateStudent));
	}
	else if (tourIncrement >= 20 && tourIncrement <= 45)
	{
		moveY = (moveY - 15 * sin(M_PI / 180 * -rotateStudent));
		moveX = (moveX - 15 * cos(M_PI / 180 * -rotateStudent));
	}
	else if (tourIncrement >= 47 && tourIncrement <= 65)
	{
		moveY = (moveY - 15 * sin(M_PI / 180 * -rotateStudent));
		moveX = (moveX - 15 * cos(M_PI / 180 * -rotateStudent));
	}
	else if (tourIncrement >= 67 && tourIncrement <= 80)
	{
		moveY = (moveY - 15 * sin(M_PI / 180 * -rotateStudent));
		moveX = (moveX - 15 * cos(M_PI / 180 * -rotateStudent));
	}
	else if (tourIncrement >= 82 && tourIncrement <= 115)
	{
		moveY = (moveY - 15 * sin(M_PI / 180 * -rotateStudent));
		moveX = (moveX - 15 * cos(M_PI / 180 * -rotateStudent));
	}
	else if (tourIncrement >= 117 && tourIncrement <= 140)
	{
		moveY = (moveY - 15 * sin(M_PI / 180 * -rotateStudent));
		moveX = (moveX - 15 * cos(M_PI / 180 * -rotateStudent));
	}
	else if (tourIncrement >= 142 && tourIncrement <= 210)
	{
		moveY = (moveY - 15 * sin(M_PI / 180 * -rotateStudent));
		moveX = (moveX - 15 * cos(M_PI / 180 * -rotateStudent));
	}
	else if (tourIncrement >= 212 && tourIncrement <= 240)
	{
		moveY = (moveY - 15 * sin(M_PI / 180 * -rotateStudent));
		moveX = (moveX - 15 * cos(M_PI / 180 * -rotateStudent));
	}
	else if (tourIncrement == 241)
	{
		onTour = false;
	}
	drawStudent(1, 0.0, 1, 10, 1, 1, 1, 4, 1, 11, 1);
	tourIncrement++;
	Sleep(200);

}


/* 
Collision Detection
*/
bool
detectCollision(GLfloat plannedX, GLfloat plannedZ)
{
	studentPos1X = 50.0;
	studentPos1Z = 60.0;
	studentPos2X = 30.0;
	studentPos2Z = 35.0;
	studentPos3X = -40.0;
	studentPos3Z = -30.0;
	studentPos4X = 178.0;
	studentPos4Z = 190.0;
	studentPos5X = 780.0;
	studentPos5Z = 40.0;
	if (collisionDetection == false)
	{
		return false;
	}
	/*else if (((plannedX >= 80.0) && (plannedX <= 85.0) && (plannedZ >= 82.0) && (plannedZ <= 185.0)))
	{
		return true;
	}*/
	else if (((plannedX >= 80.0) && (plannedX <= 85.0) && (plannedZ >= 82.0) && (plannedZ <= 125.0))) //before door
	{
		return true;
	}
	else if (((plannedX >= 80.0) && (plannedX <= 85.0) && (plannedZ >= 140.0) && (plannedZ <= 185.0)))
	{
		return true;
	}
	else if (((plannedX >= 80.0) && (plannedX <= 455.0) && (plannedZ >= 82.0) && (plannedZ <= 90.0)))
	{
		return true;
	}
	else if (((plannedX >= 83.0) && (plannedX <= 457.0) && (plannedZ >= 173.0) && (plannedZ <= 189.0)))
	{
		return true;
	}
	else if (((plannedX >= 440.0) && (plannedX <= 459.0) && (plannedZ >= -190.0) && (plannedZ <= 189.0)))
	{
		return true;
	}
	else if (((plannedX >= 290.0) && (plannedX <= 309.0) && (plannedZ >= -190.0) && (plannedZ <= 100.0)))
	{
		return true;
	}
	else if (((plannedX >= 170.0) && (plannedX <= 760.00) && (plannedZ >= -190.0) && (plannedZ <= -170.0)))
	{
		return true;
	}
	else if (((plannedX >= 170.0) && (plannedX <= 760.00) && (plannedZ >= -430.0) && (plannedZ <= -411.0)))
	{
		return true;
	}
	else if (((plannedX >= 170.0) && (plannedX <= 189.00) && (plannedZ >= -430.0) && (plannedZ <= -173.0)))
	{
		return true;
	}
	else if (((plannedX >= 740.0) && (plannedX <= 759.00) && (plannedZ >= -428.0) && (plannedZ <= -173.0)))
	{
		return true;
	}
	else if (((plannedX >= 190.0) && (plannedX <= 413.00) && (plannedZ >= 200.0) && (plannedZ <= 248.0)))//bushes
	{
		return true;
	}
	else if (((plannedX >= 1015.0) && (plannedX <= 1080.00) && (plannedZ >= -258.0) && (plannedZ <= -192.0)))//tree
	{
		return true;
	}
	else if (((plannedX >= 300.0) && (plannedX <= 400) && (plannedZ >= -100.0) && (plannedZ <= 0.0)))
	{
		return true;
	}
	else if (((plannedX >= 660.0) && (plannedX <= 750) && (plannedZ >= -15.0) && (plannedZ <= 15.0)))//bushes
	{
		return true;
	}
	else if (((plannedX >= 750.0) && (plannedX <= 820) && (plannedZ >= -20.0) && (plannedZ <= 5.0)))// bushes
	{
		return true;
	}
	else if (((plannedX >= 820.0) && (plannedX <= 870) && (plannedZ >= -40.0) && (plannedZ <= -10.0)))// bushes
	{
		return true;
	}
	else if (((plannedX >= -158.0) && (plannedX <= -75) && (plannedZ >= -245.0) && (plannedZ <= -75.0)))// bus
	{
		return true;
	}
	//detect students
	
	else if (((plannedX >= studentPos1X) && (plannedX <= studentPos1X + 25) && (plannedZ >= studentPos1Z) && (plannedZ <= studentPos1Z + 25)))
	{
		return true;
	}
	else if (((plannedX >= studentPos2X) && (plannedX <= studentPos2X + 25) && (plannedZ >= studentPos2Z) && (plannedZ <= studentPos2Z + 25)))
	{
		return true;
	}
	else if (((plannedX >= studentPos3X) && (plannedX <= studentPos3X + 25) && (plannedZ >= studentPos3Z) && (plannedZ <= studentPos3Z + 25)))
	{
		return true;
	}
	else if (((plannedX >= studentPos4X) && (plannedX <= studentPos4X + 25) && (plannedZ >= studentPos4Z) && (plannedZ <= studentPos4Z + 25)))
	{
		return true;
	}
	else if (((plannedX >= studentPos5X) && (plannedX <= studentPos5X + 25) && (plannedZ >= studentPos5Z) && (plannedZ <= studentPos5Z + 25)))
	{
		return true;
	}
	else if (plannedX > 1350.0 || plannedX < -1350.0 || plannedZ > 1350.0 || plannedZ < -1350.0) //scene boundary
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
Controls the user input.
Key input is at the top of the code.
*/
void
processSpecialKeys(int key, int xdir, int ydir)
{
	GLfloat testX, testY;
	if (!(onTour))
	{
		switch (key)
		{

		case GLUT_KEY_UP: //If up arrow pressed
			//Move student forward
			//Collision Detection
			testY = (moveY - speed * sin(M_PI / 180 * -rotateStudent));
			testX = (moveX - speed * cos(M_PI / 180 * -rotateStudent));
			if ((detectCollision(testX, testY)) == false)
			{
				if (switchController != 1)
				{
					moveY = (moveY - speed * sin(M_PI / 180 * -rotateStudent));
					moveX = (moveX - speed * cos(M_PI / 180 * -rotateStudent));
				}
				else
				{
					moveY -= 15.0;
				}
			}
			break;
		case GLUT_KEY_DOWN: //If down arrow pressed
			//Move student backward 
			testY = (moveY + speed * sin(M_PI / 180 * -rotateStudent));
			testX = (moveX + speed * cos(M_PI / 180 * -rotateStudent));
			if ((detectCollision(testX, testY)) == 0)
			{
				if (switchController != 1)
				{
					moveY = (moveY + speed * sin(M_PI / 180 * -rotateStudent));
					moveX = (moveX + speed * cos(M_PI / 180 * -rotateStudent));
				}
				else
				{
					moveY += 15.0;
				}
			}
			break;
		case GLUT_KEY_LEFT: //If left arrow pressed
			//Rotate student left
			rotateStudent = rotateStudent + 5;
			break;
		case GLUT_KEY_RIGHT: //If right arrow pressed
			//Rotate student right
			rotateStudent = rotateStudent - 5;
			break;
		case GLUT_KEY_PAGE_DOWN: //If pgup pressed
			if (!(zoom >= 35.0))
			{
				zoom = zoom + 1.0; //Zoom out
			}
			break;
		case GLUT_KEY_PAGE_UP: //If pgdn pressed
			if (!(zoom <= -4.0))
			{
				zoom = zoom - 1.0; //Zoom in
			}
			break;
		case GLUT_KEY_HOME://Toggle Topdown mode
			if (topDown == 0)
			{
				topDown = 1;
			}
			else
			{
				topDown = 0;
			}
			break;
		case GLUT_KEY_F1:
			if (transparency >= 0.1)//decrease transparency
			{
				transparency -= 0.1;
			}
			break;
		case GLUT_KEY_F2:
			if (transparency <= 1.0)//increase transparency
			{
				transparency += 0.1;
			}
			break;
		}
	}
}

void
processRegularKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'l':
			if (lightMode == 1) //white spotlight only (default)
			{
				lightMode = 2;
			}
			else if (lightMode == 2) //color light only
			{
				lightMode = 3;
			}
			else if (lightMode == 3) //both lights
			{
				lightMode = 4;
			}
			else //no lights
			{
				lightMode = 1;
			}
			break;
		case '+': //increase light
			if (lightIntensity < 0.5)
			{
				lightIntensity += 0.05;
			}
			break;
		case '-': //decrease light
			if (lightIntensity > -0.2)
			{
				lightIntensity -= 0.05;
			}
			break;
		case 't': //take tour
			switchController = 0;
			onTour = true;
			moveX = 0.0;
			moveY = 0.0;
			rotateStudent = 90.0;
			tourIncrement = 0;
			takeTour();
			break;
		case 'r': //run
			if (!(onTour))
			{
				if (speedToggle)
				{
					speedToggle = false;
					speed = 10.0;
				}
				else
				{
					speedToggle = true;
					speed = 50.0;
				}
			}
			break;
		case 'c': //collision detection
			if (collisionDetection)
			{
				collisionDetection = false;
			}
			else
			{
				collisionDetection = true;
			}
			break;
		case 'q'://quit tour
			if (onTour)
			{
				onTour = false;
				moveX = 0.0;
				moveY = 0.0;
				rotateStudent = 90.0;
				tourIncrement = 0;
			}
			break;
		case 'u': //student look up
			if (headControl < 70)
			{
				headControl += 5;
			}
			break;
		case 'd': //student look down
			if (headControl > -60)
			{
				headControl -= 5;
			}
			break;
		case 's': //Switch between student and bus control
			if (!onTour)
			{
				if (switchController == 0) //bus
				{
					switchController = 1;
					moveX = 0.0;
					moveY = 0.0;
					rotateStudent = 90.0;
					lightMode = 4;
					collisionDetection = true;
				}
				else if (switchController == 1)//camera
				{
					switchController = 2;
					moveX = 0.0;
					moveY = 0.0;
					rotateStudent = 90.0;
					lightMode = 1;
					collisionDetection = false;
				}
				else //main student
				{
					switchController = 0;
					moveX = 0.0;
					moveY = 0.0;
					rotateStudent = 90.0;
					lightMode = 1;
					collisionDetection = true;
				}
			}
			break;


	}
}
/*
Initialize all points in respective arrays.
*/
void
init(void)
{
	width = 1000.0;
	height = 800.0;
}

/*
Draw a rectangle
*/
void 
drawRectangle(GLfloat bottomLeftX, GLfloat bottomRightX, GLfloat topRightX, GLfloat topLeftX, GLfloat bottomLeftZ, GLfloat bottomRightZ, GLfloat topRightZ, GLfloat topLeftZ)
{
	glBegin(GL_POLYGON);
		glVertex3f(bottomLeftX, 1.0f, bottomLeftZ);
		glVertex3f(bottomRightX, 1.0f, bottomRightZ);
		glVertex3f(topRightX, 1.0f, topRightZ);
		glVertex3f(topLeftX, 1.0f, topLeftZ);
	glEnd();
}



/*
This function draws a student

For color choices:
0 - white
1 - black
2 - red
3 - green
4 - blue
5 - purple
6 - yellow
7 - orange
8 - pink
9 - gray
10 - brown
11 - light pink
12 - light brown
*/
void
drawStudent(bool transform, float rotate, bool girl, int hairColor, bool n3DS, bool shirtLogo, int shirtColor, int shortColor, bool glasses, int skinColor, int shoeColor)
{
	/*  Draw Student  */

	//Starting points for student
	GLfloat startX, startY;
	startX = 550.0 - 500.0;
	startY = 500.0 - 280.0;

	glPushMatrix();

	//Center of student on x-axis = 500
	//Center of student on y-axis = 280

	//Transformations
	if (transform)
	{
		glTranslatef(moveX, 13.5, moveY); //move
		glScalef(0.05, 0.05, 0.05); //scale
		glRotatef(rotateStudent - 90, 0.0, 1.0, 0.0); //rotate
	}
	else
	{
		glTranslatef(0.0, 13.5, 0.0); //move
		glScalef(0.05, 0.05, 0.05); //scale
		glRotatef(rotate - 90, 0.0, 1.0, 0.0); //rotate
	}

	glPushMatrix();
	glutSolidCube(50.0);
	glPopMatrix();

	// Student's body (face, arms, legs)
	glBegin(GL_QUADS);

	if (skinColor == 10)
	{
		glColor3f(0.55f, 0.27f, 0.07f); // Brown
	}
	else if (skinColor == 11)
	{
		glColor3f(1.0f, 0.62f, 0.47f); // light pink
	}
	else if (skinColor == 12)
	{
		glColor3f(0.80f, 0.43f, 0.15f); // Light Brown (tan)
	}
	else
	{
		glColor3f(1.0f, 0.62f, 0.47f); // light pink
	}

	//front
	vec3Arr[0] = startX;
	vec3Arr[1] = startY;
	vec3Arr[2] = 50.0f;

	vec2Arr[0] = startX - 100.0f;
	vec2Arr[1] = startY;
	vec2Arr[2] = 50.0f;

	vec1Arr[0] = startX - 100.0f;
	vec1Arr[1] = startY - 100.0f;
	vec1Arr[2] = 50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX, startY, 50.0f);
	glVertex3f(startX - 100.0f, startY, 50.0f);
	glVertex3f(startX - 100.0f, startY - 100.0f, 50.0f);
	glVertex3f(startX, startY - 100.0f, 50.0f);

	//back
	vec1Arr[0] = startX;
	vec1Arr[1] = startY;
	vec1Arr[2] = -50.0f;

	vec2Arr[0] = startX - 100.0f;
	vec2Arr[1] = startY;
	vec2Arr[2] = -50.0f;

	vec3Arr[0] = startX - 100.0f;
	vec3Arr[1] = startY - 100.0f;
	vec3Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX, startY, -50.0f);
	glVertex3f(startX - 100.0f, startY, -50.0f);
	glVertex3f(startX - 100.0f, startY - 100.0f, -50.0f);
	glVertex3f(startX, startY - 100.0f, -50.0f);

	//right side
	vec3Arr[0] = startX - 100.0f;
	vec3Arr[1] = startY;
	vec3Arr[2] = 50.0f;

	vec2Arr[0] = startX - 100.0f;
	vec2Arr[1] = startY;
	vec2Arr[2] = -50.0f;

	vec1Arr[0] = startX - 100.0f;
	vec1Arr[1] = startY - 100.0f;
	vec1Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 100.0f, startY, 50.0f);
	glVertex3f(startX - 100.0f, startY, -50.0f);
	glVertex3f(startX - 100.0f, startY - 100.0f, -50.0f);
	glVertex3f(startX - 100.0f, startY - 100.0f, 50.0f);

	//left side
	vec3Arr[0] = startX;
	vec3Arr[1] = startY;
	vec3Arr[2] = 50.0f;

	vec2Arr[0] = startX;
	vec2Arr[1] = startY - 100.0f;
	vec2Arr[2] = 50.0f;

	vec1Arr[0] = startX;
	vec1Arr[1] = startY - 100.0f;
	vec1Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX, startY, 50.0f);
	glVertex3f(startX, startY - 100.0f, 50.0f);
	glVertex3f(startX, startY - 100.0f, -50.0f);
	glVertex3f(startX, startY, -50.0f);

	glEnd();

	//right arm
	glBegin(GL_QUADS);

	vec3Arr[0] = startX - 155.0f;
	vec3Arr[1] = startY - 100.0f;
	vec3Arr[2] = 20.0f;

	vec2Arr[0] = startX - 190.0f;
	vec2Arr[1] = startY - 200.0f;
	vec2Arr[2] = 20.0f;

	vec1Arr[0] = startX - 165.0f;
	vec1Arr[1] = startY - 210.0f;
	vec1Arr[2] = 20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 155.0f, startY - 150.0f, 20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX - 165.0f, startY - 210.0f, 20.0f);
	glVertex3f(startX - 135.0f, startY - 170.0f, 20.0f);

	vec1Arr[0] = startX - 155.0f;
	vec1Arr[1] = startY - 100.0f;
	vec1Arr[2] = -20.0f;

	vec2Arr[0] = startX - 190.0f;
	vec2Arr[1] = startY - 200.0f;
	vec2Arr[2] = -20.0f;

	vec3Arr[0] = startX - 165.0f;
	vec3Arr[1] = startY - 210.0f;
	vec3Arr[2] = -20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 155.0f, startY - 150.0f, -20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX - 165.0f, startY - 210.0f, -20.0f);
	glVertex3f(startX - 135.0f, startY - 170.0f, -20.0f);

	vec3Arr[0] = startX - 155.0f;
	vec3Arr[1] = startY - 100.0f;
	vec3Arr[2] = 20.0f;

	vec2Arr[0] = startX - 155.0f;
	vec2Arr[1] = startY - 150.0f;
	vec2Arr[2] = -20.0f;

	vec1Arr[0] = startX - 190.0f;
	vec1Arr[1] = startY - 200.0f;
	vec1Arr[2] = -20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 155.0f, startY - 150.0f, 20.0f);
	glVertex3f(startX - 155.0f, startY - 150.0f, -20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, 20.0f);

	vec1Arr[0] = startX - 135.0f;
	vec1Arr[1] = startY - 170.0f;
	vec1Arr[2] = 20.0f;

	vec2Arr[0] = startX - 135.0f;
	vec2Arr[1] = startY - 170.0f;
	vec2Arr[2] = -20.0f;

	vec3Arr[0] = startX - 165.0f;
	vec3Arr[1] = startY - 210.0f;
	vec3Arr[2] = -20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 135.0f, startY - 170.0f, 20.0f);
	glVertex3f(startX - 135.0f, startY - 170.0f, -20.0f);
	glVertex3f(startX - 165.0f, startY - 210.0f, -20.0f);
	glVertex3f(startX - 165.0f, startY - 210.0f, 20.0f);

	glEnd();

	//left arm
	glBegin(GL_QUADS);

	vec1Arr[0] = startX + 55.0f;
	vec1Arr[1] = startY - 150.0f;
	vec1Arr[2] = 20.0f;

	vec2Arr[0] = startX + 90.0f;
	vec2Arr[1] = startY - 200.0f;
	vec2Arr[2] = 20.0f;

	vec3Arr[0] = startX + 65.0f;
	vec3Arr[1] = startY - 210.0f;
	vec3Arr[2] = 20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 55.0f, startY - 150.0f, 20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX + 65.0f, startY - 210.0f, 20.0f);
	glVertex3f(startX + 35.0f, startY - 170.0f, 20.0f);

	vec3Arr[0] = startX + 55.0f;
	vec3Arr[1] = startY - 150.0f;
	vec3Arr[2] = -20.0f;

	vec2Arr[0] = startX + 90.0f;
	vec2Arr[1] = startY - 200.0f;
	vec2Arr[2] = -20.0f;

	vec1Arr[0] = startX + 65.0f;
	vec1Arr[1] = startY - 210.0f;
	vec1Arr[2] = -20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 55.0f, startY - 150.0f, -20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX + 65.0f, startY - 210.0f, -20.0f);
	glVertex3f(startX + 35.0f, startY - 170.0f, -20.0f);

	vec1Arr[0] = startX + 55.0f;
	vec1Arr[1] = startY - 150.0f;
	vec1Arr[2] = 20.0f;

	vec2Arr[0] = startX + 55.0f;
	vec2Arr[1] = startY - 150.0f;
	vec2Arr[2] = -20.0f;

	vec3Arr[0] = startX + 90.0f;
	vec3Arr[1] = startY - 200.0f;
	vec3Arr[2] = -20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 55.0f, startY - 150.0f, 20.0f);
	glVertex3f(startX + 55.0f, startY - 150.0f, -20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, 20.0f);

	vec1Arr[0] = startX + 65.0f;
	vec1Arr[1] = startY - 210.0f;
	vec1Arr[2] = 20.0f;

	vec2Arr[0] = startX + 65.0f;
	vec2Arr[1] = startY - 210.0f;
	vec2Arr[2] = -20.0f;

	vec3Arr[0] = startX + 35.0f;
	vec3Arr[1] = startY - 170.0f;
	vec3Arr[2] = -20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 65.0f, startY - 210.0f, 20.0f);
	glVertex3f(startX + 65.0f, startY - 210.0f, -20.0f);
	glVertex3f(startX + 35.0f, startY - 170.0f, -20.0f);
	glVertex3f(startX + 35.0f, startY - 170.0f, 20.0f);

	glEnd();

	//right hand

	glBegin(GL_QUADS);

	vec3Arr[0] = startX - 160.0f;
	vec3Arr[1] = startY - 200.0f;
	vec3Arr[2] = 20.0f;

	vec2Arr[0] = startX - 190.0f;
	vec2Arr[1] = startY - 200.0f;
	vec2Arr[2] = 20.0f;

	vec1Arr[0] = startX - 200.0f;
	vec1Arr[1] = startY - 230.0f;
	vec1Arr[2] = 20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 160.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX - 200.0f, startY - 230.0f, 20.0f);
	glVertex3f(startX - 180.0f, startY - 240.0f, 20.0f);

	vec3Arr[0] = startX - 161.0f;
	vec3Arr[1] = startY - 205.0f;
	vec3Arr[2] = 20.0f;

	vec2Arr[0] = startX - 165.0f;
	vec2Arr[1] = startY - 205.0f;
	vec2Arr[2] = 20.0f;

	vec1Arr[0] = startX - 168.0f;
	vec1Arr[1] = startY - 230.0f;
	vec1Arr[2] = 20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 161.0f, startY - 205.0f, 20.0f);
	glVertex3f(startX - 165.0f, startY - 205.0f, 20.0f);
	glVertex3f(startX - 168.0f, startY - 230.0f, 20.0f);
	glVertex3f(startX - 161.0f, startY - 230.0f, 20.0f);

	vec1Arr[0] = startX - 160.0f;
	vec1Arr[1] = startY - 200.0f;
	vec1Arr[2] = -20.0f;

	vec2Arr[0] = startX - 190.0f;
	vec2Arr[1] = startY - 200.0f;
	vec2Arr[2] = -20.0f;

	vec3Arr[0] = startX - 200.0f;
	vec3Arr[1] = startY - 230.0f;
	vec3Arr[2] = -20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 160.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX - 200.0f, startY - 230.0f, -20.0f);
	glVertex3f(startX - 180.0f, startY - 240.0f, -20.0f);

	vec1Arr[0] = startX - 161.0f;
	vec1Arr[1] = startY - 205.0f;
	vec1Arr[2] = -20.0f;

	vec2Arr[0] = startX - 165.0f;
	vec2Arr[1] = startY - 205.0f;
	vec2Arr[2] = -20.0f;

	vec3Arr[0] = startX - 168.0f;
	vec3Arr[1] = startY - 230.0f;
	vec3Arr[2] = -20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 161.0f, startY - 205.0f, -20.0f);
	glVertex3f(startX - 165.0f, startY - 205.0f, -20.0f);
	glVertex3f(startX - 168.0f, startY - 230.0f, -20.0f);
	glVertex3f(startX - 161.0f, startY - 230.0f, -20.0f);

	vec1Arr[0] = startX - 200.0f;
	vec1Arr[1] = startY - 230.0f;
	vec1Arr[2] = 20.0f;

	vec2Arr[0] = startX - 200.0f;
	vec2Arr[1] = startY - 230.0f;
	vec2Arr[2] = -20.0f;

	vec3Arr[0] = startX - 190.0f;
	vec3Arr[1] = startY - 200.0f;
	vec3Arr[2] = -20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 200.0f, startY - 230.0f, 20.0f);
	glVertex3f(startX - 200.0f, startY - 230.0f, -20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, 20.0f);

	vec1Arr[0] = startX - 160.0f;
	vec1Arr[1] = startY - 200.0f;
	vec1Arr[2] = 20.0f;

	vec2Arr[0] = startX - 160.0f;
	vec2Arr[1] = startY - 200.0f;
	vec2Arr[2] = -20.0f;

	vec3Arr[0] = startX - 180.0f;
	vec3Arr[1] = startY - 240.0f;
	vec3Arr[2] = -20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 160.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX - 160.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX - 180.0f, startY - 240.0f, -20.0f);
	glVertex3f(startX - 180.0f, startY - 240.0f, 20.0f);

	vec1Arr[0] = startX - 161.0f;
	vec1Arr[1] = startY - 205.0f;
	vec1Arr[2] = 20.0f;

	vec2Arr[0] = startX - 161.0f;
	vec2Arr[1] = startY - 205.0f;
	vec2Arr[2] = -20.0f;

	vec3Arr[0] = startX - 161.0f;
	vec3Arr[1] = startY - 230.0f;
	vec3Arr[2] = -20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 161.0f, startY - 205.0f, 20.0f);
	glVertex3f(startX - 161.0f, startY - 205.0f, -20.0f);
	glVertex3f(startX - 161.0f, startY - 230.0f, -20.0f);
	glVertex3f(startX - 161.0f, startY - 230.0f, 20.0f);

	glEnd();

	//left hand

	glBegin(GL_QUADS);

	vec3Arr[0] = startX + 60.0f;
	vec3Arr[1] = startY - 200.0f;
	vec3Arr[2] = 20.0f;

	vec2Arr[0] = startX + 90.0f;
	vec2Arr[1] = startY - 200.0f;
	vec2Arr[2] = 20.0f;

	vec1Arr[0] = startX + 100.0f;
	vec1Arr[1] = startY - 230.0f;
	vec1Arr[2] = 20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 60.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX + 100.0f, startY - 230.0f, 20.0f);
	glVertex3f(startX + 80.0f, startY - 240.0f, 20.0f);

	vec3Arr[0] = startX + 100.0f;
	vec3Arr[1] = startY - 200.0f;
	vec3Arr[2] = 22.0f;

	vec2Arr[0] = startX + 80.0f;
	vec2Arr[1] = startY - 190.0f;
	vec2Arr[2] = 22.0f;

	vec1Arr[0] = startX + 80.0f;
	vec1Arr[1] = startY - 200.0f;
	vec1Arr[2] = 22.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 100.0f, startY - 200.0f, 22.0f);
	glVertex3f(startX + 80.0f, startY - 190.0f, 22.0f);
	glVertex3f(startX + 80.0f, startY - 200.0f, 22.0f);
	glVertex3f(startX + 100.0f, startY - 210.0f, 22.0f);

	vec3Arr[0] = startX + 60.0f;
	vec3Arr[1] = startY - 200.0f;
	vec3Arr[2] = -20.0f;

	vec2Arr[0] = startX + 90.0f;
	vec2Arr[1] = startY - 200.0f;
	vec2Arr[2] = -20.0f;

	vec1Arr[0] = startX + 100.0f;
	vec1Arr[1] = startY - 230.0f;
	vec1Arr[2] = -20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 60.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX + 100.0f, startY - 230.0f, -20.0f);
	glVertex3f(startX + 80.0f, startY - 240.0f, -20.0f);

	vec3Arr[0] = startX + 100.0f;
	vec3Arr[1] = startY - 230.0f;
	vec3Arr[2] = 20.0f;

	vec2Arr[0] = startX + 100.0f;
	vec2Arr[1] = startY - 230.0f;
	vec2Arr[2] = -20.0f;

	vec1Arr[0] = startX + 90.0f;
	vec1Arr[1] = startY - 200.0f;
	vec1Arr[2] = -20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 100.0f, startY - 230.0f, 20.0f);
	glVertex3f(startX + 100.0f, startY - 230.0f, -20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, 20.0f);

	vec1Arr[0] = startX + 60.0f;
	vec1Arr[1] = startY - 200.0f;
	vec1Arr[2] = 20.0f;

	vec2Arr[0] = startX + 60.0f;
	vec2Arr[1] = startY - 200.0f;
	vec2Arr[2] = -20.0f;

	vec3Arr[0] = startX + 80.0f;
	vec3Arr[1] = startY - 240.0f;
	vec3Arr[2] = -20.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 60.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX + 60.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX + 80.0f, startY - 240.0f, -20.0f);
	glVertex3f(startX + 80.0f, startY - 240.0f, 20.0f);

	glEnd();

	//left leg
	glBegin(GL_QUADS);

	vec3Arr[0] = startX + 10.0f;
	vec3Arr[1] = startY - 320.0f;
	vec3Arr[2] = 30.0f;

	vec2Arr[0] = startX - 35.0f;
	vec2Arr[1] = startY - 320.0f;
	vec2Arr[2] = 30.0f;

	vec1Arr[0] = startX - 35.0f;
	vec1Arr[1] = startY - 405.0f;
	vec1Arr[2] = 30.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 10.0f, startY - 320.0f, 30.0f);
	glVertex3f(startX - 35.0f, startY - 320.0f, 30.0f);
	glVertex3f(startX - 35.0f, startY - 405.0f, 30.0f);
	glVertex3f(startX + 10.0f, startY - 405.0f, 30.0f);

	vec1Arr[0] = startX + 10.0f;
	vec1Arr[1] = startY - 320.0f;
	vec1Arr[2] = -30.0f;

	vec2Arr[0] = startX - 35.0f;
	vec2Arr[1] = startY - 320.0f;
	vec2Arr[2] = -30.0f;

	vec3Arr[0] = startX - 35.0f;
	vec3Arr[1] = startY - 405.0f;
	vec3Arr[2] = -30.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 10.0f, startY - 320.0f, -30.0f);
	glVertex3f(startX - 35.0f, startY - 320.0f, -30.0f);
	glVertex3f(startX - 35.0f, startY - 405.0f, -30.0f);
	glVertex3f(startX + 10.0f, startY - 405.0f, -30.0f);

	vec3Arr[0] = startX - 35.0f;
	vec3Arr[1] = startY - 320.0f;
	vec3Arr[2] = 30.0f;

	vec2Arr[0] = startX - 35.0f;
	vec2Arr[1] = startY - 320.0f;
	vec2Arr[2] = -30.0f;

	vec1Arr[0] = startX - 35.0f;
	vec1Arr[1] = startY - 405.0f;
	vec1Arr[2] = -30.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 35.0f, startY - 320.0f, 30.0f);
	glVertex3f(startX - 35.0f, startY - 320.0f, -30.0f);
	glVertex3f(startX - 35.0f, startY - 405.0f, -30.0f);
	glVertex3f(startX - 35.0f, startY - 405.0f, 30.0f);

	vec1Arr[0] = startX + 10.0f;
	vec1Arr[1] = startY - 320.0f;
	vec1Arr[2] = 30.0f;

	vec2Arr[0] = startX + 10.0f;
	vec2Arr[1] = startY - 320.0f;
	vec2Arr[2] = -30.0f;

	vec3Arr[0] = startX + 10.0f;
	vec3Arr[1] = startY - 405.0f;
	vec3Arr[2] = -30.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 10.0f, startY - 320.0f, 30.0f);
	glVertex3f(startX + 10.0f, startY - 320.0f, -30.0f);
	glVertex3f(startX + 10.0f, startY - 405.0f, -30.0f);
	glVertex3f(startX + 10.0f, startY - 405.0f, 30.0f);

	glEnd();

	//right leg
	glBegin(GL_QUADS);

	vec3Arr[0] = startX - 65.0f;
	vec3Arr[1] = startY - 320.0f;
	vec3Arr[2] = 30.0f;

	vec2Arr[0] = startX - 110.0f;
	vec2Arr[1] = startY - 320.0f;
	vec2Arr[2] = 30.0f;

	vec1Arr[0] = startX - 110.0f;
	vec1Arr[1] = startY - 405.0f;
	vec1Arr[2] = 30.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 65.0f, startY - 320.0f, 30.0f);
	glVertex3f(startX - 110.0f, startY - 320.0f, 30.0f);
	glVertex3f(startX - 110.0f, startY - 405.0f, 30.0f);
	glVertex3f(startX - 65.0f, startY - 405.0f, 30.0f);

	vec1Arr[0] = startX - 65.0f;
	vec1Arr[1] = startY - 320.0f;
	vec1Arr[2] = -30.0f;

	vec2Arr[0] = startX - 110.0f;
	vec2Arr[1] = startY - 320.0f;
	vec2Arr[2] = -30.0f;

	vec3Arr[0] = startX - 110.0f;
	vec3Arr[1] = startY - 405.0f;
	vec3Arr[2] = -30.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 65.0f, startY - 320.0f, -30.0f);
	glVertex3f(startX - 110.0f, startY - 320.0f, -30.0f);
	glVertex3f(startX - 110.0f, startY - 405.0f, -30.0f);
	glVertex3f(startX - 65.0f, startY - 405.0f, -30.0f);

	vec1Arr[0] = startX - 65.0f;
	vec1Arr[1] = startY - 320.0f;
	vec1Arr[2] = 30.0f;

	vec2Arr[0] = startX - 65.0f;
	vec2Arr[1] = startY - 320.0f;
	vec2Arr[2] = -30.0f;

	vec3Arr[0] = startX - 65.0f;
	vec3Arr[1] = startY - 405.0f;
	vec3Arr[2] = -30.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 65.0f, startY - 320.0f, 30.0f);
	glVertex3f(startX - 65.0f, startY - 320.0f, -30.0f);
	glVertex3f(startX - 65.0f, startY - 405.0f, -30.0f);
	glVertex3f(startX - 65.0f, startY - 405.0f, 30.0f);

	vec3Arr[0] = startX - 110.0f;
	vec3Arr[1] = startY - 320.0f;
	vec3Arr[2] = 30.0f;

	vec2Arr[0] = startX - 110.0f;
	vec2Arr[1] = startY - 320.0f;
	vec2Arr[2] = -30.0f;

	vec1Arr[0] = startX - 110.0f;
	vec1Arr[1] = startY - 405.0f;
	vec1Arr[2] = -30.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 110.0f, startY - 320.0f, 30.0f);
	glVertex3f(startX - 110.0f, startY - 320.0f, -30.0f);
	glVertex3f(startX - 110.0f, startY - 405.0f, -30.0f);
	glVertex3f(startX - 110.0f, startY - 405.0f, 30.0f);

	glEnd();

	//Student's glasses

	if (glasses)
	{
		glBegin(GL_LINES);

		glColor3f(0.0f, 0.0f, 0.0f); // Black
		glLineWidth(10.0f);
		glVertex3f(startX - 53.0f, startY - 40.0f, 52.5f);
		glVertex3f(startX - 78.0f, startY - 40.0f, 52.5f);

		glVertex3f(startX - 78.0f, startY - 40.0f, 52.5f);
		glVertex3f(startX - 78.0f, startY - 60.0f, 52.5f);

		glVertex3f(startX - 78.0f, startY - 60.0f, 52.5f);
		glVertex3f(startX - 53.0f, startY - 60.0f, 52.5f);

		glVertex3f(startX - 53.0f, startY - 60.0f, 52.5f);
		glVertex3f(startX - 53.0f, startY - 40.0f, 52.5f);

		glVertex3f(startX - 20.0f, startY - 40.0f, 52.5f);
		glVertex3f(startX - 46.0f, startY - 40.0f, 52.5f);

		glVertex3f(startX - 46.0f, startY - 40.0f, 52.5f);
		glVertex3f(startX - 46.0f, startY - 60.0f, 52.5f);

		glVertex3f(startX - 46.0f, startY - 60.0f, 52.5f);
		glVertex3f(startX - 20.0f, startY - 60.0f, 52.5f);

		glVertex3f(startX - 20.0f, startY - 60.0f, 52.5f);
		glVertex3f(startX - 20.0f, startY - 40.0f, 52.5f);

		glVertex3f(startX - 46.0f, startY - 50.0f, 52.5f);
		glVertex3f(startX - 53.0f, startY - 50.0f, 52.5f);

		glVertex3f(startX - 20.0f, startY - 50.0f, 52.5f);
		glVertex3f(startX, startY - 50.0f, 52.5f);

		glVertex3f(startX - 78.0f, startY - 50.0f, 52.5f);
		glVertex3f(startX - 100.0f, startY - 50.0f, 52.5f);

		glEnd();
	}

	// Student's right eye
	GLfloat theta, x, y;

	//right pupil
	glBegin(GL_POLYGON);

	glColor3f(0.0f, 0.0f, 0.0f); // Black

	for (int l = 0; l < 360; l++)
	{
		theta = 2.0 * 3.1415926f / 360 * float(l);
		x = cosf(theta);
		y = sinf(theta);
		glVertex3f(x * 2 + (startX - 65.0), y * 2 + (startY - 50.0), 52.1f);
	}

	glEnd();

	//right eye
	glBegin(GL_POLYGON);

	glColor3f(1.0f, 1.0f, 1.0f); // White

	for (int l = 0; l < 360; l++)
	{
		theta = 2.0 * 3.1415926f / 360 * float(l);
		x = cosf(theta);
		y = sinf(theta);
		glVertex3f(x * 7 + (startX - 65.0), y * 5 + (startY - 50.0), 52.0f);
	}

	glEnd();

	// Student's left eye

	//left pupil
	glBegin(GL_POLYGON);

	glColor3f(0.0f, 0.0f, 0.0f); // Black

	for (int l = 0; l < 360; l++)
	{
		theta = 2.0 * 3.1415926f / 360 * float(l);
		x = cosf(theta);
		y = sinf(theta);
		glVertex3f(x * 2 + (startX - 35.0), y * 2 + (startY - 50.0), 52.1f);
	}

	glEnd();

	//left eye
	glBegin(GL_POLYGON);

	glColor3f(1.0f, 1.0f, 1.0f); // White

	for (int l = 0; l < 360; l++)
	{
		theta = 2.0 * 3.1415926f / 360 * float(l);
		x = cosf(theta);
		y = sinf(theta);
		glVertex3f(x * 7 + (startX - 35.0), y * 5 + (startY - 50.0), 52.0f);
	}

	glEnd();

	// Student's nose
	glBegin(GL_LINES);

	glColor3f(0.0f, 0.0f, 0.0f); // Black
	glLineWidth(2.0);
	glVertex3f(startX - 50.0f, startY - 60.0f, 52.0f);
	glVertex3f(startX - 50.0f, startY - 70.0f, 52.0f);

	glEnd();

	// Student's mouth
	glBegin(GL_LINES);

	glColor3f(0.0f, 0.0f, 0.0f); // Black
	glLineWidth(2.0);
	glVertex3f(startX - 60.0f, startY - 80.0f, 52.0f);
	glVertex3f(startX - 40.0f, startY - 80.0f, 52.0f);

	glEnd();

	// Student's shirt

	if (shirtColor == 0)
	{
		glColor3f(1.0f, 1.0f, 1.0f); // White
	}
	else if (shirtColor == 1)
	{
		glColor3f(0.0f, 0.0f, 0.0f); // Black
	}
	else if (shirtColor == 2)
	{
		glColor3f(1.0f, 0.0f, 0.0f); // Red
	}
	else if (shirtColor == 3)
	{
		glColor3f(0.13f, 0.54f, 0.13f); // Green
	}
	else if (shirtColor == 4)
	{
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
	}
	else if (shirtColor == 5)
	{
		glColor3f(0.62f, 0.13f, 0.94f); // Purple
	}
	else if (shirtColor == 6)
	{
		glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	}
	else if (shirtColor == 7)
	{
		glColor3f(1.0f, 0.60f, 0.0f); // Orange
	}
	else if (shirtColor == 8)
	{
		glColor3f(1.0f, 0.41f, 0.70f); // Pink
	}
	else if (shirtColor == 9)
	{
		glColor3f(0.5f, 0.5f, 0.5f); // Gray
	}
	else if (shirtColor == 10)
	{
		glColor3f(0.55f, 0.27f, 0.07f); // Brown
	}
	else if (shirtColor == 11)
	{
		glColor3f(1.0f, 0.62f, 0.47f); // light pink
	}
	else if (shirtColor == 12)
	{
		glColor3f(0.80f, 0.43f, 0.15f); // Light Brown (tan)
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f); // Black
	}
	
	glBegin(GL_QUADS);

	//front

	vec1Arr[0] = startX + 20.0f;
	vec1Arr[1] = startY - 100.0f;
	vec1Arr[2] = 50.1f;

	vec2Arr[0] = startX + 20.0f;
	vec2Arr[1] = startY - 270.0f;
	vec2Arr[2] = 50.1f;

	vec3Arr[0] = startX - 120.0f;
	vec3Arr[1] = startY - 270.0f;
	vec3Arr[2] = 50.1f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 20.0f, startY - 100.0f, 50.1f);
	glVertex3f(startX - 120.0f, startY - 100.0f, 50.1f);
	glVertex3f(startX - 120.0f, startY - 270.0f, 50.1f);
	glVertex3f(startX + 20.0f, startY - 270.0f, 50.1f);

	//back

	vec1Arr[0] = startX + 20.0f;
	vec1Arr[1] = startY - 100.0f;
	vec1Arr[2] = -50.1f;

	vec2Arr[0] = startX - 120.0f;
	vec2Arr[1] = startY - 100.0f;
	vec2Arr[2] = -50.1f;

	vec3Arr[0] = startX - 120.0f;
	vec3Arr[1] = startY - 270.0f;
	vec3Arr[2] = -50.1f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 20.0f, startY - 100.0f, -50.1f);
	glVertex3f(startX - 120.0f, startY - 100.0f, -50.1f);
	glVertex3f(startX - 120.0f, startY - 270.0f, -50.1f);
	glVertex3f(startX + 20.0f, startY - 270.0f, -50.1f);

	//right side
	vec1Arr[0] = startX - 120.0f;
	vec1Arr[1] = startY - 100.0f;
	vec1Arr[2] = -50.1f;

	vec2Arr[0] = startX - 120.0f;
	vec2Arr[1] = startY - 100.0f;
	vec2Arr[2] = 50.1f;

	vec3Arr[0] = startX - 120.0f;
	vec3Arr[1] = startY - 270.0f;
	vec3Arr[2] = 50.1f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 120.0f, startY - 100.0f, 50.1f);
	glVertex3f(startX - 120.0f, startY - 100.0f, -50.1f);
	glVertex3f(startX - 120.0f, startY - 270.0f, -50.1f);
	glVertex3f(startX - 120.0f, startY - 270.0f, 50.1f);

	//left side
	vec1Arr[0] = startX + 20.0f;
	vec1Arr[1] = startY - 100.0f;
	vec1Arr[2] = 50.1f;

	vec2Arr[0] = startX + 20.0f;
	vec2Arr[1] = startY - 100.0f;
	vec2Arr[2] = -50.1f;

	vec3Arr[0] = startX + 20.0f;
	vec3Arr[1] = startY - 270.0f;
	vec3Arr[2] = -50.1f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 20.0f, startY - 100.0f, 50.1f);
	glVertex3f(startX + 20.0f, startY - 100.0f, -50.1f);
	glVertex3f(startX + 20.0f, startY - 270.0f, -50.1f);
	glVertex3f(startX + 20.0f, startY - 270.0f, 50.1f);

	glEnd();

	// Student's right shirt arm
	glBegin(GL_QUADS);

	vec3Arr[0] = startX - 120.0f;
	vec3Arr[1] = startY - 100.0f;
	vec3Arr[2] = 50.0f;

	vec2Arr[0] = startX - 160.0f;
	vec2Arr[1] = startY - 150.0f;
	vec2Arr[2] = 50.0f;

	vec1Arr[0] = startX - 130.0f;
	vec1Arr[1] = startY - 190.0f;
	vec1Arr[2] = 50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 120.0f, startY - 100.0f, 50.0f);
	glVertex3f(startX - 160.0f, startY - 150.0f, 50.0f);
	glVertex3f(startX - 130.0f, startY - 190.0f, 50.0f);
	glVertex3f(startX - 120.0f, startY - 170.0f, 50.0f);

	vec1Arr[0] = startX - 120.0f;
	vec1Arr[1] = startY - 100.0f;
	vec1Arr[2] = -50.0f;

	vec2Arr[0] = startX - 160.0f;
	vec2Arr[1] = startY - 150.0f;
	vec2Arr[2] = -50.0f;

	vec3Arr[0] = startX - 130.0f;
	vec3Arr[1] = startY - 190.0f;
	vec3Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 120.0f, startY - 100.0f, -50.0f);
	glVertex3f(startX - 160.0f, startY - 150.0f, -50.0f);
	glVertex3f(startX - 130.0f, startY - 190.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 170.0f, -50.0f);

	vec1Arr[0] = startX - 120.0f;
	vec1Arr[1] = startY - 100.0f;
	vec1Arr[2] = 50.0f;

	vec2Arr[0] = startX - 160.0f;
	vec2Arr[1] = startY - 150.0f;
	vec2Arr[2] = 50.0f;

	vec3Arr[0] = startX - 160.0f;
	vec3Arr[1] = startY - 150.0f;
	vec3Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 120.0f, startY - 100.0f, 50.0f);
	glVertex3f(startX - 160.0f, startY - 150.0f, 50.0f);
	glVertex3f(startX - 160.0f, startY - 150.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 100.0f, -50.0f);

	vec1Arr[0] = startX - 120.0f;
	vec1Arr[1] = startY - 170.0f;
	vec1Arr[2] = 50.0f;

	vec2Arr[0] = startX - 130.0f;
	vec2Arr[1] = startY - 190.0f;
	vec2Arr[2] = 50.0f;

	vec3Arr[0] = startX - 130.0f;
	vec3Arr[1] = startY - 190.0f;
	vec3Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 120.0f, startY - 170.0f, 50.0f);
	glVertex3f(startX - 130.0f, startY - 190.0f, 50.0f);
	glVertex3f(startX - 130.0f, startY - 190.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 170.0f, -50.0f);

	glEnd();

	// Student's left shirt arm
	glBegin(GL_QUADS);

	vec1Arr[0] = startX + 20.0f;
	vec1Arr[1] = startY - 100.0f;
	vec1Arr[2] = 50.0f;

	vec2Arr[0] = startX + 60.0f;
	vec2Arr[1] = startY - 150.0f;
	vec2Arr[2] = 50.0f;

	vec3Arr[0] = startX + 30.0f;
	vec3Arr[1] = startY - 190.0f;
	vec3Arr[2] = 50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 20.0f, startY - 100.0f, 50.0f);
	glVertex3f(startX + 60.0f, startY - 150.0f, 50.0f);
	glVertex3f(startX + 30.0f, startY - 190.0f, 50.0f);
	glVertex3f(startX + 20.0f, startY - 170.0f, 50.0f);

	vec3Arr[0] = startX + 20.0f;
	vec3Arr[1] = startY - 100.0f;
	vec3Arr[2] = -50.0f;

	vec2Arr[0] = startX + 60.0f;
	vec2Arr[1] = startY - 150.0f;
	vec2Arr[2] = -50.0f;

	vec1Arr[0] = startX + 30.0f;
	vec1Arr[1] = startY - 190.0f;
	vec1Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 20.0f, startY - 100.0f, -50.0f);
	glVertex3f(startX + 60.0f, startY - 150.0f, -50.0f);
	glVertex3f(startX + 30.0f, startY - 190.0f, -50.0f);
	glVertex3f(startX + 20.0f, startY - 170.0f, -50.0f);

	vec3Arr[0] = startX + 20.0f;
	vec3Arr[1] = startY - 100.0f;
	vec3Arr[2] = 50.0f;

	vec2Arr[0] = startX + 60.0f;
	vec2Arr[1] = startY - 150.0f;
	vec2Arr[2] = 50.0f;

	vec1Arr[0] = startX + 60.0f;
	vec1Arr[1] = startY - 150.0f;
	vec1Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 20.0f, startY - 100.0f, 50.0f);
	glVertex3f(startX + 60.0f, startY - 150.0f, 50.0f);
	glVertex3f(startX + 60.0f, startY - 150.0f, -50.0f);
	glVertex3f(startX + 20.0f, startY - 100.0f, -50.0f);

	vec1Arr[0] = startX + 30.0f;
	vec1Arr[1] = startY - 190.0f;
	vec1Arr[2] = 50.0f;

	vec2Arr[0] = startX + 20.0f;
	vec2Arr[1] = startY - 170.0f;
	vec2Arr[2] = 50.0f;

	vec3Arr[0] = startX + 20.0f;
	vec3Arr[1] = startY - 170.0f;
	vec3Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 30.0f, startY - 190.0f, 50.0f);
	glVertex3f(startX + 20.0f, startY - 170.0f, 50.0f);
	glVertex3f(startX + 20.0f, startY - 170.0f, -50.0f);
	glVertex3f(startX + 30.0f, startY - 190.0f, -50.0f);

	glEnd();

	// Student's shirt engineer logo

	if (shirtLogo)
	{
		//white large circle
		glBegin(GL_POLYGON);

		glColor3f(1.0f, 1.0f, 1.0f); // White

		for (int l = 0; l < 360; l++)
		{
			theta = 2.0 * 3.1415926f / 360 * float(l);
			x = cosf(theta);
			y = sinf(theta);
			glVertex3f(x * 50 + (startX - 50.0), y * 50 + (startY - 170.0), 51.0f);
		}

		glEnd();

		//small circle top left
		glBegin(GL_POLYGON);

		glColor3f(1.0f, 1.0f, 1.0f); // White

		for (int l = 0; l < 360; l++)
		{
			theta = 2.0 * 3.1415926f / 360 * float(l);
			x = cosf(theta);
			y = sinf(theta);
			glVertex3f(x * 15 + (startX - 65.0), y * 15 + (startY - 150.0), 51.5f);
		}

		glEnd();

		//small circle botton right
		glBegin(GL_POLYGON);

		glColor3f(1.0f, 1.0f, 1.0f); // White

		for (int l = 0; l < 360; l++)
		{
			theta = 2.0 * 3.1415926f / 360 * float(l);
			x = cosf(theta);
			y = sinf(theta);
			glVertex3f(x * 15 + (startX - 35.0), y * 15 + (startY - 190.0), 51.5f);
		}

		glEnd();

		//black large circle
		glBegin(GL_POLYGON);

		glColor3f(0.0f, 0.0f, 0.0f); // Black

		for (int l = 0; l < 360; l++)
		{
			theta = 2.0 * 3.1415926f / 360 * float(l);
			x = cosf(theta);
			y = sinf(theta);
			glVertex3f(x * 47 + (startX - 50.0), y * 47 + (startY - 170.0), 51.2f);
		}

		glEnd();

		//square top left
		glBegin(GL_POLYGON);

		glColor3f(0.0f, 0.0f, 0.0f); // Black

		glVertex3f(startX - 80.0f, startY - 140.0f, 51.7f);
		glVertex3f(startX - 70.0f, startY - 130.0f, 51.7f);
		glVertex3f(startX - 55.0f, startY - 150.0f, 51.7f);
		glVertex3f(startX - 65.0f, startY - 160.0f, 51.7f);

		glEnd();

		//square bottom right
		glBegin(GL_POLYGON);

		glColor3f(0.0f, 0.0f, 0.0f); // Black

		glVertex3f(startX - 45.0f, startY - 190.0f, 51.7f);
		glVertex3f(startX - 35.0f, startY - 180.0f, 51.7f);
		glVertex3f(startX - 20.0f, startY - 200.0f, 51.7f);
		glVertex3f(startX - 30.0f, startY - 210.0f, 51.7f);

		glEnd();

		//handle of wrench
		glBegin(GL_POLYGON);

		glColor3f(1.0f, 1.0f, 1.0f); // White

		glVertex3f(startX - 80.0f, startY - 145.0f, 51.5f);
		glVertex3f(startX - 70.0f, startY - 135.0f, 51.5f);
		glVertex3f(startX - 20.0f, startY - 195.0f, 51.5f);
		glVertex3f(startX - 30.0f, startY - 205.0f, 51.5f);

		glEnd();
	}

	// Student's hair
	
	if (hairColor == 0)
	{
		glColor3f(1.0f, 1.0f, 1.0f); // White
	}
	else if (hairColor == 1)
	{
		glColor3f(0.0f, 0.0f, 0.0f); // Black
	}
	else if (hairColor == 2)
	{
		glColor3f(1.0f, 0.0f, 0.0f); // Red
	}
	else if (hairColor == 3)
	{
		glColor3f(0.13f, 0.54f, 0.13f); // Green
	}
	else if (hairColor == 4)
	{
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
	}
	else if (hairColor == 5)
	{
		glColor3f(0.62f, 0.13f, 0.94f); // Purple
	}
	else if (hairColor == 6)
	{
		glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	}
	else if (hairColor == 7)
	{
		glColor3f(1.0f, 0.60f, 0.0f); // Orange
	}
	else if (hairColor == 8)
	{
		glColor3f(1.0f, 0.41f, 0.70f); // Pink
	}
	else if (hairColor == 9)
	{
		glColor3f(0.5f, 0.5f, 0.5f); // Gray
	}
	else if(hairColor == 10)
	{
		glColor3f(0.55f, 0.27f, 0.07f); // Brown
	}
	else if (hairColor == 11)
	{
		glColor3f(1.0f, 0.62f, 0.47f); // light pink
	}
	else if (hairColor == 12)
	{
		glColor3f(0.80f, 0.43f, 0.15f); // Light Brown (tan)
	}
	else
	{
		glColor3f(0.55f, 0.27f, 0.07f); // Brown
	}

	glBegin(GL_QUADS);

	//bangs
	vec1Arr[0] = startX + 6.0f;
	vec1Arr[1] = startY;
	vec1Arr[2] = 55.3f;

	vec2Arr[0] = startX + 20.0f;
	vec2Arr[1] = startY;
	vec2Arr[2] = 55.3f;

	vec3Arr[0] = startX + 20.0f;
	vec3Arr[1] = startY - 30.0f;
	vec3Arr[2] = 55.3f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 6.0f, startY, 55.3f);
	glVertex3f(startX - 106.0f, startY, 55.3f);
	glVertex3f(startX - 106.0f, startY - 30.0f, 55.3f);
	glVertex3f(startX + 6.0f, startY - 30.0f, 55.3f);

	//top
	vec3Arr[0] = startX + 6.0f;
	vec3Arr[1] = startY;
	vec3Arr[2] = 55.3f;

	vec1Arr[0] = startX - 106.0f;
	vec1Arr[1] = startY;
	vec1Arr[2] = 55.3f;

	vec2Arr[0] = startX - 106.0f;
	vec2Arr[1] = startY;
	vec2Arr[2] = -55.3f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 6.0f, startY, 55.3f);
	glVertex3f(startX - 106.0f, startY, 55.3f);
	glVertex3f(startX - 106.0f, startY, -55.3f);
	glVertex3f(startX + 6.0f, startY, -55.3f);

	if (girl) //girl
	{
		//right side

		vec3Arr[0] = startX - 106.0f;
		vec3Arr[1] = startY;
		vec3Arr[2] = 55.3f;

		vec2Arr[0] = startX - 106.0f;
		vec2Arr[1] = startY;
		vec2Arr[2] = -55.3f;

		vec1Arr[0] = startX - 106.0f;
		vec1Arr[1] = startY - 100.0f;
		vec1Arr[2] = -55.3f;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glNormal3f(x, y, z);
		glVertex3f(startX - 106.0f, startY, 55.3f);
		glVertex3f(startX - 106.0f, startY, -55.3f);
		glVertex3f(startX - 106.0f, startY - 100.0f, -55.3f);
		glVertex3f(startX - 106.0f, startY - 100.0f, 55.3f);

		//left side
		vec3Arr[0] = startX + 6.0f;
		vec3Arr[1] = startY;
		vec3Arr[2] = 55.3f;

		vec2Arr[0] = startX + 6.0f;
		vec2Arr[1] = startY - 100.0f;
		vec2Arr[2] = 55.3f;

		vec1Arr[0] = startX + 6.0f;
		vec1Arr[1] = startY - 100.0f;
		vec1Arr[2] = -55.3f;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glNormal3f(x, y, z);
		glVertex3f(startX + 6.0f, startY, 55.3f);
		glVertex3f(startX + 6.0f, startY - 100.0f, 55.3f);
		glVertex3f(startX + 6.0f, startY - 100.0f, -55.3f);
		glVertex3f(startX + 6.0f, startY, -55.3f);

		//left front
		vec3Arr[0] = startX - 86.0f;
		vec3Arr[1] = startY;
		vec3Arr[2] = 55.3f;

		vec2Arr[0] = startX - 106.0f;
		vec2Arr[1] = startY;
		vec2Arr[2] = 55.3f;

		vec1Arr[0] = startX - 106.0f;
		vec1Arr[1] = startY - 200.0f;
		vec1Arr[2] = 55.3f;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glNormal3f(x, y, z);
		glVertex3f(startX - 86.0f, startY, 55.3f);
		glVertex3f(startX - 106.0f, startY, 55.3f);
		glVertex3f(startX - 106.0f, startY - 200.0f, 55.3f);
		glVertex3f(startX - 86.0f, startY - 200.0f, 55.3f);

		//right front
		vec3Arr[0] = startX + 6.0f;
		vec3Arr[1] = startY;
		vec3Arr[2] = 55.3f;

		vec2Arr[0] = startX - 15.0f;
		vec2Arr[1] = startY;
		vec2Arr[2] = 55.3f;

		vec1Arr[0] = startX - 15.0f;
		vec1Arr[1] = startY - 200.0f;
		vec1Arr[2] = 55.3f;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glNormal3f(x, y, z);
		glVertex3f(startX + 6.0f, startY, 55.3f);
		glVertex3f(startX - 15.0f, startY, 55.3f);
		glVertex3f(startX - 15.0f, startY - 200.0f, 55.3f);
		glVertex3f(startX + 6.0f, startY - 200.0f, 55.3f);

		//back
		vec1Arr[0] = startX + 6.0f;
		vec1Arr[1] = startY;
		vec1Arr[2] = -55.3f;

		vec2Arr[0] = startX - 106.0f;
		vec2Arr[1] = startY;
		vec2Arr[2] = -55.3f;

		vec3Arr[0] = startX - 106.0f;
		vec3Arr[1] = startY - 200.0f;
		vec3Arr[2] = -55.3f;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glNormal3f(x, y, z);
		glVertex3f(startX + 6.0f, startY, -55.3f);
		glVertex3f(startX - 106.0f, startY, -55.3f);
		glVertex3f(startX - 106.0f, startY - 200.0f, -55.3f);
		glVertex3f(startX + 6.0f, startY - 200.0f, -55.3f);
	}
	else //boy
	{
		//right side
		vec3Arr[0] = startX - 106.0f;
		vec3Arr[1] = startY;
		vec3Arr[2] = 55.3f;

		vec2Arr[0] = startX - 106.0f;
		vec2Arr[1] = startY;
		vec2Arr[2] = -55.3f;

		vec1Arr[0] = startX - 106.0f;
		vec1Arr[1] = startY - 50.0f;
		vec1Arr[2] = -55.3f;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glNormal3f(x, y, z);
		glVertex3f(startX - 106.0f, startY, 55.3f);
		glVertex3f(startX - 106.0f, startY, -55.3f);
		glVertex3f(startX - 106.0f, startY - 50.0f, -55.3f);
		glVertex3f(startX - 106.0f, startY - 50.0f, 55.3f);

		//left side
		vec3Arr[0] = startX + 6.0f;
		vec3Arr[1] = startY;
		vec3Arr[2] = 55.3f;

		vec2Arr[0] = startX + 6.0f;
		vec2Arr[1] = startY - 50.0f;
		vec2Arr[2] = 55.3f;

		vec1Arr[0] = startX + 6.0f;
		vec1Arr[1] = startY - 50.0f;
		vec1Arr[2] = -55.3f;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glNormal3f(x, y, z);
		glVertex3f(startX + 6.0f, startY, 55.3f);
		glVertex3f(startX + 6.0f, startY - 50.0f, 55.3f);
		glVertex3f(startX + 6.0f, startY - 50.0f, -55.3f);
		glVertex3f(startX + 6.0f, startY, -55.3f);

		//back
		vec1Arr[0] = startX + 6.0f;
		vec1Arr[1] = startY;
		vec1Arr[2] = -55.3f;

		vec2Arr[0] = startX - 106.0f;
		vec2Arr[1] = startY;
		vec2Arr[2] = -55.3f;

		vec3Arr[0] = startX - 106.0f;
		vec3Arr[1] = startY - 50.0f;
		vec3Arr[2] = -55.3f;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glNormal3f(x, y, z);
		glVertex3f(startX + 6.0f, startY, -55.3f);
		glVertex3f(startX - 106.0f, startY, -55.3f);
		glVertex3f(startX - 106.0f, startY - 50.0f, -55.3f);
		glVertex3f(startX + 6.0f, startY - 50.0f, -55.3f);
	}

	glEnd();

	// Student's 3DS

	if (n3DS)
	{
		//base
		glBegin(GL_QUADS);

		glColor3f(0.0f, 0.0f, 0.0f); // Black

		glVertex3f(startX + 120.0f, startY - 180.0f, 21.0f);
		glVertex3f(startX + 85.0f, startY - 170.0f, 21.0f);
		glVertex3f(startX + 85.0f, startY - 200.0f, 21.0f);
		glVertex3f(startX + 120.0f, startY - 210.0f, 21.0f);

		glVertex3f(startX + 120.0f, startY - 210.0f, 21.0f);
		glVertex3f(startX + 85.0f, startY - 200.0f, 21.0f);
		glVertex3f(startX + 65.0f, startY - 220.0f, 21.0f);
		glVertex3f(startX + 100.0f, startY - 230.0f, 21.0f);

		glColor3f(0.5f, 0.5f, 0.5f); // Gray

		glVertex3f(startX + 110.0f, startY - 210.0f, 21.8f);
		glVertex3f(startX + 90.0f, startY - 205.0f, 21.8f);
		glVertex3f(startX + 75.0f, startY - 220.0f, 21.8f);
		glVertex3f(startX + 95.0f, startY - 225.0f, 21.8f);

		glEnd();

		//pad
		glBegin(GL_POLYGON);

		glColor3f(0.5f, 0.5f, 0.5f); // Gray

		for (int l = 0; l < 360; l++)
		{
			theta = 2.0 * 3.1415926f / 360 * float(l);
			x = cosf(theta);
			y = sinf(theta);
			glVertex3f(x * 2.8 + (startX + 83.0), y * 2.8 + (startY - 206.0), 21.5f);
		}

		glEnd();

		//buttons
		glBegin(GL_POLYGON);

		for (int l = 0; l < 360; l++)
		{
			theta = 2.0 * 3.1415926f / 360 * float(l);
			x = cosf(theta);
			y = sinf(theta);
			glVertex3f(x * 1.0 + (startX + 110.0), y * 1.0 + (startY - 215.0), 21.5f);
		}

		glEnd();

		glBegin(GL_POLYGON);

		for (int l = 0; l < 360; l++)
		{
			theta = 2.0 * 3.1415926f / 360 * float(l);
			x = cosf(theta);
			y = sinf(theta);
			glVertex3f(x * 1.0 + (startX + 107.0), y * 1.0 + (startY - 215.0), 21.5f);
		}

		glEnd();

		glBegin(GL_POLYGON);

		for (int l = 0; l < 360; l++)
		{
			theta = 2.0 * 3.1415926f / 360 * float(l);
			x = cosf(theta);
			y = sinf(theta);
			glVertex3f(x * 1.0 + (startX + 107.0), y * 1.0 + (startY - 218.0), 21.5f);
		}

		glEnd();

		glBegin(GL_POLYGON);

		for (int l = 0; l < 360; l++)
		{
			theta = 2.0 * 3.1415926f / 360 * float(l);
			x = cosf(theta);
			y = sinf(theta);
			glVertex3f(x * 1.0 + (startX + 110.0), y * 1.0 + (startY - 218.0), 21.5f);
		}

		glEnd();
	}

	// Student's shorts

	glBegin(GL_QUADS);

	if (shortColor == 0)
	{
		glColor3f(1.0f, 1.0f, 1.0f); // White
	}
	else if (shortColor == 1)
	{
		glColor3f(0.0f, 0.0f, 0.0f); // Black
	}
	else if (shortColor == 2)
	{
		glColor3f(1.0f, 0.0f, 0.0f); // Red
	}
	else if (shortColor == 3)
	{
		glColor3f(0.13f, 0.54f, 0.13f); // Green
	}
	else if (shortColor == 4)
	{
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
	}
	else if (shortColor == 5)
	{
		glColor3f(0.62f, 0.13f, 0.94f); // Purple
	}
	else if (shortColor == 6)
	{
		glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	}
	else if (shortColor == 7)
	{
		glColor3f(1.0f, 0.60f, 0.0f); // Orange
	}
	else if (shortColor == 8)
	{
		glColor3f(1.0f, 0.41f, 0.70f); // Pink
	}
	else if (shortColor == 9)
	{
		glColor3f(0.5f, 0.5f, 0.5f); // Gray
	}
	else if (shortColor == 10)
	{
		glColor3f(0.55f, 0.27f, 0.07f); // Brown
	}
	else if (shortColor == 11)
	{
		glColor3f(1.0f, 0.62f, 0.47f); // light pink
	}
	else if (shortColor == 12)
	{
		glColor3f(0.80f, 0.43f, 0.15f); // Light Brown (tan)
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.5f); // Navy blue
	}

	//base
	vec3Arr[0] = startX + 20.0f;
	vec3Arr[1] = startY - 270.0f;
	vec3Arr[2] = 50.0f;

	vec2Arr[0] = startX - 120.0f;
	vec2Arr[1] = startY - 270.0f;
	vec2Arr[2] = 50.0f;

	vec1Arr[0] = startX - 120.0f;
	vec1Arr[1] = startY - 300.0f;
	vec1Arr[2] = 50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 20.0f, startY - 270.0f, 50.0f);
	glVertex3f(startX - 120.0f, startY - 270.0f, 50.0f);
	glVertex3f(startX - 120.0f, startY - 300.0f, 50.0f);
	glVertex3f(startX + 20.0f, startY - 300.0f, 50.0f);

	vec1Arr[0] = startX + 20.0f;
	vec1Arr[1] = startY - 270.0f;
	vec1Arr[2] = -50.0f;

	vec2Arr[0] = startX - 120.0f;
	vec2Arr[1] = startY - 270.0f;
	vec2Arr[2] = -50.0f;

	vec3Arr[0] = startX - 120.0f;
	vec3Arr[1] = startY - 300.0f;
	vec3Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 20.0f, startY - 270.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 270.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 300.0f, -50.0f);
	glVertex3f(startX + 20.0f, startY - 300.0f, -50.0f);

	//right side
	vec3Arr[0] = startX - 120.0f;
	vec3Arr[1] = startY - 270.0f;
	vec3Arr[2] = 50.0f;

	vec2Arr[0] = startX - 120.0f;
	vec2Arr[1] = startY - 270.0f;
	vec2Arr[2] = -50.0f;

	vec1Arr[0] = startX - 120.0f;
	vec1Arr[1] = startY - 320.0f;
	vec1Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 120.0f, startY - 270.0f, 50.0f);
	glVertex3f(startX - 120.0f, startY - 270.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 320.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 320.0f, 50.0f);

	//left side
	vec1Arr[0] = startX + 20.0f;
	vec1Arr[1] = startY - 270.0f;
	vec1Arr[2] = 50.0f;

	vec2Arr[0] = startX + 20.0f;
	vec2Arr[1] = startY - 270.0f;
	vec2Arr[2] = -50.0f;

	vec3Arr[0] = startX + 20.0f;
	vec3Arr[1] = startY - 320.0f;
	vec3Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 20.0f, startY - 270.0f, 50.0f);
	glVertex3f(startX + 20.0f, startY - 270.0f, -50.0f);
	glVertex3f(startX + 20.0f, startY - 320.0f, -50.0f);
	glVertex3f(startX + 20.0f, startY - 320.0f, 50.0f);

	//right pant
	vec3Arr[0] = startX + 20.0f;
	vec3Arr[1] = startY - 300.0f;
	vec3Arr[2] = 50.0f;

	vec2Arr[0] = startX - 45.0f;
	vec2Arr[1] = startY - 300.0f;
	vec2Arr[2] = 50.0f;

	vec1Arr[0] = startX - 45.0f;
	vec1Arr[1] = startY - 320.0f;
	vec1Arr[2] = 50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 20.0f, startY - 300.0f, 50.0f);
	glVertex3f(startX - 45.0f, startY - 300.0f, 50.0f);
	glVertex3f(startX - 45.0f, startY - 320.0f, 50.0f);
	glVertex3f(startX + 20.0f, startY - 320.0f, 50.0f);

	vec1Arr[0] = startX + 20.0f;
	vec1Arr[1] = startY - 300.0f;
	vec1Arr[2] = -50.0f;

	vec2Arr[0] = startX - 45.0f;
	vec2Arr[1] = startY - 300.0f;
	vec2Arr[2] = -50.0f;

	vec3Arr[0] = startX - 45.0f;
	vec3Arr[1] = startY - 320.0f;
	vec3Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 20.0f, startY - 300.0f, -50.0f);
	glVertex3f(startX - 45.0f, startY - 300.0f, -50.0f);
	glVertex3f(startX - 45.0f, startY - 320.0f, -50.0f);
	glVertex3f(startX + 20.0f, startY - 320.0f, -50.0f);

	vec1Arr[0] = startX - 45.0f;
	vec1Arr[1] = startY - 300.0f;
	vec1Arr[2] = 50.0f;

	vec2Arr[0] = startX - 45.0f;
	vec2Arr[1] = startY - 300.0f;
	vec2Arr[2] = -50.0f;

	vec3Arr[0] = startX - 45.0f;
	vec3Arr[1] = startY - 320.0f;
	vec3Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 45.0f, startY - 300.0f, 50.0f);
	glVertex3f(startX - 45.0f, startY - 300.0f, -50.0f);
	glVertex3f(startX - 45.0f, startY - 320.0f, -50.0f);
	glVertex3f(startX - 45.0f, startY - 320.0f, 50.0f);

	//left pant
	vec3Arr[0] = startX - 55.0f;
	vec3Arr[1] = startY - 300.0f;
	vec3Arr[2] = 50.0f;

	vec2Arr[0] = startX - 120.0f;
	vec2Arr[1] = startY - 300.0f;
	vec2Arr[2] = 50.0f;

	vec1Arr[0] = startX - 120.0f;
	vec1Arr[1] = startY - 320.0f;
	vec1Arr[2] = 50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 55.0f, startY - 300.0f, 50.0f);
	glVertex3f(startX - 120.0f, startY - 300.0f, 50.0f);
	glVertex3f(startX - 120.0f, startY - 320.0f, 50.0f);
	glVertex3f(startX - 55.0f, startY - 320.0f, 50.0f);

	vec1Arr[0] = startX - 55.0f;
	vec1Arr[1] = startY - 300.0f;
	vec1Arr[2] = -50.0f;

	vec2Arr[0] = startX - 120.0f;
	vec2Arr[1] = startY - 300.0f;
	vec2Arr[2] = -50.0f;

	vec3Arr[0] = startX - 120.0f;
	vec3Arr[1] = startY - 320.0f;
	vec3Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 55.0f, startY - 300.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 300.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 320.0f, -50.0f);
	glVertex3f(startX - 55.0f, startY - 320.0f, -50.0f);

	vec1Arr[0] = startX - 55.0f;
	vec1Arr[1] = startY - 300.0f;
	vec1Arr[2] = 50.0f;

	vec2Arr[0] = startX - 55.0f;
	vec2Arr[1] = startY - 300.0f;
	vec2Arr[2] = -50.0f;

	vec3Arr[0] = startX - 55.0f;
	vec3Arr[1] = startY - 320.0f;
	vec3Arr[2] = -50.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 55.0f, startY - 300.0f, 50.0f);
	glVertex3f(startX - 55.0f, startY - 300.0f, -50.0f);
	glVertex3f(startX - 55.0f, startY - 320.0f, -50.0f);
	glVertex3f(startX - 55.0f, startY - 320.0f, 50.0f);

	glEnd();

	//Student's short pockets
	glBegin(GL_LINE_LOOP);

	glColor3f(0.0f, 0.0f, 0.0f); // black

	glVertex3f(startX + 5.0f, startY - 270.0f, -51.5f);
	glVertex3f(startX - 25.0, startY - 270.0f, -51.5f);
	glVertex3f(startX - 25.0f, startY - 300.0f, -51.5f);
	glVertex3f(startX + 5.0f, startY - 300.0f, -51.5f);

	glEnd();

	glBegin(GL_LINE_LOOP);

	glColor3f(0.0f, 0.0f, 0.0f); // black

	glVertex3f(startX - 100.0f, startY - 270.0f, -51.5f);
	glVertex3f(startX - 70.0, startY - 270.0f, -51.5f);
	glVertex3f(startX - 70.0f, startY - 300.0f, -51.5f);
	glVertex3f(startX - 100.0f, startY - 300.0f, -51.5f);

	glEnd();

	//Student's shoes

	if (shoeColor == 0)
	{
		glColor3f(1.0f, 1.0f, 1.0f); // White
	}
	else if (shoeColor == 1)
	{
		glColor3f(0.0f, 0.0f, 0.0f); // Black
	}
	else if (shoeColor == 2)
	{
		glColor3f(1.0f, 0.0f, 0.0f); // Red
	}
	else if (shoeColor == 3)
	{
		glColor3f(0.13f, 0.54f, 0.13f); // Green
	}
	else if (shoeColor == 4)
	{
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
	}
	else if (shoeColor == 5)
	{
		glColor3f(0.62f, 0.13f, 0.94f); // Purple
	}
	else if (shoeColor == 6)
	{
		glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	}
	else if (shoeColor == 7)
	{
		glColor3f(1.0f, 0.60f, 0.0f); // Orange
	}
	else if (shoeColor == 8)
	{
		glColor3f(1.0f, 0.41f, 0.70f); // Pink
	}
	else if (shoeColor == 9)
	{
		glColor3f(0.5f, 0.5f, 0.5f); // Gray
	}
	else if (shoeColor == 10)
	{
		glColor3f(0.55f, 0.27f, 0.07f); // Brown
	}
	else if (shoeColor == 11)
	{
		glColor3f(1.0f, 0.62f, 0.47f); // light pink
	}
	else if (shoeColor == 12)
	{
		glColor3f(0.80f, 0.43f, 0.15f); // Light Brown (tan)
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f); // black
	}

	glBegin(GL_QUADS);

	//left shoe
	vec3Arr[0] = startX + 15.0f;
	vec3Arr[1] = startY - 405.0f;
	vec3Arr[2] = 60.0f;

	vec2Arr[0] = startX - 40.0f;
	vec2Arr[1] = startY - 405.0f;
	vec2Arr[2] = 60.0f;

	vec1Arr[0] = startX - 40.0f;
	vec1Arr[1] = startY - 440.0f;
	vec1Arr[2] = 60.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 15.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 40.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 40.0f, startY - 440.0f, 60.0f);
	glVertex3f(startX + 15.0f, startY - 440.0f, 60.0f);

	vec1Arr[0] = startX + 15.0f;
	vec1Arr[1] = startY - 405.0f;
	vec1Arr[2] = 60.0f;

	vec2Arr[0] = startX - 40.0f;
	vec2Arr[1] = startY - 405.0f;
	vec2Arr[2] = 60.0f;

	vec3Arr[0] = startX - 40.0f;
	vec3Arr[1] = startY - 405.0f;
	vec3Arr[2] = -35.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 15.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 40.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 40.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX + 15.0f, startY - 405.0f, -35.0f);

	vec1Arr[0] = startX + 15.0f;
	vec1Arr[1] = startY - 405.0f;
	vec1Arr[2] = -35.0f;

	vec2Arr[0] = startX - 40.0f;
	vec2Arr[1] = startY - 405.0f;
	vec2Arr[2] = -35.0f;

	vec3Arr[0] = startX - 40.0f;
	vec3Arr[1] = startY - 440.0f;
	vec3Arr[2] = -35.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 15.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX - 40.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX - 40.0f, startY - 440.0f, -35.0f);
	glVertex3f(startX + 15.0f, startY - 440.0f, -35.0f);

	vec3Arr[0] = startX - 40.0f;
	vec3Arr[1] = startY - 405.0f;
	vec3Arr[2] = 60.0f;

	vec2Arr[0] = startX - 40.0f;
	vec2Arr[1] = startY - 405.0f;
	vec2Arr[2] = -35.0f;

	vec1Arr[0] = startX - 40.0f;
	vec1Arr[1] = startY - 440.0f;
	vec1Arr[2] = -35.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 40.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 40.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX - 40.0f, startY - 440.0f, -35.0f);
	glVertex3f(startX - 40.0f, startY - 440.0f, 60.0f);

	vec1Arr[0] = startX + 15.0f;
	vec1Arr[1] = startY - 405.0f;
	vec1Arr[2] = 60.0f;

	vec2Arr[0] = startX + 15.0f;
	vec2Arr[1] = startY - 405.0f;
	vec2Arr[2] = -35.0f;

	vec3Arr[0] = startX + 15.0f;
	vec3Arr[1] = startY - 440.0f;
	vec3Arr[2] = -35.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX + 15.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX + 15.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX + 15.0f, startY - 440.0f, -35.0f);
	glVertex3f(startX + 15.0f, startY - 440.0f, 60.0f);

	glEnd();

	//right shoe
	glBegin(GL_QUADS);

	vec3Arr[0] = startX - 60.0f;
	vec3Arr[1] = startY - 405.0f;
	vec3Arr[2] = 60.0f;

	vec2Arr[0] = startX - 115.0f;
	vec2Arr[1] = startY - 405.0f;
	vec2Arr[2] = 60.0f;

	vec1Arr[0] = startX - 115.0f;
	vec1Arr[1] = startY - 440.0f;
	vec1Arr[2] = 60.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 60.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 115.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 115.0f, startY - 440.0f, 60.0f);
	glVertex3f(startX - 60.0f, startY - 440.0f, 60.0f);

	vec3Arr[0] = startX - 60.0f;
	vec3Arr[1] = startY - 405.0f;
	vec3Arr[2] = 60.0f;

	vec2Arr[0] = startX - 115.0f;
	vec2Arr[1] = startY - 405.0f;
	vec2Arr[2] = 60.0f;

	vec1Arr[0] = startX - 115.0f;
	vec1Arr[1] = startY - 405.0f;
	vec1Arr[2] = -35.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 60.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 115.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 115.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX - 60.0f, startY - 405.0f, -35.0f);

	vec1Arr[0] = startX - 60.0f;
	vec1Arr[1] = startY - 405.0f;
	vec1Arr[2] = -35.0f;

	vec2Arr[0] = startX - 115.0f;
	vec2Arr[1] = startY - 405.0f;
	vec2Arr[2] = -35.0f;

	vec3Arr[0] = startX - 115.0f;
	vec3Arr[1] = startY - 440.0f;
	vec3Arr[2] = -35.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 60.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX - 115.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX - 115.0f, startY - 440.0f, -35.0f);
	glVertex3f(startX - 60.0f, startY - 440.0f, -35.0f);

	vec3Arr[0] = startX - 115.0f;
	vec3Arr[1] = startY - 405.0f;
	vec3Arr[2] = 60.0f;

	vec2Arr[0] = startX - 115.0f;
	vec2Arr[1] = startY - 405.0f;
	vec2Arr[2] = -35.0f;

	vec1Arr[0] = startX - 115.0f;
	vec1Arr[1] = startY - 440.0f;
	vec1Arr[2] = -35.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 115.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 115.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX - 115.0f, startY - 440.0f, -35.0f);
	glVertex3f(startX - 115.0f, startY - 440.0f, 60.0f);

	vec1Arr[0] = startX - 60.0f;
	vec1Arr[1] = startY - 405.0f;
	vec1Arr[2] = 60.0f;

	vec2Arr[0] = startX - 60.0f;
	vec2Arr[1] = startY - 405.0f;
	vec2Arr[2] = -35.0f;

	vec3Arr[0] = startX - 60.0f;
	vec3Arr[1] = startY - 440.0f;
	vec3Arr[2] = -35.0f;

	CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

	glNormal3f(x, y, z);
	glVertex3f(startX - 60.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 60.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX - 60.0f, startY - 440.0f, -35.0f);
	glVertex3f(startX - 60.0f, startY - 440.0f, 60.0f);

	glEnd();

	//Pop Matrix
	glPopMatrix();
}

/*
This function draws the students and student center
*/
void
display(void)
{
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH); //Smooth shading
	glClearColor(0.52, 0.8, 0.92, 0.0); //Sky Blue background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Color and depth buffer clear

	//Set up perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f + zoom, 1000.0 / 800.0, 0.01, 6000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Toggle topdown mode with LookAt
	if (topDown == 1)
	{
		gluLookAt(moveX, 200 + zoom, moveY + 1.0,
			moveX, 0.0, moveY,
			0.0, 1.0, 0.0);
	}
	else if (switchController == 1) //bus
	{
		
		lightMode = 4;
		gluLookAt(moveX - 175.0, 70.0, moveY - 10.0,
			moveX-120.0, 0.0, moveY-100.0,
			0.0, 1.0, 0.0);
	}
	else if (switchController == 2)//camera
	{
		gluLookAt(moveX + 20 * sin((rotateStudent + 90) * M_PI / 180), 50 + zoom, moveY + 20 * cos((rotateStudent + 90) * M_PI / 180),
			moveX, headControl + 40.0, moveY,
			0.0, 1.0, 0.0);
	}
	else //main student
	{
		gluLookAt(moveX + 100 * sin((rotateStudent + 90) * M_PI / 180), 50 + zoom, moveY + 100 * cos((rotateStudent + 90) * M_PI / 180),
			moveX, headControl, moveY,
			0.0, 1.0, 0.0);
	}

	//Create Light Sources

	GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	//White Light
	GLfloat light_position0[] = { moveX + (50.0 * 0.05), 30.0, moveY + (220.0 * 0.05), 1.0 };
	GLfloat spot_direction0[] = { sin(M_PI / 180.0 * rotateStudent + 300.0), 0.0, cos(M_PI / 180.0 * rotateStudent + 300.0) };
	GLfloat light_ambient0[] = { 0.0 + lightIntensity, 0.0 + lightIntensity, 0.0 + lightIntensity, 1.0 };
	GLfloat light_diffuse0[] = { 0.5 + lightIntensity, 0.5 + lightIntensity, 0.5 + lightIntensity, 1.0 };
	GLfloat light_specular0[] = { 1.0 + lightIntensity, 1.0 + lightIntensity, 1.0 + lightIntensity, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction0);

	//Purple Light
	GLfloat light_position1[] = { 1200.0, 250.0, -150.0, 1.0 };
	GLfloat spot_direction1[] = { 0.0, -1.0, 0.0 };
	GLfloat light_ambient1[] = { 1.0 + lightIntensity, 0.0 + lightIntensity, 1.0 + lightIntensity, 1.0 };
	GLfloat light_diffuse1[] = { 0.5 + lightIntensity, 0.5 + lightIntensity, 0.5 + lightIntensity, 1.0 };
	GLfloat light_specular1[] = { 1.0 + lightIntensity, 1.0 + lightIntensity, 1.0 + lightIntensity, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction1);

	//Switch between light modes
	if (lightMode == 1)
	{
		glEnable(GL_LIGHT0); //white light
	}
	else if (lightMode == 2)
	{
		glDisable(GL_LIGHT0); //white light
		glEnable(GL_LIGHT1); //color light
	}
	else if (lightMode == 3)
	{
		//both
		glEnable(GL_LIGHT0);
	}
	else if (lightMode == 4)
	{
		//none
		glDisable(GL_LIGHT0); //white light
		glDisable(GL_LIGHT1); //color light
	}
	
	//Draw Students

	/*
	(Also in original method)
	For color choices :
	0 - white
	1 - black
	2 - red
	3 - green
	4 - blue
	5 - purple
	6 - yellow
	7 - orange
	8 - pink
	9 - gray
	10 - brown
	11 - light pink
	12 - light brown

	Method Call:
	drawStudent(bool transform, float rotate, bool girl, int hairColor, bool n3DS, bool shirtLogo, int shirtColor, int shortColor, bool glasses, int skinColor, int shoeColor)
	*/

	if ((posX > 0.0 && posX > 100.0) && (posY > -50.0 && posY > 50.0) && (posZ > 0.0 && posZ > 100.0))
	{
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glTranslatef(50.0f, 0.0f, 50.0f);
		glRotatef(45.0f, 1.0, 1.0, 0.0);
		glutSolidCube(1000.0);
		glTranslatef(15.0f, 5.0f, 15.0f);
		glRotatef(45.0f, 1.0, 1.0, 0.0);
		glutSolidCube(10.0);
		glPopMatrix();
	}

	//Moveable Student
	if (!(onTour))
	{
		
	}
	else
	{
		//take tour
		takeTour();
	}

	
	//Others

	if (switchController == 1)
	{
		drawStudent(0, 0.0, 1, 10, 1, 1, 1, 4, 1, 11, 1);
		glPushMatrix();
		glTranslatef(50.0f, 0.0f, 50.0f);
		drawStudent(0, 45.0, 1, 5, 0, 0, 1, 3, 1, 12, 8);
		glTranslatef(20.0f, 0.0f, 30.0f);
		drawStudent(0, 0.0, 1, 1, 1, 0, 2, 1, 0, 10, 1);
		glTranslatef(-100.0f, 0.0f, -100.0f);
		drawStudent(0, 180.0, 0, 10, 1, 0, 3, 1, 1, 12, 1);
		glTranslatef(220.0f, 0.0f, 220.0f);
		drawStudent(0, 0.0, 1, 6, 0, 0, 9, 10, 1, 11, 7);
		glTranslatef(500.0f, 0.0f, -200.0f);
		drawStudent(0, 0.0, 1, 4, 0, 0, 5, 1, 1, 12, 1);
		glTranslatef(100.0f, 0.0f, 50.0f);
		drawStudent(0, 0.0, 0, 2, 0, 0, 8, 1, 1, 11, 1);
		glPopMatrix();
	}
	else if (switchController == 2)
	{
		drawStudent(0, 0.0, 1, 10, 1, 1, 1, 4, 1, 11, 1);
		glPushMatrix();
		glTranslatef(50.0f, 0.0f, 50.0f);
		drawStudent(0, 45.0, 1, 5, 0, 0, 1, 3, 1, 12, 8);
		glTranslatef(20.0f, 0.0f, 30.0f);
		drawStudent(0, 0.0, 1, 1, 1, 0, 2, 1, 0, 10, 1);
		glTranslatef(-100.0f, 0.0f, -100.0f);
		drawStudent(0, 180.0, 0, 10, 1, 0, 3, 1, 1, 12, 1);
		glTranslatef(220.0f, 0.0f, 220.0f);
		drawStudent(0, 0.0, 1, 6, 0, 0, 9, 10, 1, 11, 7);
		glTranslatef(500.0f, 0.0f, -200.0f);
		drawStudent(0, 0.0, 1, 4, 0, 0, 5, 1, 1, 12, 1);
		glTranslatef(100.0f, 0.0f, 50.0f);
		drawStudent(0, 0.0, 0, 2, 0, 0, 8, 1, 1, 11, 1);
		glPopMatrix();
	}
	else
	{
		drawStudent(1, 0.0, 1, 10, 1, 1, 1, 4, 1, 11, 1);
		glPushMatrix();
		glTranslatef(50.0f, 0.0f, 50.0f);
		drawStudent(0, 45.0, 1, 5, 0, 0, 1, 3, 1, 12, 8);
		glTranslatef(20.0f, 0.0f, 30.0f);
		drawStudent(0, 90.0, 1, 1, 1, 0, 2, 1, 0, 10, 1);
		glTranslatef(-100.0f, 0.0f, -100.0f);
		drawStudent(0, 180.0, 0, 10, 1, 0, 3, 1, 1, 12, 1);
		glTranslatef(220.0f, 0.0f, 220.0f);
		drawStudent(0, 0.0, 1, 6, 0, 0, 9, 10, 1, 11, 7);
		glTranslatef(500.0f, 0.0f, -200.0f);
		drawStudent(0, 0.0, 1, 4, 0, 0, 5, 1, 1, 12, 1);
		glTranslatef(100.0f, 0.0f, 50.0f);
		drawStudent(0, 0.0, 0, 2, 0, 0, 8, 1, 1, 11, 1);
		glPopMatrix();
	}

	/* Draw Student Center and Area*/

	//Draw light post

	glColor4f(1.0, 1.0, 1.0, transparency); //White

	glPushMatrix();
	glTranslatef(1200.0, 0.0, -150.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glutSolidCube(3.0);
	glTranslatef(0.0, 3.0, 0.0);
	glPopMatrix();

	glPushMatrix();

	glScalef(1.5, 1.5, 1.5);

	//Draw ground

	glColor3f(0.0, 0.4, 0.0); //Green

	for (x = -900; x <= 900; x += 10)
	{
		for (z = -900; z <= 900; z += 10)
		{
			vec1Arr[0] = x;
			vec1Arr[1] = 1.0;
			vec1Arr[2] = z;
			vec2Arr[0] = x + 10.0;
			vec2Arr[1] = 1.0;
			vec2Arr[2] = z;
			vec3Arr[0] = x + 10.0;
			vec3Arr[1] = 1.0;
			vec3Arr[2] = z + 10.0;

			CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &xNormal, &yNormal, &zNormal);

			glNormal3f(xNormal, yNormal, zNormal);
			drawRectangle(x, x + 10.0, x + 10.0, x, z, z, z + 10.0, z + 10.0);
		}
	}

	

	float cx = 740; // X location
	float cy = height - 260; //Y location

	//Draw the light red oval on grounds
	glColor3f(0.99, 0.5, 0.44); //Light Red
	cx = 460;
	cy = -50;

	glBegin(GL_POLYGON);
	for (int j = 0; j < 360; j++)
	{
		float theta = 3.1415926f / 180 * float(j);
		float x = cosf(theta);
		float y = sinf(theta);
		vec1Arr[0] = 0;
		vec1Arr[1] = 1.5;
		vec1Arr[2] = 0;
		vec2Arr[0] = 0;
		vec2Arr[1] = 1.5;
		vec2Arr[2] = 0;
		vec3Arr[0] = 0;
		vec3Arr[1] = 1.5;
		vec3Arr[2] = 0;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &xNormal, &yNormal, &zNormal);

		glNormal3f(xNormal, yNormal, zNormal);
		glVertex3f(x * 150 + cx, 1.5, y * 45 + cy);
	}
	glEnd();

	//Draw the first smaller oval on grounds
	glColor3f(1.0, 0.89, 0.77);
	
	glEnable(GL_NORMALIZE);
	glBegin(GL_POLYGON);
	for (int k = 0; k < 360; k++)
	{
		float theta = 3.1415926f / 180 * float(k);
		float x = cosf(theta);
		float y = sinf(theta);
		vec1Arr[0] = 0;
		vec1Arr[1] = 2.0;
		vec1Arr[2] = 0;
		vec2Arr[0] = 0;
		vec2Arr[1] = 2.0;
		vec2Arr[2] = 0;
		vec3Arr[0] = 0;
		vec3Arr[1] = 2.0;
		vec3Arr[2] = 0;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &xNormal, &yNormal, &zNormal);

		glNormal3f(xNormal, yNormal, zNormal);
		glVertex3f(x * 75 + cx, 2.0, y * 22.5 + cy);
	}
	glEnd();

	//Draw the line inside the first smaller oval on grounds
	glColor3f(0.99, 0.5, 0.44);
	glLineWidth(1.0);
	glBegin(GL_LINES);
	for (int k = 0; k < 360; k++)
	{
		float theta = 3.1415926f / 180 * float(k);
		float x = cosf(theta);
		float y = sinf(theta);
		glVertex3f(x * 72 + cx, 2.5, y * 19.5 + cy);
	}
	glEnd();

	glPushMatrix();
	//Draw the second smaller oval on grounds
	glColor3f(1.0, 0.89, 0.77);
	glTranslatef(70, 0, 0);
	glBegin(GL_POLYGON);
	for (int k = 0; k < 360; k++)
	{
		float theta = 3.1415926f / 180 * float(k);
		float x = cosf(theta);
		float y = sinf(theta);
		vec1Arr[0] = 0;
		vec1Arr[1] = 2.0;
		vec1Arr[2] = 0;
		vec2Arr[0] = 0;
		vec2Arr[1] = 2.0;
		vec2Arr[2] = 0;
		vec3Arr[0] = 0;
		vec3Arr[1] = 2.0;
		vec3Arr[2] = 0;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &xNormal, &yNormal, &zNormal);

		glNormal3f(xNormal, yNormal, zNormal);
		glVertex3f(x * 40 + cx, 2.0, y * 22.5 + cy);
	}
	glEnd();
	
	//Draw the line inside the second smaller oval on grounds
	glColor3f(0.99, 0.5, 0.44);
	glLineWidth(1.0);
	glBegin(GL_LINES);
	for (int k = 0; k < 360; k++)
	{
		float theta = 3.1415926f / 180 * float(k);
		float x = cosf(theta);
		float y = sinf(theta);
		glVertex3f(x * 38 + cx, 2.5, y * 19.5 + cy);
	}
	glEnd();
	glPopMatrix();
	

	//Draw door
	glBegin(GL_QUADS);

		glColor4f(1.0, 1.0, 1.0, transparency); //White

		vec3Arr[0] = 59.0f;
		vec3Arr[1] = 1.0f;
		vec3Arr[2] = 82.0f;

		vec2Arr[0] = 59.0f;
		vec2Arr[1] = 1.0f;
		vec2Arr[2] = 98.0f;

		vec1Arr[0] = 59.0f;
		vec1Arr[1] = 30.0f;
		vec1Arr[2] = 98.0f;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glVertex3f(59.0f, 1.0f, 82.0f);
		glVertex3f(59.0f, 1.0f, 98.0f);
		glVertex3f(59.0f, 30.0f, 98.0f);
		glVertex3f(59.0f, 30.0f, 82.0f);

	glEnd();

	//Draw bricks
	
	glColor4f(0.69, 0.13, 0.13, transparency); //Dark red

	glBegin(GL_QUADS);

		vec3Arr[0] = 60.0;
		vec3Arr[1] = 1.0;
		vec3Arr[2] = 60.0;

		vec2Arr[0] = 300.0;
		vec2Arr[1] = 1.0;
		vec2Arr[2] = 60.0;

		vec1Arr[0] = 300.0;
		vec1Arr[1] = 70.0;
		vec1Arr[2] = 60.0;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glVertex3f(60.0f, 1.0f, 60.0f);
		glVertex3f(300.0f, 1.0f, 60.0f);
		glVertex3f(300.0f, 70.0f, 60.0f);
		glVertex3f(60.0f, 70.0f, 60.0f);

		vec3Arr[0] = 60.0;
		vec3Arr[1] = 1.0;
		vec3Arr[2] = 120.0;

		vec2Arr[0] = 300.0;
		vec2Arr[1] = 1.0;
		vec2Arr[2] = 120.0;

		vec1Arr[0] = 300.0;
		vec1Arr[1] = 70.0;
		vec1Arr[2] = 120.0;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glVertex3f(60.0f, 1.0f, 120.0f);
		glVertex3f(300.0f, 1.0f, 120.0f);
		glVertex3f(300.0f, 70.0f, 120.0f);
		glVertex3f(60.0f, 70.0f, 120.0f);

		vec1Arr[0] = 60.0;
		vec1Arr[1] = 70.0;
		vec1Arr[2] = 60.0;

		vec2Arr[0] = 300.0;
		vec2Arr[1] = 70.0;
		vec2Arr[2] = 60.0;

		vec3Arr[0] = 300.0;
		vec3Arr[1] = 70.0;
		vec3Arr[2] = 120.0;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glVertex3f(60.0f, 70.0f, 60.0f);
		glVertex3f(300.0f, 70.0f, 60.0f);
		glVertex3f(300.0f, 70.0f, 120.0f);
		glVertex3f(60.0f, 70.0f, 120.0f);

		vec1Arr[0] = 60.0;
		vec1Arr[1] = 1.0;
		vec1Arr[2] = 60.0;

		vec2Arr[0] = 60.0;
		vec2Arr[1] = 1.0;
		vec2Arr[2] = 120.0;

		vec3Arr[0] = 60.0;
		vec3Arr[1] = 70.0;
		vec3Arr[2] = 120.0;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glVertex3f(60.0f, 1.0f, 60.0f);
		glVertex3f(60.0f, 1.0f, 120.0f);
		glVertex3f(60.0f, 70.0f, 120.0f);
		glVertex3f(60.0f, 70.0f, 60.0f);

		vec1Arr[0] = 300.0;
		vec1Arr[1] = 1.0;
		vec1Arr[2] = 60.0;

		vec2Arr[0] = 300.0;
		vec2Arr[1] = 1.0;
		vec2Arr[2] = 120.0;

		vec3Arr[0] = 300.0;
		vec3Arr[1] = 70.0;
		vec3Arr[2] = 120.0;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glVertex3f(300.0f, 1.0f, 60.0f);
		glVertex3f(300.0f, 1.0f, 120.0f);
		glVertex3f(300.0f, 70.0f, 120.0f);
		glVertex3f(300.0f, 70.0f, 60.0f);

	glEnd();

	glBegin(GL_QUADS);

		vec1Arr[0] = 200.0;
		vec1Arr[1] = 1.0;
		vec1Arr[2] = 60.0;

		vec2Arr[0] = 200.0;
		vec2Arr[1] = 70.0;
		vec2Arr[2] = 60.0;

		vec3Arr[0] = 200.0;
		vec3Arr[1] = 70.0;
		vec3Arr[2] = 120.0;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glVertex3f(200.0f, 1.0f, 60.0f);
		glVertex3f(200.0f, 70.0f, 60.0f);
		glVertex3f(200.0f, 70.0f, -120.0f);
		glVertex3f(200.0f, 1.0f, -120.0f);

		vec1Arr[0] = 300.0;
		vec1Arr[1] = 1.0;
		vec1Arr[2] = 60.0;

		vec2Arr[0] = 300.0;
		vec2Arr[1] = 70.0;
		vec2Arr[2] = 60.0;

		vec3Arr[0] = 300.0;
		vec3Arr[1] = 70.0;
		vec3Arr[2] = -120.0;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glVertex3f(300.0f, 1.0f, 60.0f);
		glVertex3f(300.0f, 70.0f, 60.0f);
		glVertex3f(300.0f, 70.0f, -120.0f);
		glVertex3f(300.0f, 1.0f, -120.0f);

		vec1Arr[0] = 120.0;
		vec1Arr[1] = 1.0;
		vec1Arr[2] = -120.0;

		vec2Arr[0] = 500.0;
		vec2Arr[1] = 1.0;
		vec2Arr[2] = -120.0;

		vec3Arr[0] = 500.0;
		vec3Arr[1] = 70.0;
		vec3Arr[2] = -120.0;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glVertex3f(120.0f, 1.0f, -120.0f);
		glVertex3f(500.0f, 1.0f, -120.0f);
		glVertex3f(500.0f, 70.0f, -120.0f);
		glVertex3f(120.0f, 70.0f, -120.0f);

		vec1Arr[0] = 120.0;
		vec1Arr[1] = 1.0;
		vec1Arr[2] = -280.0;

		vec2Arr[0] = 500.0;
		vec2Arr[1] = 1.0;
		vec2Arr[2] = -280.0;

		vec3Arr[0] = 500.0;
		vec3Arr[1] = 70.0;
		vec3Arr[2] = -280.0;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glVertex3f(120.0f, 1.0f, -280.0f);
		glVertex3f(500.0f, 1.0f, -280.0f);
		glVertex3f(500.0f, 70.0f, -280.0f);
		glVertex3f(120.0f, 70.0f, -280.0f);

		vec1Arr[0] = 120.0;
		vec1Arr[1] = 1.0;
		vec1Arr[2] = -120.0;

		vec2Arr[0] = 120.0;
		vec2Arr[1] = 1.0;
		vec2Arr[2] = -280.0;

		vec3Arr[0] = 120.0;
		vec3Arr[1] = 70.0;
		vec3Arr[2] = -280.0;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glVertex3f(120.0f, 1.0f, -120.0f);
		glVertex3f(120.0f, 1.0f, -280.0f);
		glVertex3f(120.0f, 70.0f, -280.0f);
		glVertex3f(120.0f, 70.0f, -120.0f);

		vec1Arr[0] = 500.0;
		vec1Arr[1] = 1.0;
		vec1Arr[2] = -120.0;

		vec2Arr[0] = 500.0;
		vec2Arr[1] = 1.0;
		vec2Arr[2] = -280.0;

		vec3Arr[0] = 500.0;
		vec3Arr[1] = 70.0;
		vec3Arr[2] = -280.0;

		CalculateVectorNormal(vec1Arr, vec2Arr, vec3Arr, &x, &y, &z);

		glVertex3f(500.0f, 1.0f, -120.0f);
		glVertex3f(500.0f, 1.0f, -280.0f);
		glVertex3f(500.0f, 70.0f, -280.0f);
		glVertex3f(500.0f, 70.0f, -120.0f);

	glEnd();

	//Draw roof

	glColor4f(0.4, 0.4, 0.4, transparency); //Gray

	glBegin(GL_QUADS);

		glVertex3f(300.0f, 70.0f, 60.0f);
		glVertex3f(260.0f, 85.0f, 80.0f);
		glVertex3f(260.0f, 85.0f, 100.0f);
		glVertex3f(300.0f, 70.0f, 120.0f);

		glVertex3f(300.0f, 70.0f, 60.0f);
		glVertex3f(260.0f, 85.0f, 80.0f);
		glVertex3f(80.0f, 85.0f, 80.0f);
		glVertex3f(60.0f, 70.0f, 60.0f);

		glVertex3f(300.0f, 70.0f, 120.0f);
		glVertex3f(260.0f, 85.0f, 100.0f);
		glVertex3f(80.0f, 85.0f, 100.0f);
		glVertex3f(60.0f, 70.0f, 120.0f);

		glVertex3f(60.0f, 70.0f, 60.0f);
		glVertex3f(80.0f, 85.0f, 80.0f);
		glVertex3f(80.0f, 85.0f, 100.0f);
		glVertex3f(60.0f, 70.0f, 120.0f);

		//middle

		glVertex3f(200.0f, 70.0f, -200.0f);
		glVertex3f(200.0f, 70.0f, 80.0f);
		glVertex3f(220.0f, 85.0f, 80.0f);
		glVertex3f(220.0f, 85.0f, -200.0f);

		glVertex3f(300.0f, 70.0f, 80.0f);
		glVertex3f(300.0f, 70.0f, -200.0f);
		glVertex3f(240.0f, 85.0f, -200.0f);
		glVertex3f(240.0f, 85.0f, 80.0f);

		//back

		glVertex3f(120.0f, 70.0f, -280.0f);
		glVertex3f(500.0f, 70.0f, -280.0f);
		glVertex3f(420.0f, 85.0f, -240.0f);
		glVertex3f(150.0f, 85.0f, -240.0f);

		glVertex3f(150.0f, 85.0f, -200.0f);
		glVertex3f(420.0f, 85.0f, -200.0f);
		glVertex3f(500.0f, 70.0f, -160.0f);
		glVertex3f(120.0f, 70.0f, -160.0f);

		glVertex3f(120.0f, 70.0f, -280.0f);
		glVertex3f(150.0f, 85.0f, -240.0f);
		glVertex3f(150.0f, 85.0f, -200.0f);
		glVertex3f(120.0f, 70.0f, -160.0f);

		glVertex3f(500.0f, 70.0f, -280.0f);
		glVertex3f(420.0f, 85.0f, -240.0f);
		glVertex3f(420.0f, 85.0f, -200.0f);
		glVertex3f(500.0f, 70.0f, -160.0f);

		//White part of roof

		glColor4f(0.9, 0.9, 0.9, transparency); //Off-White

		glVertex3f(260.0f, 85.0f, 80.0f);
		glVertex3f(80.0f, 85.0f, 80.0f);
		glVertex3f(80.0f, 85.0f, 100.0f);
		glVertex3f(260.0f, 85.0f, 100.0f);

		glVertex3f(220.0f, 85.0f, -200.0f);
		glVertex3f(240.0f, 85.0f, -200.0f);
		glVertex3f(240.0f, 85.0f, 80.0f);
		glVertex3f(220.0f, 85.0f, 80.0f);

		glVertex3f(420.0f, 85.0f, -200.0f);
		glVertex3f(150.0f, 85.0f, -200.0f);
		glVertex3f(150.0f, 85.0f, -220.0f);
		glVertex3f(420.0f, 85.0f, -220.0f);

		glVertex3f(420.0f, 85.0f, -220.0f);
		glVertex3f(150.0f, 85.0f, -220.0f);
		glVertex3f(150.0f, 85.0f, -240.0f);
		glVertex3f(420.0f, 85.0f, -240.0f);

		glVertex3f(120.0f, 70.0f, -120.0f);
		glVertex3f(200.0f, 70.0f, -120.0f);
		glVertex3f(200.0f, 70.0f, -160.0f);
		glVertex3f(120.0f, 70.0f, -160.0f);

		glVertex3f(250.0f, 70.0f, -120.0f);
		glVertex3f(500.0f, 70.0f, -120.0f);
		glVertex3f(500.0f, 70.0f, -160.0f);
		glVertex3f(250.0f, 70.0f, -160.0f);

	glEnd();

	//Draw bushes
	glColor4f(0.1, 0.6, 0.1, transparency); //Green

		glPushMatrix();
		glTranslatef(140.0, 10.0, 150.0);
		glutSolidSphere(10.0, 360, 360);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(180.0, 10.0, 150.0);
		glutSolidSphere(10.0, 360, 360);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(220.0, 10.0, 150.0);
		glutSolidSphere(10.0, 360, 360);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(260.0, 10.0, 150.0);
		glutSolidSphere(10.0, 360, 360);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(450.0, 5.0, 0.0);
		glutSolidSphere(5.0, 360, 360);

		glTranslatef(20.0, 0.0, -1.0);
		glutSolidSphere(5.0, 360, 360);

		glTranslatef(20.0, 0.0, -1.0);
		glutSolidSphere(5.0, 360, 360);

		glTranslatef(20.0, 0.0, -1.5);
		glutSolidSphere(5.0, 360, 360);

		glTranslatef(20.0, 0.0, -3.0);
		glutSolidSphere(5.0, 360, 360);

		glTranslatef(20.0, 0.0, -4.0);
		glutSolidSphere(5.0, 360, 360);

		glTranslatef(20.0, 0.0, -5.0);
		glutSolidSphere(5.0, 360, 360);
		glPopMatrix();

		//Tree

		glPushMatrix();
		glTranslatef(700.0, 70.0, -150.0);
		glutSolidSphere(40.0, 360, 360);
		glPopMatrix();

		glColor4f(0.54, 0.27, 0.074, transparency); //Brown
		glPushMatrix();
		glTranslatef(700.0, 10.0, -150.0);
		glutSolidCube(30.0);

		glTranslatef(0.0, 30.0, 0.0);
		glutSolidCube(30.0);
		glPopMatrix();

	glPopMatrix();

	//Draw bus
	glPushMatrix();
	if (switchController == 1)
	{
		glTranslatef(0.0, 0.0, moveY);
	}
	drawBus();
	glPopMatrix();

	// Swap buffers for double buffering
	glutSwapBuffers();
	//Redisplay
	glutPostRedisplay();

}

void
drawBus()
{
	glPushMatrix();


	glColor4f(1.0, 1.0, 1.0, transparency); //White

	glTranslatef(-100.0, 30.0, -100.0);
	glutSolidCube(30.0);

	glTranslatef(-30.0, 0.0, 0.0);
	glutSolidCube(30.0);
	glTranslatef(30.0, 0.0, 0.0);

	glTranslatef(0.0, 0.0, -30.0);
	glutSolidCube(30.0);

	glTranslatef(-30.0, 0.0, 0.0);
	glutSolidCube(30.0);
	glTranslatef(30.0, 0.0, 0.0);

	glTranslatef(0.0, 0.0, -30.0);
	glutSolidCube(30.0);

	glTranslatef(-30.0, 0.0, 0.0);
	glutSolidCube(30.0);
	glTranslatef(30.0, 0.0, 0.0);

	glTranslatef(0.0, 0.0, -30.0);
	glutSolidCube(30.0);

	glTranslatef(-30.0, 0.0, 0.0);
	glutSolidCube(30.0);
	glTranslatef(30.0, 0.0, 0.0);

	glTranslatef(0.0, 0.0, -30.0);
	glutSolidCube(30.0);

	glTranslatef(-30.0, 0.0, 0.0);
	glutSolidCube(30.0);
	glTranslatef(30.0, 0.0, 0.0);

	glColor4f(0.2, 0.3, 0.7, transparency); //Blue

	glTranslatef(0.0, -30.0, 0.0);
	glutSolidCube(30.0);

	glTranslatef(-30.0, 0.0, 0.0);
	glutSolidCube(30.0);
	glTranslatef(30.0, 0.0, 0.0);

	glTranslatef(0.0, 0.0, 30.0);
	glutSolidCube(30.0);

	glTranslatef(-30.0, 0.0, 0.0);
	glutSolidCube(30.0);
	glTranslatef(30.0, 0.0, 0.0);

	glTranslatef(0.0, 0.0, 30.0);
	glutSolidCube(30.0);

	glTranslatef(-30.0, 0.0, 0.0);
	glutSolidCube(30.0);
	glTranslatef(30.0, 0.0, 0.0);

	glTranslatef(0.0, 0.0, 30.0);
	glutSolidCube(30.0);

	glTranslatef(-30.0, 0.0, 0.0);
	glutSolidCube(30.0);
	glTranslatef(30.0, 0.0, 0.0);

	glTranslatef(0.0, 0.0, 30.0);
	glutSolidCube(30.0);

	glTranslatef(-30.0, 0.0, 0.0);
	glutSolidCube(30.0);
	glTranslatef(30.0, 0.0, 0.0);

	glColor3f(1.0f, 0.60f, 0.0f); //Orange

	glTranslatef(0.0, 40.0, 0.0);
	glutSolidCube(29.0);

	glTranslatef(-30.0, 0.0, 0.0);
	glutSolidCube(29.0);
	glTranslatef(30.0, 0.0, 0.0);

	glTranslatef(0.0, 0.0, -29.0);
	glutSolidCube(29.0);

	glTranslatef(-30.0, 0.0, 0.0);
	glutSolidCube(29.0);
	glTranslatef(30.0, 0.0, 0.0);

	glTranslatef(0.0, 0.0, -29.0);
	glutSolidCube(29.0);

	glTranslatef(-30.0, 0.0, 0.0);
	glutSolidCube(29.0);
	glTranslatef(30.0, 0.0, 0.0);

	glTranslatef(0.0, 0.0, -29.0);
	glutSolidCube(29.0);

	glTranslatef(-30.0, 0.0, 0.0);
	glutSolidCube(29.0);
	glTranslatef(30.0, 0.0, 0.0);

	glTranslatef(0.0, 0.0, -29.0);
	glutSolidCube(29.0);

	glTranslatef(-30.0, 0.0, 0.0);
	glutSolidCube(29.0);
	glTranslatef(30.0, 0.0, 0.0);

	glColor3f(0.0f, 0.0f, 0.0f); //Black

	glTranslatef(8.0, -10.0, 5.0);
	glutSolidCube(15.0);

	glTranslatef(0.0, -15.0, 0.0);
	glutSolidCube(15.0);

	glTranslatef(0.0, 15.0, 25.0);
	glutSolidCube(15.0);

	glTranslatef(0.0, 0.0, 18.0);
	glutSolidCube(15.0);

	glTranslatef(0.0, 0.0, 18.0);
	glutSolidCube(15.0);

	glTranslatef(0.0, 0.0, 18.0);
	glutSolidCube(15.0);

	glTranslatef(0.0, 0.0, 18.0);
	glutSolidCube(15.0);

	glTranslatef(0.0, 0.0, 18.0);
	glutSolidCube(15.0);

	glTranslatef(-46.0, 0.0, 0.0);
	glutSolidCube(15.0);

	glTranslatef(0.0, 0.0, -18.0);
	glutSolidCube(15.0);

	glTranslatef(0.0, 0.0, -18.0);
	glutSolidCube(15.0);

	glTranslatef(0.0, 0.0, -18.0);
	glutSolidCube(15.0);

	glTranslatef(0.0, 0.0, -18.0);
	glutSolidCube(15.0);

	glTranslatef(0.0, 0.0, -18.0);
	glutSolidCube(15.0);

	glTranslatef(0.0, 0.0, -25.0);
	glutSolidCube(15.0);

	glTranslatef(0.0, -15.0, 0.0);
	glutSolidCube(15.0);

	glTranslatef(3.0, 15.0, -18.0);
	glutSolidCube(13.0);

	glTranslatef(13.0, 0.0, 0.0);
	glutSolidCube(13.0);

	glTranslatef(13.0, 0.0, 0.0);
	glutSolidCube(13.0);

	glTranslatef(13.0, 0.0, 0.0);
	glutSolidCube(13.0);

	glTranslatef(-15.0, 0.0, 138.0);
	glutSolidCube(15.0);

	glTranslatef(-15.0, 0.0, 0.0);
	glutSolidCube(15.0);



	glPopMatrix();


	glPushMatrix();

	glTranslatef(-84.0, 8.0, -105.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glutSolidCone(6.5, 1.0, 150.0, 10.0);


	glTranslatef(0.0, 0.0, -63.0);
	glutSolidCone(6.5, 1.0, 150.0, 10.0);

	glTranslatef(120.0, 0.0, 0.0);

	glutSolidCone(6.5, 1.0, 150.0, 10.0);
	glTranslatef(0.0, 0.0, 63.0);
	glutSolidCone(6.5, 1.0, 150.0, 10.0);

	glPopMatrix();

}

/*
Reshapes the window.
*/
void
reshape(int w, int h)
{
	width = (GLdouble)w;
	height = (GLdouble)h;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0f, 1000.0/800.0, 0.01, 600.0);
}

/*
Main function for drawing the students and student center.
*/
int
main(int argc, char *argv[])
{
	init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //Double buffering, RGB colors, depth
	glutInitWindowSize((int)width, (int)height); //Window size
	int wd = glutCreateWindow("COMP-5/6400 Assignment 6"); //Window title
	glutDisplayFunc(display); //Display 
	glutReshapeFunc(reshape); //Reshape
	glutSpecialFunc(processSpecialKeys); //For key input
	glutKeyboardFunc(processRegularKeys);
	glEnable(GL_BLEND); //Enable transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST); //Depth test
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL); //Enable colors
	glDepthFunc(GL_LESS);
	glutMainLoop();
	return 0;
}
