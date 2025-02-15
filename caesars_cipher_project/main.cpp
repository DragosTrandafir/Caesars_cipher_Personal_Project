#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include<cstring>
#include<cmath>
using namespace std;

float* alphabet_distribution(ifstream& f) {
    // this function creates an array with the frequency of the letters
   // in the English alphabet, 0 is the index of frequency of 'a', 1 is the index of frequency of 'b' in the array etc...
    float* alphabet_letters_frequency = new float[26];
    float letter_frequency;
    int letter_index = 0;
    while (letter_index < 26 && f >> letter_frequency) {
        alphabet_letters_frequency[letter_index] = letter_frequency;
        letter_index++;
    }
    return alphabet_letters_frequency;
}

float* string_distribution(const char* given_cipher_string) {
    /* this function uses a frequency array to measure how often each letter appears in a text,
    taking into consideration only lower-case and upper-case letters.
    */
    float* cipher_letters_frequency = new float[26];
    for (int letter_index = 0; letter_index < 26; letter_index++)
        cipher_letters_frequency[letter_index] = 0;
    for (int cipher_letter_index = 0; cipher_letter_index < strlen(given_cipher_string); cipher_letter_index++)
        if (given_cipher_string[cipher_letter_index] >= 'a' && given_cipher_string[cipher_letter_index] <= 'z')
            cipher_letters_frequency[int(given_cipher_string[cipher_letter_index]) - 97] += 1;
        else if (given_cipher_string[cipher_letter_index] >= 'A' && given_cipher_string[cipher_letter_index] <= 'Z')
            cipher_letters_frequency[int(given_cipher_string[cipher_letter_index]) - 65] += 1;
    return cipher_letters_frequency;
}
float chi_square_distance(float* arr1, float* arr2) {
    // here we calculate the Chi-square distance between the 2 arrays formed before, by the formula Χ² = Σ [ (O_i – E_i)² / E_i ],
    // where O_i is the number of appearances of the letter in our text and E_i is the number of appearances of the letter in the alphabet
    float s = 0.0;
    for (int letter_index = 0; letter_index < 26; letter_index++)
        s += ((arr1[letter_index] - arr2[letter_index]) * (arr1[letter_index] - arr2[letter_index])) / arr2[letter_index];
    return s;

}
//these 2 functions move a character n positions in the alphabet, one is for the lower-case letters and the other for the upper-case letters
char convertLowerCase(char c, int n) {
    n = n % 26;
    return 'a' + (c - 'a' + n) % 26;
}

char convertUpperCase(char c, int n) {
    n = n % 26;
    return 'A' + (c - 'A' + n) % 26;

}

/*
this is the most complex function in the program, but also the most important:
we create in the memory 2 strings - one for storing the changed text for every number of positions from 1 to 25
(possible number of shifts corresponding to every letter of the alphabet)
                                  - one for saving the text which has the smallest Chi-square distance with the English alphabet
So, for every possible number of positions we can move all the letters in our text, we convert the text and check if the Chi-square distance is smaller.
At the end, we return the changed text or our initial text in case our original text was already 'translated' in English.

    */
char* break_cipher(char* cipher, float* alphabet_letters_frequency) {
    char* trial_decription = new char[strlen(cipher) + 1];//allocate also de '\0' character
    char* smallest_chi_decription = new char[strlen(cipher) + 1];

    float minn_distance, distance;

    minn_distance = chi_square_distance(string_distribution(cipher), alphabet_letters_frequency);
    for (int nr_shifts = 1; nr_shifts < 26; nr_shifts++) {
        for (int cipher_letter_index = 0; cipher_letter_index < strlen(cipher) + 1; cipher_letter_index++)
            if (cipher[cipher_letter_index] <= 'z' && cipher[cipher_letter_index] >= 'a')
                trial_decription[cipher_letter_index] = convertLowerCase(cipher[cipher_letter_index], nr_shifts);
            else if (cipher[cipher_letter_index] <= 'Z' && cipher[cipher_letter_index] >= 'A')
                trial_decription[cipher_letter_index] = convertUpperCase(cipher[cipher_letter_index], nr_shifts);
            else
                trial_decription[cipher_letter_index] = cipher[cipher_letter_index];

        distance = chi_square_distance(string_distribution(trial_decription), alphabet_letters_frequency);
        if (distance <= minn_distance) {
            minn_distance = distance;
            strcpy(smallest_chi_decription, trial_decription);
        }
    }
    if (minn_distance != chi_square_distance(string_distribution(cipher), alphabet_letters_frequency))
    {
        return smallest_chi_decription;
    }

    else
        return cipher;


}
void print_menu() {
    cout << endl;
    cout << "1. Get the frequency of letters in the English alphabet (the frequency of the letter 'a' is stored on the first position, of 'b' on the second etc...)" << endl;
    cout << "2. Get the normal frequency of letters from a text " << endl;
    cout << "3. Compute the Chi-square distance between the histogram of your text and the one of the English alphabet." << endl;
    cout << "4. Break the Caesar s cipher of your text." << endl;
    cout << "5. STOP" << endl;
    cout << "Read option: ";
    cout << endl;
}


int main() {

    float* alphabet_letters_frequency = new float[26];
    char* cipher_string = new char[600];
    float* cipher_letters_frequency = new float[26];
    ifstream f("distribution.txt");
    // menu-based interface
    bool stop = false;
    int option;
    cout << "The options should be red in order!" << endl;
    while (stop == false) {
        print_menu();
        cin >> option;
        if (option == 1) {
            alphabet_letters_frequency = alphabet_distribution(f);
            for (int alphabet_letter_index = 0; alphabet_letter_index < 26; alphabet_letter_index++)
                cout << alphabet_letters_frequency[alphabet_letter_index] << " ";
            cout << endl;
        }
        else if (option == 2) {
            cin.ignore();
            //s=new char[600];
            cout << "Read a string:" << endl;
            cin.getline(cipher_string, 599);
            cipher_letters_frequency = string_distribution(cipher_string);
            for (int i = 0; i < 26; i++)
                cout << cipher_letters_frequency[i] << " ";
            cout << endl;
        }
        else if (option == 3) {
            cout << chi_square_distance(cipher_letters_frequency, alphabet_letters_frequency) << endl;
        }
        else if (option == 4) {
            cout << break_cipher(cipher_string, alphabet_letters_frequency);
        }
        else if (option == 5)
            stop = true;
        else cout << "The option does not exist!" << endl;
    }
    // freeing the memory, to avoid memory leaks
    delete[] alphabet_letters_frequency;
    delete[] cipher_letters_frequency;
    delete[] cipher_string;
    f.close();
    return 0;
}
