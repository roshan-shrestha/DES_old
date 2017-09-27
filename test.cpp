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

static vector<int> exp_table = {32,1,2,3,4,5,4,5,
                                6,7,8,9,8,9,10,11,
                                12,13,12,13,14,15,
                                16,17,16,17,18,19,
                                20,21,20,21,22,23,
                                24,25,24,25,26,27,
                                28,29,28,29,30,31,32,1};

static vector<int> left_shift_schedule = {1, 1, 2, 2, 2, 2, 2, 2};

static vector<int> permutation_one = {57,49,41,33,25,17,9,1,58,50,42,34,26,18,
                                      10,2,59,51,43,35,27,19,11,3,60,52,44,36,
                                      63,55,47,39,31,23,15,7,62,54,46,38,30,22,
                                      14,6,61,53,45,37,29,21,13,5,28,20,12,4};

static vector<int> permutation_two = {14,17,11,24,1,5,3,28,15,6,21,10,23,19,
                                      12,4,26,8,16,7,27,20,13,2,41,52,31,37,
                                      47,55,30,40,51,45,33,48,44,49,39,56,
                                      34,53,46,42,50,36,29,32};

static vector<int> inverse_perm_table = {40,8,48,16,56,24,64,32,39,7,47,
                                   15,55,23,63,31,38,6,46,14,54,22,
                                   62,30,37,5,45,13,53,21,61,29,36,
                                   4,44,12,52,20,60,28,35,3,43,11,
                                   51,19,59,27,34,2,42,10,50,18,58,
                                   26,33,1,41,9,49,17,57,25};

short sbox_array[8][4][16] =
        {
                {
                        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
                        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
                        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
                        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
                },
                {
                        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
                        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
                        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
                        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
                },
                {
                        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
                        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
                        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
                        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
                },
                {
                        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
                        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
                        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
                        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
                },
                {
                        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
                        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
                        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
                        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
                },
                {
                        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
                        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
                        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
                        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
                },
                {
                        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
                        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
                        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
                        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
                },
                {
                        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
                        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
                        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
                        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
                }
        };

static vector<int> e_table = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
16, 17, 18, 19, 20, 21,
20, 21, 22, 23, 24, 25,
24, 25, 26, 27, 28, 29,
28, 29, 30, 31, 32, 1};

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
string initial_perm(string eight_binary)
{
    string ip_binary;
    for (int j = 0 ; j < eight_binary.length(); j++)
    {
        ip_binary += eight_binary[ip[j]-1];
    }
    return ip_binary;
}

//Permutation choice one
string key_perm_one(string eight_key)
{
    string perm_one_binary;

    for (int k = 0; k < permutation_one.size() ; k++)
    {
        perm_one_binary += eight_key[permutation_one[k]-1];
    }

    return perm_one_binary;
}

//Permutation one two
string key_perm_two(string joined_key )
{
    string perm_two_binary;

    for (int k = 0; k < permutation_two.size() ; k++)
    {
        perm_two_binary += joined_key[permutation_two[k]-1];
    }

    return perm_two_binary;
}

string inverse_perm(string result)
{
    string final_result;

    for (int k = 0; k < inverse_perm_table.size() ; k++)
    {
        final_result += result[inverse_perm_table[k]-1];
    }

    return final_result;
}

//Expansion
string expansion(string &exp)
{
    string change;
    int count = 0;

    change += exp[exp.length()-1];

    for (int i = 0; i < exp.length(); i+=4)
    {
        if (count != 0)
        {
            change += exp[count-1];
        }

        change += exp.substr(count, 4);

        count += 4;

        if (count != 32)
        {
            change += exp[count];
        }
        change += "";
    }

    change += exp[0];
    exp = change;
    return exp;
}

//XOR operation
string xor_operation_48(string string1, string string2)
{
    return ((bitset<48>(string1) ^ bitset<48>(string2)).to_string());
}

//XOR operation 32
string xor_operation_32(string string1, string string2)
{
    return ((bitset<32>(string1) ^ bitset<32>(string2)).to_string());
}

//Permuted 32 bit table after S box operation.
string perm_32(string sbox_result)
{
    string p32_result;
    for (int k = 0; k < p32.size() ; k++)
    {
        p32_result += sbox_result[p32[k]-1];
    }
    return p32_result;
}


string keygen(string binary_key, int round)
{
    //Permutation one on the 64 bit key to get 56 bit.
    string perm_one_binary = key_perm_one(binary_key);

    //Split the 56 bit key into two 28 bit binary
    string left_key_binary = perm_one_binary.substr(0,28);
    string right_key_binary = perm_one_binary.substr(28,perm_one_binary.length()-1);

    int noshift;
    if ( round == 1 || round == 2 )
    {
        noshift = 1;
    }
    else
    {
        noshift = 2;
    }

    while(noshift > 0)
    {
        int temp;
        temp = left_key_binary[0];
        for (int i = 0 ; i < 28 ; i++ )
        {
            left_key_binary[i] = left_key_binary[i+1];
        }
        left_key_binary[27] = temp;

        temp = right_key_binary[0];
        for (int i = 0 ; i < 28 ; i++)
        {
            right_key_binary[i] = right_key_binary[i+1];

        }
        right_key_binary[27] = temp;
        noshift--;
    }

    //Join the shifted keys together.
    string joined_key = left_key_binary + right_key_binary;

    // Permutation two in the joined 56 bit key to get 48 bit.
    string perm_two_binary = key_perm_two(joined_key);

    return perm_two_binary;

}

int binToDec(int n)
{
    int factor = 1;
    int total = 0;

    while (n != 0)
    {
        total += (n%10) * factor;
        n /= 10;
        factor *= 2;
    }

    return total;
}

string sbox(string bin, int boxnum)
{
    string row, column;
    char row_begin = bin[0];
    char row_end = bin[bin.length()-1];

    row += bin[0];
    row += bin[bin.length()-1];
    column = bin.substr(1, 4);

    short row_num = binToDec(stoi(row));
    short column_num = binToDec(stoi(column));

    return (bitset<4>(sbox_array[boxnum][row_num][column_num])).to_string();
}


string encrypt(string input, string key, int i)
{

    string result_expansion = expansion(input);

    string result_key = keygen(key,i);

    string result_xor = xor_operation_48(result_key, result_expansion);

    string result_sbox, temp;

    int choice = 0;

    for (int i = 0; i < 48; i+=6)
    {
        temp = sbox(result_xor.substr(i,6), choice);
        choice++;
        result_sbox += temp;
    }

    string last_perm = perm_32(result_sbox);

    return last_perm;
}

int main()
{
    string read, write, key;

    ifstream in_file("input.txt");
    ifstream key_file("key_file.txt");
    ofstream out_file("output.txt");

    getline(in_file, read);
    cout << read << endl;

    getline(key_file, key);
    cout << "This is the key: " << key << endl;

//    write = "This file was created inside a C++ program.";

    string padread = padtext(read);
    string binary_done = str_bin(padread);

    vector <string> permuted_vector;

    string padkey = padtext(key);
    string binary_key = str_bin(padkey);

    string result_ip = initial_perm(binary_key);

    //Split the vector into two 32 bit binary
    string left_binary = result_ip.substr(0,32);
    string right_binary = result_ip.substr(32,32);

    for (int i = 0; i < binary_done.length() ; i += 64)
    {
        permuted_vector.push_back(binary_done.substr( i , 64 ));
    }

    string encrypt_result;
    string final;
    string temp;

    for (int i = 1 ; i <= 8 ; i++)
    {
        encrypt_result = encrypt(right_binary, binary_key, i);
        temp = xor_operation_32(encrypt_result, left_binary);
        left_binary = right_binary;
        right_binary = temp;
    }

    final = left_binary + right_binary;

    string lafinal = inverse_perm(final);

    string tempone;

    for (int i = 0 ; i < 64 ; i+=8)
    {
        tempone += binToDec(stoi(lafinal.substr(i,8)));
//        cout << tempone << endl;
    }

    out_file << tempone << endl;

    return 0;
}
