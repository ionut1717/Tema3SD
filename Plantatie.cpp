#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

ifstream f("plantatie.in");
ofstream g("plantatie.out");

int tabelCautare[501][501][10];
int dimensiuneMatrice;
int numarInterogari;
int matriceOriginala[501][501];

void precalculareMaxime() {
    for (int i = 1; i <= dimensiuneMatrice; i++)
        for (int j = 1; j <= dimensiuneMatrice; j++)
           tabelCautare[i][j][0] = matriceOriginala[i][j];

    for (int k = 1; (1 << k) <= dimensiuneMatrice; k++) {
        for (int i = 1; i + (1 << k) - 1 <= dimensiuneMatrice; i++)
            for (int j = 1; j + (1 << k) - 1 <= dimensiuneMatrice; j++) {
                int pas = 1 << (k - 1);
                tabelCautare[i][j][k] = max(max(tabelCautare[i][j][k - 1], tabelCautare[i][j + pas][k - 1]),
                                            max(tabelCautare[i + pas][j][k - 1], tabelCautare[i + pas][j + pas][k - 1]));
            }
    }
}

int main() {
    int linieStart, coloanaStart, laturaPatrat;
    f >> dimensiuneMatrice >> numarInterogari;

    for (int i = 1; i <= dimensiuneMatrice; i++)
       for (int j = 1; j <= dimensiuneMatrice; j++) {
          f >> matriceOriginala[i][j];
       }

    precalculareMaxime();

    for (int i = 0; i < numarInterogari; i++) {
        f >> linieStart >> coloanaStart >> laturaPatrat;
        int k_log = (int)log2(laturaPatrat);
        int putere2 = 1 << k_log;

        int maxim_patrat = max(max(tabelCautare[linieStart][coloanaStart][k_log], tabelCautare[linieStart][coloanaStart + laturaPatrat - putere2][k_log]),
                               max(tabelCautare[linieStart + laturaPatrat - putere2][coloanaStart][k_log], tabelCautare[linieStart + laturaPatrat - putere2][coloanaStart + laturaPatrat - putere2][k_log]));
        g << maxim_patrat << "\n";
    }

    return 0;
}