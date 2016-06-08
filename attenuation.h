typedef struct attenuation {
    double a;
    double b;
    double c;
}Attenuation;

double attFactor(Attenuation, double);
void initializeAttenuationFactors(Attenuation*, double, double, double);