#include <iostream>
#include <conio.h>
#include "src/main/searcher/Searcher.h"

using namespace std;

int main() {
    Searcher searcher("mpst_full_data.csv");

    searcher.find("I tre volti della paura");
    searcher.find("Dungeons & Dragons: The Book of Vile Darkness");
    searcher.find("The Shop Around the Corner");
    searcher.find("Mr. Holland's Opus");
    searcher.find("Scarface");
    searcher.find("A Single Man");
    searcher.find("Baise-moi");

    _getch();

    return 0;
}
