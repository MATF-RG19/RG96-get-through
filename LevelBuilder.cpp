#include "LevelBuilder.h"
#include <GL/glut.h>

LevelBuilder::LevelBuilder(){}
   

void LevelBuilder::napraviNivo(){
    buildFloor(20.0);
    buildWall(0, 0, 0, false);
    buildWall(3, 0, 0, false);
    buildWall(6, 0, 0, false);
    buildWall(9, 0, 0, false);
    buildWall(3, 1.5, 90, true);
}


void LevelBuilder::buildWall(double posX, double posZ, double rotD, bool rot){
    glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslatef(posX, 1.5, posZ);
        if(rot){
            glRotatef(rotD, 0, 1, 0);
        }
        glScalef(3, 3, 0.1);
        glutSolidCube(1);
    glPopMatrix();
}

void LevelBuilder::buildCeiling(double posX, double posZ){};

void LevelBuilder::buildFloor(double posX){
    glBegin(GL_POLYGON);
        glColor3f(posX, 0, 0);
        glVertex3f(posX, 0, -posX);
        glVertex3f(posX, 0, posX);
        glVertex3f(-posX, 0, posX);
        glVertex3f(-posX, 0, -posX);
    glEnd();
};



