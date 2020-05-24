#include "LevelBuilder.h"
#include <GL/glut.h>
#include <cstring>
#include <string>
#include "Image.h"


//pomocne promenljive
static GLuint name[3];   
float width_wall = 0.1f;
float texture_repeat_wall = 5;

/*
    Ucitavamo slike za teksture putem klase Image iz odgovarajuceg direktorijuma,
    zatim podesavamo OpenGl parametre za prikazivanje tekstura i povezujemo ih sa 
    niskom koja ce da oznacava koju teksturu zelimo da primenimo. 
*/
LevelBuilder::LevelBuilder(){

	//----------------------------------- TEKSTURA ZA ZID --------------------------------------
	std::string zid("res/wall.bmp");
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
    std::string pod("res/earth.bmp");
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


    //-----------------------------TEKSTURA BURETA--------------------------------------------
    std::string bur("res/bure.bmp");
    char* cstr2 = new char[bur.length()+1];
    std::strcpy(cstr2, bur.c_str());

    image_read(image, cstr2);

    glBindTexture(GL_TEXTURE_2D, name[2]);
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
   
/*
    Odavde se zovu funkcije za izgradnju pojedinacnih objekata, zidova, burica i podloge.   
*/
void LevelBuilder::napraviNivo(){
	glEnable(GL_TEXTURE_2D);

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
   
   	//--------------------HODNIK--------------------
   	for(int i=0; i>-20; i-=2){
    	buildWall(0, -19.9f+i, 90, true);
    }
    for(int i=0; i>-20; i-=2){
    	buildWall(-2, -19.9f+i, 90, true);
    }

    buildWall(0, -40, 180, true);
    //--------------------HODNIK--------------------


    buildBure(0, 0); buildBure(10, 0); buildBure(0, 4); buildBure(12, 16); 
    buildBure(-2, -15); buildBure(-3, 7); buildBure(-14, -7); buildBure(19, 1); 
    buildBure(-19, -19); buildBure(15, 3); buildBure(16, 12); buildBure(1, 19);
    buildBure(2, 15); buildBure(7, -17); buildBure(-14, 3); buildBure(-15, -15); 
    buildBure(-5, 19); buildBure(-7, 17); buildBure(-9, 15); buildBure(-4, -3); 
    //ima ih 20


    glDisable(GL_TEXTURE_2D);
   
}


void LevelBuilder::crtajZid(){
	buildWall(0, 20, 180, true);
}

/*  
    Gradimo pravougaonik koji predstavlja zid i nakon toga dodajemo teksture na vidljive strane
*/
void LevelBuilder::buildWall(double posX, double posZ, double rotD, bool rot){

	glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, name[0]);
    glTranslatef(posX, 0, posZ);
	if(rot){
	    glRotatef(rotD, 0, 1, 0);
	}	
    
    glEnable(GL_TEXTURE_2D);
  	
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

    glDisable(GL_TEXTURE_2D);

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
    
    glEnable(GL_TEXTURE_2D);

    glPopMatrix();



}

/*
    Crtamo cetiri pravougaonika i sklapamo ih u jedan objekat, potom za svakom dodajemo odabranu teksturu
    bureta u odgovarajucoj tacki, nakon iscrtavanja iskljucujemo crtanje tekstura  
*/
void LevelBuilder::buildBure(double posX, double posZ){
 	
 	glPushMatrix();
 		glBindTexture(GL_TEXTURE_2D, name[2]);

 		glBegin(GL_QUADS);

 			glTexCoord2f(0, 0);
 			glVertex3f(posX, 0, posZ);
 			glTexCoord2f(1, 0);
 			glVertex3f(posX, 0, posZ+1);
 			glTexCoord2f(1, 1);
 			glVertex3f(posX, 0.8f, posZ+1);
 			glTexCoord2f(0, 1);
 			glVertex3f(posX, 0.8f, posZ);
 		glEnd();

 		glBegin(GL_QUADS);

 			glTexCoord2f(0, 0);
 			glVertex3f(posX+1, 0, posZ);
 			glTexCoord2f(1, 0);
 			glVertex3f(posX+1, 0, posZ+1);
 			glTexCoord2f(1, 1);
 			glVertex3f(posX+1, 0.8f, posZ+1);
 			glTexCoord2f(0, 1);
 			glVertex3f(posX+1, 0.8f, posZ);
 		glEnd();

 		glBegin(GL_QUADS);

 			glTexCoord2f(0, 0);
 			glVertex3f(posX, 0, posZ+1);
 			glTexCoord2f(1, 0);
 			glVertex3f(posX+1, 0, posZ+1);
 			glTexCoord2f(1, 1);
 			glVertex3f(posX+1, 0.8f, posZ+1);
 			glTexCoord2f(0, 1);
 			glVertex3f(posX, 0.8f, posZ+1);
 		glEnd();

 		glBegin(GL_QUADS);

 			glTexCoord2f(0, 0);
 			glVertex3f(posX, 0, posZ);
 			glTexCoord2f(1, 0);
 			glVertex3f(posX+1, 0, posZ);
 			glTexCoord2f(1, 1);
 			glVertex3f(posX+1, 0.8f, posZ);
 			glTexCoord2f(0, 1);
 			glVertex3f(posX, 0.8f, posZ);
 		glEnd();

 		glBindTexture(GL_TEXTURE_2D, 0);

 	glPopMatrix();

 }


/*
    Crtamo pod razmera koje su predate parametrom, povezujemo ga sa teksturom zemlje,
    zatim odredjujemo tacke prikazivanja teksture i koliko puta se ponavljaju (50)
*/
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



