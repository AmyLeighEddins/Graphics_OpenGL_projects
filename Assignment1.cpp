#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLdouble width, height; 
int wd;                   
int top[100][2];       
int ceiling[100][2];
int brick[100][2];
int darkceiling[100][2];
int bus[10][2];
int bustop[10][2];

void 
init(void)
{
	width = 1081.0;                 
	height = 579.0;                  
	top[0][0] = (int)(344);  
	top[0][1] = (int)(height-349);
	top[1][0] = (int)(344); 
	top[1][1] = (int)(height - 319);
	top[2][0] = (int)(426);
	top[2][1] = (int)(height - 319);
	top[3][0] = (int)(426);
	top[3][1] = (int)(height - 180);
	top[4][0] = (int)(344);
	top[4][1] = (int)(height - 180);
	top[5][0] = (int)(344);
	top[5][1] = (int)(height - 147);
	top[6][0] = (int)(471);
	top[6][1] = (int)(height - 147);
	top[7][0] = (int)(471);
	top[7][1] = (int)(height - 120);
	top[8][0] = (int)(679);
	top[8][1] = (int)(height - 120);
	top[9][0] = (int)(679);
	top[9][1] = (int)(height - 180);
	top[10][0] = (int)(471);
	top[10][1] = (int)(height - 180);
	top[11][0] = (int)(471);
	top[11][1] = (int)(height - 319);
	top[12][0] = (int)(510);
	top[12][1] = (int)(height - 319);
	top[13][0] = (int)(510);
	top[13][1] = (int)(height - 349);

	top[14][0] = (int)(300);
	top[14][1] = (int)(height - 225);
	top[15][0] = (int)(380);
	top[15][1] = (int)(height - 225);
	top[16][0] = (int)(380);
	top[16][1] = (int)(height - 260);
	top[17][0] = (int)(300);
	top[17][1] = (int)(height - 260);

	top[18][0] = (int)(344);
	top[18][1] = (int)(height - 400);
	top[19][0] = (int)(510);
	top[19][1] = (int)(height - 400);
	top[20][0] = (int)(510);
	top[20][1] = (int)(height - 420);
	top[21][0] = (int)(344);
	top[21][1] = (int)(height - 420);

	top[22][0] = (int)(720);
	top[22][1] = (int)(height - 225);
	top[23][0] = (int)(720);
	top[23][1] = (int)(height - 175);
	top[24][0] = (int)(745);
	top[24][1] = (int)(height - 175);
	top[25][0] = (int)(745);
	top[25][1] = (int)(height - 225);

	top[26][0] = (int)(515);
	top[26][1] = (int)(height - 225);
	top[27][0] = (int)(550);
	top[27][1] = (int)(height - 225);
	top[28][0] = (int)(550);
	top[28][1] = (int)(height - 300);
	top[29][0] = (int)(515);
	top[29][1] = (int)(height - 300);

	top[30][0] = (int)(745);
	top[30][1] = (int)(height - 110);
	top[31][0] = (int)(745);
	top[31][1] = (int)(height - 145);
	top[32][0] = (int)(765);
	top[32][1] = (int)(height - 145);
	top[33][0] = (int)(765);
	top[33][1] = (int)(height - 110);

	top[34][0] = (int)(550);
	top[34][1] = (int)(height - 310);
	top[35][0] = (int)(580);
	top[35][1] = (int)(height - 310);
	top[36][0] = (int)(580);
	top[36][1] = (int)(height - 350);
	top[37][0] = (int)(550);
	top[37][1] = (int)(height - 350);

	top[38][0] = (int)(220);
	top[38][1] = (int)(height - 300);
	top[39][0] = (int)(300);
	top[39][1] = (int)(height - 300);
	top[40][0] = (int)(300);
	top[40][1] = (int)(height - 315);
	top[41][0] = (int)(220);
	top[41][1] = (int)(height - 315);

	top[42][0] = (int)(340);
	top[42][1] = (int)(height - 275);
	top[43][0] = (int)(380);
	top[43][1] = (int)(height - 275);
	top[44][0] = (int)(380);
	top[44][1] = (int)(height - 300);
	top[45][0] = (int)(340);
	top[45][1] = (int)(height - 300);

	top[46][0] = (int)(360);
	top[46][1] = (int)(height - 100);
	top[47][0] = (int)(400);
	top[47][1] = (int)(height - 100);
	top[48][0] = (int)(400);
	top[48][1] = (int)(height - 125);
	top[49][0] = (int)(360);
	top[49][1] = (int)(height - 125);

	ceiling[0][0] = (int)(300);
	ceiling[0][1] = (int)(height - 400);
	ceiling[1][0] = (int)(300);
	ceiling[1][1] = (int)(height - 300);
	ceiling[2][0] = (int)(550);
	ceiling[2][1] = (int)(height - 300);
	ceiling[3][0] = (int)(550);
	ceiling[3][1] = (int)(height - 400);
	ceiling[4][0] = (int)(260);
	ceiling[4][1] = (int)(height - 370);
	ceiling[5][0] = (int)(260);
	ceiling[5][1] = (int)(height - 315);
	ceiling[6][0] = (int)(300);
	ceiling[6][1] = (int)(height - 315);
	ceiling[7][0] = (int)(300);
	ceiling[7][1] = (int)(height - 370);

	ceiling[8][0] = (int)(300);
	ceiling[8][1] = (int)(height - 225);
	ceiling[9][0] = (int)(300);
	ceiling[9][1] = (int)(height - 125);
	ceiling[10][0] = (int)(425);
	ceiling[10][1] = (int)(height - 125);
	ceiling[11][0] = (int)(720);
	ceiling[11][1] = (int)(height - 175);
	ceiling[12][0] = (int)(720);
	ceiling[12][1] = (int)(height - 225);
	
	ceiling[13][0] = (int)(425);
	ceiling[13][1] = (int)(height - 125);
	ceiling[14][0] = (int)(425);
	ceiling[14][1] = (int)(height - 100);
	ceiling[15][0] = (int)(745);
	ceiling[15][1] = (int)(height - 100);
	ceiling[16][0] = (int)(745);
	ceiling[16][1] = (int)(height - 175);
	ceiling[17][0] = (int)(720);
	ceiling[17][1] = (int)(height - 175);

	ceiling[18][0] = (int)(380);
	ceiling[18][1] = (int)(height - 225);
	ceiling[19][0] = (int)(515);
	ceiling[19][1] = (int)(height - 225);
	ceiling[20][0] = (int)(515);
	ceiling[20][1] = (int)(height - 300);
	ceiling[21][0] = (int)(380);
	ceiling[21][1] = (int)(height - 300);

	ceiling[22][0] = (int)(300);
	ceiling[22][1] = (int)(height - 420);
	ceiling[23][0] = (int)(300);
	ceiling[23][1] = (int)(height - 400);
	ceiling[24][0] = (int)(344);
	ceiling[24][1] = (int)(height - 400);
	ceiling[25][0] = (int)(344);
	ceiling[25][1] = (int)(height - 420);

	ceiling[26][0] = (int)(190);
	ceiling[26][1] = (int)(height - 330);
	ceiling[27][0] = (int)(200);
	ceiling[27][1] = (int)(height - 265);
	ceiling[28][0] = (int)(230);
	ceiling[28][1] = (int)(height - 270);
	ceiling[29][0] = (int)(220);
	ceiling[29][1] = (int)(height - 335);

	brick[0][0] = (int)(260);
	brick[0][1] = (int)(height - 370);
	brick[1][0] = (int)(300);
	brick[1][1] = (int)(height - 370);
	brick[2][0] = (int)(300);
	brick[2][1] = (int)(height - 420);
	brick[3][0] = (int)(260);
	brick[3][1] = (int)(height - 420);

	brick[4][0] = (int)(300);
	brick[4][1] = (int)(height - 260);
	brick[5][0] = (int)(380);
	brick[5][1] = (int)(height - 260);
	brick[6][0] = (int)(380);
	brick[6][1] = (int)(height - 300);
	brick[7][0] = (int)(300);
	brick[7][1] = (int)(height - 300);

	brick[8][0] = (int)(300);
	brick[8][1] = (int)(height - 400);
	brick[9][0] = (int)(550);
	brick[9][1] = (int)(height - 400);
	brick[10][0] = (int)(550);
	brick[10][1] = (int)(height - 465);
	brick[11][0] = (int)(300);
	brick[11][1] = (int)(height - 465);

	brick[12][0] = (int)(515);
	brick[12][1] = (int)(height - 225);
	brick[13][0] = (int)(720);
	brick[13][1] = (int)(height - 225);
	brick[14][0] = (int)(720);
	brick[14][1] = (int)(height - 260);
	brick[15][0] = (int)(515);
	brick[15][1] = (int)(height - 260);

	brick[16][0] = (int)(720);
	brick[16][1] = (int)(height - 260);
	brick[17][0] = (int)(720);
	brick[17][1] = (int)(height - 225);
	brick[18][0] = (int)(760);
	brick[18][1] = (int)(height - 225);
	brick[19][0] = (int)(760);
	brick[19][1] = (int)(height - 260);

	brick[20][0] = (int)(745);
	brick[20][1] = (int)(height - 175);
	brick[21][0] = (int)(745);
	brick[21][1] = (int)(height - 145);
	brick[22][0] = (int)(765);
	brick[22][1] = (int)(height - 145);
	brick[23][0] = (int)(765);
	brick[23][1] = (int)(height - 175);

	brick[24][0] = (int)(550);
	brick[24][1] = (int)(height - 350);
	brick[25][0] = (int)(580);
	brick[25][1] = (int)(height - 350);
	brick[26][0] = (int)(580);
	brick[26][1] = (int)(height - 380);
	brick[27][0] = (int)(550);
	brick[27][1] = (int)(height - 380);

	darkceiling[0][0] = (int)(740);
	darkceiling[0][1] = (int)(height - 205);
	darkceiling[1][0] = (int)(755);
	darkceiling[1][1] = (int)(height - 210);
	darkceiling[2][0] = (int)(760);
	darkceiling[2][1] = (int)(height - 220);
	darkceiling[3][0] = (int)(755);
	darkceiling[3][1] = (int)(height - 230);
	darkceiling[4][0] = (int)(740);
	darkceiling[4][1] = (int)(height - 235);
	darkceiling[5][0] = (int)(725);
	darkceiling[5][1] = (int)(height - 230);
	darkceiling[6][0] = (int)(720);
	darkceiling[6][1] = (int)(height - 220);
	darkceiling[7][0] = (int)(725);
	darkceiling[7][1] = (int)(height - 210);

	darkceiling[8][0] = (int)(350);
	darkceiling[8][1] = (int)(height - 360);
	darkceiling[9][0] = (int)(375);
	darkceiling[9][1] = (int)(height - 360);
	darkceiling[10][0] = (int)(375);
	darkceiling[10][1] = (int)(height - 380);
	darkceiling[11][0] = (int)(350);
	darkceiling[11][1] = (int)(height - 380);

	darkceiling[12][0] = (int)(392.5);
	darkceiling[12][1] = (int)(height - 360);
	darkceiling[13][0] = (int)(418.5);
	darkceiling[13][1] = (int)(height - 360);
	darkceiling[14][0] = (int)(418.5);
	darkceiling[14][1] = (int)(height - 380);
	darkceiling[15][0] = (int)(392.5);
	darkceiling[15][1] = (int)(height - 380);

	darkceiling[16][0] = (int)(435);
	darkceiling[16][1] = (int)(height - 360);
	darkceiling[17][0] = (int)(460);
	darkceiling[17][1] = (int)(height - 360);
	darkceiling[18][0] = (int)(460);
	darkceiling[18][1] = (int)(height - 380);
	darkceiling[19][0] = (int)(435);
	darkceiling[19][1] = (int)(height - 380);

	darkceiling[20][0] = (int)(477.5);
	darkceiling[20][1] = (int)(height - 360);
	darkceiling[21][0] = (int)(502.5);
	darkceiling[21][1] = (int)(height - 360);
	darkceiling[22][0] = (int)(502.5);
	darkceiling[22][1] = (int)(height - 380);
	darkceiling[23][0] = (int)(477.5);
	darkceiling[23][1] = (int)(height - 380);

	darkceiling[24][0] = (int)(600);
	darkceiling[24][1] = (int)(height - 190);
	darkceiling[25][0] = (int)(625);
	darkceiling[25][1] = (int)(height - 190);
	darkceiling[26][0] = (int)(625);
	darkceiling[26][1] = (int)(height - 210);
	darkceiling[27][0] = (int)(600);
	darkceiling[27][1] = (int)(height - 210);

	darkceiling[28][0] = (int)(642.5);
	darkceiling[28][1] = (int)(height - 190);
	darkceiling[29][0] = (int)(667.5);
	darkceiling[29][1] = (int)(height - 190);
	darkceiling[30][0] = (int)(667.5);
	darkceiling[30][1] = (int)(height - 210);
	darkceiling[31][0] = (int)(642.5);
	darkceiling[31][1] = (int)(height - 210);

	darkceiling[32][0] = (int)(350);
	darkceiling[32][1] = (int)(height - 190);
	darkceiling[33][0] = (int)(375);
	darkceiling[33][1] = (int)(height - 190);
	darkceiling[34][0] = (int)(375);
	darkceiling[34][1] = (int)(height - 210);
	darkceiling[35][0] = (int)(350);
	darkceiling[35][1] = (int)(height - 210);

	darkceiling[36][0] = (int)(600);
	darkceiling[36][1] = (int)(height - 100);
	darkceiling[37][0] = (int)(625);
	darkceiling[37][1] = (int)(height - 100);
	darkceiling[38][0] = (int)(625);
	darkceiling[38][1] = (int)(height - 115);
	darkceiling[39][0] = (int)(600);
	darkceiling[39][1] = (int)(height - 115);

	darkceiling[40][0] = (int)(642.5);
	darkceiling[40][1] = (int)(height - 100);
	darkceiling[41][0] = (int)(667.5);
	darkceiling[41][1] = (int)(height - 100);
	darkceiling[42][0] = (int)(667.5);
	darkceiling[42][1] = (int)(height - 115);
	darkceiling[43][0] = (int)(642.5);
	darkceiling[43][1] = (int)(height - 115);

	darkceiling[44][0] = (int)(480);
	darkceiling[44][1] = (int)(height - 100);
	darkceiling[45][0] = (int)(505);
	darkceiling[45][1] = (int)(height - 100);
	darkceiling[46][0] = (int)(505);
	darkceiling[46][1] = (int)(height - 115);
	darkceiling[47][0] = (int)(480);
	darkceiling[47][1] = (int)(height - 115);

	darkceiling[48][0] = (int)(350);
	darkceiling[48][1] = (int)(height - 300);
	darkceiling[49][0] = (int)(375);
	darkceiling[49][1] = (int)(height - 300);
	darkceiling[50][0] = (int)(375);
	darkceiling[50][1] = (int)(height - 315);
	darkceiling[51][0] = (int)(350);
	darkceiling[51][1] = (int)(height - 315);

	darkceiling[52][0] = (int)(350);
	darkceiling[52][1] = (int)(height - 125);
	darkceiling[53][0] = (int)(375);
	darkceiling[53][1] = (int)(height - 125);
	darkceiling[54][0] = (int)(375);
	darkceiling[54][1] = (int)(height - 140);
	darkceiling[55][0] = (int)(350);
	darkceiling[55][1] = (int)(height - 140);

	darkceiling[56][0] = (int)(505);
	darkceiling[56][1] = (int)(height - 260);
	darkceiling[57][0] = (int)(505);
	darkceiling[57][1] = (int)(height - 290);
	darkceiling[58][0] = (int)(560);
	darkceiling[58][1] = (int)(height - 280);
	darkceiling[59][0] = (int)(560);
	darkceiling[59][1] = (int)(height - 250);

	darkceiling[60][0] = (int)(395);
	darkceiling[60][1] = (int)(height - 295);
	darkceiling[61][0] = (int)(395);
	darkceiling[61][1] = (int)(height - 275);
	darkceiling[62][0] = (int)(415);
	darkceiling[62][1] = (int)(height - 270);
	darkceiling[63][0] = (int)(415);
	darkceiling[63][1] = (int)(height - 290);

	darkceiling[64][0] = (int)(395);
	darkceiling[64][1] = (int)(height - 265);
	darkceiling[65][0] = (int)(395);
	darkceiling[65][1] = (int)(height - 245);
	darkceiling[66][0] = (int)(415);
	darkceiling[66][1] = (int)(height - 240);
	darkceiling[67][0] = (int)(415);
	darkceiling[67][1] = (int)(height - 260);

	darkceiling[68][0] = (int)(480);
	darkceiling[68][1] = (int)(height - 230);
	darkceiling[69][0] = (int)(500);
	darkceiling[69][1] = (int)(height - 235);
	darkceiling[70][0] = (int)(500);
	darkceiling[70][1] = (int)(height - 255);
	darkceiling[71][0] = (int)(480);
	darkceiling[71][1] = (int)(height - 250);


	bus[0][0] = (int)(160);
	bus[0][1] = (int)(height - 300);
	bus[1][0] = (int)(170);
	bus[1][1] = (int)(height - 300);
	bus[2][0] = (int)(170);
	bus[2][1] = (int)(height - 330);
	bus[3][0] = (int)(160);
	bus[3][1] = (int)(height - 330);

	bustop[0][0] = (int)(162);
	bustop[0][1] = (int)(height - 298);
	bustop[1][0] = (int)(168);
	bustop[1][1] = (int)(height - 298);
	bustop[2][0] = (int)(168);
	bustop[2][1] = (int)(height - 328);
	bustop[3][0] = (int)(162);
	bustop[3][1] = (int)(height - 328);
	


}


void
display(void)
{
	int i;

	glClearColor(1.0, 0.89, 0.77, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.69, 0.13, 0.13);
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)brick[0]);
	glVertex2iv((GLint *)brick[1]);
	glVertex2iv((GLint *)brick[2]);
	glVertex2iv((GLint *)brick[3]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)brick[4]);
	glVertex2iv((GLint *)brick[5]);
	glVertex2iv((GLint *)brick[6]);
	glVertex2iv((GLint *)brick[7]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)brick[8]);
	glVertex2iv((GLint *)brick[9]);
	glVertex2iv((GLint *)brick[10]);
	glVertex2iv((GLint *)brick[11]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)brick[12]);
	glVertex2iv((GLint *)brick[13]);
	glVertex2iv((GLint *)brick[14]);
	glVertex2iv((GLint *)brick[15]);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)brick[16]);
	glVertex2iv((GLint *)brick[17]);
	glVertex2iv((GLint *)brick[18]);
	glVertex2iv((GLint *)brick[19]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)brick[20]);
	glVertex2iv((GLint *)brick[21]);
	glVertex2iv((GLint *)brick[22]);
	glVertex2iv((GLint *)brick[23]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)brick[24]);
	glVertex2iv((GLint *)brick[25]);
	glVertex2iv((GLint *)brick[26]);
	glVertex2iv((GLint *)brick[27]);
	glEnd();

	float cx = 740;
	float cy = height - 260;
	float r = 20;
	int num_segments = 30;

	glBegin(GL_POLYGON);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

		float x = r * cosf(theta);
		float y = r * sinf(theta);

		glVertex2f(x + cx, y + cy);

	}
	glEnd();

	glColor3f(0.8, 0.78, 0.78);
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)ceiling[0]);
	glVertex2iv((GLint *)ceiling[1]);
	glVertex2iv((GLint *)ceiling[2]);
	glVertex2iv((GLint *)ceiling[3]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)ceiling[4]);
	glVertex2iv((GLint *)ceiling[5]);
	glVertex2iv((GLint *)ceiling[6]);
	glVertex2iv((GLint *)ceiling[7]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)ceiling[8]);
	glVertex2iv((GLint *)ceiling[9]);
	glVertex2iv((GLint *)ceiling[10]);
	glVertex2iv((GLint *)ceiling[11]);
	glVertex2iv((GLint *)ceiling[12]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)ceiling[13]);
	glVertex2iv((GLint *)ceiling[14]);
	glVertex2iv((GLint *)ceiling[15]);
	glVertex2iv((GLint *)ceiling[16]);
	glVertex2iv((GLint *)ceiling[17]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)ceiling[18]);
	glVertex2iv((GLint *)ceiling[19]);
	glVertex2iv((GLint *)ceiling[20]);
	glVertex2iv((GLint *)ceiling[21]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)ceiling[22]);
	glVertex2iv((GLint *)ceiling[23]);
	glVertex2iv((GLint *)ceiling[24]);
	glVertex2iv((GLint *)ceiling[25]);
	glEnd();
	

	
	glColor3f(0.96, 0.96, 0.96);
	glLineWidth(3.0);
	glBegin(GL_POLYGON);
		glVertex2iv((GLint *)top[0]);
		glVertex2iv((GLint *)top[1]);
		glVertex2iv((GLint *)top[12]);
		glVertex2iv((GLint *)top[13]);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2iv((GLint *)top[2]);
		glVertex2iv((GLint *)top[3]);
		glVertex2iv((GLint *)top[10]);
		glVertex2iv((GLint *)top[11]);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2iv((GLint *)top[4]);
		glVertex2iv((GLint *)top[5]);
		glVertex2iv((GLint *)top[6]);
		glVertex2iv((GLint *)top[10]);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2iv((GLint *)top[7]);
		glVertex2iv((GLint *)top[8]);
		glVertex2iv((GLint *)top[9]);
		glVertex2iv((GLint *)top[10]);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2iv((GLint *)top[14]);
		glVertex2iv((GLint *)top[15]);
		glVertex2iv((GLint *)top[16]);
		glVertex2iv((GLint *)top[17]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)top[18]);
	glVertex2iv((GLint *)top[19]);
	glVertex2iv((GLint *)top[20]);
	glVertex2iv((GLint *)top[21]);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)top[22]);
	glVertex2iv((GLint *)top[23]);
	glVertex2iv((GLint *)top[24]);
	glVertex2iv((GLint *)top[25]);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)top[26]);
	glVertex2iv((GLint *)top[27]);
	glVertex2iv((GLint *)top[28]);
	glVertex2iv((GLint *)top[29]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)top[30]);
	glVertex2iv((GLint *)top[31]);
	glVertex2iv((GLint *)top[32]);
	glVertex2iv((GLint *)top[33]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)top[34]);
	glVertex2iv((GLint *)top[35]);
	glVertex2iv((GLint *)top[36]);
	glVertex2iv((GLint *)top[37]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)top[38]);
	glVertex2iv((GLint *)top[39]);
	glVertex2iv((GLint *)top[40]);
	glVertex2iv((GLint *)top[41]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)top[42]);
	glVertex2iv((GLint *)top[43]);
	glVertex2iv((GLint *)top[44]);
	glVertex2iv((GLint *)top[45]);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)top[46]);
	glVertex2iv((GLint *)top[47]);
	glVertex2iv((GLint *)top[48]);
	glVertex2iv((GLint *)top[49]);
	glEnd();

	glLineWidth(10.0);
	glBegin(GL_LINES);
	glVertex2f(360,height - 105);
	glVertex2f(280,height - 105);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex2f(280, height - 200);
	glVertex2f(280, height - 100);
	glEnd();

	glLineWidth(3.0);
	glColor3f(0.8, 0.78, 0.78);
	glBegin(GL_POLYGON);
	glVertex2iv((GLint *)ceiling[26]);
	glVertex2iv((GLint *)ceiling[27]);
	glVertex2iv((GLint *)ceiling[28]);
	glVertex2iv((GLint *)ceiling[29]);
	glEnd();


	glColor3f(0.96, 0.96, 0.96);
	cx = 740;
	cy = height - 220; 
	r = 20;
	num_segments = 20;
	
		glBegin(GL_POLYGON);
		for (int ii = 0; ii < num_segments; ii++)
		{
			float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

			float x = r * cosf(theta);
			float y = r * sinf(theta);

			glVertex2f(x + cx, y + cy);

		}
		glEnd();

		glColor3f(0.41, 0.41, 0.41);
		glLineWidth(3.0);
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[0]);
		glVertex2iv((GLint *)darkceiling[1]);
		glVertex2iv((GLint *)darkceiling[2]);
		glVertex2iv((GLint *)darkceiling[3]);
		glVertex2iv((GLint *)darkceiling[4]);
		glVertex2iv((GLint *)darkceiling[5]);
		glVertex2iv((GLint *)darkceiling[6]);
		glVertex2iv((GLint *)darkceiling[7]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[8]);
		glVertex2iv((GLint *)darkceiling[9]);
		glVertex2iv((GLint *)darkceiling[10]);
		glVertex2iv((GLint *)darkceiling[11]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[12]);
		glVertex2iv((GLint *)darkceiling[13]);
		glVertex2iv((GLint *)darkceiling[14]);
		glVertex2iv((GLint *)darkceiling[15]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[16]);
		glVertex2iv((GLint *)darkceiling[17]);
		glVertex2iv((GLint *)darkceiling[18]);
		glVertex2iv((GLint *)darkceiling[19]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[20]);
		glVertex2iv((GLint *)darkceiling[21]);
		glVertex2iv((GLint *)darkceiling[22]);
		glVertex2iv((GLint *)darkceiling[23]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[24]);
		glVertex2iv((GLint *)darkceiling[25]);
		glVertex2iv((GLint *)darkceiling[26]);
		glVertex2iv((GLint *)darkceiling[27]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[28]);
		glVertex2iv((GLint *)darkceiling[29]);
		glVertex2iv((GLint *)darkceiling[30]);
		glVertex2iv((GLint *)darkceiling[31]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[32]);
		glVertex2iv((GLint *)darkceiling[33]);
		glVertex2iv((GLint *)darkceiling[34]);
		glVertex2iv((GLint *)darkceiling[35]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[36]);
		glVertex2iv((GLint *)darkceiling[37]);
		glVertex2iv((GLint *)darkceiling[38]);
		glVertex2iv((GLint *)darkceiling[39]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[40]);
		glVertex2iv((GLint *)darkceiling[41]);
		glVertex2iv((GLint *)darkceiling[42]);
		glVertex2iv((GLint *)darkceiling[43]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[44]);
		glVertex2iv((GLint *)darkceiling[45]);
		glVertex2iv((GLint *)darkceiling[46]);
		glVertex2iv((GLint *)darkceiling[47]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[48]);
		glVertex2iv((GLint *)darkceiling[49]);
		glVertex2iv((GLint *)darkceiling[50]);
		glVertex2iv((GLint *)darkceiling[51]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[52]);
		glVertex2iv((GLint *)darkceiling[53]);
		glVertex2iv((GLint *)darkceiling[54]);
		glVertex2iv((GLint *)darkceiling[55]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[56]);
		glVertex2iv((GLint *)darkceiling[57]);
		glVertex2iv((GLint *)darkceiling[58]);
		glVertex2iv((GLint *)darkceiling[59]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[60]);
		glVertex2iv((GLint *)darkceiling[61]);
		glVertex2iv((GLint *)darkceiling[62]);
		glVertex2iv((GLint *)darkceiling[63]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[64]);
		glVertex2iv((GLint *)darkceiling[65]);
		glVertex2iv((GLint *)darkceiling[66]);
		glVertex2iv((GLint *)darkceiling[67]);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2iv((GLint *)darkceiling[68]);
		glVertex2iv((GLint *)darkceiling[69]);
		glVertex2iv((GLint *)darkceiling[70]);
		glVertex2iv((GLint *)darkceiling[71]);
		glEnd();


		for (GLfloat y = 0.0; y < 579.0; y++)
		{
			glColor3f(1.0, 0.27, 0.0);
			glBegin(GL_POLYGON);
			glVertex2f(bus[0][0], y);
			glVertex2f(bus[1][0], y);
			glVertex2f(bus[2][0], y - 25);
			glVertex2f(bus[3][0], y - 25);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex2f(bus[0][0], y - 50);
			glVertex2f(bus[1][0], y - 50);
			glVertex2f(bus[2][0], y - 50 - 25);
			glVertex2f(bus[3][0], y - 50 - 25);
			glEnd();
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_POLYGON);
			glVertex2f(bustop[0][0], y-1);
			glVertex2f(bustop[1][0], y-1);
			glVertex2f(bustop[2][0], y - 25+1);
			glVertex2f(bustop[3][0], y - 25+1);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex2f(bustop[0][0], y - 50-1);
			glVertex2f(bustop[1][0], y - 50-1);
			glVertex2f(bustop[2][0], y - 50 - 25+1);
			glVertex2f(bustop[3][0], y - 50 - 25+1);
			glEnd();
			if (y == 579)
			{
				y = 0.0;
			}
			glFlush();
			glutPostRedisplay();
			for (int delay = 0; delay < 2000000; delay++)
			{
				
			}
			glColor3f(1.0, 0.89, 0.77);
			glBegin(GL_POLYGON);
			glVertex2f(bus[0][0], y);
			glVertex2f(bus[1][0], y);
			glVertex2f(bus[2][0], y - 25);
			glVertex2f(bus[3][0], y - 25);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex2f(bus[0][0], y - 50);
			glVertex2f(bus[1][0], y - 50);
			glVertex2f(bus[2][0], y - 50 - 25);
			glVertex2f(bus[3][0], y - 50 - 25);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex2f(bustop[0][0], y - 1);
			glVertex2f(bustop[1][0], y - 1);
			glVertex2f(bustop[2][0], y - 25 + 1);
			glVertex2f(bustop[3][0], y - 25 + 1);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex2f(bustop[0][0], y - 50 - 1);
			glVertex2f(bustop[1][0], y - 50 - 1);
			glVertex2f(bustop[2][0], y - 50 - 25 + 1);
			glVertex2f(bustop[3][0], y - 50 - 25 + 1);
			glEnd();
		}
		glFlush();

	
	
	


}


void
reshape(int w, int h)
{
	
	width = (GLdouble)w;
	height = (GLdouble)h;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);
}

int
main(int argc, char *argv[])
{
	init();

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize((int)width, (int)height);

	wd = glutCreateWindow("COMP-5/6400 Assignment 1");

	glutReshapeFunc(reshape);

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}
