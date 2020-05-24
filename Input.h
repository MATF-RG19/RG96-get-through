#ifndef __input__
#define __input__

#include <vector>

class Input
{

	private:
        double pos_x, pos_y, pos_z, vecx, vecy, vecz, ldx, ldz;     //tacka pozicije, vektor pravca i promene
        double yaw, pitch;                                          //rotacija gore dole i levo desno
        bool izlaz;                                                 //boolean promenljiva koja predstavlja kriterijum zavrsetka igrice
        float wallerr = 0.5f;                                       //Dozvoljena greska u koliziji sa zidovima
       	std::vector<std::vector<int>> pozicije_burica;              //Pozicije burica   
       	std::vector<bool> lopticaUBuretu;                           //Boolean promeljive za svaku od burica koje sadrze informaciju o tome da li je loptica ubacena u njih

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
        void upadUBure(double trX,double trY,double trZ);
        bool svaBurad();
        bool getIzlaz();

};

#endif
