#include "antrastes.h"
#include <iostream>

using namespace std;

int main()
{
    readFile();
    double** matrica = matricos_skaiciavimas(points);
    int n = 5;
    geriausiavieta(n,matrica);
    spausdinimas(10,matrica);
    cout << endl;
    cout << "Atstumas tarp tasku: " << atstumas(3,6,matrica);

    return 0;
}