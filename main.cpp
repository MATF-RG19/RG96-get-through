#include <GL/glut.h>
#include<cmath>
#include <iostream>

#include "Image.h"
#include "Input.h"
#include "LevelBuilder.h"

using namespace std;

const double brzinaKretanja = 0.5;

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



Input input;
LevelBuilder lvl; //= new LevelBuilder();

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
        	buttons_list[4] = false;
        	break;
        case 'l':
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
    if(buttons_list[4]){
    	input.yawOkretanje(-0.1);
    }
    if(buttons_list[5]){
    	input.yawOkretanje(0.1);
    }

    glutTimerFunc(33, on_timer, 0);
    glutPostRedisplay();
}
