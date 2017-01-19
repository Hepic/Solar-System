#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "keyboard.h"

bool pause = false;


void processNormalKeys(unsigned char key, int x, int y)
{
    if(key == 27)
        exit(0);
    
    else if(key == 80  ||  key == 112)
        pause ^= true;
}


void processSpecialKeys(int key, int x, int y)
{
    if(pause)
        return;

    switch(key)
    {
        case GLUT_KEY_LEFT:
            glRotatef(1, 0, 1, 0);
        break;

        case GLUT_KEY_RIGHT:
            glRotatef(-1, 0, 1, 0);
        break;
  
        case GLUT_KEY_UP:
            glRotatef(1, 1, 0, 0);
        break;
        
        case GLUT_KEY_DOWN:
            glRotatef(-1, 1, 0, 0);
        break;
    }
}
