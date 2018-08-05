// -------------------------------------------
//					Paragraph
// -------------------------------------------

#include "Paragraph.h"

void Paragraph::addLine(const Line& line)
{
    //push line into paragraph
    paragraph_.push_back(line);
}

tuple<bool, vector<int>> Paragraph::contains(const Word& search_word) const
{
    //declare a vector of integers to return to client
    vector<int> lineNumbers;//empty vector
    //word in paragraph flag
    auto wordInParagraph = false;
    
    //for all the lines in paragraph
    for(size_t line = 0; line < paragraph_.size();line++){
        //ask line if it contains word
        if(paragraph_.at(line).contains(search_word)){
            //push line number into lineNumber vector
            lineNumbers.push_back(line+1);
            //set flag true;
            wordInParagraph = true;
        }//end if
    }//end loop
    
	return {wordInParagraph, lineNumbers};
}