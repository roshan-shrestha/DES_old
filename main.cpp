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
string xor_operation(string string1, string string2)
{
    return ((bitset<48>(string1) ^ bitset<48>(string2)).to_string());
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

int main()
{
    string read, write, key;

    string padread, padkey;
    string binary_done;
    string binary_key;

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

    string permuted_string;
    string left_binary;
    string right_binary;
    vector <string> permuted_vector;
    vector <string> left_permuted_vector;
    vector <string> right_permuted_vector;
    vector <string> result;

    for (int i = 0; i < binary_done.length() ; i+=64)
    {
        permuted_string = perm(binary_done.substr(i,64));
        permuted_vector.push_back(permuted_string);
    }

    padkey = padtext(key);
    binary_key = str_bin(padkey);

    string final_key = keygen(binary_key, 1);

    cout << final_key << endl;

//    // 8 rounds of encryption has different key scheduling.
//    for (int i = 0 ; i < left_shift_schedule.size() ; i++)
//    {
//
//    }

    for (int i = 0; i < permuted_vector.size() ; i++)
    {
        //Split the vector into two 32 bit binary
        left_binary = permuted_vector[i].substr(0,32);
        right_binary = permuted_vector[i].substr(32,32);

        left_permuted_vector.push_back(left_binary);
        right_permuted_vector.push_back(right_binary);

        //Stores the expanded 48 bit here.
        string expanded = expansion(right_binary);

        //Calls the xor operation on expanded bit and permuted two key.
        string xor_result = xor_operation(expanded, final_key);

        cout << expanded << endl;

        cout << endl;
        cout << xor_result << endl;


//        if (i == 0)
//        {
//            //result[i] = encrypt(left_permuted_vector[i],right_permuted_vector[i]);
//
//        }
//        else
//        {
//           // result[i] = encrypt(right_permuted_vector[i-1], ( bitset<32>(left_permuted_vector[i-1] ) ^ bitset<32>(result[i-1])).to_string() );
//        }

    }

    return 0;
}
