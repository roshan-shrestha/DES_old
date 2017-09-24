#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

int main()
{
    string read, write, key;
    int count = 0;
    int asci;
    string binary;
    string eight_binary;
    ifstream in_file("input.txt");
    ifstream key_file("key_file.txt");
    ofstream out_file("output.txt");

    getline(in_file, read);
    cout << read << endl;

    getline(key_file, key);
    cout << "This is the key: " << key << endl;

    write = "This file was created inside a C++ program.";
    out_file << write << endl;

    vector<char> split_array(read.begin(),read.end());

    // Access each character in the file ( each char can be accessed by *i)
    for (vector<char>::const_iterator i = split_array.begin(); i != split_array.end(); ++i)
    {
        count++;
        //cout << "count is: "<< count << endl;
        asci = int(*i);
        binary = bitset<8>(asci).to_string();
        eight_binary += binary;
        if ((count % 8) == 0)
        {
            cout << eight_binary << endl;
            eight_binary.clear();
        }
        

    }
    return 0;
}
