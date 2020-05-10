#include <GL/glut.h>
#include<cmath>
#include <iostream>

#include "Image.h"
#include "Input.h"
#include "LevelBuilder.h"

using namespace std;

const double brzinaKretanja = 0.2;

static void on_keyboard(unsigned char key, int x, int y);
static void on_keyboard_up(unsigned char key, int x, int y);
static void on_display();
static void on_reshape(int width, int height);
static void on_timer(int value);

static void on_idle();

// w s a d j k 
// 0 1 2 3 4 5
bool buttons_list[6];

int sirina = 0;
int visina = 0;


//za loptu
static int isAnimate = 0; 
static float t = 0.0; 
static float h = 0.1; 
static float v = 0.5; 
static float g = 0.05;  
Input input;
LevelBuilder lvl; //= new LevelBuilder();

double xx = 0;
double yy = 0;
double zz = 0;

double dirX = 0;
double dirZ = 0;

double trX =0; double trY = 0; double trZ = 0;


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Get Through");

    glutKeyboardFunc(on_keyboard);
    glutKeyboardUpFunc(on_keyboard_up);
    
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutIdleFunc(on_idle);

    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);

    lvl = LevelBuilder();

    glutIgnoreKeyRepeat(1);

    glutTimerFunc(33, on_timer, 0);
    glutMainLoop();

    return 0;
}

static void on_idle(){
    on_display();
}

static void on_display(){

    glClearColor(0.85f, 0.94f, 0.98f,0); 
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	input.kamera_osvezi();
    lvl.napraviNivo();
   
	if(isAnimate){
	    glPushMatrix();
	     	glColor3f(0, 0, 1);
	    	// h*t, v*t - (g/2.0)*t*t 

	    	if(dirX > 0 && dirZ > 0){
	    		trX = h*t+xx+1;
	    		trY = v*t - (g/2.0)*t*t;
	    		trZ = zz;
		    }
		    else if(dirX < 0 && dirZ > 0){
		    	trX = xx;
		    	trY = v*t - (g/2.0)*t*t;
		    	trZ = h*t+zz+1;
		    }
		    else if(dirX < 0 && dirZ < 0){
		    	trX = -h*t+xx-1;
		    	trY = v*t - (g/2.0)*t*t;
		    	trZ = zz;
		    }
		    else{
		    	trX = xx;
		    	trY = v*t - (g/2.0)*t*t;
		    	trZ = -h*t+zz-1;
		    }
		    
		  	glTranslatef(trX, trY, trZ);		    
		   
		    glutSolidSphere(0.1, 10, 10);
		glPopMatrix();
	}
	
	if(!input.svaBurad()){
    	lvl.crtajZid();
    }

    glutSwapBuffers(); 
}

static void on_reshape(int width, int height){
    sirina = width; visina = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(60, width/height, 0.1f, 100);
    glMatrixMode(GL_MODELVIEW);
}

static void on_keyboard(unsigned char key, int x, int y){
    switch (key)
    {
        case 'w':
            buttons_list[0] = true;
            break;

        case 's':
            buttons_list[1] = true;
            break;
        
        case 'a':
            buttons_list[2] = true;
            break;

        case 'd':
            buttons_list[3] = true;
            break;
        case 'j':
        	buttons_list[4] = true;
        	break;
        case 'l':
        	buttons_list[5] = true;
        	break;
        case ' ':
        	xx = input.retX();
	        yy = input.retY();
	    	zz = input.retZ();
	    	dirX = input.retVx();
	    	dirZ = input.retVz();

        	if(isAnimate==0) {isAnimate =1;}
	        
	        if(t > 17){
	        	t = 0.0;
	        	input.upadUBure(trX, trY, trZ);
	        	glutPostRedisplay();
	        }
        	break;

        case 27:
            exit(EXIT_SUCCESS);
            break;
    }
}

static void on_keyboard_up(unsigned char key, int x, int y){
    switch (key)
    {
        case 'w':
            buttons_list[0] = false;
            break;

        case 's':
            buttons_list[1] = false;
            break;
        
        case 'a':
            buttons_list[2] = false;
            break;

        case 'd':
            buttons_list[3] = false;
            break;
        case 'j':
        	if(buttons_list[4] == true){
        		input.yawOkretanje(-1.5708); //radijan za 90
        	}
        	buttons_list[4] = false;
        	break;
        case 'l':
        	if(buttons_list[5] == true){
        		input.yawOkretanje(1.5708); //radijan 
        	}
        	buttons_list[5] = false;


    }
}

static void on_timer(int value){
    if(buttons_list[0]){
        input.Hodaj(brzinaKretanja);
    }
    if(buttons_list[1]){
        input.Hodaj(-brzinaKretanja);
    }
    if(buttons_list[2]){
        input.LevoDesno(brzinaKretanja);
    }
    if(buttons_list[3]){
        input.LevoDesno(-brzinaKretanja);
    }


    if(isAnimate){
    	t += 1.0;
    }

    glutTimerFunc(33, on_timer, 0);
    glutPostRedisplay();
}
