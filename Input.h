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
        void pocetna_pozicija(float x, float y, float z);
        void yawOkretanje(float angle);
        void pitchOkretanje(float angle);
        void Hodaj(float promena);
        void LevoDesno(float promena);

    private:
        float pos_x, pos_y, pos_z, vecx, vecy, vecz, ldx, ldz;
        float yaw, pitch; 
};

#endif
