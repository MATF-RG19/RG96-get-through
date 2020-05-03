#ifndef __input__
#define __input__

class Input
{
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

    private:
        double pos_x, pos_y, pos_z, vecx, vecy, vecz, ldx, ldz;
        double yaw, pitch; 
        float wallerr = 0.5f;

};

#endif
