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

void prefix(char* str, int* pi) {
    int m = strlen(str);
    int len = 0;
    pi[0] = 0;
    for (int i = 1; i < m; i++) {
        while (len > 0 && str[len] != str[i])
            len = pi[len];
        if (str[len] == str[i]) {
            len++;
        }
        pi[i] = len;
    }
}

void kmp(char* text, char* str) {
    int n = strlen(text);
    int m = strlen(str);

    ofstream f("kmp.txt", ios::app);
    f << "Velicina texta : " << n << endl
      << "Velicina stringa : " << m << endl
      << "Pozicije : ";

    int* pi = (int*)malloc(m * sizeof(int));

    auto millsStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    prefix(str, pi);

    auto millsPref = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    int q = 0;

    for (int i = 0; i < n; i++) {
        while (q > 0 && str[q] != text[i]) {
            q = pi[q - 1];
        }
        if (str[q] == text[i]) {
            q++;
        }
        if (q == m) {
            f << i << " ";
            q = pi[q - 1];
        }
    }
    auto millsEnd = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    f << endl
      << "Vreme za prefix : " << millsPref - millsStart << " ms" << endl
      << "Vreme za poredjenje : " << millsEnd - millsPref << " ms" << endl
      << "Vreme ukupno : " << millsEnd - millsStart << " ms" << endl
      << "----------------------" << endl;
    f.close();
    delete pi;
}

int main(int argc, char* argv[]) {
    char imeFajla[100];
    char str[100];

    cout << "Unesi ime fajla : ";
    cin.getline(imeFajla, 100);
    cout << "Unesi string za trazenje : ";
    cin.getline(str, 100);

    ifstream f(imeFajla);
    f.seekg(0, f.end);
    size_t size = f.tellg();
    size += 1;
    char* text = (char*)malloc(size);
    f.seekg(0, f.beg);
    f.get(text, size);
    text[size] = '\0';
    f.close();

    kmp(text, str);

    return 1;
}