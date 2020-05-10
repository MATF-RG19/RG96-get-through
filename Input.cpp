#include <math.h>
#include <vector>
#include <GL/glut.h>
#include "Input.h"
#include <iostream>
#include <algorithm>


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
	izlaz = false;
	pitch = 0;
	yaw = 1.6f;
	pos_x = -1;
	pos_z = -35;
	pos_y = 1;
	vecy = vecz = 1;

	pozicije_burica = {{0, 0}, {10, 0}, {0, 4}, {12, 16},
        									{-2, -15}, {-3, 7}, {-14, -7}, {19, 1},
    										{-19, -19}, {15, 3}, {16, 12}, {1, 19},
    										{2, 15}, {7, -17}, {-14, 3}, {-15, -15},
    										{-5, 19}, {-7, 17}, {-9, 15}, {-4, -3}};


    lopticaUBuretu.resize(20, false);
    //std::fill(lopticaUBuretu.begin(), lopticaUBuretu.end(), false); 									
}


void Input::Hodaj(double promena)
{
    double lx = cos(yaw)*cos(pitch);
    double lz = sin(yaw)*cos(pitch);
	pos_x = pos_x + promena*lx;
	pos_z = pos_z + promena*lz;

	KolizijaZidovi();
	KolizijaBurad();
	kamera_osvezi();
}

void Input::LevoDesno(double promena)
{
	pos_x = pos_x + promena*ldx;
	pos_z = pos_z + promena*ldz;

	KolizijaZidovi();
	KolizijaBurad();
	kamera_osvezi();
}

void Input::yawOkretanje(double angle)
{
	yaw += angle;

	kamera_osvezi();
}

void Input::KolizijaBurad(){

	for(int i=0; i < 20; i++){
		
		if(pos_x >= pozicije_burica[i][0] && pos_x <= pozicije_burica[i][0]+1 && pos_z >= pozicije_burica[i][1] && pos_z <= pozicije_burica[i][1]+1){
			if(pos_x - pozicije_burica[i][0] >0 && pos_x -pozicije_burica[i][0] < 0.3 && pos_z > pozicije_burica[i][1] && pos_z < pozicije_burica[i][1]+1){
				pos_x = pozicije_burica[i][0];
			}
 
			if(pos_x - pozicije_burica[i][0] > 0.7 && pos_x -pozicije_burica[i][0] < 1 && pos_z > pozicije_burica[i][1] && pos_z < pozicije_burica[i][1]+1){
				pos_x = pozicije_burica[i][0]+1;
			}

			if(pos_z - pozicije_burica[i][1] > 0 && pos_z -pozicije_burica[i][1] < 0.3 && pos_x > pozicije_burica[i][0]-0.2 && pos_x < pozicije_burica[i][0]+1.2){
				pos_z = pozicije_burica[i][1];
			}

			if(pos_z - pozicije_burica[i][1] > 0.7 && pos_z -pozicije_burica[i][1] < 1 && pos_x > pozicije_burica[i][0]-0.2 && pos_x < pozicije_burica[i][0]+1.2){
				pos_z = pozicije_burica[i][1]+1;
			}

		}		
	}
}

void Input::upadUBure(double trX,double trY,double trZ){
	for(int i=0; i < 20; i++){
		if(trX >= pozicije_burica[i][0]-0.8 && trX <= pozicije_burica[i][0]+1.8 && trZ >= pozicije_burica[i][1]-0.8 && trZ <= pozicije_burica[i][1]+1.8){
			lopticaUBuretu[i] = true;
		}		
	}
}

bool Input::svaBurad(){
	int br = 0;
	bool ret = true;

	for(bool it: lopticaUBuretu){
		if(it == false){
			ret = false;
			br += 1;
		}
	}

	std::cout << br << std::endl;

	return ret;
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

	if(pos_z > (20.f - wallerr)){  //&& pos_x < (-2.f+wallerr) && pos_x > (0.f - wallerr)
		if(pos_x < 0 && pos_x > -2){
			izlaz = true;
		}else{
			pos_z = (20.f - wallerr);
		}
	}

	if(pos_x > 20.f-wallerr){
		pos_x = 20.f-wallerr;
	}
	else if(pos_x < -20.f+wallerr){
		pos_x = -20.f+wallerr;
	}
}

bool Input::getIzlaz(){
	return izlaz;
}

double Input::retX(){
	return pos_x;
}

double Input::retY(){
	return pos_y;
}

double Input::retZ(){
	return pos_z;
}

double Input::retVx(){
	return vecx;
}
double Input::retVy(){
	return vecy;
}
double Input::retVz(){
	return vecz;
}

double Input::retYaw(){
	return yaw;
}