#include "antrastes.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;


const int N = 50;
int kiekis = 0;
taskai* points = nullptr;

int numP = 5;
int P[] = {0,1,2,3,4};

void readFile()
{
    ifstream failas("data.dat");
    if(!failas.is_open())
    {
        cout << "Failas neatsidare!" << endl;
    }

    kiekis = N;
    points = new taskai[N];

    for(int i = 0; i < N; i++)
    {
        failas >> points[i].plat >> points[i].ilg >> points[i].pop;
    }
    failas.close();

}

double HaversineDistance(taskai* A, taskai* B)
{
    double dlat = fabs(A->plat - B->plat);
    double dlon = fabs(A->ilg - B->ilg);
    double aa = pow((sin((double)dlat/(double)2*0.01745)),2) + cos(A->plat*0.01745) * cos(B->plat*0.01745) * pow((sin((double)dlon/(double)2*0.01745)),2);
    double c = 2 * atan2(sqrt(aa), sqrt(1-aa));
    double d = 6371 * c;
    return d;
}

double** matricos_skaiciavimas(taskai* points)
{
    double** matrica = new double*[N];

    for(int i = 0; i < N; i++)
    {
        matrica[i] = new double[i+1];
    }

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j <= i; j++)
        {
                matrica[i][j] = HaversineDistance(&points[i], &points[j]);
        }
    }
    return matrica;
}

void spausdinimas(int n, double** matrica)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            cout << setprecision(1) << fixed << matrica[i][j] << " ";
        }
        cout << endl;
    }
}
double atstumas(int A, int B, double** matrica)
{
    double atstumas = 0;
    if(A==B)
    {
        return 0.0;
    }
    else if(A > B)
    {
        atstumas = matrica[A][B];
    }
    else if(A < B)
    {
        atstumas = matrica[B][A];
    }
    return atstumas;
}



double getClosestDistance(int i, int* F,int numF, double** matrica)
{
    double mazAtstumas = 1e9;

    for(int k = 0;k < numF;k++)
    {
        double Atstumas = atstumas(i,F[k],matrica);
        if(Atstumas < mazAtstumas)
        {
            mazAtstumas = Atstumas;
        }
    }
    return mazAtstumas;
}

double getUtilityofX(int* X, int numX, double** matrica)
{
    double naudingumas = 0.0;
    double gyvsum = 0.0;

    for(int i = 0; i < N;i++)
    {
        gyvsum += points[i].pop;
    }
    for(int i = 0; i < N; i++)
    {
        double oldDist = getClosestDistance(i,P,numP,matrica);
        double newDist = getClosestDistance(i,X,numX,matrica);
        if(newDist < oldDist)
        {
            naudingumas += points[i].pop;
        }
        else if(newDist == oldDist)
        {
            naudingumas += points[i].pop / 3.0;
        }

    }
    return ((naudingumas / gyvsum) * 100);
}

void geriausiavieta(int n, double** matrica)
{
    int* X = new int[n];
    int* bestX = new int[n];
    double didziausiasnaudingumas = 0.0;

    for(int i = 0; i < n; i++)
    {
        X[i] = i;
    }

    bool done = false;

    while(!done)
    {
        double dabartinisnaud = getUtilityofX(X,n,matrica);

        if(dabartinisnaud > didziausiasnaudingumas)
        {
            didziausiasnaudingumas = dabartinisnaud;

            for(int i = 0; i < n; i++)
        {
            bestX[i] = X[i];
        }
        }


        int i = n - 1;
        while(i >= 0 && X[i] == N - n + i)
        {
            i--;
        }

        if(i < 0)
        {
            done = true;
        }
        else
        {
            X[i]++;

            for(int j = i + 1; j < n; j++)
            {
                X[j] = X[j-1] + 1;
            }
        }
    }

    cout << "\nGeriausias naudingumas: " << didziausiasnaudingumas << endl;
    cout << "Geriausios vietos (miestų indeksai): ";
    for (int i = 0; i < n; i++)
    {
        cout << bestX[i] << " ";
    }
    cout << endl;
    
    delete[] X;
    delete[] bestX;

}