#include <iostream>
#include <conio.h>
#include "src/main/csv/Csv.h"

using namespace std;


int main() {
    auto csv = Csv("data.csv");

    _getch();

    return 0;
}
