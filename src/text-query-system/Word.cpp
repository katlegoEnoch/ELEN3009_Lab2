//File_name: Word.cpp
//Author:    Stax The Engipreneur
//Date:      04 August 2018
//Details:   To make program case-insensitive, we'll only store lower-case words. Lowercase is the standard

// -------------------------------------------
//					Word
// -------------------------------------------

#include "Word.h"

#include <locale>
using std::islower;
using std::isupper;

Word::Word(const string& word): word_{word}
{
	// throws an exception (in the form of WordContainsNoLetters object)
	// indicating that the word being constructed contains no letters
	if (word_.empty()) throw WordContainsNoLetters{};

	// Note, we will cover exceptions in more detail later on in the course.
    
    //program only constructs lowercase words
    //iterate through string and...
    for(string::size_type str_it = 0; str_it < word_.size(); str_it++){
        //if char pointed by str_it  is uppercase
        if(isupper(word_.at(str_it))){
            //convert to upper_case
            word_.at(str_it) = static_cast<char>(tolower(word_.at(str_it)));
        }//end if
        //else leave character as is - lowercase
    }//all items of string processed. All upper case letters converted to lowercase.
}

// overloads the equivalence operator which allows to Words to be compared using ==
bool Word::operator==(const Word& rhs) const
{
	if (word_ == rhs.word_)
		return true;
	else
		return false;
}

bool Word::isQueryable() const
{
	return false;
}
