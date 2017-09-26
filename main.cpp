#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

//Initial Permutation
static vector<int> ip = {
               58, 50, 42, 34, 26, 18, 10,  2,
               60, 52, 44, 36, 28, 20, 12,  4,
               62, 54, 46, 38, 30, 22, 14,  6,
               64, 56, 48, 40, 32, 24, 16,  8,
               57, 49, 41, 33, 25, 17,  9,  1,
               59, 51, 43, 35, 27, 19, 11,  3,
               61, 53, 45, 37, 29, 21, 13,  5,
               63, 55, 47, 39, 31, 23, 15,  7};

const vector<int> p32 = {
                16,  7, 20, 21,
                29, 12, 28, 17,
                 1, 15, 23, 26,
                 5, 18, 31, 10,
                 2,  8, 24, 14,
                32, 27,  3,  9,
                19, 13, 30,  6,
                22, 11,  4, 25
             };

static vector<int> exp_table = {32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,
             17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};

string padtext(string read)
{
    int length = read.length();

    //Pad 'x' to make the total number of characters in the multiple of 8.
    while ((length % 8) != 0)
    {
        read += 'x';
        length = read.length();
    }

    return read;
}

string str_bin(string read)
{
    int count = 0;
    int ascii;

    string each_binary;
    string all_binary;

    //Create a vector of characters that splits the string into each character.
    //String refers to 'read'.
    vector<char> split_array(read.begin(),read.end());

    // Access each character in the string ( each char can be accessed by *i)
    for (vector<char>::const_iterator i = split_array.begin(); i != split_array.end(); ++i)
    {
        // A int count variable to track the count of characters
        count++;

        //Converts each character into ASCII value
        ascii = int(*i);

        //Convert ASCI value to eight bit binary.
        each_binary = bitset<8>(ascii).to_string();

        //Concatenate eight characters to make 64 bit (1 char = 8 bit)
        all_binary += each_binary;
        //Concatenates all the character.

    }
    return all_binary;

}

//Initial permutation of the concatenated binary
string perm(string eight_binary)
{
    string ip_binary;
    for (int j = 0 ; j < eight_binary.length(); j++)
    {
        ip_binary += eight_binary[ip[j]-1];
    }
    return ip_binary;
}

// Mode = 1 for string
// Mode = 2 for key
//void tempfunction(string read, int mode)
//{
//    int count = 0;
//    int ascii;
//
//    string binary;
//    string eight_binary;
//    string ip_binary;
//
//    string left_binary;
//    string right_binary;
//
//    string left_key_binary, right_key_binary;
//
//    if (mode == 1)
//    {
//        //Create a vector of characters that splits the string into each character.
//        //String refers to 'read'.
//        vector<char> split_array(read.begin(),read.end());
//
//        // Access each character in the string ( each char can be accessed by *i)
//        for (vector<char>::const_iterator i = split_array.begin(); i != split_array.end(); ++i)
//        {
//            // A int count variable to track the count of characters
//            count++;
//
//            //Converts each character into ASCII value
//            ascii = int(*i);
//
//            //Convert ASCI value to eight bit binary.
//            binary = bitset<8>(ascii).to_string();
//
//            if (mode == 1)
//            {
//                //Concatenate eight characters to make 64 bit (1 char = 8 bit)
//                eight_binary += binary;
//                //Concatenate until 8th character.
//
//                if ((count % 8) == 0)
//                {
//                    //Initial permutation of the concatenated binary
//                    for (int j = 0 ; j < eight_binary.length(); j++)
//                    {
//                        ip_binary += eight_binary[ip[j]-1];
//                    }
//                    cout << ip_binary << endl;
//
//                    //Split the result into two 32 bit binary
//                    left_binary = ip_binary.substr(0,32);
//                    right_binary = ip_binary.substr(32,eight_binary.length()-1);
//
//                    cout << left_binary << ' ' << right_binary << endl;
//
//                    ip_binary.clear();
//                    eight_binary.clear();
//
//                }
//            }
//        }
//    }
//    else if (mode == 2)
//    {
//        vector<char> split_key(read.begin(),read.end());
//
//
//        for (vector<char>::const_iterator i = split_key.begin(); i != split_key.end(); ++i)
//        {
//            // A int count variable to track the count of characters
//            count++;
//
//            //Converts each character into ASCII value
//            ascii = int(*i);
//
//            //Convert ASCI value to eight bit binary.
//            binary = bitset<8>(ascii).to_string();
//
//
//            if ((count % 8) != 0)
//            {
//                //Concatenate eight characters to make 64 bit (1 char = 8 bit)
//                eight_binary += binary;
//                //Concatenate until 8th character.
//
//            }
//        }
//        cout << "56 bit key: " << eight_binary << endl;
//
//        //Split the key into two 32 bit binary
//        left_key_binary = eight_binary.substr(0,28);
//        right_key_binary = eight_binary.substr(28,eight_binary.length()-1);
//
//        cout << left_key_binary << ' ' << right_key_binary << endl;
//
//        int shifted = stoi(left_key_binary) << 1;
//
//        //cout << "left shift: " << shifted << endl;
//
//    }
//}

string encrypt(string left, string right)
{
    return "poop";
}

int main()
{
    string read, write, key;

    string padread, padkey;
    string binary_done;

    ifstream in_file("input.txt");
    ifstream key_file("key_file.txt");
    ofstream out_file("output.txt");

    getline(in_file, read);
    cout << read << endl;

    getline(key_file, key);
    cout << "This is the key: " << key << endl;

    write = "This file was created inside a C++ program.";
    out_file << write << endl;

    padread = padtext(read);
    binary_done = str_bin(padread);

    string permuted;
    string left_binary;
    string right_binary;
    vector <string> permuted_vector;
    vector <string> left_permuted_vector;
    vector <string> right_permuted_vector;
    vector <string> result;

    for (int i = 0; i < binary_done.length() ; i+=64)
    {
        permuted = perm(binary_done.substr(i,64));
        permuted_vector.push_back(permuted);
    }

    for (int i = 0; i < permuted_vector.size() ; i++)
    {
        //Split the vector into two 32 bit binary
        left_binary = permuted_vector[i].substr(0,32);
        right_binary = permuted_vector[i].substr(32,32);

        left_permuted_vector.push_back(left_binary);
        right_permuted_vector.push_back(right_binary);

        cout << left_binary << " " << right_binary<< endl;

        if (i == 0)
        {
            result[i] = encrypt(left_permuted_vector[i],right_permuted_vector[i]);
        }
        else
        {
            result[i] = encrypt(right_permuted_vector[i-1], ( bitset<32>(left_permuted_vector[i-1] ) ^ bitset<32>(result[i-1])).to_string() );
        }

    }

//    cout << binary_done << endl;
//    tempfunction(padread, mode);
//
//    mode = 2;
//    padkey = padtext(key);
//    cout << "pad key: " << endl;
//    cout << padkey << endl;
//
//    tempfunction(padkey, mode);

    return 0;
}
