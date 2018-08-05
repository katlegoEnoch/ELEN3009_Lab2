// -------------------------------------------
//					Line
// -------------------------------------------

#include "Line.h"

//we'll construct a set of Words from a string
Line::Line(const string& line)
{
	// Hint: some of string's member functions might come in handy here
	// for extracting words.
    string wordString;
    int loc;
    //make a copy of the string
    auto temp = line;
    
    //if(line.empty()) throw LineContainsNoWords{};
    
    //we'll keep deleting words on the string
    //only process line with words
    if(!line.empty()){
        do{
            //search for first occurence of ' '
            loc = temp.find(' ');
            //assign all characters to left of loc to word
            wordString.assign(temp,0,loc);
            //construct word object from word string and..
            //push word into line container
            line_.push_back(Word{wordString});
            //erase all characters up to ' '
            temp.erase(0,loc+1);
        }while(loc != -1);
    }//end if
    else//if line is empty push
        line_.clear();
        
}

bool Line::contains(const Word& search_word) const
{
    //only process queryable words
    if(search_word.isQueryable()){
        //iterate through line an search for word
        for(size_t word = 0; word < line_.size(); word++){
            //compare search word to words in line's memory
            if(line_.at(word) == search_word){
                //return true reply
                return true;
            }//end if
        }//all words in line processed
    }//end if
    else//if word is no queryable
        return false;
    
    //if none of Words in line match search word
	return false;
}
