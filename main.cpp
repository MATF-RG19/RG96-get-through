#include <GL/glut.h>
#include<cmath>
#include <iostream>


#include "Input.h"
#include "LevelBuilder.h"

using namespace std;

const double rotacionaBrzina = M_PI/180*0.2;
const double brzinaKretanja = 0.07;

static void on_keyboard(unsigned char key, int x, int y);
static void on_keyboard_up(unsigned char key, int x, int y);
static void on_display();
static void on_reshape(int width, int height);
static void on_mouse_motion(int x, int y);
static void on_mouse(int button, int state, int x, int y);
static void on_timer(int value);

static void on_idle();

// w s a d lmouse rmouse 
// 0 1 2 3 4      5
bool buttons_list[6];

int sirina = 0;
int visina = 0;



Input input;
LevelBuilder lvl;

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Get Through");

    glutKeyboardFunc(on_keyboard);
    glutKeyboardUpFunc(on_keyboard_up);
    glutMouseFunc(on_mouse);
    glutMotionFunc(on_mouse_motion);
    glutPassiveMotionFunc(on_mouse_motion);
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutIdleFunc(on_idle);

    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_NORMALIZE);
    //glEnable(GL_TEXTURE_2D);

    glutIgnoreKeyRepeat(1);

    glutTimerFunc(1, on_timer, 0);
    glutMainLoop();

    return 0;
}

static void on_idle(){
    on_display();
}

static void on_display(){

    glClearColor(1.0,1.0,1.0,0); 
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
    gluPerspective(60, width/height, 1, 1000);
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

    }
}

static void on_timer(int value){
    if(buttons_list[0])
        input.Hodaj(brzinaKretanja);
    else if(buttons_list[1])
        input.Hodaj(-brzinaKretanja);
    else if(buttons_list[2])
        input.LevoDesno(brzinaKretanja);
    else if(buttons_list[3])
        input.LevoDesno(-brzinaKretanja);

    glutTimerFunc(1, on_timer, 0);
}

static void on_mouse(int button, int state, int x, int y){
    if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
        buttons_list[4] = true;
    else if(state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
        buttons_list[5] = true;

    else if(state == GLUT_UP && button == GLUT_LEFT_BUTTON)
        buttons_list[4] = false;
    else if(state == GLUT_UP && button == GLUT_RIGHT_BUTTON)
        buttons_list[5] = false;
    
}

static void on_mouse_motion(int x, int y){
    static bool warp_hak = false;
    if(warp_hak){
        warp_hak = false;
        return ;
    }

    int dx = x - sirina/2;
    int dy = y - visina/2;
    if(dx)
        input.yawOkretanje(rotacionaBrzina*dx);
    if(dy)
        input.pitchOkretanje(-rotacionaBrzina*dy); //kulturni ljudi ne igraju igrice sa invertovanim misem

    glutWarpPointer(sirina/2, visina/2); //nazad na centar
    warp_hak = true;   
}