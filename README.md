# Caesars_cipher
Breaking the Caesar's cipher from a given text

This project is constructed as a user-friendly interface application, which uses multiple functions to 
break the Caesar's cipher and to do other operation related to this topic, letting the user to chose from the options.

float* alphabet_distribution(ifstream& f) {
    float* arr = new float[26];
    float x;
    int i = 0;
    while (i < 26 && f >> x) {
        arr[i] = x;
        i++;
    }
    return arr;
}

This project is very useful because we can see how a generated text can be translated in the English language, by the frequency of the letters in the English alphabet.

You can run this project by simply downloading the .rar file and running the main.cpp file in a C++ IDE.
