#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "visuals.h"
#include "renders.h"
#include "keyboard.h"


void Render()
{      
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    DrawSun();  
    DrawStars();
    DrawSun(); 
    DrawEarth();
    DrawMoon(); 

    glutSwapBuffers();
    
    if(!pause)
        glutPostRedisplay();    
}


void Idle()
{
    if(!pause)
        Render();
}


void Resize(int w, int h)
{ 
    if(h == 0)
        h = 1;
  
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    
    gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


void Setup()
{
    Initialize();

    glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  
    GLfloat light_position[] = { 0.0, 30.0, 50.0, 0.0 };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position);

	GLfloat ambientLight[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat diffuseLight[] = {0.8, 0.8, 0.8, 1.0};
   
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glClearColor(0.0, 0.0, 0.0, 1.0);
}
