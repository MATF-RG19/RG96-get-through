#ifndef __levelbuilder__
#define __levelbuilder__

#include <GL/glut.h>
#include <vector>


class LevelBuilder{
public:
    LevelBuilder();

    void napraviNivo();
    void buildWall(double posX, double posZ, double rotD, bool rot);
    void buildCeiling(double posX, double posZ);
    void buildFloor(double posX);
    void buildBure(double posX, double posZ);
	void crtajZid();
};

#endif