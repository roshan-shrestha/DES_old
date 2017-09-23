#include <iostream>
#include <fstream>

using namespace std;

//bitset<64> charToBits(const char pt[8])
//{
//    bitset<64>;
//    for
//}

int main()
{
    string read, write, key;
    ifstream in_file("input.txt");
    ifstream key_file("key_file.txt");
    ofstream out_file("output.txt");

    getline(in_file, read);
    cout << read << endl;

    getline(key_file, key);
    cout << "this is the key: " << key;

    write = "This file was created inside a C++ program.";
    out_file << write << endl;

    return 0;
}
