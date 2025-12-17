#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

struct taskai{
    double plat;
    double ilg;
    int pop;
};

int kiekis = 0;
taskai* points = nullptr;

void readFile()
{
    ifstream failas("data.dat");
    if(!failas.is_open())
    {
        cout << "Failas neatsidare!" << endl;
    }

    double a,b;
    int c;
    while(failas >> a >> b >> c)
    {
        kiekis++;
    }
    failas.close();

    points = new taskai[kiekis];
    failas.open("data.dat");

    for(int i = 0; i < kiekis; i++)
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
    double** matrica = new double*[kiekis];

    for(int i = 0; i < kiekis; i++)
    {
        matrica[i] = new double[i+1];
    }

    for(int i = 0; i < kiekis; i++)
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

int main()
{
    
    readFile();
    double** matrica = matricos_skaiciavimas(points);
    spausdinimas(10, matrica);
    cout << endl;
    cout << "Atstumas tarp tasku: " << atstumas(3, 6, matrica) << endl;
}