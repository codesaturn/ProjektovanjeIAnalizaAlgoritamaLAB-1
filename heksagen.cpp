#include <stdlib.h>
#include <time.h>

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

int main(int argc, char* argv[]) {
    fstream f("100-h.txt");
    srand(time(NULL));

    auto millsStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    for (int i = 0; i < 100; i++) {
        /* int size = rand() % 10;
         for (int k = 0; k < size; k++) {*/
        int j = rand() % 16;
        char c = (j < 10) ? (char)(j + '0') : (j - 10) + 'A';
        f << c;
        /*}
        f << ' ';*/
    }

    auto mills = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millsStart;
    f.close();
    cout << "Generated in " << mills << "ms\n";
}