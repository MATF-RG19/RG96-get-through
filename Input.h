#ifndef __input__
#define __input__

#include <vector>

class Input
{

	private:
        double pos_x, pos_y, pos_z, vecx, vecy, vecz, ldx, ldz;
        double yaw, pitch; 
        float wallerr = 0.5f;
       	std::vector<std::vector<int>> pozicije_burica;
       	
    public:
        Input() { 
            naNule(); 
        }


        void kamera_osvezi();
        void naNule();
        void pocetna_pozicija(double x, double y, double z);
        void yawOkretanje(double angle);
        void Hodaj(double promena);
        void LevoDesno(double promena);
        void KolizijaZidovi();
        void KolizijaBurad();
        double retX();
        double retY();
        double retZ();
        double retVx();
        double retVy();
        double retVz();
        double retYaw();

};

#endif
