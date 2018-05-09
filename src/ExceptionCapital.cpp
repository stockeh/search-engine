#include <ExceptionCapital.h>
#include <stemming.h>
#include <algorithm>

bool ExceptionCapital::containsUpperDigit(int start, string& word) const {
  for (unsigned int i = start; i < word.length(); ++i){
    if (isdigit(word[i]) || isupper(word[i])) {
      return true;
    }
  }
  return false;
}

void ExceptionCapital::resolveAmbiguity(const unordered_map<string, double>& list, string& word) const {
  // Check to see if Word appears elsewhere in list.
  if (list.find(word.substr(1, string::npos)) != list.end())
    word = word.substr(1, string::npos); // Remove the +. Meant to be capitalized
  else {
    word = word.substr(1, string::npos); // Remove the +. Not meant to be capitalized
    word[0] = tolower(word[0]);          // change to lower.
  }
}

void ExceptionCapital::iterateList(unordered_map<string, double>& list, unordered_map<string, double>& sortedList, readException& exceptionTable){
  Stemming stem;
  for(auto it = list.begin(); it != list.end(); ++it) {
    string word = it->first;
    if(word[0] == '+' && !containsUpperDigit(2, word))
        resolveAmbiguity(list, word);
    notUpperDigit = !containsUpperDigit(0, word);
    lenOfTwo = false;
    if (word.length() > 2)
        lenOfTwo = true;
    if(exceptionTable.containsKey(word) && notUpperDigit && lenOfTwo) // Found in Exception table, and able to stem.
        word = exceptionTable.getValue(word);                         // Replace word with key in exceptionFile.
    else if(notUpperDigit && lenOfTwo)
        stem.setValues(word); // STEMMING
    if(sortedList.find(word) != sortedList.end())
        sortedList[word] = it->second + sortedList[word];
    else
        sortedList.insert(std::pair<string, double>(word, it->second));
  }

}
