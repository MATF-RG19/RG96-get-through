#ifndef __levelbuilder__
#define __levelbuilder__

class LevelBuilder{
public:
    LevelBuilder();
    
    void napraviNivo();

    void buildWall(double posX, double posZ, double rotD, bool rot);
    void buildCeiling(double posX, double posZ);
    void buildFloor(double posX);

};

#endif