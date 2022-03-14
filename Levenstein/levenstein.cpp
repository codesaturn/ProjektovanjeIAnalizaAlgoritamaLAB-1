#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

#define min(x, y) ((x) < (y) ? (x) : (y))

int levenstein(char* str1, char* str2) {
    int N = strlen(str1) + 1;
    int M = strlen(str2) + 1;
    int mat[100][100];

    for (int i = 0; i < N; i++) {
        mat[i][0] = i;
    }
    for (int j = 0; j < M; j++) {
        mat[0][j] = j;
    }

    int a, b;

    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            a = str1[i - 1] == str2[j - 1] ? 0 : 1;
            b = min(mat[i - 1][j] + 1, mat[i][j - 1] + 1);
            mat[i][j] = min(b, mat[i - 1][j - 1] + a);
        }
    }
    return mat[N - 1][M - 1];
}

int main() {
    char fileName[100];
    char str[100];
    char strf[100];

    cout << "Unesi naziv fajla : " << endl;
    cin.getline(fileName, 100);

    cout << "Unesi string za pretrazivanje : " << endl;
    cin.getline(str, 100);

    ifstream f(fileName);
    ofstream rez("rez.txt", ios::app);

    rez << "File : " << fileName << endl;
    rez << "Str : " << str << endl;
    rez << "Duzina : " << strlen(str) << endl;
    rez << "Pogadjanja  <= 3 : " << endl;
    int l;
    int i = 1;
    auto millsStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    while (!f.eof()) {
        f >> strf;
        l = levenstein(strf, str);
        if (l <= 3) {
            rez << "\t";
            rez << l << ", " << i << endl;
        }
        i++;
    }
    auto end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millsStart;
    rez << "Time : " << end << " ms\n";
    rez << "---------------------------------\n";

    rez.close();
    f.close();
}