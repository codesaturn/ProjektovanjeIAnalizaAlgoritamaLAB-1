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

char transform(char c) {
    if (c == '\0')
        return c;

    char nc = '\0';

    switch (c) {
        case 'b':
        case 'f':
        case 'p':
        case 'v':
            nc = '1';
            break;
        case 'd':
        case 't':
            nc = '3';
            break;
        case 'l':
            nc = '4';
            break;
        case 'm':
        case 'n':
            nc = '5';
            break;
        case 'r':
            nc = '6';
            break;
        case 'c':
        case 'g':
        case 'j':
        case 'k':
        case 'q':
        case 's':
        case 'x':
        case 'z':
            nc = '2';
            break;
    }
    return nc;
}

void soundex(char* str) {
    for (int i = 1; i < strlen(str); i++) {
        char c = transform(str[i]);
        str[i] = (c == '\0') ? str[i] : c;
    }

    if (transform(str[0] - 'A' + 'a') == str[1])
        for (int j = 1; j < strlen(str); j++)
            str[j] = str[j + 1];

    for (int i = 1; i < strlen(str); i++) {
        if (transform(str[i]) == '\0' && str[i] >= 'a') {
            for (int j = i; j < strlen(str); j++)
                str[j] = str[j + 1];
            i--;
        }
    }

    if (strlen(str) < 4) {
        for (int i = strlen(str); i < 4; i++)
            str[i] = '0';
    }
    str[4] = '\0';
}

int main() {
    char fileName[100];
    char str[100];
    char strf[100];
    char nosx[100];

    cout << "Unesi naziv fajla : " << endl;
    cin.getline(fileName, 100);

    cout << "Unesi string za pretrazivanje : " << endl;
    cin.getline(str, 100);

    ifstream f(fileName);
    ofstream rez("rez.txt", ios::app);

    rez << "File : " << fileName << endl;
    rez << "Str : " << str << endl;
    rez << "Duzina : " << strlen(str) << endl;
    soundex(str);
    rez << "SoundEx : " << str << endl;
    rez << "Rezultati : " << endl;
    int i = 1;
    auto millsStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    while (!f.eof()) {
        f >> strf;
        strcpy(nosx, strf);
        soundex(strf);
        if (strcmp(str, strf) == 0) {
            rez << "\t";
            rez << i << ", " << nosx << endl;
        }
        i++;
    }
    auto end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millsStart;
    rez << "Time : " << end << " ms\n";
    rez << "---------------------------------\n";

    rez.close();
    f.close();
}