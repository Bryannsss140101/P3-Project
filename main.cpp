#include <iostream>
#include <conio.h>
#include "src/main/csv/Csv.h"
#include "src/main/dataframe/DataFrame.h"

using namespace std;

int main() {
    auto csv = Csv("data.csv");
    csv.read_csv();
    auto df = csv.get_dataframe();


    cout << df << endl;

    _getch();

    return 0;
}
