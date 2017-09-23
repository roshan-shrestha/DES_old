#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string read, write;
    ifstream in_file("input.txt");
    ofstream out_file("output.txt");

    getline(in_file, read);
    cout << read << endl;

    write = "This file was created inside a C++ program.";
    out_file << write << endl;

    return 0;
}