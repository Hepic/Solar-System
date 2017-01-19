#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "visuals.h"
#include "keyboard.h"


int main(int argc, char* argv[])
{ 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowSize(800, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Solar System");

    Setup(); 

    glutDisplayFunc(Render);
    glutReshapeFunc(Resize);
    glutIdleFunc(Idle);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    glutMainLoop();

    return 0;	
}  
