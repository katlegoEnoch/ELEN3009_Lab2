#include "Word.h"
#include "Line.h"
#include "Paragraph.h"
#include "FileReader.h"

#include <string>
#include <iostream>
using namespace std;


int main()
{
    string word = "Can'&%$#$@$^**%&*t";
    
    for(string::size_type str_it = 0; str_it < word.size();str_it++){
        //if current char is punctuation
        if(ispunct(word.at(str_it))){
            //erase character from string
            word.erase(str_it,1);//erase only char pointed by str_it
            //if you do erase, move the iterator back by one
            str_it--;
        }//end if
    }//all characaters of string processed
    cout << endl;
    
    for(string::size_type i = 0; i < word.size();i++){
        cout << word.at(i);
    }
    cout << endl;
    return 0;
}