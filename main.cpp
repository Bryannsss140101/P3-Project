#include <iostream>
#include <conio.h>
#include "src/main/csv/Csv.h"
#include "src/main/csv/DataFrame.h"
#include "src/main/csv/Dictionary.h"

using namespace std;

int main() {
    /*uto csv = Csv("data.csv");
    csv.read_csv();
    auto df = csv.get_data();*/

    /*DataFrame df;

    df.add_column("ID");
    df.add_column("Name");
    df.add_column("Last name");
    df.add_column("Number");

    df.add_row({"1", "Bryan", "Ninamango", "916760026"});
    df.add_row({"2", "Lesly", "Condor", "9123756842"});
    df.add_row({"3", "Khyara", "Arroyo", "902456789"});

    auto a = df.get_data();

    cout << df;*/

    Dictionary<int, vector<string> > dictionary;

    dictionary.add(1, vector<string>{"uno", "UNO", "UnO"});

    dictionary.add(2, vector<string>{"dos", "DOS", "DoS"});

    dictionary.add(3, vector<string>{"tres", "TRES", "TrEs"});

    dictionary.add(3, vector<string>{"cuatro", "CUATRO", "CuAtRo"});

    cout << dictionary << endl;

    dictionary.remove(2);

    cout << dictionary << endl;

    auto a = dictionary[2];

    cout << a << endl;

    cout << dictionary << endl;

    _getch();

    return 0;
}
