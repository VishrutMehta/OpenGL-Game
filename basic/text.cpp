#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <time.h>
#include "SOIL.h"
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800,800);

	glutCreateWindow("My Adventure Game");
	glutFullScreen();
	GLuint tex_2d = SOIL_load_OGL_texture
		(
		 "download.jpg",
		 SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	/* check for an error during the load process */
	if( 0 == tex_2d )
	{
		printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
	}

	//	glutDisplayFunc(drawScene);
//	glutIdleFunc(drawScene);
	glutMainLoop();
	return 0;

}

