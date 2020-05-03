#include "LevelBuilder.h"
#include <GL/glut.h>
#include <cstring>
#include <string>
#include "Image.h"



static GLuint name[3];   
float width_wall = 0.1f;
float texture_repeat_wall = 5;

LevelBuilder::LevelBuilder(){

	//----------------------------------- TEKSTURA ZA ZID --------------------------------------
	std::string zid("wall.bmp");
	char* cstr = new char [zid.length() + 1];
	std::strcpy(cstr, zid.c_str());

	Image * image;
	glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    image = image_init(0, 0);

    image_read(image, cstr);

    glGenTextures(2, name);

    glBindTexture(GL_TEXTURE_2D, name[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    //-----------------------------TEKSTURA PODLOGE--------------------------------------------
    std::string pod("earth.bmp");
    char* cstr1 = new char[pod.length()+1];
    std::strcpy(cstr1, pod.c_str());

    image_read(image, cstr1);

    glBindTexture(GL_TEXTURE_2D, name[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);




    /////////////////////// 	***	  DONE 	***    //////////////////////////////////////
    glBindTexture(GL_TEXTURE_2D, 0);

    image_done(image);

}
   

void LevelBuilder::napraviNivo(){
    buildFloor(40.0);
    
    for(int i=20; i>=-19; i-=2){
    	if(i!=0){
    		buildWall(i, 20, 180, true);
    	}
    }
    for(int i=20; i>=-19; i-=2){
    	if(i!=0){
    		buildWall(i, -20, 180, true);
    	}
    }
    for(int i=20; i>=-19; i-=2){
    	buildWall(-20, i, 90, true);
    }
    for(int i=20; i>=-19; i-=2){
    	buildWall(20, i, 90, true);
    }
   
   	for(int i=0; i>-20; i-=2){
    	buildWall(0, -19.9f+i, 90, true);
    }
    for(int i=0; i>-20; i-=2){
    	buildWall(-2, -19.9f+i, 90, true);
    }

    buildWall(0, -40, 180, true);

    buildBure(0, 0);
}


void LevelBuilder::buildWall(double posX, double posZ, double rotD, bool rot){

	glPushMatrix();

	

    glBindTexture(GL_TEXTURE_2D, name[0]);
    glTranslatef(posX, 0, posZ);
	if(rot){
	    glRotatef(rotD, 0, 1, 0);
	}	
    
  	
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 0);
        glVertex3f(0, 0, width_wall);

        glTexCoord2f(texture_repeat_wall, 0);
        glVertex3f(2, 0, width_wall);

        glTexCoord2f(texture_repeat_wall, texture_repeat_wall);
        glVertex3f(2, 2, width_wall);

        glTexCoord2f(0, texture_repeat_wall);
        glVertex3f(0, 2, width_wall);


        glTexCoord2f(0, 0);
        glVertex3f(0, 0, -width_wall);

        glTexCoord2f(texture_repeat_wall, 0);
        glVertex3f(2, 0, -width_wall);

        glTexCoord2f(texture_repeat_wall, texture_repeat_wall);
        glVertex3f(2, 2, -width_wall);

        glTexCoord2f(0, texture_repeat_wall);
        glVertex3f(0, 2, -width_wall);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);



    glBegin(GL_QUADS);
		glColor3f(0.45f, 0.45f, 0.45f);    	

    	glVertex3f(2, 0, -width_wall);
        glVertex3f(2, 0, width_wall); 
        glVertex3f(2, 2, width_wall);         
        glVertex3f(2, 2, -width_wall);
    glEnd();

    glBegin(GL_QUADS);
		glColor3f(0.45f, 0.45f, 0.45f);    	

    	glVertex3f(0, 0, -width_wall);
        glVertex3f(0, 0, width_wall); 
        glVertex3f(0, 2, width_wall);         
        glVertex3f(0, 2, -width_wall);
    glEnd();

    glPopMatrix();



}

 void LevelBuilder::buildBure(double posX, double posZ){
 	glPushMatrix();

 		glBegin(GL_QUADS);
 			glColor3f(0.45f, 0.45f, 0.45f);
 			glVertex3f(1, 0, -0.5f);
 			glVertex3f(1, 0, 0.5f);
 			glVertex3f(1, 0.8f, 0.5f);
 			glVertex3f(1, 0.8f, -0.5f);
 		glEnd();

 		glBegin(GL_QUADS);
 			glColor3f(0.45f, 0.45f, 0.45f);
 			glVertex3f(1.7f, 0, -0.5f);
 			glVertex3f(1.7f, 0, 0.5f);
 			glVertex3f(1.7f, 0.8f, 0.5f);
 			glVertex3f(1.7f, 0.8f, -0.5f);
 		glEnd();

 		glBegin(GL_QUADS);
 			glColor3f(0.45f, 0.45f, 0.45f);
 			glVertex3f(1, 0, 0.5f);
 			glVertex3f(1.7f, 0, 0.5f);
 			glVertex3f(1.7f, 0.8f, 0.5f);
 			glVertex3f(1, 0.8f, 0.5f);
 		glEnd();

 		glBegin(GL_QUADS);
 			glColor3f(0.45f, 0.45f, 0.45f);
 			glVertex3f(1, 0, -0.5f);
 			glVertex3f(1.7f, 0, -0.5f);
 			glVertex3f(1.7f, 0.8f, -0.5f);
 			glVertex3f(1, 0.8f, -0.5f);
 		glEnd();


 	glPopMatrix();


 }

void LevelBuilder::buildCeiling(double posX, double posZ){};

void LevelBuilder::buildFloor(double posX){
	glBindTexture(GL_TEXTURE_2D, name[1]);

    glBegin(GL_QUADS);
        glColor3f(posX, 0, 0);

        glTexCoord2f(0, 0);
        glVertex3f(posX, 0, -posX);

        glTexCoord2f(50, 0);
        glVertex3f(posX, 0, posX);

        glTexCoord2f(50, 50);
        glVertex3f(-posX, 0, posX);

        glTexCoord2f(0, 50);
        glVertex3f(-posX, 0, -posX);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
};



