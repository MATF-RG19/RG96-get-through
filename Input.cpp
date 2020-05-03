#include <math.h>
#include <GL/glut.h>
#include "Input.h"
#include <iostream>

GLUquadricObj *quadratic;

void Input::pocetna_pozicija(double x, double y, double z)
{
	pos_x = x;
	pos_y = y;
	pos_z =z;

	kamera_osvezi();
}

void Input::kamera_osvezi()
{
	//glTranslatef(pos_x +2+vecx, 1, pos_z+vecz);
	//glutSolidCube(1);

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
	quadratic = gluNewQuadric();

	pitch = 0;
	yaw = 1.6f;
	pos_x = -1;
	pos_z = -35;
	pos_y = 1;
	vecy = vecz = 1;
}


void Input::Hodaj(double promena)
{
    double lx = cos(yaw)*cos(pitch);
    double lz = sin(yaw)*cos(pitch);
	pos_x = pos_x + promena*lx;
	pos_z = pos_z + promena*lz;

	KolizijaZidovi();
	kamera_osvezi();
}

void Input::LevoDesno(double promena)
{
	pos_x = pos_x + promena*ldx;
	pos_z = pos_z + promena*ldz;

	KolizijaZidovi();
	kamera_osvezi();
}

void Input::yawOkretanje(double angle)
{
	yaw += angle;

	kamera_osvezi();
}

void Input::KolizijaZidovi(){
	wallerr =0.5f;
	if(pos_z < (-20.f +wallerr) && pos_x < 0 && pos_x > -2){
		if(pos_z < -39.5f){
			pos_z = -39.5f;
		}

		if(pos_x > (0.f-wallerr)){
			pos_x = (0.f-wallerr);
		}
		if(pos_x < (-2.f+wallerr)){
			pos_x = (-2.f+wallerr);
		}
	}
	else if(pos_z < (-20.f +wallerr)){
		pos_z = (-20.f +wallerr);
	}

	if(pos_z > (20.f - wallerr) && pos_x < (-2.f+wallerr) && pos_x > (0.f - wallerr)){
		exit(EXIT_SUCCESS);
		std::cout << "hello";
	}

	if(pos_x > 20.f-wallerr){
		pos_x = 20.f-wallerr;
	}
	else if(pos_x < -20.f+wallerr){
		pos_x = -20.f+wallerr;
	}
}