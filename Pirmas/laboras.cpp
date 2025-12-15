#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int N = 50;
double coord[N][2];
int pop[N];

int numP = 5;
int P[] = {0,1,2,3,4};

void readFile()
{
    ifstream failas("data.dat");
    for(int i = 0;i < N;i++)
    {
        failas >> coord[i][0] >> coord[i][1] >> pop[i];
    }
}

void printData()
{
    for(int i = 0;i < N;i++)
    {
        cout << coord[i][0] << " " << coord[i][1] << " " << pop[i] << endl;
    }
}

void printData(int n)
{
    for(int i = 0;i < n;i++)
    {
        cout << coord[i][0] << " " << coord[i][1] << " " << pop[i] << endl;
    }
}

double HaversineDistance(int i,int j)
{
    double dlat = fabs(coord[i][0] - coord[j][0]);
    double dlon = fabs(coord[i][1] - coord[j][1]);
    double aa = pow((sin((double)dlat/(double)2*0.01745)),2) + cos(coord[i][0]*0.01745) * cos(coord[j][0]*0.01745) * pow((sin((double)dlon/(double)2*0.01745)),2);
    double c = 2 * atan2(sqrt(aa), sqrt(1-aa));
    double d = 6371 * c;
    return d;
}

double getClosestDistance(int i, int* F,int numF)
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
}

double getUtilityofX(int* X, int numX)
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
}

int main()
{
    int numX = 3;
    int X[] = {5,6,7};

    readFile();
    //printData();
    cout << endl;
    printData(3);
    cout << HaversineDistance(0,1) << endl;
    cout << getClosestDistance(0, P, numP) << endl;
    cout << getClosestDistance(0, X, numX) << endl;
    cout << getUtilityofX(X, numX) << endl;
}