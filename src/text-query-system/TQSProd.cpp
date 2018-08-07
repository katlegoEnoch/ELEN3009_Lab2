#include "Word.h"
#include "Line.h"
#include "Paragraph.h"
#include "FileReader.h"

#include <string>
#include <iostream>
using namespace std;


int main()
{
    //it must be in the same directory as the executable
	auto filereader = FileReader{"alice.txt"};
	auto paragraph = Paragraph{};
	filereader.readFileInto(paragraph);

    return 0;
}