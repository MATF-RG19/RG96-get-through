#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>


static void initialize(void);

static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_mouse(int button, int state, int x, int y);
static void on_motion(int x, int y);

static int window_width, window_height;
static int mouse_x, mouse_y;

int x_pos = 0;
int y_pos = 0;
int z_pos = 0;

bool ide_napred = false;
static float matrix[16];

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Get Through");

    glutKeyboardFunc(on_keyboard);
    glutMouseFunc(on_mouse);
    glutPassiveMotionFunc(on_motion);
    //https://www.opengl.org/resources/libraries/glut/spec3/node51.html
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    initialize();

    glutMainLoop();
    
    return 0;
}

static void initialize(void){

    glClearColor(1, 1, 1, 0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    //Matrica rotacije
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);   
}

static void on_reshape(int width, int height){
    window_width = width;
    window_height = height;

    glViewport(0, 0, window_width, window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width/height,1, 1500);
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'w':
            z_pos += 1;
            break;
        case 's':
            z_pos -=1;
            break;
        case 'd':
            x_pos -=1;
            break;
        case 'a':
            x_pos +=1;
            break;
        case 27:
            exit(0);
            break;
    }

    glutPostRedisplay();
}

static void on_display(void){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); // reset modelview matrix
	glLoadIdentity();
    gluLookAt(x_pos, y_pos+1, z_pos, x_pos, y_pos+1, z_pos+1, 0, 1, 0);

    glMultMatrixf(matrix);

    glScalef(20, 20, 20);
    glBegin(GL_POLYGON);
        glColor3f(0, 0, 1);
        glVertex3f(-1, 0, -1);
        glVertex3f(-1, 0, 1);
        glVertex3f(1, 0, 1);
        glVertex3f(1, 0, -1);
        
    glEnd();

    

    glutSwapBuffers();
}

static void on_mouse(int button, int state, int x, int y){
    
    mouse_x = x;
    mouse_y = y;
}


static void on_motion(int x, int y){

    int delta_x, delta_y;
  
    delta_x = x - mouse_x;
    delta_y = y - mouse_y;
    
    mouse_x = x;
    mouse_y = y;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    //x_pos, y_pos+1, z_pos+1
        glLoadIdentity();
        glTranslatef(x_pos, y_pos+1, z_pos+1);
        glRotatef(540 * (float) delta_x / window_width, 0, 1, 0);
        //glRotatef(180 * (float) delta_y / window_height, 1, 0, 0);
        glTranslatef(-x_pos, -y_pos-1, -z_pos-1);

        glMultMatrixf(matrix);

        glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
    
    glPopMatrix();

 
    glutPostRedisplay();
}