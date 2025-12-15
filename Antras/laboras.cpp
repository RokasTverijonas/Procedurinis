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
//taskai points = nullptr;
//int N = 0;
//const int N = 50;
//double coord[N][2];
//int pop[N];

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

//int numP = 5;
//int P[] = {0,1,2,3,4};

//void readFile()
//{
    //ifstream failas("data.dat");
    //for(int i = 0;i < N;i++)
    //{
        //failas >> coord[i][0] >> coord[i][1] >> pop[i];
  //  }
//}

/*void printData()
{
    for(int i = 0;i < N;i++)
    {
        cout << coord[i][0] << " " << coord[i][1] << " " << pop[i] << endl;
    }
}*/

/*void printData(int n)
{
    for(int i = 0;i < n;i++)
    {
        cout << coord[i][0] << " " << coord[i][1] << " " << pop[i] << endl;
    }
}*/

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
            if(j > i)
            {
                matrica[i][j] = 0.0;
            }
            else
            {
                matrica[i][j] = HaversineDistance(&points[i], &points[j]);
            }
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

/*double getClosestDistance(int i, int* F,int numF)
{
    double mazAtstumas = HaversineDistance(i, *F);

    for(int k = 0;k < numF;k++)
    {
        double Atstumas = HaversineDistance(i,F[k]);
        if(Atstumas < mazAtstumas)
        {
            mazAtstumas = Atstumas;
        }
    }
    return mazAtstumas;
}*/

/*double getUtilityofX(int* X, int numX)
{
    double naudingumas = 0.0;
    double gyvsum = 0.0;

    for(int i = 0;i < N;i++)
    {
        gyvsum += pop[i];
        double oldDist = getClosestDistance(i,P,numP);
        double newDist = getClosestDistance(i,X,numX);
        if(newDist < oldDist)
        {
            naudingumas += pop[i];
        }
        else if(newDist == oldDist)
        {
            naudingumas += pop[i] / 3.0;
        }

    }
    return ((naudingumas / gyvsum) * 100);
}*/

int main()
{
    //int numX = 3;
    //int X[] = {5,6,7};

    //readFile();
    //printData();
    //cout << endl;
    //printData(3);
    //cout << HaversineDistance(0,1) << endl;
    //cout << getClosestDistance(0, P, numP) << endl;
    //cout << getClosestDistance(0, X, numX) << endl;
    //cout << getUtilityofX(X, numX) << endl;
    readFile();
    double** matrica = matricos_skaiciavimas(points);
    spausdinimas(10, matrica);
    cout << endl;
    cout << "Atstumas tarp tasku: " << atstumas(3, 6, matrica) << endl;
}