#include "attenuation.h"

void initializeAttenuationFactors(Attenuation *f, double a , double b, double c) {
    (*f).a = a;
    (*f).b = b;
    (*f).c = c;
}

double attFactor(Attenuation f, double distance) {
    return 1/(f.a*(distance*distance) + f.b*distance + f.c);
}