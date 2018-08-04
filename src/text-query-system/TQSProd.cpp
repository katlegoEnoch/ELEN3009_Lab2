#include "Word.h"
#include "Line.h"
#include "Paragraph.h"
#include "FileReader.h"

#include <string>
#include <iostream>
using namespace std;


int main()
{
    string temp = "This is a simple sentence with a few words in it";
    string wordString;
    int loc;
    //construct Word from string
    //we'll keep deleting words on the string
    do{
        //search for first occurence of ' '
        loc = temp.find(' ');
        //assign all characters to left of loc to word
        wordString.assign(temp,0,loc);
        //construct word object from word string and..
        cout << wordString << endl;
        //push word into line container
        //line_.push_back(Word{wordString});
        //erase all characters up to ' '
        temp.erase(0,loc+1);
        //cout << temp << endl;
        
        //loc = temp.find(' ');
        //cout << loc << endl;
    }while(loc != -1);

    
    //for(string::size_type i = 0; i < word.size();i++){
      //  cout << word.at(i);
    //}
    //cout << endl;
    return 0;
}