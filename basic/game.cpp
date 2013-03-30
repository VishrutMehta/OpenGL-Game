#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <time.h>
#include "imageloader.h"
using namespace std;
float i;
int k=0,x1=0,x2=0;
GLuint _displayListId_blackArea; //The OpenGL id of the display list
GLuint _displayListId_whiteArea; //The OpenGL id of the display list
GLfloat angle = 0.0; //set the angle of rotation
int points = 0,gift=0;
//float up_z1 = 11;
//float up_y1 = 0.7;
//float up_x1 = 0.85;
float rotate_right = -60.0f;
float rotate_left = 60.0f;
int tp =0;
int position = 0, gir = 0;
int sx=0,sz=0,flag_exit = 0;
int wi,hi;
int fir = 0;
float change = 1.0f;
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}
GLuint x,grassTextureId;
class Person{
	public:
		float x,y,z;
		float up_z ;
		float up_y ;
		float up_x ;
		float rot_an;
		Person()
		{
			up_z = 11;
			up_y = 0.7;
			up_x = 0.85;
			rot_an=0;

		}
		void drawtree(float tree_x,float tree_y,float tree_z)
		{
			glPushMatrix();
			glTranslatef(tree_x,tree_y, tree_z);
			glPushMatrix();
			glTranslatef(0.2f,1.7f, 0.0f);
			glRotatef(270.0f,1.0f, 0.0f, 0.0f);
			glColor3f(1.0, 0.0, 0.0);
			glutSolidCone(0.2,3.0,100,100);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(1.0f,3.7f, -1.0f);
			glColor3f(0.0, 1.0, 0.0);
			glutSolidSphere(1.3, 20.0, 20.0);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-1.0f,3.7f, -0.5f);
			glColor3f(0.0, 1.0, 0.0);
			glutSolidSphere(1.3, 20.0, 20.0);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0.0f,4.7f, 0.0f);
			glColor3f(0.0, 1.0, 0.0);
			glutSolidSphere(1.3, 20.0, 20.0);
			glPopMatrix();
			glPopMatrix();

		}
		void drawPerson (void) {
			if(position == 0)
				rot_an = 0;
			else if(position == 1)
				rot_an = 270;
			else if(position == 2)
				rot_an = 180;
			else if(position == 3)
				rot_an = 90;
			glPushMatrix();
			glTranslatef(up_x,up_y,up_z);
			glScalef(0.3f,0.3f,0.3f);
			glPushMatrix();
			//person
			glTranslatef(0.0f, 3.0f, -5.0f);
			glRotatef(rot_an,0.0f,1.0f,0.0f);
			//eyes
			glPushMatrix();
			glTranslatef(0.25f, 0.0f, -1.0f);
			glColor3f(0.0, 0.0, 0.0);
			glutSolidSphere(0.25,10.0,10.0);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-0.45f, 0.0f, -1.0f);
			glutSolidSphere(0.25,10.0,10.0);
			glPopMatrix();
			//glRotatef(angle, 1.0, 0.0, 0.0); //rotate on the x axis
			//glRotatef(angle, 0.0, 1.0, 0.0); //rotate on the y axis
			//glRotatef(angle, 0.0, 0.0, 1.0); //rotate on the z axis
			glColor3f(0.8, 0.5, 0.0);
			//head
			glutSolidSphere(1.0, 20.0, 20.0);
			glPushMatrix();
			glBegin(GL_LINES);
			glColor3f(0.0f,0.0f,0.0f);
			glVertex3f(0.3f, -0.5f, -1.0f);
			glVertex3f(-0.5f, -0.5f, -1.0f);
			glEnd();
			glPopMatrix();
			//body
			glPushMatrix();
			glTranslatef(0.0f,-0.7f, 0.0f);
			glRotatef(90.0f,1.0f, 0.0f, 0.0f);
			glColor3f(1.0, 0.0, 0.0);
			GLUquadricObj *quadratic;
			quadratic = gluNewQuadric();
			//gluCylinder(quadratic,0.5f,1.2f,2.7f,32,32);
			gluCylinder(quadratic,0.5f,1.2f,2.7f,100,100);

			//right shoulder
			glPushMatrix();
			if(tp%2 == 0)
				glRotatef(-60.0f,1.0f, 0.0f, 0.0f);
			else
				glRotatef(60.0f,1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f,0.1f, 0.0f);
			glColor3f(0.8, 0.5, 0.0);
			GLUquadricObj *quadratic1;
			quadratic1 = gluNewQuadric();
			glRotatef(-60.0f,0.0f, 1.0f, 0.0f);
			gluCylinder(quadratic1,0.2f,0.2f,2.0f,32,32);
			glPopMatrix();
			//left shoulder
			glPushMatrix();
			if(tp%2 == 0)
				glRotatef(60.0f,1.0f, 0.0f, 0.0f);
			else
				glRotatef(-60.0f,1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f,0.1f, 0.0f);
			glColor3f(0.8, 0.5, 0.0);

			GLUquadricObj *quadratic2;
			quadratic2 = gluNewQuadric();
			glRotatef(60.0f,0.0f, 1.0f, 0.0f);
			gluCylinder(quadratic2,0.2f,0.2f,2.0f,32,32);
			glPopMatrix();

			//right leg
			glPushMatrix();
			glTranslatef(0.6f,-0.0f, 2.7f);
			glColor3f(0.8, 0.5, 0.0);
			//glRotatef(60.0f,0.0f, 1.0f, 0.0f);
			if(tp%2 == 0)
				glRotatef(45.0f,1.0f, 0.0f, 0.0f);
			else
				glRotatef(-45.0f,1.0f, 0.0f, 0.0f);
			GLUquadricObj *quadratic4;
			quadratic4 = gluNewQuadric();
			gluCylinder(quadratic4,0.2f,0.2f,1.5f,32,32);
			glPopMatrix();
			//left leg
			glPushMatrix();
			glTranslatef(-0.6f,-0.0f, 2.7f);
			glColor3f(0.8, 0.5, 0.0);
			//glRotatef(60.0f,0.0f, 1.0f, 0.0f);
			if(tp%2 == 0)
				glRotatef(-45.0f,1.0f, 0.0f, 0.0f);
			else
				glRotatef(45.0f,1.0f, 0.0f, 0.0f);
			GLUquadricObj *quadratic3;
			quadratic3 = gluNewQuadric();
			gluCylinder(quadratic3,0.2f,0.2f,1.5f,32,32);
			glPopMatrix();


			glPopMatrix();
			glPopMatrix();
			glPopMatrix();
			//glutWireCube(2);
		}
		void obstacle(float up_x1,float up_z1)
		{
			glPushMatrix();
			glTranslatef(up_x1,0.7,up_z1);
			glTranslatef(0.7f,-0.8f, -0.7f);
			glColor3f(210/255.0, 105/255.0f, 30/255.0);
			glRotatef(270.0f,1.0f, 0.0f, 0.0f);
			glutSolidCone(0.7,1.5,100,100);
			glPopMatrix();
		}
		void gifts(float up_x2, float up_z2)
		{
			glPushMatrix();
			glTranslatef(up_x2+0.2,0.7,up_z2);
			//glTranslatef(0.85,0.7,10);
			gift = ((gift+1)%2)^1;
			glColor3f(gift, gift^1, 0.0);
			//glColor3f(0.0, 0.0, 1.0);
			glutSolidSphere(0.3, 20.0, 20.0);
			glPopMatrix();

		}

		void draw_BlackArea()
		{
			//for removing tiles
			glColor3f(1.0f,1.0f,1.0f);
			// glPushMatrix();
			//glTranslatef(1.5f,0.0f,0.0f);
			//1
			glBegin(GL_QUADS);
			glTranslatef(0.0f,0.0f,0.0f);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glTexCoord2f(0.0f,change);
			glVertex3f(1.50f,0.0f,0.0f);
			glTexCoord2f(change,0.0f);
			glVertex3f(1.5f,-0.5f,0.0f);
			glTexCoord2f(change,change);
			glVertex3f(0.0f,-0.5f,0.0f);
			glEnd();

			//2
			glBegin(GL_QUADS);
			//	glColor3f(0.05f,0.05f,0.05f);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glTexCoord2f(0.0f,change);
			glVertex3f(0.0f,0.0f,-1.5f);
			glTexCoord2f(change,0.0f);
			glVertex3f(0.0f,-0.5f,-1.5f);
			glTexCoord2f(change,change);
			glVertex3f(0.0f,-0.5f,0.0f);
			glEnd();

			//3
			glBegin(GL_QUADS);
			//	glColor3f(0.05f,0.05f,0.05f);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(1.5f,0.0f,0.0f);
			glTexCoord2f(0.0f,change);
			glVertex3f(1.5f,0.0f,-1.5f);
			glTexCoord2f(change,0.0f);
			glVertex3f(1.5f,-0.5f,-1.5f);
			glTexCoord2f(change,change);
			glVertex3f(1.5f,-0.5f,0.0f);
			glEnd();

			//4 
			glBegin(GL_QUADS);
			//	glColor3f(0.05f,0.05f,0.05f);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(0.0f,0.0f,-1.5f);
			glTexCoord2f(0.0f,change);
			glVertex3f(1.50f,0.0f,-1.5f);
			glTexCoord2f(change,0.0f);
			glVertex3f(1.5f,-0.5f,-1.5f);
			glTexCoord2f(change,change);
			glVertex3f(0.0f,-0.5f,-1.5f);
			glEnd();

			//5 
			glBegin(GL_QUADS);
			//	glColor3f(0.05f,0.05f,0.05f);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glTexCoord2f(0.0f,change);
			glVertex3f(1.50f,0.0f,0.0f);
			glTexCoord2f(change,0.0f);
			glVertex3f(1.5f,0.0f,-1.5f);
			glTexCoord2f(change,change);
			glVertex3f(0.0f,0.0f,-1.5f);
			glEnd();

			//6 
			glBegin(GL_QUADS);
			//	glColor3f(0.0f,0.0f,0.0f);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(0.0f,-0.5f,0.0f);
			glTexCoord2f(0.0f,change);
			glVertex3f(1.50f,-0.5f,0.0f);
			glTexCoord2f(change,0.0f);
			glVertex3f(1.5f,-0.5f,-1.5f);
			glTexCoord2f(change,change);
			glVertex3f(0.0f,-0.5f,-1.5f);
			glEnd();
			//    glPopMatrix();

		}
		void draw_whiteArea()
		{
			glColor3f(1.0f,1.0f,1.0f);
			// glPushMatrix();
			glBegin(GL_QUADS);
			glTranslatef(0.0f,0.0f,0.0f);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glTexCoord2f(0.0f,change);
			glVertex3f(1.50f,0.0f,0.0f);
			glTexCoord2f(change,0.0f);
			glVertex3f(1.5f,-0.5f,0.0f);
			glTexCoord2f(change,change);
			glVertex3f(0.0f,-0.5f,0.0f);
			glEnd();


			glBegin(GL_QUADS);
			//	glColor3f(0.05f,0.05f,0.05f);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glTexCoord2f(0.0f,change);
			glVertex3f(0.0f,0.0f,-1.5f);
			glTexCoord2f(change,0.0f);
			glVertex3f(0.0f,-0.5f,-1.5f);
			glTexCoord2f(change,change);
			glVertex3f(0.0f,-0.5f,0.0f);
			glEnd();


			glBegin(GL_QUADS);
			//	glColor3f(0.05f,0.05f,0.05f);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(1.5f,0.0f,0.0f);
			glTexCoord2f(0.0f,change);
			glVertex3f(1.5f,0.0f,-1.5f);
			glTexCoord2f(change,0.0f);
			glVertex3f(1.5f,-0.5f,-1.5f);
			glTexCoord2f(change,change);
			glVertex3f(1.5f,-0.5f,0.0f);
			glEnd();

			glBegin(GL_QUADS);
			//	glColor3f(0.05f,0.05f,0.05f);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(0.0f,0.0f,-1.5f);
			glTexCoord2f(0.0f,change);
			glVertex3f(1.50f,0.0f,-1.5f);
			glTexCoord2f(change,0.0f);
			glVertex3f(1.5f,-0.5f,-1.5f);
			glTexCoord2f(change,change);
			glVertex3f(0.0f,-0.5f,-1.5f);
			glEnd();


			glBegin(GL_QUADS);
			//	glColor3f(0.05f,0.05f,0.05f);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glTexCoord2f(0.0f,change);
			glVertex3f(1.50f,0.0f,0.0f);
			glTexCoord2f(change,0.0f);
			glVertex3f(1.5f,0.0f,-1.5f);
			glTexCoord2f(change,change);
			glVertex3f(0.0f,0.0f,-1.5f);
			glEnd();


			glBegin(GL_QUADS);
			//	glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(0.0f,-0.5f,0.0f);
			glTexCoord2f(0.0f,change);
			glVertex3f(1.50f,-0.5f,0.0f);
			glTexCoord2f(change,0.0f);
			glVertex3f(1.5f,-0.5f,-1.5f);
			glTexCoord2f(change,change);
			glVertex3f(0.0f,-0.5f,-1.5f);
			glEnd();
			// glPopMatrix();

		}

};

Person p1;
int view = 0, sview = 0;
int obs_b = -1,obs_w = -1,gift_b=-1,gift_w=-1;
int j=0,call_randb = -1,call_randw = -1;
void dusra_update(int value)
{
	srand ( time(NULL) );
	call_randb = rand()%32 + 1;
	call_randw = rand()%32 + 1;
	obs_b = rand()%32;
	obs_w = rand()%32;
	gift_b = rand()%32;
	gift_w = rand()%32;
	glutTimerFunc(3000, dusra_update, 0);
}
int mode = 0;
void handleKeypress(unsigned char key,int x,int y)
{
	if(key == 27)
	{
		exit(0);
	}
	if(key == 'j')
	{
		x1 = 1;	
	}
	if(key == 'c')
	{
		view = 1;
	}
	if(key == 'n')
	{
		view = 0;
	}
	if(key == 't')
	{
		view = 2;
	}
	if(key == '0')
	{
		mode = 0;
	}
	if(key == '1')
	{
		mode = 1;
	}
	if(key == '2')
	{
		mode = 2;
	}
	if(key == '3')
	{
		mode = 3;
	}
	if(key == '4')
	{
		mode = 4;
	}
	if(key == 'h')
	{
		view = 3;
		sview = 1;
	}
}
void handleKeypress2(int key,int x,int y)
{
	if(key == GLUT_KEY_LEFT)
	{
		position = 3;
		tp++;
		sx -= 1;
		//position = (position-1)%4;
		p1.up_x -=1.5;
	}	
	if(key == GLUT_KEY_RIGHT)
	{
		position = 1;
		tp++;
		sx +=1;
		//position = (position+1)%4;
		p1.up_x +=1.5;
	}	
	if(key == GLUT_KEY_UP)
	{
		position = 0;
		tp++;
		sz += 1;
		//rotate_right = rotate_right*(-1);
		//rotate_left = rotate_left*(-1);
		p1.up_z -=1.5;
	}	
	if(key == GLUT_KEY_DOWN)
	{
		position = 2;
		tp++;
		sz -= 1;
		/*if(rotate_right == -15)
			rotate_right = -60;
		else
			rotate_right = -15;
		if(rotate_left == 60)
			rotate_left = 15;
		else
			rotate_left = 60;*/
		p1.up_z +=1.5;
	}	

}

void handleResize(int w,int h)
{
 	wi = w,hi = h;	
	/*glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(double)w/(double)h,1.0,200);
	gluLookAt(0.0f,10.5f, 20.0f,
			0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f);*/
}


void initRendering()
{
	/*	glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, x);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glDisable(GL_NORMALIZE);
		glEnable(GL_BLEND);
		glColor4f(1, 1, 1, WATER_ALPHA);
		glNormal3f(0, 1, 0);

		glBegin(GL_QUADS);
		glTexCoord2f(200 / WATER_TEXTURE_SIZE,
		-waterTextureOffset / WATER_TEXTURE_SIZE);
		glVertex3f(-100, 0, -100);
		glTexCoord2f(200 / WATER_TEXTURE_SIZE,
		(200 - waterTextureOffset) / WATER_TEXTURE_SIZE);
		glVertex3f(-100, 0, 100);
		glTexCoord2f(0, (200 - waterTextureOffset) / WATER_TEXTURE_SIZE);
		glVertex3f(100, 0, 100);
		glTexCoord2f(0, -waterTextureOffset / WATER_TEXTURE_SIZE);
		glVertex3f(100, 0, -100);
		glEnd();
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	 */

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0f,0.0f,0.2f,1.0f);
	Image* image = loadBMP("images.bmp");
	grassTextureId = loadTexture(image);

	Image* image1 = loadBMP("fire2.bmp");
	x = loadTexture(image1);
	//Set up a display list for drawing a cube
	_displayListId_blackArea = glGenLists(1); // Make room for the display list
	glNewList(_displayListId_blackArea, GL_COMPILE); // Begin the display list
	change = 1.0f;
	p1.draw_BlackArea(); //Add commands for drawing a black area to the display list
	glEndList(); //End the display list

	//Set up a display list for drawing a cube
	_displayListId_whiteArea = glGenLists(2); //Make room for the display list
	glNewList(_displayListId_whiteArea, GL_COMPILE); //Begin the display list
	p1.draw_whiteArea(); //Add commands for drawing a black to the display list
	glEndList(); //End the display list



	// To uncomment later
	GLfloat sun_direction[] = { 0.0, 2.0, -1.0, 1.0 };
	GLfloat sun_intensity[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat ambient_intensity[] = { 0.3, 0.3, 0.3, 1.0 };
	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);   // Setting a background color
	glEnable(GL_LIGHTING);              // Set up ambient light.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);

	glEnable(GL_LIGHT0);                // Set up sunlight.
	glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);

	glEnable(GL_COLOR_MATERIAL);        // Configure glColor().
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	delete image;
	delete image1;


}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);


	/*	GLuint texture = LoadGLTexture("water.bmp", 396, 734);
		glEnable(GL_TEXTURE_2D);
		glBindTexture( GL_TEXTURE_2D, texture );*/

	//Add ambient light
	/*	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color(0.2, 0.2, 0.2)
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	//Add positioned light
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	//Add directed light
	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);*/
	glRotatef(-0.0, 0.0f, 1.0f, 0.0f);
	glTranslatef(-4*1.5, 0.0, 4*1.5);
	//int gifts_x1 = -1, gifts_x2 = -1, gifts_z1 = -1, gifts_z2 = -1;
	int g=0,h=0,gg=-1,hh=-2,fl1=0,fl2=0,kk=0;
	int tile_x1=-1,tile_z1=-1;
	int tile_x2=-1,tile_z2=-1,cok = 0;
	int obs_x1=-1,obs_z1=-1,obs_x2=-1,obs_z2=-1;
	//int gifts_x1=-1,gifts_z1=-1,gifts_x2=-1,gifts_z2=-1;
	p1.drawtree(-40.0,0.0,-40.0);
	p1.drawtree(-30.0,0.0,-40.0);
	p1.drawtree(-20.0,0.0,-40.0);
	p1.drawtree(-10.0,0.0,-40.0);
	p1.drawtree(0.0,0.0,-40.0);
	p1.drawtree(10.0,0.0,-40.0);
	p1.drawtree(20.0,0.0,-40.0);
	p1.drawtree(30.0,0.0,-40.0);
	p1.drawtree(40.0,0.0,-40.0);
	p1.drawtree(0.0,0.0,0.0);
	p1.drawtree(12.0,0.0,0.0);
	glPushMatrix();
	glTranslatef(-50*1.5, 0.0, 50*1.5);
	//change = 10.0f;
	for(float j=0.0;j>(-100*1.5);j-=1.5)
	{
		k++;
		for(i=0.0;i<(50*3.0);i+=3.0)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, x);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);

			if(k%2==0)
			{
				glPushMatrix();
				glTranslatef(i,-1.0,j);
	p1.draw_BlackArea(); //Add commands for drawing a black area to the display list
			//	glCallList(_displayListId_blackArea);
				glPopMatrix();

			}
			else
			{
				glPushMatrix();
				glTranslatef(i+1.5,-1.0,j);
	p1.draw_BlackArea(); //Add commands for drawing a black area to the display list
			//	glCallList(_displayListId_blackArea);
				glPopMatrix();

			}
			glDisable(GL_TEXTURE_2D);
		}
	}
	for(float j=0.0;j>(-100*1.5);j-=1.5)
	{
		k++;
		for(i=0.0;i<(50*3.0);i+=3.0)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, x);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			if(k%2!=0)
			{
				glPushMatrix();
				glTranslatef(i,-1.0,j);
	p1.draw_whiteArea(); //Add commands for drawing a black to the display list
	//			glCallList(_displayListId_whiteArea);
				glPopMatrix();

			}
			else
			{
				glPushMatrix();
				glTranslatef(i+1.5,-1.0,j);
	p1.draw_whiteArea(); //Add commands for drawing a black to the display list
	//			glCallList(_displayListId_whiteArea);
				glPopMatrix();

			}
			glDisable(GL_TEXTURE_2D);
		}
	}
	glPopMatrix();
k=0;
change = 1.0;
	if(mode == 2)
	{
		for(float j=0.0;j>(-8*1.5);j-=1.5)
		{
			k++;kk++;
			if(kk%2==0)
			{
				fl1 = 1;
			}
			if(kk%2==1 && kk>1)
				cok =1;
			for(i=0.0;i<(4*3.0);i+=3.0)
			{
				g++;
				if(fl1 == 1)
				{
					fl1=0;
					gg = gg + 1;
				}
				else if(cok == 1)
				{
					cok = 0;
					gg = gg +3;
				}
				else
					gg = gg + 2;
				//if(call_randb == g)
				//{
				tile_x1 = gg%8;
				tile_z1 = gg/8;

				//}
				//else{
				if((tile_x1 == sx && tile_z1 == sz && gir == 1) || (sx < 0) || (sx > 7) || (sz < 0) || (sz > 7))
				{
					flag_exit = 1;
				}
				else{
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, grassTextureId);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					if(k%2==0)
					{
						if(obs_b == g)
						{
							obs_x1=gg%8;
							obs_z1=gg/8;
							p1.obstacle(i,j);
						}

						glPushMatrix();
						glTranslatef(i,0.0,j);
						glCallList(_displayListId_blackArea);
						glPopMatrix();

					}
					else
					{
						if(obs_b == g)
						{
							obs_x1=gg%8;
							obs_z1=gg/8;
							p1.obstacle(i+1.5,j);
						}

						glPushMatrix();
						glTranslatef(i+1.5,0.0,j);
						glCallList(_displayListId_blackArea);
						glPopMatrix();

					}
				}
				//}
			}
		}
		kk=0;int dnt = 0;
		for(float j=0.0;j>(-8*1.5);j-=1.5)
		{
			k++;kk++;
			if(kk%2==1 && kk>1)
			{
				fl2 = 1;
			}
			if(kk%2==0)
				dnt =1;
			for(i=0.0;i<(4*3.0);i+=3.0)
			{
				h++;
				if(fl2 == 1)
				{
					fl2=0;
					hh = hh + 1;
				}
				else if(dnt ==1)
				{
					dnt =0;
					hh = hh +3;
				}
				else
					hh = hh +2;
				//if(call_randw == h)
				//{
				tile_x2 = hh%8;
				tile_z2 = hh/8;
				//}
				//else{
				if( (tile_x2 == sx && tile_z2 == sz && gir == 1) || (sx < 0) || (sx > 7) || (sz < 0) || (sz > 7))
				{
					flag_exit = 1;
				}
				else{
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, grassTextureId);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					if(k%2!=0)
					{
						if(obs_w == h)
						{
							obs_x2=hh%8;
							obs_z2=hh/8;
							p1.obstacle(i,j);
						}
						glPushMatrix();
						glTranslatef(i,0.0,j);
						glCallList(_displayListId_whiteArea);
						glPopMatrix();

					}
					else
					{
						if(obs_w == h)
						{
							obs_x2=hh%8;
							obs_z2=hh/8;
							p1.obstacle(i+1.5,j);
						}

						glPushMatrix();
						glTranslatef(i+1.5,0.0,j);
						glCallList(_displayListId_whiteArea);
						glPopMatrix();

					}
				}
				//}
			}
		}
	}
	if(mode == 1)
	{
		for(float j=0.0;j>(-8*1.5);j-=1.5)
		{
			k++;kk++;
			if(kk%2==0)
			{
				fl1 = 1;
				//	printf("-------------in----------\n");
			}
			if(kk%2==1 && kk>1)
				cok =1;
			for(i=0.0;i<(4*3.0);i+=3.0)
			{
				g++;
				if(fl1 == 1)
				{
					fl1=0;
					gg = gg + 1;
				}
				else if(cok == 1)
				{
					cok = 0;
					gg = gg +3;
				}
				else
					gg = gg + 2;
				//	printf("gg: %d\n", gg);
				if(call_randb == g)
				{
					//		printf("------------------GG is %d\n",gg);
					tile_x1 = gg%8;
					tile_z1 = gg/8;

				}
				else{
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, grassTextureId);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					//	tile_x1 = gg%8;
					//	tile_z1 = gg/8;
					if(k%2==0)
					{
						if(obs_b == g)
						{
							obs_x1=gg%8;
							obs_z1=gg/8;
							p1.obstacle(i,j);
						}
						/*	if(gift_b == g)
							{
							gifts_x1=gg%8;
							gifts_z1=gg/8;
							p1.gifts(i,j);
							}*/
						glPushMatrix();
						glTranslatef(i,0.0,j);
						glCallList(_displayListId_blackArea);
						glPopMatrix();

					}
					else
					{
						if(obs_b == g)
						{
							obs_x1=gg%8;
							obs_z1=gg/8;
							p1.obstacle(i+1.5,j);
						}
						/*if(gift_b == g)
						  {
						  gifts_x1=gg%8;
						  gifts_z1=gg/8;
						  p1.gifts(i+1.5,j);
						  }*/
						glPushMatrix();
						glTranslatef(i+1.5,0.0,j);
						glCallList(_displayListId_blackArea);
						glPopMatrix();

					}
				}
			}
		}
		kk=0;int dnt = 0;
		for(float j=0.0;j>(-8*1.5);j-=1.5)
		{
			k++;kk++;
			if(kk%2==1 && kk>1)
			{
				fl2 = 1;
				//		printf("---------------in----------------\n");
			}
			if(kk%2==0)
				dnt =1;
			for(i=0.0;i<(4*3.0);i+=3.0)
			{
				h++;
				if(fl2 == 1)
				{
					fl2=0;
					hh = hh + 1;
				}
				else if(dnt ==1)
				{
					dnt =0;
					hh = hh +3;
				}
				else
					hh = hh +2;
				//	printf("hh:%d\n",hh);
				if(call_randw == h)
				{
					//	printf("------------------HH is %d\n",hh);
					tile_x2 = hh%8;
					tile_z2 = hh/8;
				}
				else{
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, grassTextureId);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					//	tile_x2 = hh%8;
					//	tile_z2 = hh/8;					
					if(k%2!=0)
					{
						if(obs_w == h)
						{
							obs_x2=hh%8;
							obs_z2=hh/8;
							p1.obstacle(i,j);
						}
						/*if(gift_w == h)
						  {
						  gifts_x2=hh%8;
						  gifts_z2=hh/8;
						  p1.gifts(i,j);
						  }*/
						glPushMatrix();
						glTranslatef(i,0.0,j);
						glCallList(_displayListId_whiteArea);
						glPopMatrix();

					}
					else
					{
						if(obs_w == h)
						{
							obs_x2=hh%8;
							obs_z2=hh/8;
							p1.obstacle(i+1.5,j);
						}
						/*if(gift_w == h)
						  {
						  gifts_x2=hh%8;
						  gifts_z2=hh/8;
						  p1.gifts(i+1.5,j);
						  }*/
						glPushMatrix();
						glTranslatef(i+1.5,0.0,j);
						glCallList(_displayListId_whiteArea);
						glPopMatrix();

					}
				}
			}
		}
	}
	else if(mode == 0)
	{
		for(float j=0.0;j>(-8*1.5);j-=1.5)
		{
			k++;
			for(i=0.0;i<(4*3.0);i+=3.0)
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, grassTextureId);

				//Bottom
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

				if(k%2==0)
				{
					glPushMatrix();
					glTranslatef(i,0.0,j);
					glCallList(_displayListId_blackArea);
					glPopMatrix();

				}
				else
				{
					glPushMatrix();
					glTranslatef(i+1.5,0.0,j);
					glCallList(_displayListId_blackArea);
					glPopMatrix();

				}
			}
		}
		for(float j=0.0;j>(-8*1.5);j-=1.5)
		{
			k++;
			for(i=0.0;i<(4*3.0);i+=3.0)
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, grassTextureId);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

				if(k%2!=0)
				{
					glPushMatrix();
					glTranslatef(i,0.0,j);
					glCallList(_displayListId_whiteArea);
					glPopMatrix();

				}
				else
				{
					glPushMatrix();
					glTranslatef(i+1.5,0.0,j);
					glCallList(_displayListId_whiteArea);
					glPopMatrix();

				}
			}
		}
	}
	if(mode == 0 || mode ==1)
	{
		if((tile_x1 == sx && tile_z1 == sz) ||( tile_x2 == sx && tile_z2 == sz) || (sx < 0) || (sx > 7) || (sz < 0) || (sz > 7))
		{
			flag_exit = 1;
		}
		if((sx == obs_x1 && sz == obs_z1) || (sx == obs_x2 && sz == obs_z2))
		{
			printf("You are DEAD !!!\nLOL!!!!!\n");
			exit(0);
		}
	}
	glPushMatrix(); 
	glTranslatef(0.0f, 0.0f, -5.0f); // Push eveything 5 units back into the scene, otherwise we won't see the primitive  
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	p1.drawPerson();
	//p1.obstacle();
	//p1.gifts(1,1);
	glPopMatrix();
	glutSwapBuffers();
	angle++;


}
float prevx,prevz;
void tesra_update(int value)
{
	if(fir == 0)
	{
		gir = 0;
		prevx = p1.up_x,prevz = p1.up_z;
		fir = 1;
	}
	else if(fir == 1)
	{
		if(prevx == p1.up_x && prevz == p1.up_z)
			gir = 1;
		fir = 0;
	}
	glutTimerFunc(1000, tesra_update, 0);
}
int counter = 0;
void update(int value) {
	//	_angle += 1.0f;
	//	if (_angle > 360) {
	//		_angle -= 360;
	//	}
	glViewport(0,0,wi,hi);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(double)wi/(double)hi,1.0,200);
	if(view == 0)
	{
		gluLookAt(0.0f,10.5f, 20.0f,
				0.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f);
	}
	else if(view == 1)
	{
		if(position == 0)
		{
			glTranslatef(6.0,-2.0,2.5);
			gluLookAt(p1.up_x,p1.up_y, p1.up_z - 2.0,
					p1.up_x,0.0f,p1.up_z - 5.0f,
					0.0f,1.0f,0.0f);
		}
		if(position == 2)
		{
			//	glRotatef(180,0.0f,1.0f,0.0f);

			glTranslatef(6.0,-2.0,2.5);
			gluLookAt(p1.up_x,p1.up_y ,(-1)* p1.up_z + 5.0,
					p1.up_x,0.0,p1.up_z + 5.0f,
					0.0f,1.0f,0.0f);
		}
		if(position == 1)
		{
			glTranslatef(6.0,-2.0,2.5);
			gluLookAt(p1.up_x,p1.up_y, p1.up_z - 2.0,
					p1.up_x,0.0f,p1.up_z - 5.0f,
					0.0f,1.0f,0.0f);
		}
		if(position == 2)
		{
			glTranslatef(6.0,-2.0,2.5);
			gluLookAt(p1.up_x,p1.up_y, p1.up_z - 2.0,
					p1.up_x,0.0f,p1.up_z - 5.0f,
					0.0f,1.0f,0.0f);
		}
	}
	else if(view == 2)
	{//tower

		gluLookAt(0.0f,20.0f, 20.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
	}
	else if(view == 3)
	{//heli
		if(sview == 1)
		{
			gluLookAt(p1.up_x - 0.85,40.5f, p1.up_z - 11.0 + 20.0,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
		}
		else{
			gluLookAt(0.0f,40.5f, 20.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
		}
	}
	if(counter == 10)
	{
		printf("You fell down, Sorry\nGAME OVER\n");
		exit(0);
	}
	if(flag_exit == 1)
	{
		p1.up_y -= 0.5;
		counter++;
	}
	if(x2 == 1)
	{
		x2 = 0;
		p1.up_y -= 1;
	}
	if(x1 == 1)
	{
		x1 = 0;
		if(position == 0)
		{
			sz += 2;
			x2 = 1;
			p1.up_y = p1.up_y + 1;
			p1.up_z = p1.up_z - 3;
		}
		if(position == 2)
		{
			sz -= 2;
			x2 = 1;
			p1.up_y = p1.up_y + 1;
			p1.up_z = p1.up_z + 3;
		}
		if(position == 1)
		{
			sx += 2;
			x2 = 1;
			p1.up_y = p1.up_y + 1;
			p1.up_x = p1.up_x + 3;
		}
		if(position == 3)
		{
			sx -= 2;
			x2 = 1;
			p1.up_y = p1.up_y + 1;
			p1.up_x = p1.up_x - 3;
		}
	}
	//glutPostRedisplay();
	glutTimerFunc(50, update, 0);
}



int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800,800);

	glutCreateWindow("My Adventure Game");
	initRendering();
	glutFullScreen();

	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(handleKeypress2);
	glutReshapeFunc(handleResize);
	glutTimerFunc(50, update, 0);
	glutTimerFunc(2000, dusra_update, 0);
	glutTimerFunc(1000, tesra_update, 0);

	glutMainLoop();
	return 0;

}
