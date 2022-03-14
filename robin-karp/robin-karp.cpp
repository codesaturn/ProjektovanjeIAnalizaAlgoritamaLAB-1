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

void robinkarp_h(char* text, char* str) {
    int d = 16;
    int q = 271;
    int m = strlen(str);
    int n = strlen(text);
    int h = 1;
    int p = 0;
    int t0 = 0;

    ofstream f("robin-karp.txt", ios_base::app);
    f << "Velicina teksta : " << n << "\nVelicina stringa : " << m << "\nPozicije : ";
    auto millsStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    for (int i = 0; i < m; i++) {
        p = (d * p + (str[i] >= '0' && str[i] <= '9' ? (str[i] - '0') : (str[i] - 'A'))) % q;
        t0 = (d * t0 + (text[i] >= '0' && text[i] <= '9' ? (text[i] - '0') : (text[i] - 'A'))) % q;
    }
    for (int i = 0; i < m - 1; i++)
        h = (d * h) % q;

    for (int s = 0; s <= n - m; s++) {
        if (p == t0) {
            int flag = 1;
            for (int i = 0; i < m && flag; i++) {
                flag = text[i + s] == str[i];
            }
            if (flag) {
                f << s << " ";
            }
        }

        t0 = (d * (t0 - (text[s] >= '0' && text[s] <= '9' ? (text[s] - '0') : (text[s] - 'A')) * h) + (text[s + m] >= '0' && text[s + m] <= '9' ? (text[s + m] - '0') : (text[s + m] - 'A'))) % q;

        if (t0 < 0)
            t0 = (t0 + q);
    }

    auto mills = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millsStart;
    f << endl
      << "Potrebno vreme : " << mills << "ms" << endl
      << "---------------------------------------------\n";
    f.close();
}

void robinkarp(char* text, char* str) {
    int d = 256;
    int q = 271;
    int m = strlen(str);
    int n = strlen(text);
    int h = 1;
    int p = 0;
    int t0 = 0;

    ofstream f("robin-karp.txt", ios_base::app);
    f << "Velicina teksta : " << n << "\nVelicina stringa : " << m << "\nPozicije : ";
    auto millsStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    for (int i = 0; i < m; i++) {
        p = (d * p + str[i]) % q;
        t0 = (d * t0 + text[i]) % q;
    }
    for (int i = 0; i < m - 1; i++)
        h = (d * h) % q;

    for (int s = 0; s <= n - m; s++) {
        if (p == t0) {
            int flag = 1;
            for (int i = 0; i < m && flag; i++) {
                flag = text[i + s] == str[i];
            }
            if (flag) {
                f << s << " ";
            }
        }

        t0 = (d * (t0 - text[s] * h) + text[s + m]) % q;

        if (t0 < 0)
            t0 = (t0 + q);
    }

    auto mills = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millsStart;
    f << endl
      << "Potrebno vreme : " << mills << "ms" << endl
      << "---------------------------------------------\n";
    f.close();
}
/*
NAPOMENA : Za generisanje vremena sam korisitio samo robinkarp,
 bez ove provere za text i da se dodaje 0 - 15,
jer to uvecava vreme i ne vidim razlog za to
dodato je u slucaju da je potrebno
*/
int main() {
    cout << "Unesi odabir azbuke : 0 - heksa , 1 - ASCII\n";
    int azbuka;
    cin >> azbuka;
    cout << "Unesi ime fajla iz kog se cita tekst\n";
    char imeFajla[100];
    cin.getline(imeFajla, 100);
    cout << "Unesi string koji se trazi\n";
    char str[100];
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
    switch (azbuka) {
        case 0:
            robinkarp_h(text, str);
            break;
        case 1:
            robinkarp(text, str);
            break;
        default:
            robinkarp(text, str);
            break;
    }
    delete text;
}