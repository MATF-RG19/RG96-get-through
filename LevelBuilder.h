#ifndef __levelbuilder__
#define __levelbuilder__

#include <GL/glut.h>
#include <vector>


class LevelBuilder{
public:

    LevelBuilder(); //Konstruktor

    void napraviNivo(); //Ova funkcija poziva ostale funkcije za konstruisanje nivoa
    void buildWall(double posX, double posZ, double rotD, bool rot); 
    void buildFloor(double posX);
    void buildBure(double posX, double posZ);
	void crtajZid();
};

#endif