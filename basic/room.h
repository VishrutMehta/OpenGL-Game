#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <cstdio>
#include "imageloader.h"
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
GLuint grassTextureId; //The id of the texture

class room{
	public : 
		void drawGrass(){
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, grassTextureId);

			//Bottom
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glColor3f(1.0f, 1.0f, 1.0f);

			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1.50f,0.0f,0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(1.5f,0.3f,0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0.0f,0.3f,0.0f);
			glEnd();


			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0.0f,0.0f,-1.5f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.0f,0.3f,-1.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.0f,0.3f,0.0f);
			glEnd();


			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(1.5f,0.0f,0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(1.5f,0.0f,-1.5f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(1.5f,0.3f,-1.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1.5f,0.3f,0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f,0.0f,-1.5f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(1.50f,0.0f,-1.5f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(1.5f,0.3f,-1.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.0f,0.3f,-1.5f);
			glEnd();


			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(1.50f,0.0f,0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(1.5f,0.0f,-1.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.0f,0.0f,-1.5f);
			glEnd();


			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f,0.3f,0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(1.50f,0.3f,0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(1.5f,0.3f,-1.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.0f,0.3f,-1.5f);
			glEnd();

		}
		void draw(){
//			glTranslatef(-1.0, 0.0, -1.5);
			for(float j=0.0;j>(-8*1.5);j-=1.5)
			{
				k++;
				for(float i=0.0;i<(4*3.0);i+=3.0){
					if(k%2==0){
						glPushMatrix();
						glTranslatef(i,0.0,j);
						drawGrass();
						glPopMatrix();

					}
					else
					{
						glPushMatrix();
						glTranslatef(i+1.5,0.0,j);
						drawGrass();
						glPopMatrix();

					}
				}
			}
			for(float j=0.0;j>(-8*1.5);j-=1.5){
				k++;
				for(float i=0.0;i<(4*3.0);i+=3.0)
				{
					if(k%2!=0){
						glPushMatrix();
						glTranslatef(i,0.0,j);
						drawGrass();
						glPopMatrix();

					}
					else{
						glPushMatrix();
						glTranslatef(i+1.5,0.0,j);
						drawGrass();
						glPopMatrix();

					}
				}
			}
		}
};
