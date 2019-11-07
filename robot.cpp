/*---------------------------------------------------------------------------------
 * This file contains a program, drawing & animating a wind-mill.
 * This program is used to teach LCS and scene graph concepts.
 *
 * by S. K. Ueng, Nov.  2006
 */
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>

#define   FILL   1
#define   LINE  2 
 /*-----Define a unit box--------*/
 /* Vertices of the box */
float  points[][3] = { {-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5},
					  {0.5, 0.5, -0.5}, {-0.5, 0.5, -0.5},
					  {-0.5, -0.5, 0.5}, {0.5, -0.5, 0.5},
					  {0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5} };
/* face of box, each face composing of 4 vertices */
int    face[][4] = { {0, 3, 2, 1}, {0, 1, 5, 4}, {1, 2, 6, 5},
					{4, 5, 6, 7}, {2, 3, 7, 6}, {0, 4, 7, 3} };
/* indices of the box faces */
int    cube[6] = { 0, 1, 2, 3, 4, 5 };
int handchange = 0;
/*-----Define GLU quadric objects, a sphere and a cylinder----*/
GLUquadricObj  *sphere = NULL, *cylind = NULL;
int    polygonMode = FILL;
/*-----Define window size----*/
int width = 1024, height = 1024;

//Global variables recording rotation angles of H-arm and blades.
float  arm_ang = 45.0, bld_ang = 10.0;
float hand_swag = 10;
float fl1 = 0, fl2 = 0, fl3 = 0;
float fr1 = 0, fr2 = 0, fr3 = 0;
float hl1 = 0, hl2 = 0, hl3 = 0;
float hr1 = 0, hr2 = 0, hr3 = 0;
float cx = 0, cy = 0, cz = 0;//中心移動
float crx = 0, cry = 0, crz = 0;//中心旋轉
float hh = 0;//head
bool wf1 = false, wf2 = false, wf3 = false;
bool wh1 = false, wh2 = false, wh3 = false;
bool is_step = false;
bool is_down = false;
bool is_attack = false;
int cir = 0,cir_c=0;
float att = 0,att2=0,att3=0,att4=0,att5=0,att6=0;
GLfloat l_position[4] = { 1,1,1,1 };
/*----------------------------------------------------------
 * Procedure to initialize the working environment.
 */
void  myinit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);      /*set the background color BLACK */
					 /*Clear the Depth & Color Buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, 499, 499);

	/*-----Set a parallel projection mode-----*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-30.0, 30.0, -30.0, 30.0, 0.0, 120.0);

	glEnable(GL_DEPTH_TEST);  /*Enable depth buffer for shading computing */
	/*
	//------------------------------------------------------------------------------------------------------------------------------------------
	//材?反光性?置
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //?面反射??
	GLfloat mat_shininess[] = { 50.0 };               //高光指?
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };   //?位置(1,1,1), 最后1-??
	GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 }; //?境光??
	glShadeModel(GL_SMOOTH);           //多?性填充模式

   //材??性
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	//?光?置
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //散射光?性
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //?面反射光
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //?境光??

	glEnable(GL_LIGHTING);   //??:使用光
	glEnable(GL_LIGHT0);     //打?0#?
	glEnable(GL_DEPTH_TEST); //打?深度??
	//-------------------------------------------------------------------------------------------------------------------------------------
	*/
	glFlush();/*Enforce window system display the results*/
}


/*-------------------------------------------------------
 * Procedure to draw a polygon as a blade of the windmill
 */
void draw_blade()
{
	/*glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, 4.0, 0.0);
	glVertex3f(1.0, 8.0, 0.0);
	glVertex3f(-1.0, 8.0, 0.0);
	glVertex3f(-1.0, 4.0, 0.0);
	glEnd();*/
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(2.0, 0.0, 0.0);
	glVertex3f(4.0, 3.0, 0.0);
	glVertex3f(3.0, 6.0, 0.0);
	glVertex3f(1.0, 6.5, 0.0);
	glVertex3f(-1.0, 6.0, 0.0);
	glVertex3f(-2.0, 3.0, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 3.0);
	glVertex3f(2.0, 0.0, 3.0);
	glVertex3f(4.0, 3.0, 3.0);
	glVertex3f(3.0, 6.0, 3.0);
	glVertex3f(1.0, 6.5, 3.0);
	glVertex3f(-1.0, 6.0, 3.0);
	glVertex3f(-2.0, 3.0, 3.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.0, 0.0, 0.0);
	glVertex3f(2.0, 0.0, 3.0);
	glVertex3f(4.0, 3.0, 3.0);
	glVertex3f(4.0, 3.0, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(4,3,0);
	glVertex3f(4,3,3);
	glVertex3f(3,6,3);
	glVertex3f(3,6,0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(3,6,0);
	glVertex3f(3,6,3);
	glVertex3f(1,6.5,3);
	glVertex3f(1,6.5,0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1,6.5,0);
	glVertex3f(1,6.5,3);
	glVertex3f(-1,6,3);
	glVertex3f(-1,6,0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1,6,0);
	glVertex3f(-1,6,3);
	glVertex3f(-2,3,3);
	glVertex3f(-2,3,0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0,0,0);
	glVertex3f(-2,3,0);
	glVertex3f(-2,3,3);
	glVertex3f(0,0,3);
	glEnd();
}

/*--------------------------------------------------------
 * Procedure to draw a cube. The geometrical data of the cube
 * are defined above.
 */
void draw_cube()
{
	int    i;

	//glColor3f(1.0, 1.0, 1.0);  /* Set the current color */
	for (i = 0; i < 6; i++) {
		glBegin(GL_POLYGON);  /* Draw the face */
		glVertex3fv(points[face[i][0]]);
		glVertex3fv(points[face[i][1]]);
		glVertex3fv(points[face[i][2]]);
		glVertex3fv(points[face[i][3]]);
		glEnd();
	}
}
void obstacle()
{
	glPushMatrix();
	glTranslatef(2.0, 0.0, 15.0);
	glColor3f(0, 0.3, 0);    /* Gray colored */
	glScalef(7.0, 30.0, 7.0);
	draw_cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40.0, 0.0, 5.0);
	//glColor3f(0.5, 0, 0);    /* Gray colored */
	glScalef(7.0, 30.0, 7.0);
	draw_cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.0, 0.0, 45.0);
	//glColor3f(0.5, 0, 0);    /* Gray colored */
	glScalef(7.0, 30.0, 7.0);
	draw_cube();
	glPopMatrix();
}
void draw_cylinder(void)
{
	if (cylind == NULL) {
		cylind = gluNewQuadric();
	}
	/*--- Draw a cylinder ---*/

	gluCylinder(cylind, 0.3, 0.3, /* radius of top and bottom circle */
		4.0,              /* height of the cylinder */
		12,               /* use 12-side polygon approximating circle*/
		4);               /* Divide it into 3 sections */

}
void draw_coord_sys(void)
{

	//draw coord. sys. in line or fill mode.
	if (polygonMode == LINE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Draw a sphere to show the origin
	if (sphere == NULL) {
		sphere = gluNewQuadric();
	}
	glColor3f(1.0, 1.0, 1.0);
	gluSphere(sphere, 0.5,   /* radius=0.5 */
		12,            /* composing of 12 slices*/
		12);           /* composing of 12 stacks */
//Draw the x-axis in RED.
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glRotatef(90.0, 0, 1, 0);   // The x-axis
	draw_cylinder();
	glPopMatrix();
	//Draw the Y-axis in GREEN.
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();  //The y-axis
	glRotatef(-90.0, 1, 0, 0);
	if (cylind == NULL) {
		cylind = gluNewQuadric();
		gluQuadricDrawStyle(cylind, GLU_FILL);
		gluQuadricNormals(cylind, GLU_SMOOTH);
	}
	gluCylinder(cylind, 0.2, 0.2, 100, 12, 3);
	glColor3f(0.0, 1.0, 0.0);
	if (cylind == NULL) {
		cylind = gluNewQuadric();
		gluQuadricDrawStyle(cylind, GLU_FILL);
		gluQuadricNormals(cylind, GLU_SMOOTH);
	}
	gluCylinder(cylind, 0.3, 0.3, 5, 12, 3);
	glPopMatrix();
	//Draw the z-axis in BLUE.
	glColor3f(0.0, 0.0, 1.0);
	draw_cylinder();   //The z-axis
}
void draw_floor()
{
	int   i, j;

	if (polygonMode == LINE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++) {
			if ((i + j) % 2 == 0) glColor3f(0, 0, 0);
			else glColor3f(0.3, 0.3, 0.3);
			glBegin(GL_POLYGON);
			glVertex3f(i, 0.0, j);
			glVertex3f(i, 0.0, j + 1);
			glVertex3f(i + 1, 0.0, j + 1);
			glVertex3f(i + 1, 0.0, j);
			glEnd();
		}
	for (i = 0; i < 10; i++)
		for (j = 0; j < 100; j+=1) {
			if ((i ) % 2 == 0) glColor3f(0.3, 0.3, 0.3);
			else glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_POLYGON);
			glVertex3f(i, j, 0);
			glVertex3f(i,j+1, 0);
			glVertex3f(i + 1, j+1, 0);
			glVertex3f(i + 1, j, 0);
			glEnd();
		}
	for (i = 0; i < 100; i++)
		for (j = 0; j < 100; j += 1) {
			if ((j) % 2 == 0) glColor3f(0.3, 0.3, 0.3);
			else glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_POLYGON);
			glVertex3f(0,i, j);
			glVertex3f(0,i, j + 1);
			glVertex3f(0,i + 1, j + 1);
			glVertex3f(0,i + 1, j);
			glEnd();
		}
}
/*-------------------------------------------------------
 * Display and Idle callback func. This func. draws three
 * cubes at proper places to simulate a solar system.
 */
void head()
{
	//頭
	glRotatef(hh, 1.0, 0.0, 0.0);
	glTranslatef(-1.5, -1, -3);
	
	glScalef(1.5, 2., 1.5);
	glColor3f(0.48, 0, 0);
	
	//gluSphere(sphere, 1,24,12);
	draw_blade();
	//draw_coord_sys();
	glPushMatrix();
	glTranslatef(0.0, 0.15, 0.5);
	glScalef(0.85, 0.85, 0.85);
	glColor3f(0.92, 0.89, 0.41);
	draw_blade();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.02, 0.2, 0.20);
	glScalef(1.02, 0.9, 0.85);
	glColor3f(0.92, 0.89, 0.41);
	draw_blade();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7, 4, 2.7);
	glScalef(0.2, 0.3, 0.2);
	glColor3f(0.48, 0, 0);
	draw_blade();
	glPopMatrix();

	glTranslatef(0.8, 3.2, 3.5);

	glPushMatrix();
	glTranslatef(-1.7, -0.4, 0);
	glRotatef(-8, 0.0, 0.0, 1.0);
	glColor3f(0.2, 0.2, 0.2);
	glScalef(0.45, 0.07, 0.08);
	draw_blade();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.2, -0.3, 0.02);
	glRotatef(-8, 0.0, 0.0, 1.0);
	glColor3f(0.8, 0.8, 1);
	glScalef(0.2, 0.01, 0.1);
	draw_blade();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, -0.6, 0);
	glRotatef(8, 0.0, 0.0, 1.0);
	glColor3f(0.2, 0.2, 0.2);
	glScalef(0.45, 0.07, 0.08);
	draw_blade();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1, -0.4, 0.02);
	glRotatef(8, 0.0, 0.0, 1.0);
	glColor3f(0.8, 0.8, 1);
	glScalef(0.2, 0.01, 0.1);
	draw_blade();
	glPopMatrix();

	

}
void body()
{
	//身體
	if (sphere == NULL) {
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
	}
	glColor3f(0.48, 0, 0);
	gluSphere(sphere, 1.5,24,12); 
	glPushMatrix();
		glTranslatef(-0.25, 0.5, 1);
		glScalef(0.15, 0.1, 0.15);
		glColor3f(1, 1, 1);
		draw_blade();
		//gluSphere(sphere, 1.5, 24, 12);
		glScalef(4, 4, 4);
	glPopMatrix();
}
void neck()
{
	//脖子
	glTranslatef(0.0, 1.7, -0.0);
	//glScalef(2/3, 0.4, 2/3);
	glScalef(0.5, 0.3, 0.5);
	glColor3f(0.48, 0, 0);
	if (sphere == NULL) {
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
	}
	gluSphere(sphere, 1,
		24,
		12);
}
void hand(int direc,int swag)
{
	//左手
	glPushMatrix();
	//glRotatef(90, 1.0, 0.0, 0.0);
	if(direc==0)
		glTranslatef(2.3, -1.0, -0.3);
	else
		glTranslatef(-2.3, -1.0, -0.3);
	//glRotatef(-arm_ang , 1.0, 0.0, 0.0);
	if (direc == 0)
		glRotatef(swag, 0.0, 0.0, 1.0);
	else
		glRotatef(-swag, 0.0, 0.0, 1.0);
	if (sphere == NULL) {
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
	}
	glColor3f(0.38, 0, 0);
	if (direc == 0)
		glRotatef(hl1, 1.0, 0.0, 0.0);
	else
		glRotatef(-hr1, 1.0, 0.0, 0.0);
	if (direc == 0)
		glRotatef(att, 0.0, 0.0, 1.0);
	else
		glRotatef(-att, 1.0, 0.0, 1.0);
	gluSphere(sphere, 1.0,12,12);
	
	glPushMatrix();
		glScalef(0.8, 0.8, 0.8);
		glTranslatef(0, 0, 0.5);
		glColor3f(0.92, 0.89, 0.41);
		gluSphere(sphere, 1.0, 12, 12);
	glPopMatrix();
	
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.48, 0, 0);
	if (cylind == NULL) {
		cylind = gluNewQuadric();
		gluQuadricDrawStyle(cylind, GLU_FILL);
		gluQuadricNormals(cylind, GLU_SMOOTH);
	}
	gluCylinder(cylind, 0.8, 0.7, 2.5, 12, 3);
	glPushMatrix();
	glScalef(0.8, 0.8, 0.8);
	if (direc == 0)
		glTranslatef(0.3, 0.5, 2);
	if (direc == 1)
		glTranslatef(-0.3, 0.5, 2);
	glColor3f(0.92, 0.89, 0.41);
	//draw_coord_sys();
	gluCylinder(cylind, 0.7, 0.6, 1, 12, 3);
	glPopMatrix();

	glRotatef(-90, 1.0, 0.0, 0.0);

	//glRotatef(-20, 0.0, 1.0, 0.0);
	glTranslatef(0, -3, 0);
	//glRotatef(-30, 1.0, 0.0, 0.0);
	glColor3f(0.38, 0, 0);
	if (sphere == NULL) {
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
	}
	if (direc == 0)
		glRotatef(hl2, 1.0, 0.0, 0.0);
	else
		glRotatef(-hr2, 1.0, 0.0, 0.0);
	gluSphere(sphere, 1,
		12,
		12);
	//draw_coord_sys();
	glTranslatef(0, -0.5, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.48, 0, 0);
	if (cylind == NULL) {
		cylind = gluNewQuadric();
		gluQuadricDrawStyle(cylind, GLU_FILL);
		gluQuadricNormals(cylind, GLU_SMOOTH);
	}
	gluCylinder(cylind, 0.65, 0.65, 3.0, 12, 3);
	glPushMatrix();
	glScalef(0.8, 0.8, 0.8);
	if (direc == 0)
		glTranslatef(0.3, 0.5, 0);
	if (direc == 1)
		glTranslatef(-0.3, 0.5, 0);
	glColor3f(0.92, 0.89, 0.41);
	//draw_coord_sys();
	gluCylinder(cylind, 0.5, 0.1, 3, 12, 3);
	glPopMatrix();

	glRotatef(-90, 1.0, 0.0, 0.0);

	glTranslatef(0, -3, 0);
	glColor3f(0.38, 0, 0);
	glScalef(0.8, 0.8, 1.3);
	if (sphere == NULL) {
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
	}
	//draw_coord_sys();
	if (direc == 0)
		glRotatef(hl3, 1.0, 0.0, 0.0);
	else
		glRotatef(-hr3, 1.0, 0.0, 0.0);
	//draw_coord_sys();
	if (direc == 0)
		glRotatef(-50, 0.0, 1.0, 0.0);
	if (direc == 1)
		glRotatef(50, 0.0, 1.0, 0.0);
	if (direc == 1)
		glRotatef(att2, 0.0, 1.0, 0.0);
	if (direc == 0)
		glRotatef(att3, 1.0, 0.0, 0.0);
	if (direc == 1)
		glRotatef(att3, 1.0, 0.0, 0.0);

	gluSphere(sphere, 1,
		12,
		12);
	//
	if (is_attack)
	{
		glPushMatrix();
		if (att6 < 10)
		{
			att4 += 1;
			att5 += 2;
			att6 += 1;
			glTranslatef(0, 0, 0.5);
			glColor3f(1, 1, 0.9);
			gluCylinder(cylind, att4, att5, att6, 12, 3);
			//display();
		}
		else
		{
			is_attack = false;
		}
		glPopMatrix();
	}
	//draw_coord_sys();
	glPushMatrix();
		glTranslatef(0, -0.1, 0.2);
		glColor3f(1, 1, 1);
		glScalef(0.8, 0.8, 0.8);
		gluSphere(sphere, 1,12,12);
	glPopMatrix();
	glTranslatef(0, -0, 0);
	//draw_coord_sys();
	glPushMatrix();
		glRotatef(90, 1.0, 0.0, 0.0);
		//draw_coord_sys();
		glRotatef(0, 0.0, 1.0, 0.0);
		glColor3f(0.38, 0, 0);
		if (cylind == NULL) {
			cylind = gluNewQuadric();
			gluQuadricDrawStyle(cylind, GLU_FILL);
			gluQuadricNormals(cylind, GLU_SMOOTH);
		}
		gluCylinder(cylind, 0.15, 0.15, 2.0, 12, 3);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(20, 0.0, 1.0, 0.0);
	glColor3f(0.38, 0, 0);
	if (cylind == NULL) {
		cylind = gluNewQuadric();
		gluQuadricDrawStyle(cylind, GLU_FILL);
		gluQuadricNormals(cylind, GLU_SMOOTH);
	}
	gluCylinder(cylind, 0.15, 0.15, 2.0, 12, 3);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(40, 0.0, 1.0, 0.0);
	glColor3f(0.38, 0, 0);
	if (cylind == NULL) {
		cylind = gluNewQuadric();
		gluQuadricDrawStyle(cylind, GLU_FILL);
		gluQuadricNormals(cylind, GLU_SMOOTH);
	}
	gluCylinder(cylind, 0.15, 0.15, 2.0, 12, 3);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(-20, 0.0, 1.0, 0.0);
	glColor3f(0.38, 0, 0);
	if (cylind == NULL) {
		cylind = gluNewQuadric();
		gluQuadricDrawStyle(cylind, GLU_FILL);
		gluQuadricNormals(cylind, GLU_SMOOTH);
	}
	gluCylinder(cylind, 0.15, 0.15, 2.0, 12, 3);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(-40, 0.0, 1.0, 0.0);
	glColor3f(0.38, 0, 0);
	if (cylind == NULL) {
		cylind = gluNewQuadric();
		gluQuadricDrawStyle(cylind, GLU_FILL);
		gluQuadricNormals(cylind, GLU_SMOOTH);
	}
	gluCylinder(cylind, 0.15, 0.15, 2.0, 12, 3);
	glPopMatrix();

		
	glPopMatrix();
	// glPopMatrix();
	
}
void value_init()
{
	arm_ang = 45.0;
	bld_ang = 10.0;
	hand_swag = 10;
	fl1 = 0;
	fl2 = 0;
	fl3 = 0;
	 fr1 = 0;
	 fr2 = 0;
	 fr3 = 0;
	 hl1 = 0;
	 hl2 = 0;
	 hl3 = 0;
	 hr1 = 0;
	 hr2 = 0;
	 hr3 = 0;
	 hh = 0;
	 cx = 0;
	 cy = 0;
	 cz = 0;//中心移動
	 crx = 0;
	 cry = 0;
	 crz = 0;//中心旋轉
	 wf1 = false;
	 wf2 = false;
	 wf3 = false;
	 wh1 = false;
	 wh2 = false;
	 wh3 = false;
	 is_step = false;
	 is_down = false;
	 is_attack = false;
	 cir = 0;
	 cir_c = 0;
	 att = 0;
	 att2 = 0;
	 att3 = 0;
	 att4 = 0;
	 att5 = 0;
	 att6 = 0;
}
void waist()
{
	//腰
	glPushMatrix();
	glScalef(1.5, 1.5, 1);
	if (sphere == NULL) {
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
	}
	glColor3f(0.38, 0, 0);
	gluSphere(sphere, 1,
		24,
		12);
	//draw_coord_sys();
	glPopMatrix();
}
void foot(int direc)
{
	//左腳
	glPushMatrix();
	if(direc==0)
		glTranslatef(2.0, 0.0, 0.0);
	else
		glTranslatef(-2.0, 0.0, 0.0);

	if (direc == 0)
		glRotatef(fl1, 1.0, 0.0, 0.0);
	else
		glRotatef(-fr1, 1.0, 0.0, 0.0);
	glColor3f(0.28, 0, 0);
	glScalef(1, 1, 1);
	if (sphere == NULL) {
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
	}
	gluSphere(sphere, 1,
		24,
		12);

	glTranslatef(0.0, -0.6, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	//glRotatef(10, 0.0, 1.0, 0.0);
	glColor3f(0.48, 0, 0);
	if (cylind == NULL) {
		cylind = gluNewQuadric();
		gluQuadricDrawStyle(cylind, GLU_FILL);
		gluQuadricNormals(cylind, GLU_SMOOTH);
	}
	gluCylinder(cylind, 0.9, 0.8, 4.5, 12, 3);
	glPushMatrix();
		glScalef(0.8, 0.8, 0.8);
		if (direc == 0)
			glTranslatef(0.3, 0.5, 0);
		if (direc == 1)
			glTranslatef(-0.3, 0.5, 0);
		glColor3f(0.92, 0.89, 0.41);
		//draw_coord_sys();
		gluCylinder(cylind, 0.7, 0.6, 3, 12, 3);
	glPopMatrix();

	glRotatef(-90, 1.0, 0.0, 0.0);
	glTranslatef(-0.0, -4.0, 0.0);
	glColor3f(0.28, 0, 0);
	if (sphere == NULL) {
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
	}
	if (direc == 0)
		glRotatef(fl2, 1.0, 0.0, 0.0);
	else
		glRotatef(-fr2, 1.0, 0.0, 0.0);
	gluSphere(sphere, 1,24,12);


	glTranslatef(-0.0, -1.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.48, 0, 0);
	if (cylind == NULL) {
		cylind = gluNewQuadric();
		gluQuadricDrawStyle(cylind, GLU_FILL);
		gluQuadricNormals(cylind, GLU_SMOOTH);
	}
	gluCylinder(cylind, 0.8, 0.6, 5, 12, 3);
	glPushMatrix();
	glScalef(0.8, 0.8, 0.8);
	if (direc == 0)
		glTranslatef(0.3, 0.5, 0);
	if (direc == 1)
		glTranslatef(-0.3, 0.5, 0);
	glColor3f(0.92, 0.89, 0.41);
	//draw_coord_sys();
	gluCylinder(cylind, 0.8, 0.4, 1, 12, 3);
	glPopMatrix();

	glRotatef(-90, 1.0, 0.0, 0.0);
	glTranslatef(-0.0, -4.5, 0);
	glColor3f(0.28, 0, 0);
	if (sphere == NULL) {
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
	}
	if (direc == 0)
		glRotatef(fl3, 1.0, 0.0, 0.0);
	else
		glRotatef(-fr3, 1.0, 0.0, 0.0);
	gluSphere(sphere, 1,
		24,
		12);
	//draw_coord_sys();


	glTranslatef(0.0, -0.0, 1.5);
	glColor3f(0.48, 0, 0);
	glScalef(2, 1, 4);
	draw_cube();
	glPopMatrix();
}
void display()
{

	/*Clear previous frame and the depth buffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*----Define the current eye position and the eye-coordinate system---*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();           /* Initialize modelview matrix */
	//gluLookAt(1.0, 5.0, 15.0, 10.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//glLightfv(GL_LIGHT1, GL_POSITION, l_position);
	gluLookAt(45.0, 50.0, 55.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//glLightfv(GL_LIGHT0, GL_POSITION, l_position);
	/*-------Draw the floor & coordinate system----*/
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	obstacle();
	glScalef(10.0, 1.0, 10.0);
	draw_floor();
	glPopMatrix();
	draw_coord_sys();
	if (cylind == NULL) {
		cylind = gluNewQuadric();
		gluQuadricDrawStyle(cylind, GLU_FILL);
		gluQuadricNormals(cylind, GLU_SMOOTH);
	}
	if (sphere == NULL) {
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
	}
	glTranslatef(20.0, 20.0, 20.0);
	glRotatef((GLfloat)cir_c, 0.0, 1.0, 0.0);
	//gluSphere(sphere, 1,24,12);
	glRotatef(40.0, 0.0, 1.0, 0.0);  /* rotate about y-axis by 30' */
	//draw_coord_sys();
	glTranslatef(0.0, 0.0, -5.0);
	glTranslatef(cx, cy, cz);
	glRotatef(crx, 1.0, 0.0, 0.0);  
	glRotatef(cry, 0.0, 1.0, 0.0);
	glRotatef(crz, 0.0, 0.0, 1.0);
	
	glTranslatef(-5.0, 0.0, 0.0);
	glRotatef((GLfloat)cir, 0.0, 1.0, 0.0);
	glPushMatrix();              /* Save M1 coord. sys */
		//glTranslatef(cx, cy, cz);
		glRotatef(0.0, 0.0, 1.0, 0.0);
		glScalef(1.5, 2.0, 1.5);     /* Scale up the axes by 6 times */
		glColor3f(0.38, 0.68, 0.68);    /* Gray colored */
		body();
		//draw_coord_sys();
		neck();
		//draw_coord_sys();
		head();
		
		//draw_coord_sys();
	glPopMatrix();               /* Get M1 back */
	glTranslatef(0, 3.0, 0.0);
	glRotatef(0, 0.0, 1.0, 0.0);
	//hand_swag = 10;
	hand(0,hand_swag);
	hand(1, hand_swag);
	glTranslatef(0.0, -6.0, 0.0);
	waist();
	
	glTranslatef(0.0, -2.0, 0.0);
	//骨盆
	glPushMatrix();
		glColor3f(0.48, 0.0, 0.0);
		glScalef(2, 1.5, 1);
		if (sphere == NULL) {
			sphere = gluNewQuadric();
			gluQuadricDrawStyle(sphere, GLU_FILL);
		}
		gluSphere(sphere, 1,
			24,
			12);
	glPopMatrix();
	glTranslatef(0.0, -1.2, 0.0);
	foot(0);
	foot(1);
	

	

	/*-------Swap the back buffer to the front --------*/
	glutSwapBuffers();
	glFlush(); /*--Display the results----*/
}
void my_reshape(int w, int h)
{
	width = w;
	height = h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w > h)
		glOrtho(-30.0, 30.0, -30.0*(float)h / (float)w, 30.0*(float)h / (float)w,
			0.0, 120.0);
	else
		glOrtho(-30.0*(float)w / (float)h, 30.0*(float)w / (float)h, -30.0, 30.0,
			0.0, 120.0);

}
void fly()
{
	if (hand_swag < 20)
	{
		hand_swag += 2;
		hh -= 15;
	}
	else
	{
		if (att3 < 50)
		{
			att3 += 2;
		}
		else
		{
			if (cy < 50)
			{
				cy += 5;
				is_attack = true;
			}
		}
	}
}
void jump()
{
	
	if(fl1 > -50&&wf1==false)
	{
		fl1 -= 2;
		fr1 += 2;
		fl2 += 4;
		fr2 -= 4;
		hl1 += 2;
		hr1 -= 2;
		hl2 -= 2;
		hr2 += 2;
		if(fl3>-45)
			fl3-=2;
		if(fr3<45)
			fr3 += 2;
		cy -= 0.2;
	}
	else if (fl1 <= -50 || wf1 == true)
	{
		wf1 = true;
		if (fl1 < 0)
		{
			fl1 += 2;
			fr1 -= 2;
			fl2 -= 4;
			fr2 += 4;
			hl1 -= 12;
			hr1 += 12;
			if (hl2 < 0)
				hl2 += 2;
			if (hr2 > 0)
				hr2 -= 2;
			if (fl3 < 0)
				fl3 += 2;
			if (fr3 >0 )
				fr3 -= 2;
			cy += 0.7;
		}
		else if (hl1 < 0) {
			if (cy > 0)
				cy -= 0.7;
			if(hl1<0)
				hl1 += 12;
			if(hr1>0)
				hr1 -= 12;
		}
		else
		{
			fl1 = 0;
			fl2 = 0;
			fr1 = 0;
			fr2 = 0;
			hl1 = 0;
			hl2 = 0;
			hr1 = 0;
			hr2 = 0;
			wf1 = false;
		}
	}
}
void attack()
{
	if (hr1 < 110)
	{
		hr1 += 2;

	}
	else
	{
		if(att<10)
		att += 2;
		else
		{
			if (att2 < 130)
				att2 += 2;
			else
			{
				if (att3 < 90)
					att3 += 4;
				else
				{
					is_attack = true;
					
				}
			}
		}
	}
}
void handswag()
{
	if (hand_swag < 30.0&&handchange == 0) {
		hand_swag += 2.0;
		//arm_ang -= 360.0; 
	}
	else if (hand_swag >= 30.0 || handchange == 1)
	{
		handchange = 1;
		hand_swag -= 2.0;
		if (hand_swag <= 0)
			handchange = 0;
	}
}
void step()
{
	
		if (hand_swag < 10)
		{
			handswag();
		}
		if (wf2 == false)
		{
			is_down = false;
			if (fl1 > -70 && wf1 == false)
			{
				fl1 -= 2;
				fl2 += 2;
				hr1 += 2;
				hl1 += 2;
			}
			else if (fl1 <= -70 || wf1 == true)
			{
				wf1 = true;
				fl1 += 2;
				fl2 -= 2;
				hr1 -= 2;
				hl1 -= 2;
				if (fl1 >= 0)
				{
					is_down = true;
					wf2 = true;
					wf1 = false;
				}
			}
		}
		else if (wf2 == true)
		{
			is_down = false;
			if (fr1 < 70 && wf1 == false)
			{
				fr1 += 2;
				fr2 -= 2;
				hl1 -= 2;
				hr1 -= 2;
			}
			else if (fr1 >= 70 || wf1 == true)
			{
				wf1 = true;
				fr1 -= 2;
				fr2 += 2;
				hl1 += 2;
				hr1 += 2;
				if (fr1 <= 0)
				{
					is_down = true;
					wf2 = false;
					wf1 = false;
					wf3 = true;
				}
			}
		}
		display();
	
}
void walk_around()
{
	while (cry < 360)
	{
		step();
		cry += 4;
	}
	cry = 0;
	walk_around();
}
void walk_circle()
{
	cir_c = (cir_c + 4) % 360;
	//cir = (cir + 5) % 360;
	//moon = (moon + 5) % 360;
	glutPostRedisplay();
	//break;
}
void walk()
{
	//fl1 = -30;
	
	
		if (hand_swag < 15)
		{
			handswag();
		}
		if (wf2 == false)
		{
			if (fl1 > -40 && wf1 == false)
			{
				fl1 -= 2;
				fr1 -= 2;
				hr1 += 4;
				hl1 += 4;
				if (wf3 == false)
				{
					fl2 += 1;
					fr2 -= 1;
					hr2 += 0.7;
					hl2 -= 0.7;
				}

				cz += 0.05;
				//cy -= 0.01;

			}
			else if (fl1 <= 30 || wf1 == true)
			{
				cz += 0.05;
				wf1 = true;
				fl1 += 2;
				fr1 += 2;
				hr1 -= 4;
				hl1 -= 4;
				//fl2 -= 3;
				//hr2 -= 3;
				//fr2 += 1.7;
				//hl2 -= 1.3;
				if (fl1 > 30)
				{
					wf2 = true;
					wf1 = false;
				}
			}
		}
		else if (wf2 == true)
		{
			if (fr1 > -40 && wf1 == false)
			{
				fr1 -= 2;
				fl1 -= 2;
				hl1 += 4;
				hr1 += 4;
				//fr2 += 1.7;
				//fl2 -= 0.05;
				//hl2 += 1.3;
				//hr2 += 1.3;
				cz += 0.05;
				//cy -= 0.01;

			}
			else if (fr1 <= 30 || wf1 == true)
			{
				cz += 0.05;
				wf1 = true;

				fr1 += 2;
				fl1 += 2;
				hl1 -= 4;
				hr1 -= 4;
				//fr2 -= 3;
				//fl2 += 3;
				//hl2 -= 1.3;
				//hr2 -= 1.3;
				if (fr1 > 30)
				{
					wf2 = false;
					wf1 = false;
					wf3 = true;
				}
			}
		}
		display();
	
}

/*--------------------------------------------------
 * Keyboard callback func. When a 'q' key is pressed,
 * the program is aborted.
 */
void my_keyboard(unsigned char key, int x, int y)
{
	if (key == 'Q' || key == 'q') exit(0);
	if (key == 'r') {
		//arm_ang += 5.0;
		//if (arm_ang > 360.0) arm_ang -= 360.0;
		if (arm_ang < 80.0&&handchange == 0) {
			arm_ang += 2.0;
			//arm_ang -= 360.0; 
		}
		else if (arm_ang >= 80.0 || handchange == 1)
		{
			handchange = 1;
			arm_ang -= 2.0;
			if (arm_ang <= 0)
				handchange = 0;
		}
	}
	else if (key == 'h') {
		//arm_ang += 5.0;
		//if (arm_ang > 360.0) arm_ang -= 360.0;
		handswag();
	}
	else if (key == 'w') {
		walk();
	}
	else if (key == 'a')
	{
		walk_around();
	}
	else if (key == 'j')
	{
		jump();
	}
	else if (key == 's') {
		is_step = !is_step;
		step();
	}
	else if (key == 'c') {
		while (true) {
			if (is_down)
				walk_circle();
			step();
		}
	}
	else if (key == 'p') {
		attack();
	}
	else if (key == 'i')
	{
		value_init();
	}
	else if (key == 'f')
	{
		fly();
	}
	display();
}


/*---------------------------------------------
 * Idle event callback function, increase blade and arm
 * rotation angles.
 */
void idle_func()
{
	bld_ang += 5.0;
	if (bld_ang > 360.0) {
		bld_ang -= 360.0;
		
		
	}
	display(); /* show the scene again */
}

/*---------------------------------------------------
 * Main procedure which defines the graphics environment,
 * the operation style, and the callback func's.
 */
void main(int argc, char **argv)
{
	/*-----Initialize the GLUT environment-------*/
	glutInit(&argc, argv);

	/*-----Depth buffer is used, be careful !!!----*/
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("robot");

	myinit();      /*---Initialize other state varibales----*/

	/*----Associate callback func's whith events------*/
	glutDisplayFunc(display);
	glutIdleFunc(idle_func);    /* Add idle event */
	glutReshapeFunc(my_reshape);
	glutKeyboardFunc(my_keyboard);

	glutMainLoop();
}
