#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream f("euclid.in");
ofstream g("euclid.out");

int cmmdc(int a, int b) {
    while (b) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int log(int x) {
    int p = 0;
    while ((1 << (p + 1)) <= x) p++;
    return p;
}

int tablouGCD[10][405][405];
int temporar[405][405];
int numarTeste, linii, coloane, inaltimeSubmatrice, latimeSubmatrice;

int main() {
    f >> numarTeste;
    for (int t = 1; t <= numarTeste; t++) {
        f >> linii >> coloane >> inaltimeSubmatrice >> latimeSubmatrice;

        for (int i = 1; i <= linii; i++)
            for (int j = 1; j <= coloane; j++)
                f >> tablouGCD[0][i][j];

        for (int putere = 1; (1 << putere) <= coloane; putere++)
            for (int i = 1; i <= linii; i++)
                for (int j = 1; j + (1 << putere) - 1 <= coloane; j++)
                    tablouGCD[putere][i][j] = cmmdc(tablouGCD[putere - 1][i][j], tablouGCD[putere - 1][i][j + (1 << (putere - 1))]);

        int putereLatime = log(latimeSubmatrice);
        for (int i = 1; i <= linii; i++)
            for (int j = 1; j + latimeSubmatrice - 1 <= coloane; j++)
                temporar[i][j] = cmmdc(tablouGCD[putereLatime][i][j], tablouGCD[putereLatime][i][j + latimeSubmatrice - (1 << putereLatime)]);

        for (int i = 1; i <= linii; i++)
            for (int j = 1; j <= coloane; j++)
                tablouGCD[0][i][j] = temporar[i][j];

        for (int putere = 1; (1 << putere) <= linii; putere++)
            for (int i = 1; i + (1 << putere) - 1 <= linii; i++)
                for (int j = 1; j <= coloane; j++)
                    tablouGCD[putere][i][j] = cmmdc(tablouGCD[putere - 1][i][j], tablouGCD[putere - 1][i + (1 << (putere - 1))][j]);

        int putereInaltime = log(inaltimeSubmatrice), rezultatFinal = 0;
        for (int i = 1; i + inaltimeSubmatrice - 1 <= linii; i++)
            for (int j = 1; j + latimeSubmatrice - 1 <= coloane; j++)
                rezultatFinal = max(rezultatFinal, cmmdc(tablouGCD[putereInaltime][i][j], tablouGCD[putereInaltime][i + inaltimeSubmatrice - (1 << putereInaltime)][j]));

        g << "Case #" << t << ": " << rezultatFinal << '\n';
    }
    return 0;
}