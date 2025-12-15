#ifndef antrastes_H
#define antrastes_H

#include <iostream>

struct taskai{
    double plat;
    double ilg;
    int pop;
};

extern const int N;
extern int kiekis;
extern taskai* points;

extern int numP;
extern int P[];

void readFile();
double HaversineDistance(taskai* A, taskai* B);
double** matricos_skaiciavimas(taskai* points);
void spausdinimas(int n, double** matrica);
double atstumas(int A, int B, double** matrica);
double getClosestDistance(int i, int* F,int numF, double** matrica);
double getUtilityofX(int* X, int numX, double** matrica);
void geriausiavieta(int n, double** matrica);

#endif
