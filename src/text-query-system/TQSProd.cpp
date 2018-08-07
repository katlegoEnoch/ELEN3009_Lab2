#include "Word.h"
#include "Line.h"
#include "Paragraph.h"
#include "FileReader.h"

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


int main()
{
    //declare program variables
    string fileName;
    string searchWord;
    
    //variables to store process outputs
    vector<int> lineNumbers;
    bool containsWord;
    
    //prompt user for input
    cout << "Please enter file name: ";
    cin  >>  fileName;
    
    //if file not found, exception will be thrown and will need to be caught
    auto filereader = FileReader{fileName};
    auto paragraph = Paragraph{};
    filereader.readFileInto(paragraph);
    
    do{
        //prompt user for further input
        cout << "\nPlease enter a word to search for or '.' to quit: ";
        cin  >> searchWord;
        //create word from string, query paragraph for word
        //Word will throw exception after . 'punct' is deleted
        try{
        std::tie (containsWord,lineNumbers) = paragraph.contains(Word{searchWord});
        }catch(WordContainsNoLetters){
            //do nothing
        }
        //process search results
        //using search results we can display outcome
        if(containsWord){
            //display first line
            cout << "\nWord found: line " << lineNumbers.at(0);
            //print other lines containing word
            for(string::size_type line = 1; line < lineNumbers.size();line++){
                cout << "\n" <<setw(17) << "Line " << lineNumbers.at(line);
            }//end for loop
            cout << endl;
        }//end if
        else
            cout << "\nWord not found" << endl;
    }while(searchWord != ".");
    
    
    return 0;
}