#include "Word.h"
#include "Line.h"
#include "Paragraph.h"
#include "FileReader.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

const auto PUNCTUATION = "~`!@#$%^&*()-_+={}[]\\|:;'<>?,./\""s;
const auto UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"s;
const auto LOWERCASE = "abcdefghijklmnopqrstuvwxyz"s;
const auto MIN_SIZE_FOR_QUERY = 3;

// ------------- Tests for Word ----------------

// Test the null case first - cannot have an empty word
// These assertion types (CHECK_THROWS_AS, CHECK, CHECK_FALSE) are described in the doctest reference:
// https://github.com/onqtam/doctest/blob/master/doc/markdown/assertions.md
// Also see further examples at:
// https://github.com/onqtam/doctest/blob/master/examples/all_features/assertion_macros.cpp

TEST_CASE("Empty Word cannot be created") {	 
    CHECK_THROWS_AS(Word{""}, WordContainsNoLetters);
}

TEST_CASE("Identical Words are equal") {
    CHECK(Word{"that"} == Word{"that"});    
}

TEST_CASE("Non-identical Words are not equal") {
	CHECK_FALSE(Word{"this"} == Word{"that"});
}

// --------

TEST_CASE("Case is ignored when comparing Words") {
	CHECK(Word{LOWERCASE} == Word{UPPERCASE});
}
//
TEST_CASE("Punctuation is ignored when comparing Words") {
	auto word_with_punct = Word{PUNCTUATION + "hel" + PUNCTUATION + "lo" + PUNCTUATION};
	auto word_without_punct = Word{"hello"};
	CHECK(word_without_punct == word_with_punct);
}
//
TEST_CASE("Word cannot consist solely of punctuation") {
	CHECK_THROWS_AS(Word{"!@#$%"}, WordContainsNoLetters);
}
//
TEST_CASE("Word cannot contain a space") {
	CHECK_THROWS_AS(Word{"hello there"}, WordContainsSpace);
}

/*The next two examples illustrate how to test for alternatives instead of including if statements in cases*/

//
TEST_CASE("Word is queryable if greater than or equal to a specific size") {
	auto test_string = ""s;
	test_string.resize(MIN_SIZE_FOR_QUERY, 'a');
	auto test_word = Word{test_string};
	CHECK(test_word.isQueryable());
}
//
TEST_CASE("Word is not queryable if less than a specific size") {
// Write this test...
    //create a small string
    auto smallString = ""s;
    smallString.resize(MIN_SIZE_FOR_QUERY-1,'a');
    //construct a word from the string
    auto smallWord = Word{smallString};
    //ask if the word constructed is queryable, assert that it's not
    CHECK_FALSE(smallWord.isQueryable());
    
}

// ------------- Tests for Line ----------------
//
//// Test null case for contains() first - here, an empty line
TEST_CASE("Word cannot be found in empty Line") {
   auto line = Line{""};  
   CHECK_FALSE(line.contains(Word{"hello"}));
}
//
TEST_CASE("Word can be found in a Line with a single Word") {
	auto line = Line{"Stop"};
	CHECK(line.contains(Word{"Stop"}));
}
//
//// It is always good to write tests which test boundary conditions
TEST_CASE("First and last Words in a Line can be found") {
	auto line = Line{"Walking on water and developing software from a specification are easy if both are frozen."};
	CHECK(line.contains(Word{"Walking"}));
	CHECK(line.contains(Word{"frozen"}));
}
//
//// Test not only success scenarios but also failure scenarios.
TEST_CASE("Word not in a Line cannot be found") {
	auto line = Line{"I have always wished for my computer to be as easy to use as my telephone; my wish has come true because I can no longer figure out how to use my telephone."};	
	CHECK_FALSE(line.contains(Word{"cellphone"}));
}
//
TEST_CASE("Words are found irrespective of case") {
	auto line = Line{"You can stand on the shoulders of giants or a BIG enough pile of dwarfs, works either way."};	
	CHECK(line.contains(Word{"big"}));	
	CHECK(line.contains(Word{"STAND"}));
}
//
TEST_CASE("Words are found irrespective of surrounding punctuation") {
	auto line = Line{"How can you tell if a person is a programmer? They use nested parentheses in normal writing (at least I do (sometimes))."};
	CHECK(line.contains(Word{"programmer"}));	
	CHECK(line.contains(Word{"sometimes"}));
}
//
TEST_CASE("Word which is not queryable cannot be found") {
   auto line = Line{"Any fool can write code that a computer can understand. Good programmers write code that humans can understand."};   
   CHECK_FALSE(line.contains(Word{"a"}));
}

// ------------- Tests for Paragraph ----------------

//TEST_CASE("Word cannot be found in empty Paragraph") {
//}
//
TEST_CASE("Word not present in Paragraph cannot be found"){
    //declare bool and vector hold tuple returns
    bool wordInParagraph;
    vector<int> lineNumbers;
    //create paragraph object
    Paragraph paragraph;
    //create Line objects from fake lines
    auto line1 = Line{"Any fool can write code that a computer can understand. Good programmers write code that humans can understand."};
    auto line2 = Line{"How can you tell if a person is a programmer? They use nested parentheses in normal writing (at least I do (sometimes))."};
    //add lines to paragraph
    paragraph.addLine(line1);
    paragraph.addLine(line2);
    //ask paragraph if it contains word
    std::tie (wordInParagraph,lineNumbers) = paragraph.contains(Word{"katlego"});
    CHECK_FALSE(wordInParagraph);
}
//
TEST_CASE("Line number of a Word appearing once in Paragraph is returned") {
    //create bool and vector to hold function returns
    bool wordInParagraph;
    vector<int> lineNumbers;
    //create parapraph object
    Paragraph paragraph;
    //create lines from strings
    auto line1 = Line{"I have always wished for my computer to be as easy to use as my telephone; my wish has come true because I can no longer figure out how to use my telephone."};	
    auto line2 = Line{"Walking on water and developing software from a specification are easy if both are frozen."};
    //add lines to paragraph
    paragraph.addLine(line1);
    paragraph.addLine(line2);
    //ask paragraph if it contains word 'computer'
    std::tie (wordInParagraph,lineNumbers) = paragraph.contains(Word{"computer"});
    //assert that word is found in line number 1
    CHECK(lineNumbers.at(0) == 1);
    //ask paragraph if it contains word 'specification'
    std::tie (wordInParagraph,lineNumbers) = paragraph.contains(Word{"specification"});
    //asset that word if found in line number 2
    CHECK(lineNumbers.at(0) == 2);
}
//
TEST_CASE("Line numbers of a Word appearing in multiple Lines of a Paragraph is returned") {
    //create bool and vector to hold function returns
    bool wordInParagraph;
    vector<int> lineNumbers;
    //create parapraph object
    Paragraph paragraph;
    //create lines from strings
    auto line1 = Line{"I have always wished for my computer to be as easy to use as my telephone; my wish has come true because I can no longer figure out how to use my telephone."};	
    auto line2 = Line{"Walking on water and developing software on a computer from a specification are easy if both are frozen."};
    auto line3 = Line{"It shouldn't take a week to complete this exercise."};
    auto line4 = Line{"A computer is only as intelligent as the person using it."};
    //add lines to paragraph
    paragraph.addLine(line1);
    paragraph.addLine(line2);
    paragraph.addLine(line3);
    paragraph.addLine(line4);
    
    //ask paragraph if it contains word 'computer'
    std::tie (wordInParagraph,lineNumbers) = paragraph.contains(Word{"computer"});
    //assert that word is found in line 1, 2 and 4
    CHECK(lineNumbers.at(0) == 1);
    CHECK(lineNumbers.at(1) == 2);
    CHECK(lineNumbers.at(2) == 4);
}
//
TEST_CASE("Line numbers returned account for an empty Line") {
    //create bool and vector to hold function returns
    bool wordInParagraph;
    vector<int> lineNumbers;
    //create parapraph object
    Paragraph paragraph;
    //create lines from strings
    auto emptyline = Line{""};
    auto line1 = Line{"A computer is only as intelligent as the person using it."};
    //add lines to paragraph
    paragraph.addLine(emptyline);
    paragraph.addLine(line1);
    // If the first line of the paragraph is empty, and the word being searched for
    // is on the second line, the vector returned should be: [2]
    //ask paragraph if it contains word 'computer'
    std::tie (wordInParagraph,lineNumbers) = paragraph.contains(Word{"computer"});
    //assert that word is found in line 2 and not 1
    CHECK(lineNumbers.at(0) == 2);
    
}
//
//// Integration test - both Paragraph and File Reader are tested together
//TEST_CASE("File can be read into Paragraph and successfully searched") {
//	// make sure that alice.txt is in the right location for this to work!
//	// it must be in the same directory as the executable
//	auto filereader = FileReader{"alice.txt"};
//	auto paragraph = Paragraph{};
//	filereader.readFileInto(paragraph);
//
//	auto[found, line_numbers] = paragraph.contains(Word{"Daddy"});
//
//	CHECK(found);
//	CHECK(vector<int>{1,4,6} == line_numbers);
//}
