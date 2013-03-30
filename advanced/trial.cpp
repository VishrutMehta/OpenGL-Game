#include <AL/alut.h>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <GL/gl.h>
#include <cstdio>
#include <time.h>
#include "imageloader.h"
//#include <soil.h>

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define FORN(i,a,b) for (int i = (a); i <= (b); i++)
#define FOR(i,a,b) for (int i = (a); i < (b); i++)			
#define S ({int x; scanf("%d", &x); x;})
#define PN(x) ({printf("%d\n", x);})						
#define PS(x) ({printf("%d ", x);})
#define NL ({printf("\n");})
#define printarr(i, x, y) ({for(int i=0;i<y;i++){ printf("%d ", x[i]);} printf("\n");})
#define inputarr(i, x, y) ({for(int i=0;i<y;i++){ scanf("%d", &x[i]);}})

#define NUM_BUFFERS 1
#define NUM_SOURCES 1
#define NUM_ENVIRONMENTS 1
 

#define ROB 0.04
#define LAMBDA 0.5
#define SIZE 10
#define SC 1
#define RAY 1000
#define F 0.3
#define STEP 0.1
#define AIR 2
#define SCY 0.9
#define ast_rad 0.1
#define TREE 12
#define GUNS 2
#define CAMERA 1
#define TILE_NUM 8
#define BULLETS 2

using namespace std;

// Function Declarations
void end_game();
void drawplayer();
void update_air(int value);
void drawsquare();
void drawRays();
void drawScene();
void update_gifts(int value);
void update(int value);
void update_rocks(int value);
void drawBox(float len);
void drawBall(float rad);
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
// Global Variables
bool removeflag=0, day=0, spot=0, hit=0, stat=1, flash=1;
int level=1, camera=0, factor =0, win=0, counter=0, w, h, CAM=5.0, hel_cam_angle=90, trampulinmode=0, tree_x[TREE], tree_z[TREE], cam_row=0, cam_col=0;
float YSC=1.5, i1=0.9, i2=0.9, i3=0.9, tim=0;
float num = 0.0f, board_angle_lim=0.5, PHY=0.007;
float jump_step=0.005;
float board_angle_z=0.0, cam_inc=0.005;
int coin_angle=0; 
float height, width;
float tri_x = 0.0f;
float tri_y = 0.0f;
float theta = 0.0f; 
float hel_eye_x=-6, hel_eye_y=60, hel_eye_z=-10, hel_ref_x=0, hel_ref_y=-5, hel_ref_z=-10, hel_slope=0;
float hel_up_x=0, hel_up_y=0, hel_up_z=1, jump_height=0.5;
float u1=0.05,g1=0.001, t1=0.0;
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
GLuint logoTextureId, grassTextureId, waterTextureId, lavaTextureId, tryTextureId, treeTextureId, branchTextureId;
class Power
{
	public:
		int x;
		Power()
		{
			x=0;
		}
		void drawBar()
		{
			glPushMatrix();
			glTranslatef(-12, 5, -6);
			glColor3f(1,1,1);
			glRotatef(90, 0,1,0);
			GLUquadricObj *quad;
			quad = gluNewQuadric();
			gluCylinder(quad, 0.2, 0.2, x, 32, 32);
			glPopMatrix();
		}
}P;
class Flag
{
	public:
		int flag_angle;
		Flag()
		{
			flag_angle=0;
		}
		void drawFlag()
		{
			glLoadIdentity();
			glPushMatrix();
			glRotatef(board_angle_z*5-flag_angle, 0,0,1);			
			glTranslatef(6.4,0.5,2.6);

			/*glPushMatrix();
			  GLUquadric *island = gluNewQuadric();
			  gluQuadricTexture(island, GL_TRUE);
			  glEnable(GL_TEXTURE_2D);
			  glBindTexture(GL_TEXTURE_2D, waterTextureId);
			  glColor3f(139/255.0, 69/255.0, 19/255.0);
			  glTranslatef(0,-4.3,0);
			  gluSphere(island,2,50,50);
			  glDisable(GL_TEXTURE_2D);

			  glPopMatrix();*/
			glPushMatrix();
			glTranslatef(0,-1, 0);
			glPushMatrix();
			glTranslatef(0,0,0);
			glColor3f(1,1,1);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, tryTextureId);	
			//glBindTexture(GL_TEXTURE_2D, waterTextureId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glBegin(GL_QUADS);
			glTexCoord2f(0,0);
			glVertex3f(0,1,0);
			glTexCoord2f(1,0);
			glVertex3f(1.5,1,0);
			glTexCoord2f(1,1);
			glVertex3f(1.5,0,0);
			glTexCoord2f(0,1);
			glVertex3f(0,0,0);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
			glPushMatrix();
			glColor3f(139/255.0, 69/255.0, 19/255.0);
			GLUquadricObj *pole = gluNewQuadric();
			glTranslatef(0,1,0);
			glRotatef(90, 1,0,0);
			gluCylinder(pole, 0.1, 0.1, 3, 32, 32);
			glPopMatrix();
			glPopMatrix();
			glPopMatrix();
		}
}flag1;
class Guns
{
	int face;
	public:
	void drawGuns(float xcoord, float zcoord)
	{
		glPushMatrix();
		glTranslatef(xcoord, -1.5, zcoord);
		glRotatef(90, 1,0,0);
		if(xcoord<-9)
			face=1;
		else
			face=2;
		GLUquadricObj *qgun = gluNewQuadric();
		glColor3f(139/255.0, 69/255.0, 19/255.0);
		gluCylinder(qgun, 0.2, 0.5, 0.8, 32, 32);
		glTranslatef(-0.4, 0, 0);
		if(face==2)
		{
			glRotatef(180, 0,1,0);
			glTranslatef(-0.75,0,0);
		}
		glRotatef(90, 0,1,0);
		glColor3f(205/255.0, 197/255.0, 191/255.0);
		gluCylinder(qgun, 0.2, 0.2, 1.5, 32, 32);
		glPopMatrix();
	}
}gun[GUNS];
class Bullets
{
	public:
		int xpos;
		float xcoord, zcoord;
		Bullets(float x, float z)
		{
			xcoord = x; zcoord=z;
			xpos=-1;
		}
		void pos()
		{
			int number=0, flag=0;
			if( xcoord < -(TILE_NUM+1))
				xpos=-1;
			else
			{
				for(int i=-(TILE_NUM+1); i<(TILE_NUM-2);i+=2)
				{
					if(i < xcoord && xcoord <= (i+2))
					{
						flag=1;
						xpos=number;
						break;
					}
					number++;
				}
			}

		}
		void drawBullets()
		{
			glPushMatrix();
			glColor3f(0,0,0);
			glTranslatef(xcoord, -1.5, zcoord);
			GLUquadricObj *quadratic2;
			quadratic2 = gluNewQuadric();
			gluSphere(quadratic2,0.15,50,50);
			glPopMatrix();
		}

}bullet1(-9.5, -7), bullet2(7.5, -4);
class Tree
{
	public:
		void drawTree(float x_coord, float z_coord)
		{
			glPushMatrix();
			glRotatef(board_angle_z*2, 0,0,1);
			glTranslatef(x_coord, -0.3, z_coord);

			glColor3f(210/255.0f, 105/255.0f, 30/255.0f);
			glPushMatrix();

			GLUquadric *island = gluNewQuadric();
			gluQuadricTexture(island, GL_TRUE);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, lavaTextureId);

			glTranslatef(0,-4.3,0);
			gluSphere(island,2,50,50);
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();

			glColor3f(139/255.0f,69/255.0f,19/255.0f);

			glPushMatrix();
			glTranslatef(0,-1.3,0);
			glRotatef(90,1,0,0);
			GLUquadricObj *quadcap = gluNewQuadric();

			gluQuadricTexture(quadcap, GL_TRUE);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, lavaTextureId);

			gluCylinder(quadcap, 0, 0.25, 1,32,32);
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
			glColor3f(0,1,0);

			glPushMatrix();
			glTranslatef(-0.3, -1.0, 0);
			GLUquadric *qobj = gluNewQuadric();

			gluQuadricTexture(qobj,GL_TRUE);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, lavaTextureId);

			gluSphere(qobj,0.6,50,50);
			glTranslatef(0.6,0,0);
			gluSphere(qobj, 0.6, 50, 50);
			glTranslatef(-0.3, 0.7,0);
			gluSphere(qobj, 0.6, 50, 50);

			glColor3f(25/255.0, 175/255.0, 25/255.0f);

			glTranslatef(0.55, 0, 0);
			gluSphere(qobj, 0.4, 50, 50);
			glTranslatef(-1.1, 0, 0);
			gluSphere(qobj, 0.4, 50, 50);
			glPopMatrix();

			glDisable(GL_TEXTURE_2D);

			glPopMatrix();

		}
}tree1;
class Person{
	public:
		bool jump, mock, jumpflag, falling, jumpcount, happy, trampulin, trampulinflag;
		int box_x, box_y,xpos,ypos, score;
		int facing, cur_facing;
		float x,y,z,right_shoulder, left_shoulder, left_leg, right_leg, left_mock, right_mock;
		float angle;
		Person()
		{
			jumpcount=0;score=0;happy=0; trampulin=0; trampulinflag=0;
			xpos=ypos=0; mock=0;
			falling=0;
			jump=0;
			box_x=box_y=0;
			x=y=z=0;
			facing=4; cur_facing=4;
			right_shoulder=30;
			left_shoulder=-30;
			right_leg=-30;
			left_leg=30;
			right_mock=-30;
			left_mock=30;
		}
		void movement()
		{
			switch(facing)
			{
				case 1: angle=90;break;
				case 2: angle=180; break;
				case 3: angle=270; break;
				case 4: angle=0;break;
			}

		}
		void position()
		{
			int curx=xpos, cury=ypos;
			int number=0, flag=0;
			if( (x-TILE_NUM/2)*2 < -(TILE_NUM+1))
				falling=1;
			else
			{
				for(int i=-(TILE_NUM+1); i<(TILE_NUM-2);i+=2)
				{
					if(i <(x-TILE_NUM/2)*2&&(x-TILE_NUM/2)*2<= (i+2))
					{
						flag=1;
						xpos=number;
						break;
					}
					number++;
				}
				if(!flag)
					falling=1;
			}

			if( ((TILE_NUM-2*2)+2*z) < - ( (TILE_NUM-1) * 2 -1) )
				falling=1;
			else
			{
				number=0; flag=0;
				for(int i=-((TILE_NUM-1)*2-1); i<2;i+=2)
				{
					if(i<(-(TILE_NUM-2)*2+2*z)&&(- (TILE_NUM-2)*2 +2*z)<=(i+2))
					{
						flag=1;
						ypos=number;
						break;
					}
					number++;
				}
				if(!flag)
					falling=1;
			}
			if(xpos == curx && ypos==cury)
				stat=1;
			else {
				stat=0;
				counter=0;
			}
		}
		void drawPerson () {

			GLfloat white[] = {0.8f, 0.8f, 0.8f, 1.0f};
			GLfloat cyan[] = {0.f, .8f, .8f, 1.f};
			glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
			glMaterialfv(GL_FRONT, GL_SPECULAR, white);
			GLfloat shininess[] = {50};
			glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
			glPushMatrix();
			glTranslatef((x-TILE_NUM/2)*2,(y-1),(- (TILE_NUM-2)*2 +z*2));
			glPushMatrix();

			//person
			glRotatef(angle, 0.0, 1.0, 0.0);

			glColor3f(255.0/255, 228.0/255, 181.0/255);
			//head
			if(hit)
				glColor3f(1,0,0);
			glutSolidSphere( F*1.0, 20.0, 20.0); 
			glColor3f(0.0, 0.0, 0.0);

			glPushMatrix();
			glTranslatef(-0.12, 0.05, 0.3);		
			glBegin(GL_TRIANGLE_FAN);
			for(int i=0 ; i<360 ; i++) {
				glVertex2f(0.06 * cos(DEG2RAD(i)), 0.06 * sin(DEG2RAD(i)));
			}
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.12, 0.05, 0.3);		
			glBegin(GL_TRIANGLE_FAN);
			for(int i=0 ; i<360 ; i++) {
				glVertex2f(0.06 * cos(DEG2RAD(i)), 0.06 * sin(DEG2RAD(i)));
			}
			glEnd();
			glPopMatrix();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, lavaTextureId);
			//cap
			glPushMatrix();
			glTranslatef(0,F*2,0);
			glRotatef(90,1,0,0);
			if(mock==1)
				glRotatef(left_mock,1,1,1);
			GLUquadricObj *quadcap;
			quadcap = gluNewQuadric();
			gluQuadricTexture(quadcap, GL_TRUE);
			glColor3f(1,1,0);
			gluCylinder(quadcap, 0, 0.4, 0.5,32,32);
			glPopMatrix();

			//body
			glPushMatrix();
			glTranslatef(F*0.0f,F*-0.7f, F*0.0f);   
			glRotatef(90.0f,1.0f, 0.0f, 0.0f);			
			GLUquadricObj *quadratic;
			quadratic = gluNewQuadric();
			gluQuadricTexture(quadratic, GL_TRUE);
			glColor3f(1.0, 0.0, 0.0);
			gluCylinder(quadratic,F*0.5f,F*1.2f,F*2.7f,32,32);
			glColor3f(255.0/255, 228.0/255, 181.0/255);
			glDisable(GL_TEXTURE_2D);
			//right shoulder
			glPushMatrix();
			glTranslatef(F*0.0f,F*0.1f, F*0.0f);  
			glRotatef(-60.0f,0.0f, 1.0f, 0.0f);
			glRotatef(right_shoulder,1,0,0);
			if(happy)
			{
				glRotatef(right_mock, 1,1,1);
			}

			GLUquadricObj *quadratic1;
			quadratic1 = gluNewQuadric();
			gluCylinder(quadratic1,F*0.2f,F*0.2f,F*2.2f,32,32);
			glPopMatrix();

			//left shoulder
			glPushMatrix();
			glTranslatef(F*0.0f,F*0.1f, F*0.0f);  
			glRotatef(60.0f,0.0f, 1.0f, 0.0f);
			glRotatef(left_shoulder, 1,0,0);
			if(happy)
			{
				glRotatef(left_mock, 1,1,1);
			}
			GLUquadricObj *quadratic2;
			quadratic2 = gluNewQuadric();
			gluCylinder(quadratic2,F*0.2f,F*0.2f,F*2.2f,32,32);
			glPopMatrix();

			glColor3f(255.0/255, 228.0/255, 181.0/255);
			//right leg
			glPushMatrix();
			glTranslatef(F*0.6f,F*-0.0f, F*2.7f);  
			glRotatef(right_leg,1.0f, 0.0f, 0.0f);
			if(mock==1)
				glRotatef(right_mock, 0,1,0);

			GLUquadricObj *quadratic4;
			quadratic4 = gluNewQuadric();
			gluCylinder(quadratic4,F*0.2f,F*0.2f,F*1.5f,32,32);
			glPopMatrix();

			//left leg
			glPushMatrix();
			glTranslatef(F*-0.6f,F*-0.0f, F*2.7f);  
			glRotatef(left_leg,1.0f, 0.0f, 0.0f);
			GLUquadricObj *quadratic3;
			if(mock==1)
				glRotatef(left_mock, 0,1,0);

			quadratic3 = gluNewQuadric();
			gluCylinder(quadratic3,F*0.2f,F*0.2f,F*1.5f,32,32);
			glPopMatrix();


			glPopMatrix();
			glPopMatrix();
			glPopMatrix();
		}
}p1;
class water
{
	public:
		void drawWater()
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, waterTextureId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glColor3f(1,1,1);
			glPushMatrix();
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-40, -2.9, -20);
			glTexCoord2f(20.0f, 0.0f);
			glVertex3f(40, -2.9, -20);
			glTexCoord2f(20.0f, 20.0f);
			glVertex3f(40, -2.9, 20);
			glTexCoord2f(0.0f, 20.0f);
			glVertex3f(-40, -2.9, 20);
			glEnd();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		}
}wat;
class Robots
{
	public:
		int xpos, ypos;
		float xcoord, zcoord;
		Robots(float x, float z)
		{
			xcoord = x; zcoord = z;
		}
		void position()
		{
			int number=0, flag=0;
			if( xcoord < -(TILE_NUM+1))
				xpos=-1;
			else
			{
				for(int i=-(TILE_NUM+1); i<(TILE_NUM-2);i+=2)
				{
					if(i < xcoord && xcoord <= (i+2))
					{
						flag=1;
						xpos=number;
						break;
					}
					number++;
				}
				if(!flag)
					xpos=-1;
			}

			if( zcoord < - ( (TILE_NUM-1) * 2 -1) )
				ypos=-1;
			else
			{
				number=0; flag=0;
				for(int i=-((TILE_NUM-1)*2-1); i<2;i+=2)
				{
					if(i< zcoord && zcoord <=(i+2))
					{
						flag=1;
						ypos=number;
						break;
					}
					number++;
				}
				if(!flag)
					ypos=-1;;
			}
		}
		void drawRobot()
		{	
			glPushMatrix();
			glColor3f(0,1,0);
			glTranslatef(xcoord, -1.5, zcoord);
			GLUquadricObj *quadratic2;
			quadratic2 = gluNewQuadric();
			gluSphere(quadratic2,0.4,50,50);
			glRotatef(90, 1,0,0);
			glTranslatef(-0.2, 0, 0);
			glColor3f(40.0/255, 180.0/255, 40.0/255);
			gluCylinder(quadratic2, 0.0, 0.1, 0.8, 32, 32);
			glTranslatef(0.4,0,0);
			gluCylinder(quadratic2, 0.0, 0.1, 0.8, 32, 32);
			glColor3f(0,0,0);
			glTranslatef(0.0,0.5,-0.3);
			gluSphere(quadratic2, 0.1, 50, 50);
			glTranslatef(-0.4, 0,0);
			gluSphere(quadratic2, 0.1, 50, 50);
			glPopMatrix();
		}
}robot1(-8.2, 2), robot2(6.8, -1), robot3(6.8, -12);
class floor
{
	public:
		bool gift;
		int x, y, giftx, gifty;
		int xair[AIR], yair[AIR];
		floor()
		{
			for(int i=0; i<AIR; i++)
			{
				xair[i]=-1; yair[i]=-1;
			}
			gift=0;
			x=y=-1;
			giftx=gifty=-1;			
		}
		void randomair()
		{
			for(int i=0; i<AIR;i++)
			{
				xair[i]=rand()%TILE_NUM;
				yair[i]=rand()%TILE_NUM;
				if(xair[i]==x && yair[i]==y)
					xair[i]=yair[i]=-1;
			}
		}
		void randomtile(){
			x = rand()%TILE_NUM;
			y= rand()%TILE_NUM;
		}
		void drawsquare()
		{
			glRotatef(board_angle_z*5,0,0,1);
			for(int j=0; j<TILE_NUM;j++)
			{
				glPushMatrix();
				glTranslatef(-SC*TILE_NUM+j*SC*2, -1.0f, -TILE_NUM-4.0f);
				glColor3f(1.0,1.0,1.0);			

				for(int i=0;i<TILE_NUM;i++)
				{
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, grassTextureId);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					if(!(i==y && j==x))
					{
						int flag=0;
						for(int k=0;k<AIR;k++)
						{
							if(i==yair[k]&&j==xair[k])
							{
								flag=1;
								YSC=-0.2;
								glColor3f(0.6,0.6,0.6);
							}
						}
						glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3f(-1.0f*SC, -1.0f*YSC, 1.0f*SC);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3f(-1.0f*SC, -1.0f*YSC, -1.0f*SC);
						glTexCoord2f(1.0f, 1.0f);
						glVertex3f(1.0f*SC, -1.0f*YSC, -1.0f*SC);
						glTexCoord2f(0.0f, 1.0f);
						glVertex3f(1.0f*SC, -1.0f*YSC, 1.0f*SC);	
						glEnd();

						glDisable(GL_TEXTURE_2D);
						glEnable(GL_TEXTURE_2D);
						glBindTexture(GL_TEXTURE_2D, lavaTextureId);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

						glBegin(GL_QUADS);
						glTexCoord2f(1.0f, 1.0f);
						glVertex3f(1.0f*SC, -2.0f*SCY, 1.0f*SC);					
						glTexCoord2f(0.0f, 1.0f);
						glVertex3f(-1.0f*SC, -2.0f*SCY, 1.0f*SC);					
						glTexCoord2f(0.0f, 0.0f);
						glVertex3f(-1.0f*SC, -1.0f*YSC, 1.0f*SC);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3f(1.0f*SC, -1.0f*YSC, 1.0f*SC);


						glEnd();

						glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3f(1.0f*SC, -1.0f*YSC, 1.0f*SC);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3f(1.0f*SC, -1.0f*YSC, -1.0f*SC);
						glTexCoord2f(1.0f, 1.0f);
						glVertex3f(1.0f*SC, -2.0f*SCY, -1.0f*SC);
						glTexCoord2f(0.0f, 1.0f);
						glVertex3f(1.0f*SC, -2.0f*SCY, 1.0f*SC);
						glEnd();

						glBegin(GL_QUADS);
						glTexCoord2f(1.0f, 1.0f);
						glVertex3f(1*SC,-2*SCY,-1*SC);
						glTexCoord2f(0.0f, 1.0f);
						glVertex3f(1*SC,-1*YSC,-1*SC);					
						glTexCoord2f(0.0f, 0.0f);
						glVertex3f(1*SC,-1*YSC,1*SC);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3f(1*SC,-2*SCY,1*SC);

						glEnd();

						glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3f(-1*SC,-1*YSC,1*SC);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3f(-1*SC,-2*SCY,1*SC);
						glTexCoord2f(1.0f, 1.0f);
						glVertex3f(-1*SC,-2*SCY,-1*SC);
						glTexCoord2f(0.0f, 1.0f);
						glVertex3f(-1*SC,-1*YSC,-1*SC);					


						glEnd();

						glBegin(GL_QUADS);
						glTexCoord2f(1.0f, 1.0f);
						glVertex3f(1*SC,-2*SCY,-1*SC);
						glTexCoord2f(0.0f, 1.0f);
						glVertex3f(1*SC,-2*SCY,1*SC);
						glTexCoord2f(0.0f, 0.0f);
						glVertex3f(-1*SC,-2*SCY,1*SC);
						glTexCoord2f(1.0f, 0.0f);
						glVertex3f(-1*SC,-2*SCY,-1*SC);

						glEnd();
						if(flag)
						{
							flag=0;
							YSC=1.5;
							glColor3f(1.0f,1.0f,1.0f);
						}
						if(i==gifty && j==giftx)
						{
							glPushMatrix();
							glTranslatef(-0.2, -1, -0.2);
							glRotatef(90,1,0,0);
							GLUquadricObj *quadgift;
							quadgift = gluNewQuadric();
							glDisable(GL_TEXTURE_2D);
							gift=gift^1;
							glColor3f(gift^1,gift,0);
							glRotatef(90, 1,0,0);
							glRotatef(coin_angle, 0,1,0);
							gluCylinder(quadgift, 0.5, 0.5, 0.1, 32, 32);
							//		glPushMatrix();
							//		glTranslatef(-0.12, 0.05, 0.3);		
							glBegin(GL_TRIANGLE_FAN);
							for(int i=0 ; i<360 ; i++) {
								glVertex2f(0.5 * cos(DEG2RAD(i)), 0.5 * sin(DEG2RAD(i)));
							}
							glEnd();
							//		glPopMatrix();
							/*gluCylinder(quadgift, 0.0, 0.4, 0.5, 32, 32);
							  gluCylinder(quadgift, 0.4, 0.0, 0.5, 32, 32);*/

							glColor3f(1,1,1);
							glPopMatrix();
						}
					}
					glTranslatef(0.0f*SC, 0.0f*SC, 2.0f*SC);
				}
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
		}

}f;

void sound(int kind)
{
	pid_t x;
        char kil[20] = "kill -s 9 ";	
	x=fork();
	if(x<0)
		return;
	if(x==0)
	{
//		printf("into it\n");
		switch(kind)
		{
			case 1: execlp("mplayer", "mplayer", "./scream.mp3", 0); break;
			case 2: execlp("mplayer", "mplayer", "./gun.mp3", 0); break;
			case 3: execlp("mplayer", "mplayer", "./scream.mp3", 0); break;
			case 4: execlp("mplayer", "mplayer", "./bell.mp3", 0); break;
		}
		//execlp("mplayer", "mplayer", "./scream.mp3", 0);
		_exit(0);
		return;
	}
	else
	{
		wait(x);
	}

	//system("mplayer ./beep.mp3");
}

class asteroids
{
	public:
		int height, rock_z;
		asteroids()
		{
			height=5; 
			rock_z=4;
		}
		void drawrocks()
		{
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			for(int i=-12; i<20; i+=2)
			{
				glLoadIdentity();
				glTranslatef(i,height+(i+8)%3,rock_z);

				GLUquadric *qobj = gluNewQuadric();

				gluQuadricTexture(qobj,GL_TRUE);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, waterTextureId);
				gluSphere(qobj,ast_rad,50,50);
			}
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
		}
}r;
class Health
{
	public:
		float x;
		Health()
		{
			x=10;
		}
		void drawBar()
		{
			glPushMatrix();
			glTranslatef(-6.5, 4, -6);
			glColor3f(1,0,0);
			glRotatef(90, 0,1,0);
			GLUquadricObj *quad;
			quad = gluNewQuadric();
			gluCylinder(quad, 0.2, 0.2, x, 32, 32);
			glPopMatrix();
		}
}H;

int main(int argc, char *argv[]) {
	srand(time(NULL));

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	w = glutGet(GLUT_SCREEN_WIDTH);
	h = glutGet(GLUT_SCREEN_HEIGHT);				
	int windowWidth = width;
	int windowHeight = height;						
	glutInitWindowSize(w, h);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);
	glutCreateWindow("CSE251_sampleCode");  // Setup the window
	initRendering();

	// Register callbacks
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(handleMouseclick);
	glutReshapeFunc(handleResize);
	glutTimerFunc(10, update, 0);
	glutTimerFunc(3000, update_gifts, 0);
	glutTimerFunc(1400, update_air, 0);
	glutTimerFunc(400, update_rocks, 0);
	glutMainLoop();
	return 0;
}
void quad()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(0,2,0);
	glVertex3f(0.5,2,0);
	glVertex3f(0.5,0,0);
	glVertex3f(0,0,0);
	glEnd();
	glPopMatrix();
}
// Function to draw objects on the screen
void drawScene() {

	glEnable(GL_LIGHTING);

	GLfloat dirVector0[]={ 0.0, -1.0, 0.0, 1.0};
	GLfloat lightPos0[]={ (p1.x-4)*2, p1.y+3.0, -12+2*p1.z, 1.0};
	GLfloat ambientLight0[] = {i1, i2, i3, 1.0f};
	//	GLfloat diffuseLight0[] = {1.0f, 1.0f, 1.0f, 1.0f};

	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight0);

	//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
	//	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
//	sound();
	if(!day)
	{
		GLfloat sun_direction[] = { 0.0, 2.0, -1.0, 1.0 };
		GLfloat sun_intensity[] = { 0.7, 0.7, 0.7, 1.0 };
		glEnable(GL_LIGHT0);                // Set up sunlight.
		glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);
	}
	if(spot)
	{
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dirVector0);
		glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.5);
	}

	glEnable(GL_COLOR_MATERIAL);        // Configure glColor().
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//	glEnable(GL_LIGHT0);

	//Lighting

	/*	GLfloat sun_direction[] = { 0.0, 2.0, -1.0, 1.0 };
		GLfloat sun_intensity[] = { 0.7, 0.7, 0.7, 1.0 };
		GLfloat ambient_intensity[] = { i1, i2, i3, 1.0 };
	// Enable coloring

	glEnable(GL_LIGHTING);              // Set up ambient light.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);

	glEnable(GL_LIGHT0);                // Set up sunlight.
	glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);

	glEnable(GL_COLOR_MATERIAL);        // Configure glColor().
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	 */
	//Done Lighting

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(flash)
	{
		glEnable(GL_BLEND);
		//		glEnable(GL_BLEND);
		//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0,0,0,0.5f);
		switch(level)
		{
			case 1:
				glPushMatrix();
				glTranslatef(-1,0,0);
				quad();
				glPopMatrix();
				break;
			case 2:
				for(int i=-1; i<1;i+=1)
				{
					glPushMatrix();
					glTranslatef(i,0,0);
					quad();
					glPopMatrix();
				}
				break;
			case 3:
				for(int i=-1; i<2;i++)
				{
					glPushMatrix();
					glTranslatef(i,0,0);
					quad();
					glPopMatrix();
				}
				break;
		}
		//		glDisable(GL_BLEND);
	}
	H.drawBar(); P.drawBar();
	wat.drawWater();
	gun[0].drawGuns(-10.5, -7);
	gun[1].drawGuns(8.5, -4);
	flag1.drawFlag(); 
	//-21 to -12 z -17 to -3
	for(int i=0; i<TREE; i++)
	{
		tree1.drawTree(tree_x[i], tree_z[i]);	
	}
	tree1.drawTree(-4,-17); tree1.drawTree(8, -17);
	tree1.drawTree(-5, 4.2); tree1.drawTree(5,4.2); tree1.drawTree(-10.5, -1.5);
	f.drawsquare();
	p1.movement();
	p1.position();
	int xper = (p1.x-4)*2, zper = -12 + p1.z*2;
	if(level>2)
	{
		if( (int)robot1.xcoord < xper)
			robot1.xcoord+=ROB;
		else if( (int)robot1.xcoord > xper)
			robot1.xcoord-=ROB;
		else
		{
			if( (int)robot1.zcoord < zper)
				robot1.zcoord+=ROB;
			else
				robot1.zcoord-=ROB;
		}
		if( (int)robot2.xcoord < xper)
			robot2.xcoord+=ROB;
		else if( (int)robot2.xcoord > xper)
			robot2.xcoord-=ROB;
		else
		{
			if( (int)robot2.zcoord < zper)
				robot2.zcoord+=ROB;
			else
				robot2.zcoord-=ROB;
		}
		if((int)robot3.xcoord < xper)
			robot3.xcoord+=ROB;
		else if((int)robot3.xcoord > xper)
			robot3.xcoord-=ROB;
		else
		{
			if((int)robot3.zcoord < zper)
				robot3.zcoord+=ROB;
			else
				robot3.zcoord-=ROB;
		}
		if(( (robot1.xpos == robot2.xpos) && ( robot2.xpos== robot3.xpos)) && ((robot1.ypos == robot2.ypos) && (robot2.ypos == robot3.ypos)))
			robot1.xcoord=-8.2, robot1.zcoord= 2, robot2.xcoord=6.8,robot1.zcoord= -1, robot3.xcoord=6.8, robot3.zcoord=-12;
		robot1.drawRobot(); robot2.drawRobot(); robot3.drawRobot();
	}
	bullet1.pos(); bullet2.pos();
	if(level>2)
	{
		robot1.position(); robot2.position(); robot3.position();

		if ((p1.xpos == robot1.xpos && p1.ypos == robot1.ypos) || (p1.xpos == robot2.xpos && p1.ypos == robot2.ypos) ||(p1.xpos == robot3.xpos && p1.ypos == robot3.ypos))
		{
			sound(3);
			H.x-=0.04;
			hit=1;
			p1.happy=1;
			if(H.x<0)
				end_game();
		}
	}
	if((p1.xpos == bullet1.xpos && p1.ypos == 2) || (p1.xpos == bullet2.xpos && p1.ypos == 4))
	{
		H.x-=0.06;
		hit=1;
		p1.happy=1;
		if(H.x<0)
			end_game();
	}
	for(int i=0; i<AIR; i++)
	{
		if(p1.xpos == f.xair[i] && p1.ypos == f.yair[i])
		{
			
		sound(1);
			p1.mock=1;
			switch(p1.facing)
			{
				case 1: p1.x+=1; break;
				case 2: p1.z+=1; break;
				case 3: p1.x-=1; break;
				case 4: p1.z-=1; break;
			}
			PHY+=0.002;
			board_angle_lim+=0.1;
		}
	}
	if(p1.xpos == 7 && p1.ypos == 7)
	{
		win++;
		flag1.flag_angle = 10;
		if(win==level*7)
			end_game();
		else
			flag1.flag_angle=0;
	}
	if(p1.xpos == f.giftx && p1.ypos == f.gifty)
	{
		sound(4);
		p1.happy=1;
		f.giftx = f.gifty = -1;
		p1.score++;
		P.x++;
	}
	if(p1.xpos == f.x && p1.ypos==f.y && p1.jump!=1)
	{
		p1.falling=1;
	}
	r.drawrocks();
	bullet1.drawBullets();
	bullet2.drawBullets();
	p1.drawPerson();
	glColor3f(1.0, 1.0, 1.0);
	glShadeModel(GL_SMOOTH);
	glutSwapBuffers();
}
// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update_rocks(int value)
{
	if (stat && p1.trampulin!=1)
		counter++;
	if(counter==5)
	{
		f.x = p1.xpos; f.y = p1.ypos;
	}
	if(hit)
		hit=0;
	r.height--;
	if(r.height==-5)
		r.height=5;
	glutTimerFunc(400, update_rocks, 0);
}
void update_air(int value)
{
	f.randomair();
	if(rand()%2 ==1 && !p1.falling)
		f.randomtile();
	glutTimerFunc(1400, update_air, 0);
}
void update_gifts(int value)
{
	if(flash)
		flash=0;
	p1.mock=0;p1.happy=0;
	f.giftx=rand()%8; f.gifty=rand()%8;
	glutTimerFunc(3000, update_gifts, 0);
}
void update(int value) {
	if (level>1)
	{
		bullet1.xcoord+=0.2;
		bullet2.xcoord-=0.2;
		if(bullet1.xcoord > 8)
		{
			sound(2);
			bullet1.xcoord = -9.5;
		}
		if(bullet2.xcoord < -8)
		{
			sound(2);
			bullet2.xcoord = 7.5; 
		}
	}
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0,(double)w/(double)h,1.0,200);
	switch(camera)
	{
		float upx, upz, refx, refy, refz; int numx, numz;
		case 0: gluLookAt( 0, 15, 40, 0,-5,-10, 0,5,0); break;
		case 1: //float refx, refy, refz; //int numx, numz;
			switch(p1.facing)
			{
				case 1: numx=CAM; numz=0; upx=CAM; upz=0;break;
				case 2: numz=-CAM; numx=0; upx=0; upz=-CAM;break;
				case 3: numx=-CAM; numz=0; upx=-CAM; upz=0;break;
				case 4: numz=CAM; numx=0; upx=0; upz=CAM;break;
			}
			refx=(p1.x-4)*2, refy=p1.y, refz=p1.z*2-12;
			gluLookAt(refx-numx*2, refy+5.0, refz-numz*2, (refx+numx), (refy-3.0),(refz+numz),0,1,0);
			break;
		case 2: //float refx, refy, refz; //int numx, numz;
			switch(p1.facing)
			{
				case 1: numx=CAM; numz=0; upx=CAM; upz=0;break;
				case 2: numz=-CAM; numx=0; upx=0; upz=-CAM;break;
				case 3: numx=-CAM; numz=0; upx=-CAM; upz=0;break;
				case 4: numz=CAM; numx=0; upx=0; upz=CAM;break;
			}
			refx=(p1.x-4)*2, refy=p1.y, refz=p1.z*2-12;
			gluLookAt(refx-numx, refy+5.0, refz-numz, (refx+numx), (refy-3.0),(refz+numz),0,1,0);
			break;
		case 3:	gluLookAt(hel_eye_x, hel_eye_y, hel_eye_z,   hel_eye_x, hel_eye_y-10, hel_eye_z,   hel_up_x, hel_up_y, -hel_up_z);
			break;
		case 4: gluLookAt(-8+cam_col*2, -1, -12+cam_row*2, (p1.x-4)*2, p1.y-1, p1.z*2-12, 0,1,0);
			break;
	}
	coin_angle=(coin_angle+10)%361;
	if(board_angle_z>=board_angle_lim)
		cam_inc=-0.005;
	if(board_angle_z<=-board_angle_lim)
		cam_inc=0.005;
	if(!p1.falling)
	{
		board_angle_z+=cam_inc;
	}
	if(p1.falling)
	{
		tim+=0.3;
		if((int)p1.y== -6)
			end_game();
		p1.y=p1.y-0.02*tim;
	}
	if(p1.jump!=1 && p1.trampulin!=1)
	{
		if(board_angle_z<0)
			p1.x+=PHY;
		else
			p1.x-=PHY;
	}
	if(p1.trampulin && trampulinmode)
	{
		t1+=0.3;
		if(p1.y<jump_height && p1.trampulinflag==1)
		{
			//	t1+=1;
			//	printf("%d ",t1);
			//p1.y+=0.1;
				p1.y+=u1*t1;
				u1-=g1*t1;
		}
		else if( fabs(p1.y-jump_height) < 0.2 && p1.trampulinflag==1)
		{
			t1=0.0;
			p1.trampulinflag=0;
		}
		else if(p1.y>0.0)
		{
			//	printf("%f ", p1.y);
			//	p1.y-=0.1;
			p1.y-=0.05*t1;
		}
		else
		{
			//	printf("into else\n");
			p1.y=0;
			jump_height+=0.5;
			p1.trampulinflag=1;
			t1=0;
			//p1.trampulin=0;
		}

	}
	if(p1.jump==1)
	{
		if(p1.y<1.6 && p1.jumpflag==1)
		{
			jump_step=0.2;
			p1.y+=jump_step;
		}
		else if((int)p1.y==1 && p1.jumpflag==1)
		{
			p1.jumpflag=0;
		}
		else if(p1.y>0.0 && p1.jumpflag == 0)
		{
			//printf("wrong part\n");
			jump_step=-0.2;
			p1.y+=jump_step;
		}
		else
		{
			p1.y=0;
			p1.trampulinflag=1;
			p1.trampulin=1;
			p1.jump=0;
		}
		if(camera==0 || camera ==1)
		{
			switch(p1.facing)
			{
				case 1: p1.x-=0.09;break;
				case 2: p1.z-=0.09;break;
				case 3: p1.x+=0.09;break;
				case 4: p1.z+=0.09;break;
			}
		}
		else if(camera == 2)
		{
			switch(p1.facing)
			{
				case 1: p1.x+=0.09; break;
				case 2: p1.z-=0.09; break;
				case 3: p1.x-=0.09; break;
				case 4: p1.z+=0.09; break;
			}
		}
	}
	if(p1.mock == 1)
	{
		p1.left_mock*=-1;
		p1.right_mock*=-1;
	}
	if(p1.happy == 1)
	{
		p1.left_mock*=-1;
		p1.right_mock*=-1;
	}
	glutTimerFunc(10, update, 0);
}

void drawBox(float len) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex2f(-w / 2, -h / 2);
	glVertex2f(-w / 2, h / 2);
	glVertex2f(w / 2, h / 2);
	glVertex2f(w / 2, -h / 2);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
// Initializing some openGL 3D rendering options
void initRendering() {
	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL); 
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);   // Setting a background color
	for(int i=0; i<TREE/2; i++)
	{
		tree_x[i]=rand()%13-25;
		tree_z[i] = rand()%30-17;
	}
	for(int i=TREE/2; i<TREE; i++)
	{
		tree_x[i] = rand()%5+13;
		tree_z[i] = rand()%30-17;
	}

	Image* image6 = loadBMP("logo.bmp");
	logoTextureId = loadTexture(image6);
	delete image6;

	Image* image = loadBMP("grasssand.bmp");
	grassTextureId = loadTexture(image);
	delete image;

	Image* image1 = loadBMP("image.bmp");
	waterTextureId = loadTexture(image1);

	Image* image3 = loadBMP("skull.bmp");
	tryTextureId = loadTexture(image3);
	delete image1;
	delete image3;

	Image* image5 = loadBMP("tree.bmp");
	treeTextureId = loadTexture(image5);
	delete image5;

	/*Image* image6 = loadBMP("bark.bmp");
	  branchTextureId = loadTexture(image6);
	  delete image6;*/

	Image* image4 = loadBMP("background.bmp");
	lavaTextureId = loadTexture(image4);
	delete image4;

	glShadeModel (GL_SMOOTH);
	//	tree1.drawTree();

}

// Function called when the window is resized
void handleResize(int w, int h) {

	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0,(double)w/(double)h,1.0,200);
}

void handleKeypress1(unsigned char key, int x, int y) {


	if (key == 27) {
		//printf("%f ", p1.y);
		printf("YOUR SCORE IS %d\n", p1.score);
	//	system("kill -s 9");
		exit(0);     // escape key is pressed
	}
	if(key == 'w')
	{
		if(camera == 3)
			hel_eye_z-=CAMERA;
	}
	if(key == 'a')
	{
		if(camera == 3)
			hel_eye_x-=CAMERA;
	}
	if(key == 's')
	{
		if(camera == 3)
			hel_eye_z+=CAMERA;
	}
	if(key == 'd')
	{
		if(camera == 3)
			hel_eye_x+=CAMERA;
	}
	if(key == 'q')
	{
		if(camera == 3)
			hel_eye_y-=CAMERA;
	}
	if(key == 'e')
	{
		if(camera == 3)
			hel_eye_y+=CAMERA;
	}
	if(key == 'j')
	{
		p1.jump=1;
		p1.jumpflag=1;
	}
	if(key == 't')
	{
		int x = rand()%8, z=rand()%8;
		p1.x = x, p1.z= z;
	}
	if(key == 'n')
	{
		day=day^1;
		if(day)
			i1=i2=i3=0.4;
		else
			i1=i2=i3=0.9;
	}
	if(key == 'm')
	{
		p1.mock=p1.mock^1;
	}
	if(key == 'c')
	{
		camera=(camera+1)%5;
	}
	if(key == 'g')
	{
		if(p1.score>4)
		{
			p1.score-=4;
			H.x+=2;
			P.x-=4;
		}
	}
	if(key == 'p')
	{
		if(cam_col == 7)
		{
			cam_col=0;
			if(cam_row==7)
				cam_row=0;
			else cam_row++;
		}
		else
			cam_col++;
	}
	if(key == 'b')
		trampulinmode^=1;
	if(key == 'l')
		spot^=1;
}

void handleKeypress2(int key, int x, int y) {

	p1.left_leg*=-1;
	p1.right_leg*=-1;
	p1.right_shoulder*=-1;
	p1.left_shoulder*=-1;
	if(p1.jump!=1 && p1.falling!=1)
	{
		if(p1.trampulin)
		{
			jump_height=0.5;
			p1.trampulinflag=0;
			p1.trampulin=0;
			p1.y=0;
		}
		if (key == GLUT_KEY_LEFT)
		{
			if(camera == 2 || camera == 1)
			{
				p1.facing=p1.facing+1;
				if(p1.facing==5)
					p1.facing=1;
			}
			else
			{
				p1.x-=STEP;
				p1.facing=1;
			}
		}
		if (key == GLUT_KEY_RIGHT)
		{
			if(camera == 2 || camera == 1)
			{
				p1.facing--;
				if(p1.facing==0)
					p1.facing=4;
			}
			else
			{
				p1.x+=STEP;
				p1.facing=3;
			}

		}
		if (key == GLUT_KEY_UP)
		{
			if(camera==2 || camera == 1)
			{
				switch(p1.facing)
				{
					case 1: p1.x+=STEP; break;
					case 2: p1.z-=STEP; break;
					case 3: p1.x-=STEP; break;
					case 4: p1.z+=STEP; break;
				}
			}
			else
			{
				p1.z-=STEP;
				p1.facing=2;
			}

		}
		if (key == GLUT_KEY_DOWN)
		{
			if(camera==2 || camera == 1)
			{
				p1.facing+=2;
				if(p1.facing==5)
					p1.facing=1;
				if(p1.facing==6)
					p1.facing=2;
			}    
			else
			{
				p1.z+=STEP;
				p1.facing=4;
			}
		}
	}
}

void handleMouseclick(int button, int state, int x, int y) {

	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
			theta += 15;
		else if (button == GLUT_RIGHT_BUTTON)
			theta -= 15;
	}
}
void end_game()
{
	if(win)
	{
		printf("\n\n/******* YOU WON ********/\n\n YOUR SCORE IS %d\n\n", p1.score);
		level++;
		flash=1;
		p1.x=0; p1.z=0;
		win=0;
		flag1.flag_angle=0;
		if(level>3)
			exit(0);
	}
	else
	{
		printf("\n\n/******* YOU LOST ********/\n\n YOUR SCORE IS %d\n\n", p1.score);
		exit(0);
	}
}
