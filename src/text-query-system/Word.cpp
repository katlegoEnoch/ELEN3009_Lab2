//File_name: Word.cpp
//Author:    Stax The Engipreneur
//Date:      04 August 2018
//Details:   To make program case-insensitive, we'll only store lower-case words. Lowercase is the standard

// -------------------------------------------
//					Word
// -------------------------------------------

const auto MIN_SIZE_FOR_QUERY = 3;

#include "Word.h"

//#include <locale>
//using std::islower;
//using std::isupper;

Word::Word(const string& word): word_{word}
{
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
    
    //to make our system ignore punctuation, we'll remove it from the word
    //iterate through string and...
    for(string::size_type str_it = 0; str_it < word_.size();str_it++){
        //if current char is punctuation
        if(ispunct(word_.at(str_it))){
            //erase character from string
            word_.erase(str_it,1);//erase only char pointed by str_it
            //trick: the iterator has to be moved back by 1 if we do erase a punctuation from the string
            str_it--;
        }//end if
    }//all characaters of string processed
    
    // throws an exception (in the form of WordContainsNoLetters object)
	// indicating that the word being constructed contains no letters
	if (word_.empty()) throw WordContainsNoLetters{};
    
    //to throw WordContainsSpace exception, we need to search for space and
    //iterate through word...
    for(string::size_type str_it = 0; str_it < word_.size();str_it++){
        //if current letter is space
        if(word_.at(str_it)== ' '){
            //throw exception
            throw WordContainsSpace{};
        }//end if
        //else do nothing
    }//end for loop
}

// overloads the equivalence operator which allows to Words to be compared using ==
bool Word::operator==(const Word& rhs) const
{
	if (word_ == rhs.word_)
		return true;
	else
		return false;
}

//word is queryable if it contains at least three letters
//after all that cleaning up, how long is the word now?
bool Word::isQueryable() const
{
    //if word contains fewer than 3 letters
    if(word_.size() < MIN_SIZE_FOR_QUERY)
        return false;
    else
        return true;
}
