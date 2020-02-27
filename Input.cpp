#include <math.h>
#include <GL/glut.h>
#include "Input.h"

void Input::pocetna_pozicija(float x, float y, float z)
{
	pos_x = x;
	pos_y = y;
	pos_z =z;

	kamera_osvezi();
}

void Input::kamera_osvezi()
{
	
	vecx = cos(yaw) * cos(pitch);
	vecy = sin(pitch);
	vecz = sin(yaw) * cos(pitch);

	ldx = cos(yaw - M_PI_2);
	ldz = sin(yaw - M_PI_2);

	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(pos_x, pos_y, pos_z, pos_x + vecx, pos_y + vecy, pos_z + vecz, 0.0,1.0,0.0);

}



void Input::naNule()
{
	pitch = 0;
	yaw = 0;
	pos_x = pos_z = 0;
	pos_y = 1;
	vecy = vecz = 1;
}


void Input::Hodaj(float promena)
{
    float lx = cos(yaw)*cos(pitch);
    float lz = sin(yaw)*cos(pitch);
	pos_x = pos_x + promena*lx;
	pos_z = pos_z + promena*lz;

	kamera_osvezi();
}

void Input::LevoDesno(float promena)
{
	pos_x = pos_x + promena*ldx;
	pos_z = pos_z + promena*ldz;

	kamera_osvezi();
}

void Input::yawOkretanje(float angle)
{
	yaw += angle;

	kamera_osvezi();
}

void Input::pitchOkretanje(float angle)
{
	

	pitch += angle;

    if(pitch < -(89.0 * M_PI / 180.0)){
        pitch = -(89.0 * M_PI / 180.0);
	}

    if(pitch > (89.0 * M_PI / 180.0)){
        pitch = 89.0 * M_PI / 180.0;
	}

	kamera_osvezi();
}
