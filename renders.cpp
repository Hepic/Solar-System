#include <stdio.h>
#include <vector>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "renders.h"

#define NUM_STARS 20
#define NUM_STARS_TEAMS 4

using namespace std;


struct Star
{
    float x, y, z;
    int team;

    Star() {}
    Star(float _x, float _y, float _z, int t) : x(_x), y(_y), z(_z), team(t) {}
};


struct Point
{
    float x, y, z;
};


struct Triangle
{
    pair<int, int> point[3];
};


struct Model
{
    vector<Point> points, normals;
    vector<Triangle> faces;
};


float earth_rotation[2], moon_rotation[2];
float radius_star[NUM_STARS_TEAMS], opacity_star[NUM_STARS_TEAMS];
float earth_speed[2], moon_speed[2];
float radius, opacity;
bool shine_star[NUM_STARS_TEAMS];
bool shine;
Star star_position[NUM_STARS+10];
Model model;


void ReadFile()
{
    ifstream obj_file("planet.obj");

    if(!obj_file.is_open()  ||  obj_file.fail())
        exit(1);
    
    int vert, norm;
    char slash;
    string type;
    Point val;
    Triangle trg;

    while(!obj_file.eof())
    {
        obj_file >> type;
        
        if(type == "v")
        {
            obj_file >> val.x >> val.y >> val.z;
            model.points.push_back(val);
        }

        else if(type == "vn")
        {
            obj_file >> val.x >> val.y >> val.z;
            model.normals.push_back(val);
        }

        else if(type == "f")
        {
            for(int i=0; i<3; ++i)
            {
                obj_file >> vert >> slash >> slash >> norm;    
                trg.point[i] = make_pair(vert, norm);
            }
            
            model.faces.push_back(trg);
        }
    }

    obj_file.close();
}


void DrawEarth()
{
    int index;

    glPushMatrix(); 
    glColor3f(0.1, 0.1, 0.8);

    earth_rotation[0] += earth_speed[0];
    glRotatef(earth_rotation[0], 0, 1, 0);
    glTranslatef(2, 0, 0);

    glScalef(0.4, 0.4, 0.4);
   
    earth_rotation[1] += earth_speed[1];
    glRotatef(earth_rotation[1], 1, 1, 1);
    
    glBegin(GL_TRIANGLES);

    for(int i=0; i<(int)model.faces.size(); i++)
    {
        for(int j=0; j<3; ++j)
        {
            index = model.faces[i].point[j].second; 
            glNormal3f(model.normals[index-1].x, model.normals[index-1].y, model.normals[index-1].z);
            
            index = model.faces[i].point[j].first;
            glVertex3f(model.points[index-1].x/800, model.points[index-1].y/800, model.points[index-1].z/800);
        }
    }

    glEnd();
    glPopMatrix();
}


void DrawMoon()
{
    int index;

    glPushMatrix();
    glColor3f(0.9, 0.9, 0.9);

    glRotatef(earth_rotation[0], 0, 1, 0);
    glTranslatef(2, 0, 0);
    
    glScalef(0.4, 0.4, 0.4);
  
    moon_rotation[0] += moon_speed[0];
    glRotatef(moon_rotation[0], 1, 0, 1);
    glTranslatef(0, 1, 0);

    glScalef(0.4, 0.4, 0.4);
   
    moon_rotation[1] += moon_speed[1];
    glRotatef(moon_rotation[1], 1, 1, 1);
    
    glBegin(GL_TRIANGLES);
    
    for(int i=0; i<(int)model.faces.size(); i++)
    {
        for(int j=0; j<3; ++j)
        {
            index = model.faces[i].point[j].second; 
            glNormal3f(model.normals[index-1].x, model.normals[index-1].y, model.normals[index-1].z);
            
            index = model.faces[i].point[j].first;
            glVertex3f(model.points[index-1].x/800, model.points[index-1].y/800, model.points[index-1].z/800);
        }
    }
    
    glEnd();
    glPopMatrix();
}


void DrawSun()
{
    glColor3f(1, 0.8, 0.1);
    glutSolidSphere(0.5, 50, 50);
    
    glColor4f(1, 0.8, 0.1, opacity);
    glutSolidSphere(radius, 15, 15);
    
    if(opacity >= 0.9)
        shine = false;

    else if(opacity <= 0.0)
        shine = true;
    
    if(shine)
    {
        if(radius < 0.7)
            radius += 0.002;
        
        opacity += 0.01;
    }
    
    else
    {
        if(radius > 0.5  &&  opacity < 0.3)
            radius -= 0.002;
        
        opacity -= 0.01;
    }
}


void DrawStar(float dx, float dy, float dz, int team)
{
    glPushMatrix();
    glTranslatef(dx, dy, dz);

    glColor3f(1, 1, 1);
    glutSolidSphere(0.02, 5, 5);
    
    glColor4f(1, 1, 1, opacity_star[team]);
    glutSolidSphere(radius_star[team], 5, 5);
    
    glPopMatrix();
}


void DrawStars()
{
    float dx, dy, dz;
    int team;

    for(int i=1; i<=NUM_STARS; ++i)
    {
        dx = star_position[i].x;
        dy = star_position[i].y;
        dz = star_position[i].z;
        team = star_position[i].team;

        DrawStar(dx, dy, dz, team);
    }
    
    for(int i=0; i<NUM_STARS_TEAMS; ++i)
    {
        if(opacity_star[i] >= 0.9)
            shine_star[i] = false;

        else if(opacity_star[i] <= 0.0)
            shine_star[i] = true;
        
        if(shine_star[i])
        {
            if(radius_star[i] < 0.04)
                radius_star[i] += 0.0001;
            
            opacity_star[i] += 0.01;
        }
        
        else
        {
            if(radius_star[i] > 0.02  &&  opacity_star[i] < 0.3)
                radius_star[i] -= 0.0001;
            
            opacity_star[i] -= 0.01;
        }
    }
}


void Initialize()
{
    shine = true;
    radius = 0.5, opacity = 0;
    
    float dx, dy, dz;
    int team;

    for(int i=1; i<=NUM_STARS; ++i)
    {
        dx = 8 * (float)rand() / RAND_MAX - 4;
        dy = 6 * (float)rand() / RAND_MAX - 3;
        dz = 8 * (float)rand() / RAND_MAX - 4;
        team = rand() % NUM_STARS_TEAMS;

        star_position[i] = Star(dx, dy, dz, team);
    }

    for(int i=0; i<NUM_STARS_TEAMS; ++i)
    {
        if(i%2)
        {
            shine_star[i] = true;
            opacity_star[i] = 0.2 * i;
            radius_star[i] = 0.01 * i;
        }

        else
        {
            shine_star[i] = false;
            opacity_star[i] = 0.3 * i;
            radius_star[i] = 0.01 * i;
        }
    }
    
    ReadFile();
    
    for(int i=0; i<2; ++i) 
        earth_rotation[i] = moon_rotation[i] = 0;

    earth_speed[0] = 0.5; // speed for years
    earth_speed[1] = 1; // speed for days
    moon_speed[0] = moon_speed[1] = 10;
}
