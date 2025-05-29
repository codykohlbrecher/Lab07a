#include <iostream>
#include <sstream>
#include "WordCount.h"
#include "tddFuncs.h"

int main() {
    std::cout << "== Running Lab07 Tests ==" << std::endl;

    WordCount wc;
    wc.addAllWords("cat dog cat mouse dog dog ape cat");

    std::stringstream wordStream;
    wc.dumpWordsSortedByWord(wordStream);

    std::string expectedByWord = std::string("ape,1\n") + "cat,3\n" + "dog,3\n" + "mouse,1\n";

    ASSERT_EQUALS(expectedByWord, wordStream.str());

    std::stringstream countStream;
    wc.dumpWordsSortedByOccurence(countStream);

    std::string expectedByCount = std::string("cat,3\n") + "dog,3\n" + "ape,1\n" + "mouse,1\n";

    ASSERT_EQUALS(expectedByCount, countStream.str());

    return 0;
}
