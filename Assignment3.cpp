/*

COMP 5400 - Assignment 3
Amy Eddins

Key commands:
Up Arrow - move student up
Down Arrow - move student down
Right Arrow - move student right
Left Arrow - move student left
End - rotate student clockwise
Home- rotate student counterclockwise
Page Up - scale student up
Page Down - scale student down

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
GLfloat rotateStudent = 90.0;
GLfloat scale = 1.0;

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
		//Move student up 
		moveY = moveY + 5;
		break;
	case GLUT_KEY_DOWN: //If down arrow pressed
		//Move student down 
		moveY = moveY - 5;
		break;
	case GLUT_KEY_LEFT: //If left arrow pressed
		moveX = moveX - 5; //Move student left
		break;
	case GLUT_KEY_RIGHT: //If right arrow pressed
		moveX = moveX + 5; //Move student right
		break;
	case GLUT_KEY_HOME: //If end is pressed
		rotateStudent = rotateStudent + 3; //Rotate the student clockwise by 5
		break;
	case GLUT_KEY_END: //If home is pressed
		rotateStudent = rotateStudent - 3; //Rotate the student counterclockwise by 5
		break;
	case GLUT_KEY_PAGE_UP: //If pgup pressed
		scale = scale + 0.05; //Scale the student up
		break;
	case GLUT_KEY_PAGE_DOWN: //If pgdn pressed
		if (!(scale <= 0.10)) //Keep the student from being scaled under 1 
		{
			scale = scale - 0.05;
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
	height = 560.0;
}

/*
This function draws the student 
*/
void
display(void)
{
	glShadeModel(GL_SMOOTH); //Smooth shading
	glClearColor(0.5, 0.5, 0.5, 0.0); //Gray background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Color and depth buffer clear

	//Starting points for student
	GLfloat startX, startY;
	startX = 550.0;
	startY = 500.0;

	/*  Draw Student  */
	//Center of student on x-axis = 500
	//Center of student on y-axis = 280

	//Mode
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Push Matrix
	glPushMatrix();
	
	//Transformations
	//translate the student back from origin
	glTranslatef(500 + moveX, 280 + moveY, 0); //move
	glScalef(scale, scale, scale); //scale
	glRotatef(rotateStudent - 90, 0.0, 1.0, 0.0); //rotate
	//translate the student to the origin
	glTranslatef(-500, -280, 0);
	
	// Student's face
	glBegin(GL_QUADS);

		glColor3f(1.0f, 0.62f, 0.47f); // light pink

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

	glEnd();

	//Student's glasses
	glBegin(GL_LINES);

		glColor3f(0.0f, 0.0f, 0.0f); // Black
		glLineWidth(10.0f);
		glVertex3f(startX - 53.0f, startY - 40.0f, 51.5f);
		glVertex3f(startX - 78.0f, startY - 40.0f, 51.5f);
		
		glVertex3f(startX - 78.0f, startY - 40.0f, 51.5f);
		glVertex3f(startX - 78.0f, startY - 60.0f, 51.5f);
	
		glVertex3f(startX - 78.0f, startY - 60.0f, 51.5f);
		glVertex3f(startX - 53.0f, startY - 60.0f, 51.5f);
	
		glVertex3f(startX - 53.0f, startY - 60.0f, 51.5f);
		glVertex3f(startX - 53.0f, startY - 40.0f, 51.5f);

		glVertex3f(startX - 20.0f, startY - 40.0f, 51.5f);
		glVertex3f(startX - 46.0f, startY - 40.0f, 51.5f);

		glVertex3f(startX - 46.0f, startY - 40.0f, 51.5f);
		glVertex3f(startX - 46.0f, startY - 60.0f, 51.5f);

		glVertex3f(startX - 46.0f, startY - 60.0f, 51.5f);
		glVertex3f(startX - 20.0f, startY - 60.0f, 51.5f);

		glVertex3f(startX - 20.0f, startY - 60.0f, 51.5f);
		glVertex3f(startX - 20.0f, startY - 40.0f, 51.5f);

		glVertex3f(startX - 46.0f, startY - 50.0f, 51.5f);
		glVertex3f(startX - 53.0f, startY - 50.0f, 51.5f);

		glVertex3f(startX - 20.0f, startY - 50.0f, 51.5f);
		glVertex3f(startX - 10.0f, startY - 50.0f, 51.5f);

		glVertex3f(startX - 78.0f, startY - 50.0f, 51.5f);
		glVertex3f(startX - 90.0f, startY - 50.0f, 51.5f);

	glEnd();

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
				glVertex3f(x * 2 + (startX - 65.0), y * 2 + (startY - 50.0), 51.1f);
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
				glVertex3f(x * 7 + (startX - 65.0), y * 5 + (startY - 50.0), 51.0f);
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
				glVertex3f(x * 2 + (startX - 35.0), y * 2 + (startY - 50.0), 51.1f);
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
				glVertex3f(x * 7 + (startX - 35.0), y * 5 + (startY - 50.0), 51.0f);
			}

		glEnd();

	// Student's nose
	glBegin(GL_LINES);

		glColor3f(0.0f, 0.0f, 0.0f); // Black
		glLineWidth(2.0);
		glVertex3f(startX - 50.0f, startY - 60.0f, 51.0f);
		glVertex3f(startX - 50.0f, startY - 70.0f, 51.0f);

	glEnd();

	// Student's mouth
	glBegin(GL_LINES);

		glColor3f(0.0f, 0.0f, 0.0f); // Black
		glLineWidth(2.0);
		glVertex3f(startX - 60.0f, startY - 80.0f, 51.0f);
		glVertex3f(startX - 40.0f, startY - 80.0f, 51.0f);

	glEnd();

	// Student's shirt
	glBegin(GL_QUADS);

		glColor3f(0.0f, 0.0f, 0.0f); // Black

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

	// Student's shirt engineer logo

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
				glVertex3f(x * 15 + (startX - 65.0), y * 15 + (startY - 150.0), 51.2f);
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
				glVertex3f(x * 15 + (startX - 35.0), y * 15 + (startY - 190.0), 51.2f);
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
				glVertex3f(x * 47 + (startX - 50.0), y * 47 + (startY - 170.0), 51.1f);
			}

		glEnd();

		//square top left
		glBegin(GL_POLYGON);

			glColor3f(0.0f, 0.0f, 0.0f); // Black

			glVertex3f(startX - 80.0f, startY - 140.0f, 51.3f);
			glVertex3f(startX - 70.0f, startY - 130.0f, 51.3f);
			glVertex3f(startX - 55.0f, startY - 150.0f, 51.3f);
			glVertex3f(startX - 65.0f, startY - 160.0f, 51.3f);

		glEnd();

		//square bottom right
		glBegin(GL_POLYGON);

			glColor3f(0.0f, 0.0f, 0.0f); // Black

			glVertex3f(startX - 45.0f, startY - 190.0f, 51.3f);
			glVertex3f(startX - 35.0f, startY - 180.0f, 51.3f);
			glVertex3f(startX - 20.0f, startY - 200.0f, 51.3f);
			glVertex3f(startX - 30.0f, startY - 210.0f, 51.3f);

		glEnd();
		
		//handle of wrench
		glBegin(GL_POLYGON);

			glColor3f(1.0f, 1.0f, 1.0f); // White

			glVertex3f(startX - 80.0f, startY - 145.0f, 51.2f);
			glVertex3f(startX - 70.0f, startY - 135.0f, 51.2f);
			glVertex3f(startX - 20.0f, startY - 195.0f, 51.2f);
			glVertex3f(startX - 30.0f, startY - 205.0f, 51.2f);
		
		glEnd();

	// Student's hair
	glBegin(GL_QUADS);

		glColor3f(0.55f, 0.27f, 0.07f); // Brown

		//bangs
		glVertex3f(startX + 1.0f, startY, 51.3f);
		glVertex3f(startX - 101.0f, startY, 51.3f);
		glVertex3f(startX - 101.0f, startY - 30.0f, 51.3f);
		glVertex3f(startX + 1.0f, startY - 30.0f, 51.3f);

		//left front
		glVertex3f(startX - 86.0f, startY, 51.3f);
		glVertex3f(startX - 101.0f, startY, 51.3f);
		glVertex3f(startX - 101.0f, startY - 200.0f, 51.3f);
		glVertex3f(startX - 86.0f, startY - 200.0f, 51.3f);

		//right front
		glVertex3f(startX + 1.0f, startY, 51.3f);
		glVertex3f(startX - 15.0f, startY, 51.3f);
		glVertex3f(startX - 15.0f, startY - 200.0f, 51.3f);
		glVertex3f(startX + 1.0f, startY - 200.0f, 51.3f);

		//left side
		glVertex3f(startX + 1.0f, startY, 51.3f);
		glVertex3f(startX + 1.0f, startY - 100.0f, 51.3f);
		glVertex3f(startX + 1.0f, startY - 100.0f, -51.3f);
		glVertex3f(startX + 1.0f, startY, -51.3f);

		//back
		glVertex3f(startX + 1.0f, startY, -51.3f);
		glVertex3f(startX - 101.0f, startY, -51.3f);
		glVertex3f(startX - 101.0f, startY - 200.0f, -51.3f);
		glVertex3f(startX + 1.0f, startY - 200.0f, -51.3f);

		//right side
		glVertex3f(startX - 101.0f, startY, 51.3f);
		glVertex3f(startX - 101.0f, startY, -51.3f);
		glVertex3f(startX - 101.0f, startY - 100.0f, -51.3f);
		glVertex3f(startX - 101.0f, startY - 100.0f, 51.3f);

	glEnd();

	// Student's right shirt arm
	glBegin(GL_QUADS);

		glColor3f(0.0f, 0.0f, 0.0f); // Black

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

		glColor3f(0.0f, 0.0f, 0.0f); // Black

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

	// Student's right arm
	glBegin(GL_QUADS);

		glColor3f(1.0f, 0.62f, 0.47f); // light pink

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

	// Student's left arm
	glBegin(GL_QUADS);

		glColor3f(1.0f, 0.62f, 0.47f); // light pink

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

	//Student's right hand

	glBegin(GL_QUADS);

		glColor3f(1.0f, 0.62f, 0.47f); // light pink

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

	//Student's left hand

	glBegin(GL_QUADS);

		glColor3f(1.0f, 0.62f, 0.47f); // light pink

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

	// Student's 3DS

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

			glVertex3f(startX + 110.0f, startY - 210.0f, 21.1f);
			glVertex3f(startX + 90.0f, startY - 205.0f, 21.1f);
			glVertex3f(startX + 75.0f, startY - 220.0f, 21.1f);
			glVertex3f(startX + 95.0f, startY - 225.0f, 21.1f);

		glEnd();

		//pad
		glBegin(GL_POLYGON);

			glColor3f(0.5f, 0.5f, 0.5f); // Gray

			for (int l = 0; l < 360; l++)
			{
				theta = 2.0 * 3.1415926f / 360 * float(l);
				x = cosf(theta);
				y = sinf(theta);
				glVertex3f(x * 2.8 + (startX + 83.0), y * 2.8 + (startY - 206.0), 21.1f);
			}

		glEnd();

		//buttons
		glBegin(GL_POLYGON);

			for (int l = 0; l < 360; l++)
			{
				theta = 2.0 * 3.1415926f / 360 * float(l);
				x = cosf(theta);
				y = sinf(theta);
				glVertex3f(x * 1.0 + (startX + 110.0), y * 1.0 + (startY - 215.0), 21.1f);
			}

		glEnd();

		glBegin(GL_POLYGON);

		for (int l = 0; l < 360; l++)
		{
			theta = 2.0 * 3.1415926f / 360 * float(l);
			x = cosf(theta);
			y = sinf(theta);
			glVertex3f(x * 1.0 + (startX + 107.0), y * 1.0 + (startY - 215.0), 21.1f);
		}

		glEnd();

		glBegin(GL_POLYGON);

		for (int l = 0; l < 360; l++)
		{
			theta = 2.0 * 3.1415926f / 360 * float(l);
			x = cosf(theta);
			y = sinf(theta);
			glVertex3f(x * 1.0 + (startX + 107.0), y * 1.0 + (startY - 218.0), 21.1f);
		}

		glEnd();

		glBegin(GL_POLYGON);

		for (int l = 0; l < 360; l++)
		{
			theta = 2.0 * 3.1415926f / 360 * float(l);
			x = cosf(theta);
			y = sinf(theta);
			glVertex3f(x * 1.0 + (startX + 110.0), y * 1.0 + (startY - 218.0), 21.1f);
		}

		glEnd();

	// Student's shorts
	glBegin(GL_QUADS);

		glColor3f(0.0f, 0.0f, 0.5f); // Navy blue

		//base
		glVertex3f(startX + 20.0f, startY - 250.0f, 50.0f);
		glVertex3f(startX - 120.0f, startY - 250.0f, 50.0f);
		glVertex3f(startX - 120.0f, startY - 300.0f, 50.0f);
		glVertex3f(startX + 20.0f, startY - 300.0f, 50.0f);

		glVertex3f(startX + 20.0f, startY - 250.0f, -50.0f);
		glVertex3f(startX - 120.0f, startY - 250.0f, -50.0f);
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

		//left pant
		glVertex3f(startX - 55.0f, startY - 300.0f, 50.0f);
		glVertex3f(startX - 120.0f, startY - 300.0f, 50.0f);
		glVertex3f(startX - 120.0f, startY - 320.0f, 50.0f);
		glVertex3f(startX - 55.0f, startY - 320.0f, 50.0f);

		glVertex3f(startX - 55.0f, startY - 300.0f, -50.0f);
		glVertex3f(startX - 120.0f, startY - 300.0f, -50.0f);
		glVertex3f(startX - 120.0f, startY - 320.0f, -50.0f);
		glVertex3f(startX - 55.0f, startY - 320.0f, -50.0f);

	glEnd();

	//Student's short pockets
	glBegin(GL_LINE_LOOP);

		glColor3f(0.0f, 0.0f, 0.0f); // black
		
		glVertex3f(startX + 5.0f, startY - 270.0f, -50.5f);
		glVertex3f(startX - 25.0, startY - 270.0f, -50.5f);
		glVertex3f(startX - 25.0f, startY - 300.0f, -50.5f);
		glVertex3f(startX + 5.0f, startY - 300.0f, -50.5f);

	glEnd();

	glBegin(GL_LINE_LOOP);

		glColor3f(0.0f, 0.0f, 0.0f); // black

		glVertex3f(startX - 100.0f, startY - 270.0f, -50.5f);
		glVertex3f(startX - 70.0, startY - 270.0f, -50.5f);
		glVertex3f(startX - 70.0f, startY - 300.0f, -50.5f);
		glVertex3f(startX - 100.0f, startY - 300.0f, -50.5f);

	glEnd();

	//Student's left leg
	glBegin(GL_QUADS);

		glColor3f(1.0f, 0.62f, 0.47f); // light pink

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

	//Student's right leg
	glBegin(GL_QUADS);

		glColor3f(1.0f, 0.62f, 0.47f); // light pink

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
		glVertex3f(startX - 110.0f, startY - 320.0f, 30.0f);
		glVertex3f(startX - 110.0f, startY - 405.0f, -30.0f);
		glVertex3f(startX - 110.0f, startY - 405.0f, -30.0f);

	glEnd();

	//Student's left shoe
	glBegin(GL_QUADS);

		glColor3f(0.0f, 0.0f, 0.0f); // black

		glVertex3f(startX + 15.0f, startY - 405.0f, 60.0f);
		glVertex3f(startX - 40.0f, startY - 405.0f, 60.0f);
		glVertex3f(startX - 40.0f, startY - 440.0f, 60.0f);
		glVertex3f(startX + 15.0f, startY - 440.0f, 60.0f);

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

	//Student's right shoe
	glBegin(GL_QUADS);

		glColor3f(0.0f, 0.0f, 0.0f); // black

		glVertex3f(startX - 60.0f, startY - 405.0f, 60.0f);
		glVertex3f(startX - 115.0f, startY - 405.0f, 60.0f);
		glVertex3f(startX - 115.0f, startY - 440.0f, 60.0f);
		glVertex3f(startX - 60.0f, startY - 440.0f, 60.0f);

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
		glVertex3f(startX - 60.0f, startY - 440.0f, 50.0f);

	glEnd();

	//Pop Matric
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
	glOrtho(0.0, width, 0.0, height, -300.0, 300.0); //For 3D viewing
}

/*
Main function for drawing the student.
*/
int
main(int argc, char *argv[])
{
	init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //Double buffering, RGB colors, depth
	glutInitWindowSize((int)width, (int)height); //Window size
	int wd = glutCreateWindow("COMP-5/6400 Assignment 3 - Spring 2014"); //Window title
	glutDisplayFunc(display); //Display 
	glutReshapeFunc(reshape); //Reshape
	glutSpecialFunc(processSpecialKeys); //For key input
	glEnable(GL_DEPTH_TEST); //Depth test
	glDepthFunc(GL_LESS);
	glutMainLoop();
	return 0;
}
