#include <iostream>
#include <fstream>
#include<cstring>
#include<cmath>
using namespace std;

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

float* string_distribution(const char* str) {
    float* str_arr = new float[26];
    for (int i = 0; i < 26; i++)
        str_arr[i]=0;
    for(int k=0;k<strlen(str);k++)
        if(str[k]>='a' && str[k]<='z')
          str_arr[int(str[k])-97]+=1;
        else if(str[k]>='A' && str[k]<='Z')
          str_arr[int(str[k])-65]+=1;
    return str_arr;
}
float chi_square_distance(float* arr1, float* arr2){
    float s=0.0;
    for(int i=0;i<26;i++)
        s+=((arr1[i]-arr2[i])*(arr1[i]-arr2[i]))/arr2[i];
    return s;

}
char convert1(char c, int n) {
		n = n % 26;
		return 'a' + (c - 'a' + n) % 26;



}

char convert2(char c, int n) {
		n = n % 26;
		return 'A' + (c - 'A' + n) % 26;

}
char* break_cipher(char* str, float* arr){
     char* new_str=new char[strlen(str)];
     char* new_str2=new char[strlen(str)];
     float minn_distance,distance;

     minn_distance=chi_square_distance(string_distribution(str),arr);
     for(int k=1;k<26;k++){
        for (int i = 0; i < strlen(str); i++)
            if (str[i] <= 'z' && str[i] >= 'a')
                new_str[i]= convert1(str[i], k);
            else if (str[i] <= 'Z' && str[i] >= 'A')
                new_str[i]= convert2(str[i], k);
            else
                new_str[i]=str[i];

        distance = chi_square_distance(string_distribution(new_str),arr);
        if(distance<=minn_distance){
            minn_distance=distance;
            strcpy(new_str2,new_str);
        }
     }
     if(minn_distance != chi_square_distance(string_distribution(str),arr))
        return new_str2;
     else
        return str;


}
void print_menu(){
   cout<<endl;
   cout<<"1. Get the frequency of letters in the English alphabet (the frequency of the letter 'a' is stored on the first position, of 'b' on the second etc...)"<<endl;
   cout<<"2. Get the normal frequency of letters from a text "<<endl;
   cout<<"3. Compute the Chi-square distance between the histogram of your text and the one of the English alphabet."<<endl;
   cout<<"4. Break the Caesar s cipher of your text."<<endl;
   cout<<"5. STOP"<<endl;
   cout<<"Read option: ";
   cout<<endl;
}


int main() {

    float* arr;
    char* s;
    float* str_arr;
    ifstream f("distribution.txt");

    bool stop=false;
    int option;
    cout<<"The options should be red in order!"<<endl;
    while(stop==false){
        print_menu();
        cin>>option;
        if(option==1){
            arr = alphabet_distribution(f);
            for (int i = 0; i < 26; i++)
                cout << arr[i] << " ";
            cout<<endl;
        }
        else if(option==2){
            cin.ignore();
            s=new char[600];
            cout<<"Read a string:"<<endl;
            cin.getline(s,599);
            str_arr=string_distribution(s);
            for (int i = 0; i < 26; i++)
                cout << str_arr[i] << " ";
            cout<<endl;
        }
        else if(option==3){
            cout<<chi_square_distance(str_arr,arr)<<endl;
        }
        else if(option==4){
             cout<<break_cipher(s,arr);
        }
        else if(option==5)
            stop=true;
        else cout<<"The option does not exist!"<<endl;
    }
    delete[] arr;
    delete[] str_arr;
    delete[] s;
    f.close();
    return 0;
}
