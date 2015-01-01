/*

COMP 5400 - Assignment 4
Amy Eddins

Key commands:
Up Arrow - move student forward
Down Arrow - move student backward
Right Arrow - rotate student right
Left Arrow - rotate student left
Page Up - zoom in
Page Down - zoom out
Home - Toggle topdown and 3d mode
F1 - decrease transparency
F2 - increase transparency 

*/
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
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

void GetMousePos3D(int x, int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

}

/*
Controls the user input.
Key input is at the top of the code.
*/
void
processSpecialKeys(int key, int xdir, int ydir)
{
	switch (key)
	{
	case GLUT_KEY_UP: //If up arrow pressed
		//Move student forward
		moveY = (moveY - 5 * sin(M_PI / 180 * -rotateStudent));
		moveX = (moveX - 5 * cos(M_PI / 180 * -rotateStudent));
		break;
	case GLUT_KEY_DOWN: //If down arrow pressed
		//Move student backward 
		moveY = (moveY + 5 * sin(M_PI / 180 * -rotateStudent));
		moveX = (moveX + 5 * cos(M_PI / 180 * -rotateStudent));
		break;
	case GLUT_KEY_LEFT: //If left arrow pressed
		//Rotate student left
		rotateStudent = rotateStudent + 3;
		break;
	case GLUT_KEY_RIGHT: //If right arrow pressed
		//Rotate student right
		rotateStudent = rotateStudent - 3;
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

//void mouse_click_callback(int b, int s, int mouse_x, int mouse_y)
//{
//	float x = (2.0f * mouse_x) / width - 1.0f;
//	float y = 1.0f - (2.0f * mouse_y) / height;
//	float z = 1.0f;
//	vec3 ray_nds = vec3(x, y, z);
//
//	vec4 ray_clip = vec4(ray_nds.xy, -1.0, 1.0);
//
//	vec4 ray_eye = inverse(projection_matrix) * ray_clip;
//
//	ray_eye = vec4(ray_eye.xy, -1.0, 0.0);
//	vec3 ray_wor = (inverse(view_matrix) * ray_eye).xyz;
//	// don't forget to normalise the vector at some point
//	ray_wor = normalise(ray_wor);
//}

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
	glVertex3f(startX, startY, 50.0f);
	glVertex3f(startX - 100.0f, startY, 50.0f);
	glVertex3f(startX - 100.0f, startY - 100.0f, 50.0f);
	glVertex3f(startX, startY - 100.0f, 50.0f);

	//back
	glVertex3f(startX, startY, -50.0f);
	glVertex3f(startX - 100.0f, startY, -50.0f);
	glVertex3f(startX - 100.0f, startY - 100.0f, -50.0f);
	glVertex3f(startX, startY - 100.0f, -50.0f);

	//right side
	glVertex3f(startX - 100.0f, startY, 50.0f);
	glVertex3f(startX - 100.0f, startY, -50.0f);
	glVertex3f(startX - 100.0f, startY - 100.0f, -50.0f);
	glVertex3f(startX - 100.0f, startY - 100.0f, 50.0f);

	//left side
	glVertex3f(startX, startY, 50.0f);
	glVertex3f(startX, startY - 100.0f, 50.0f);
	glVertex3f(startX, startY - 100.0f, -50.0f);
	glVertex3f(startX, startY, -50.0f);

	glEnd();

	//right arm
	glBegin(GL_QUADS);

	glVertex3f(startX - 155.0f, startY - 150.0f, 20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX - 165.0f, startY - 210.0f, 20.0f);
	glVertex3f(startX - 135.0f, startY - 170.0f, 20.0f);

	glVertex3f(startX - 155.0f, startY - 150.0f, -20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX - 165.0f, startY - 210.0f, -20.0f);
	glVertex3f(startX - 135.0f, startY - 170.0f, -20.0f);

	glVertex3f(startX - 155.0f, startY - 150.0f, 20.0f);
	glVertex3f(startX - 155.0f, startY - 150.0f, -20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, 20.0f);

	glVertex3f(startX - 135.0f, startY - 170.0f, 20.0f);
	glVertex3f(startX - 135.0f, startY - 170.0f, -20.0f);
	glVertex3f(startX - 165.0f, startY - 210.0f, -20.0f);
	glVertex3f(startX - 165.0f, startY - 210.0f, 20.0f);

	glEnd();

	//left arm
	glBegin(GL_QUADS);

	glVertex3f(startX + 55.0f, startY - 150.0f, 20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX + 65.0f, startY - 210.0f, 20.0f);
	glVertex3f(startX + 35.0f, startY - 170.0f, 20.0f);

	glVertex3f(startX + 55.0f, startY - 150.0f, -20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX + 65.0f, startY - 210.0f, -20.0f);
	glVertex3f(startX + 35.0f, startY - 170.0f, -20.0f);

	glVertex3f(startX + 55.0f, startY - 150.0f, 20.0f);
	glVertex3f(startX + 55.0f, startY - 150.0f, -20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, 20.0f);

	glVertex3f(startX + 65.0f, startY - 210.0f, 20.0f);
	glVertex3f(startX + 65.0f, startY - 210.0f, -20.0f);
	glVertex3f(startX + 35.0f, startY - 170.0f, -20.0f);
	glVertex3f(startX + 35.0f, startY - 170.0f, 20.0f);

	glEnd();

	//right hand

	glBegin(GL_QUADS);

	glVertex3f(startX - 160.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX - 200.0f, startY - 230.0f, 20.0f);
	glVertex3f(startX - 180.0f, startY - 240.0f, 20.0f);

	glVertex3f(startX - 161.0f, startY - 205.0f, 20.0f);
	glVertex3f(startX - 165.0f, startY - 205.0f, 20.0f);
	glVertex3f(startX - 168.0f, startY - 230.0f, 20.0f);
	glVertex3f(startX - 161.0f, startY - 230.0f, 20.0f);

	glVertex3f(startX - 160.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX - 200.0f, startY - 230.0f, -20.0f);
	glVertex3f(startX - 180.0f, startY - 240.0f, -20.0f);

	glVertex3f(startX - 161.0f, startY - 205.0f, -20.0f);
	glVertex3f(startX - 165.0f, startY - 205.0f, -20.0f);
	glVertex3f(startX - 168.0f, startY - 230.0f, -20.0f);
	glVertex3f(startX - 161.0f, startY - 230.0f, -20.0f);

	glVertex3f(startX - 200.0f, startY - 230.0f, 20.0f);
	glVertex3f(startX - 200.0f, startY - 230.0f, -20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX - 190.0f, startY - 200.0f, 20.0f);

	glVertex3f(startX - 160.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX - 160.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX - 180.0f, startY - 240.0f, -20.0f);
	glVertex3f(startX - 180.0f, startY - 240.0f, 20.0f);

	glVertex3f(startX - 161.0f, startY - 205.0f, 20.0f);
	glVertex3f(startX - 161.0f, startY - 205.0f, -20.0f);
	glVertex3f(startX - 161.0f, startY - 230.0f, -20.0f);
	glVertex3f(startX - 161.0f, startY - 230.0f, 20.0f);

	glEnd();

	//left hand

	glBegin(GL_QUADS);

	glVertex3f(startX + 60.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX + 100.0f, startY - 230.0f, 20.0f);
	glVertex3f(startX + 80.0f, startY - 240.0f, 20.0f);

	glVertex3f(startX + 100.0f, startY - 200.0f, 22.0f);
	glVertex3f(startX + 80.0f, startY - 190.0f, 22.0f);
	glVertex3f(startX + 80.0f, startY - 200.0f, 22.0f);
	glVertex3f(startX + 100.0f, startY - 210.0f, 22.0f);

	glVertex3f(startX + 60.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX + 100.0f, startY - 230.0f, -20.0f);
	glVertex3f(startX + 80.0f, startY - 240.0f, -20.0f);

	glVertex3f(startX + 100.0f, startY - 230.0f, 20.0f);
	glVertex3f(startX + 100.0f, startY - 230.0f, -20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX + 90.0f, startY - 200.0f, 20.0f);

	glVertex3f(startX + 60.0f, startY - 200.0f, 20.0f);
	glVertex3f(startX + 60.0f, startY - 200.0f, -20.0f);
	glVertex3f(startX + 80.0f, startY - 240.0f, -20.0f);
	glVertex3f(startX + 80.0f, startY - 240.0f, 20.0f);

	glEnd();

	//left leg
	glBegin(GL_QUADS);

	glVertex3f(startX + 10.0f, startY - 320.0f, 30.0f);
	glVertex3f(startX - 35.0f, startY - 320.0f, 30.0f);
	glVertex3f(startX - 35.0f, startY - 405.0f, 30.0f);
	glVertex3f(startX + 10.0f, startY - 405.0f, 30.0f);

	glVertex3f(startX + 10.0f, startY - 320.0f, -30.0f);
	glVertex3f(startX - 35.0f, startY - 320.0f, -30.0f);
	glVertex3f(startX - 35.0f, startY - 405.0f, -30.0f);
	glVertex3f(startX + 10.0f, startY - 405.0f, -30.0f);

	glVertex3f(startX - 35.0f, startY - 320.0f, 30.0f);
	glVertex3f(startX - 35.0f, startY - 320.0f, -30.0f);
	glVertex3f(startX - 35.0f, startY - 405.0f, -30.0f);
	glVertex3f(startX - 35.0f, startY - 405.0f, 30.0f);

	glVertex3f(startX + 10.0f, startY - 320.0f, 30.0f);
	glVertex3f(startX + 10.0f, startY - 320.0f, -30.0f);
	glVertex3f(startX + 10.0f, startY - 405.0f, -30.0f);
	glVertex3f(startX + 10.0f, startY - 405.0f, 30.0f);

	glEnd();

	//right leg
	glBegin(GL_QUADS);

	glVertex3f(startX - 65.0f, startY - 320.0f, 30.0f);
	glVertex3f(startX - 110.0f, startY - 320.0f, 30.0f);
	glVertex3f(startX - 110.0f, startY - 405.0f, 30.0f);
	glVertex3f(startX - 65.0f, startY - 405.0f, 30.0f);

	glVertex3f(startX - 65.0f, startY - 320.0f, -30.0f);
	glVertex3f(startX - 110.0f, startY - 320.0f, -30.0f);
	glVertex3f(startX - 110.0f, startY - 405.0f, -30.0f);
	glVertex3f(startX - 65.0f, startY - 405.0f, -30.0f);

	glVertex3f(startX - 65.0f, startY - 320.0f, 30.0f);
	glVertex3f(startX - 65.0f, startY - 320.0f, -30.0f);
	glVertex3f(startX - 65.0f, startY - 405.0f, -30.0f);
	glVertex3f(startX - 65.0f, startY - 405.0f, 30.0f);

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
	glVertex3f(startX + 20.0f, startY - 100.0f, 50.1f);
	glVertex3f(startX - 120.0f, startY - 100.0f, 50.1f);
	glVertex3f(startX - 120.0f, startY - 270.0f, 50.1f);
	glVertex3f(startX + 20.0f, startY - 270.0f, 50.1f);

	//back
	glVertex3f(startX + 20.0f, startY - 100.0f, -50.1f);
	glVertex3f(startX - 120.0f, startY - 100.0f, -50.1f);
	glVertex3f(startX - 120.0f, startY - 270.0f, -50.1f);
	glVertex3f(startX + 20.0f, startY - 270.0f, -50.1f);

	//right side
	glVertex3f(startX - 120.0f, startY - 100.0f, 50.1f);
	glVertex3f(startX - 120.0f, startY - 100.0f, -50.1f);
	glVertex3f(startX - 120.0f, startY - 270.0f, -50.1f);
	glVertex3f(startX - 120.0f, startY - 270.0f, 50.1f);

	//left side
	glVertex3f(startX + 20.0f, startY - 100.0f, 50.1f);
	glVertex3f(startX + 20.0f, startY - 100.0f, -50.1f);
	glVertex3f(startX + 20.0f, startY - 270.0f, -50.1f);
	glVertex3f(startX + 20.0f, startY - 270.0f, 50.1f);

	glEnd();

	// Student's right shirt arm
	glBegin(GL_QUADS);

	glVertex3f(startX - 120.0f, startY - 100.0f, 50.0f);
	glVertex3f(startX - 160.0f, startY - 150.0f, 50.0f);
	glVertex3f(startX - 130.0f, startY - 190.0f, 50.0f);
	glVertex3f(startX - 120.0f, startY - 170.0f, 50.0f);

	glVertex3f(startX - 120.0f, startY - 100.0f, -50.0f);
	glVertex3f(startX - 160.0f, startY - 150.0f, -50.0f);
	glVertex3f(startX - 130.0f, startY - 190.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 170.0f, -50.0f);

	glVertex3f(startX - 120.0f, startY - 100.0f, 50.0f);
	glVertex3f(startX - 160.0f, startY - 150.0f, 50.0f);
	glVertex3f(startX - 160.0f, startY - 150.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 100.0f, -50.0f);

	glVertex3f(startX - 120.0f, startY - 170.0f, 50.0f);
	glVertex3f(startX - 130.0f, startY - 190.0f, 50.0f);
	glVertex3f(startX - 130.0f, startY - 190.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 170.0f, -50.0f);

	glEnd();

	// Student's left shirt arm
	glBegin(GL_QUADS);

	glVertex3f(startX + 20.0f, startY - 100.0f, 50.0f);
	glVertex3f(startX + 60.0f, startY - 150.0f, 50.0f);
	glVertex3f(startX + 30.0f, startY - 190.0f, 50.0f);
	glVertex3f(startX + 20.0f, startY - 170.0f, 50.0f);

	glVertex3f(startX + 20.0f, startY - 100.0f, -50.0f);
	glVertex3f(startX + 60.0f, startY - 150.0f, -50.0f);
	glVertex3f(startX + 30.0f, startY - 190.0f, -50.0f);
	glVertex3f(startX + 20.0f, startY - 170.0f, -50.0f);

	glVertex3f(startX + 20.0f, startY - 100.0f, 50.0f);
	glVertex3f(startX + 60.0f, startY - 150.0f, 50.0f);
	glVertex3f(startX + 60.0f, startY - 150.0f, -50.0f);
	glVertex3f(startX + 20.0f, startY - 100.0f, -50.0f);

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
	glVertex3f(startX + 6.0f, startY, 55.3f);
	glVertex3f(startX - 106.0f, startY, 55.3f);
	glVertex3f(startX - 106.0f, startY - 30.0f, 55.3f);
	glVertex3f(startX + 6.0f, startY - 30.0f, 55.3f);

	//top
	glVertex3f(startX + 6.0f, startY, 55.3f);
	glVertex3f(startX - 106.0f, startY, 55.3f);
	glVertex3f(startX - 106.0f, startY, -55.3f);
	glVertex3f(startX + 6.0f, startY, -55.3f);

	if (girl) //girl
	{
		//right side
		glVertex3f(startX - 106.0f, startY, 55.3f);
		glVertex3f(startX - 106.0f, startY, -55.3f);
		glVertex3f(startX - 106.0f, startY - 100.0f, -55.3f);
		glVertex3f(startX - 106.0f, startY - 100.0f, 55.3f);

		//left side
		glVertex3f(startX + 6.0f, startY, 55.3f);
		glVertex3f(startX + 6.0f, startY - 100.0f, 55.3f);
		glVertex3f(startX + 6.0f, startY - 100.0f, -55.3f);
		glVertex3f(startX + 6.0f, startY, -55.3f);

		//left front
		glVertex3f(startX - 86.0f, startY, 55.3f);
		glVertex3f(startX - 106.0f, startY, 55.3f);
		glVertex3f(startX - 106.0f, startY - 200.0f, 55.3f);
		glVertex3f(startX - 86.0f, startY - 200.0f, 55.3f);

		//right front
		glVertex3f(startX + 6.0f, startY, 55.3f);
		glVertex3f(startX - 15.0f, startY, 55.3f);
		glVertex3f(startX - 15.0f, startY - 200.0f, 55.3f);
		glVertex3f(startX + 6.0f, startY - 200.0f, 55.3f);

		//back
		glVertex3f(startX + 6.0f, startY, -55.3f);
		glVertex3f(startX - 106.0f, startY, -55.3f);
		glVertex3f(startX - 106.0f, startY - 200.0f, -55.3f);
		glVertex3f(startX + 6.0f, startY - 200.0f, -55.3f);
	}
	else //boy
	{
		//right side
		glVertex3f(startX - 106.0f, startY, 55.3f);
		glVertex3f(startX - 106.0f, startY, -55.3f);
		glVertex3f(startX - 106.0f, startY - 50.0f, -55.3f);
		glVertex3f(startX - 106.0f, startY - 50.0f, 55.3f);

		//left side
		glVertex3f(startX + 6.0f, startY, 55.3f);
		glVertex3f(startX + 6.0f, startY - 50.0f, 55.3f);
		glVertex3f(startX + 6.0f, startY - 50.0f, -55.3f);
		glVertex3f(startX + 6.0f, startY, -55.3f);

		//back
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
	glVertex3f(startX + 20.0f, startY - 270.0f, 50.0f);
	glVertex3f(startX - 120.0f, startY - 270.0f, 50.0f);
	glVertex3f(startX - 120.0f, startY - 300.0f, 50.0f);
	glVertex3f(startX + 20.0f, startY - 300.0f, 50.0f);

	glVertex3f(startX + 20.0f, startY - 270.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 270.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 300.0f, -50.0f);
	glVertex3f(startX + 20.0f, startY - 300.0f, -50.0f);

	//right side
	glVertex3f(startX - 120.0f, startY - 270.0f, 50.0f);
	glVertex3f(startX - 120.0f, startY - 270.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 320.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 320.0f, 50.0f);

	//left side
	glVertex3f(startX + 20.0f, startY - 270.0f, 50.0f);
	glVertex3f(startX + 20.0f, startY - 270.0f, -50.0f);
	glVertex3f(startX + 20.0f, startY - 320.0f, -50.0f);
	glVertex3f(startX + 20.0f, startY - 320.0f, 50.0f);

	//right pant
	glVertex3f(startX + 20.0f, startY - 300.0f, 50.0f);
	glVertex3f(startX - 45.0f, startY - 300.0f, 50.0f);
	glVertex3f(startX - 45.0f, startY - 320.0f, 50.0f);
	glVertex3f(startX + 20.0f, startY - 320.0f, 50.0f);

	glVertex3f(startX + 20.0f, startY - 300.0f, -50.0f);
	glVertex3f(startX - 45.0f, startY - 300.0f, -50.0f);
	glVertex3f(startX - 45.0f, startY - 320.0f, -50.0f);
	glVertex3f(startX + 20.0f, startY - 320.0f, -50.0f);

	glVertex3f(startX - 45.0f, startY - 300.0f, 50.0f);
	glVertex3f(startX - 45.0f, startY - 300.0f, -50.0f);
	glVertex3f(startX - 45.0f, startY - 320.0f, -50.0f);
	glVertex3f(startX - 45.0f, startY - 320.0f, 50.0f);

	//left pant
	glVertex3f(startX - 55.0f, startY - 300.0f, 50.0f);
	glVertex3f(startX - 120.0f, startY - 300.0f, 50.0f);
	glVertex3f(startX - 120.0f, startY - 320.0f, 50.0f);
	glVertex3f(startX - 55.0f, startY - 320.0f, 50.0f);

	glVertex3f(startX - 55.0f, startY - 300.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 300.0f, -50.0f);
	glVertex3f(startX - 120.0f, startY - 320.0f, -50.0f);
	glVertex3f(startX - 55.0f, startY - 320.0f, -50.0f);

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

	//left shoe

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

	glVertex3f(startX + 15.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 40.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 40.0f, startY - 440.0f, 60.0f);
	glVertex3f(startX + 15.0f, startY - 440.0f, 60.0f);

	glVertex3f(startX + 15.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 40.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 40.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX + 15.0f, startY - 405.0f, -35.0f);

	glVertex3f(startX + 15.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX - 40.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX - 40.0f, startY - 440.0f, -35.0f);
	glVertex3f(startX + 15.0f, startY - 440.0f, -35.0f);

	glVertex3f(startX - 40.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 40.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX - 40.0f, startY - 440.0f, -35.0f);
	glVertex3f(startX - 40.0f, startY - 440.0f, 60.0f);

	glVertex3f(startX + 15.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX + 15.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX + 15.0f, startY - 440.0f, -35.0f);
	glVertex3f(startX + 15.0f, startY - 440.0f, 60.0f);

	glEnd();

	//right shoe
	glBegin(GL_QUADS);

	glVertex3f(startX - 60.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 115.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 115.0f, startY - 440.0f, 60.0f);
	glVertex3f(startX - 60.0f, startY - 440.0f, 60.0f);

	glVertex3f(startX - 60.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 115.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 115.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX - 60.0f, startY - 405.0f, -35.0f);

	glVertex3f(startX - 60.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX - 115.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX - 115.0f, startY - 440.0f, -35.0f);
	glVertex3f(startX - 60.0f, startY - 440.0f, -35.0f);

	glVertex3f(startX - 115.0f, startY - 405.0f, 60.0f);
	glVertex3f(startX - 115.0f, startY - 405.0f, -35.0f);
	glVertex3f(startX - 115.0f, startY - 440.0f, -35.0f);
	glVertex3f(startX - 115.0f, startY - 440.0f, 60.0f);

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
	gluPerspective(90.0f + zoom, 1000.0 / 800.0, 0.01, 600.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//Toggle topdown mode with LookAt
	if (topDown == 1)
	{
		gluLookAt(moveX, 200 + zoom, moveY + 1.0,
			moveX, 0.0, moveY,
			0.0, 1.0, 0.0);
	}
	else
	{
		gluLookAt(moveX + 100 * sin((rotateStudent + 90) * M_PI / 180), 50 + zoom, moveY + 100 * cos((rotateStudent + 90) * M_PI / 180),
			moveX, 0.0, moveY,
			0.0, 1.0, 0.0);
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
	drawStudent(1, 0.0, 1, 10, 1, 1, 1, 4, 1, 11, 1);

	//Others
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

	/* Draw Student Center */

	glPushMatrix();

	glScalef(1.5, 1.5, 1.5);

	//Draw ground

	glBegin(GL_POLYGON);

		glColor3f(0.0, 0.4, 0.0); //Green

		glVertex3f(-1000.0f, 1.0f, -1000.0f);
		glVertex3f(6000.0f, 1.0f, -1000.0f);
		glVertex3f(6000.0f, 1.0f, 10000.0f);
		glVertex3f(-1000.0f, 1.0f, 10000.0f);

	glEnd();

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
	
	//Draw bricks
	
	glColor4f(0.69, 0.13, 0.13, transparency); //Dark red

	glBegin(GL_QUADS);

		glVertex3f(60.0f, 1.0f, 60.0f);
		glVertex3f(300.0f, 1.0f, 60.0f);
		glVertex3f(300.0f, 70.0f, 60.0f);
		glVertex3f(60.0f, 70.0f, 60.0f);

		glVertex3f(60.0f, 1.0f, 120.0f);
		glVertex3f(300.0f, 1.0f, 120.0f);
		glVertex3f(300.0f, 70.0f, 120.0f);
		glVertex3f(60.0f, 70.0f, 120.0f);

		glVertex3f(60.0f, 70.0f, 60.0f);
		glVertex3f(300.0f, 70.0f, 60.0f);
		glVertex3f(300.0f, 70.0f, 120.0f);
		glVertex3f(60.0f, 70.0f, 120.0f);

		glVertex3f(60.0f, 1.0f, 60.0f);
		glVertex3f(60.0f, 1.0f, 120.0f);
		glVertex3f(60.0f, 70.0f, 120.0f);
		glVertex3f(60.0f, 70.0f, 60.0f);

		glVertex3f(300.0f, 1.0f, 60.0f);
		glVertex3f(300.0f, 1.0f, 120.0f);
		glVertex3f(300.0f, 70.0f, 120.0f);
		glVertex3f(300.0f, 70.0f, 60.0f);

	glEnd();

	glBegin(GL_QUADS);

		glVertex3f(200.0f, 1.0f, 60.0f);
		glVertex3f(200.0f, 70.0f, 60.0f);
		glVertex3f(200.0f, 70.0f, -120.0f);
		glVertex3f(200.0f, 1.0f, -120.0f);

		glVertex3f(300.0f, 1.0f, 60.0f);
		glVertex3f(300.0f, 70.0f, 60.0f);
		glVertex3f(300.0f, 70.0f, -120.0f);
		glVertex3f(300.0f, 1.0f, -120.0f);

		glVertex3f(120.0f, 1.0f, -120.0f);
		glVertex3f(500.0f, 1.0f, -120.0f);
		glVertex3f(500.0f, 70.0f, -120.0f);
		glVertex3f(120.0f, 70.0f, -120.0f);

		glVertex3f(120.0f, 1.0f, -280.0f);
		glVertex3f(500.0f, 1.0f, -280.0f);
		glVertex3f(500.0f, 70.0f, -280.0f);
		glVertex3f(120.0f, 70.0f, -280.0f);

		glVertex3f(120.0f, 1.0f, -120.0f);
		glVertex3f(120.0f, 1.0f, -280.0f);
		glVertex3f(120.0f, 70.0f, -280.0f);
		glVertex3f(120.0f, 70.0f, -120.0f);

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

	//Draw air vents

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

		glColor3f(0.54, 0.27, 0.074); //Brown
		glPushMatrix();
		glTranslatef(700.0, 10.0, -150.0);
		glutSolidCube(30.0);

		glTranslatef(0.0, 30.0, 0.0);
		glutSolidCube(30.0);
		glPopMatrix();

	glPopMatrix();

	// Swap buffers for double buffering
	glutSwapBuffers();
	//Redisplay
	glutPostRedisplay();

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
	int wd = glutCreateWindow("COMP-5/6400 Assignment 4"); //Window title
	glutDisplayFunc(display); //Display 
	glutReshapeFunc(reshape); //Reshape
	glutSpecialFunc(processSpecialKeys); //For key input
	glEnable(GL_BLEND); //Enable transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST); //Depth test
	glDepthFunc(GL_LESS);
	glutMainLoop();
	return 0;
}
