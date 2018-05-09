#include <buildWord.h>
#include <ExceptionCapital.h>
#include <readException.h>
#include <iomanip>
#include <string>
using std::setprecision;
using std::endl;


bool buildWord::containsUpperDigit(const int& start){
  // If out contains another capital or digit, mark = 0.
  for (unsigned int i = start; i < out.length(); ++i){
    if (isdigit(out[i]) || isupper(out[i])) {
      return true;
    }
  }
  return false;
}

void buildWord::mark(){
  if (!containsUpperDigit(1)) { // Starts with a capital, does not contains Uppder | Digit
    if (list.empty() || containsEOS)
      out = "+" + out;
  }
}

void buildWord::setBool(const unsigned int& i, const string& word) {
  nextIsDigit = false;
  if (isdigit(word[i+1]))
    nextIsDigit = true;

  notOutOfBounds = false;
  if(i+1 < word.length())
    notOutOfBounds = true;

  isPeriod = false;
  if(word[i] == '.')
    isPeriod = true;

  isCamma = false;
  if(word[i] == ',')
    isCamma = true;
}

void buildWord::alphanumbericPAC(const string& word) {
  // Alphanumberic or (('.') || ('\'') || (','))
  for(unsigned int i = 0; (!ispunct(word[i]) || word[i] == ('.') || word[i] == (',') || word[i] == ('\'')) && i < word.length(); ++i) {
    setBool(i, word);
    // Is ! ('.' | ',' )
    if(!isPeriod && !isCamma) // If i is not a '.' && ',''
        out += (word[i]);
    else {
      // Is '.'
      if(notOutOfBounds && isPeriod && nextIsDigit) { // If i is a '.' followed by a digit
        if(i!=0) {
          if(isdigit(word[i-1])) // Is there a nuber before '.'
              out += (word[i]);
          else  // Is there something invalid before '.'
              break;
        }
        if(i==0) // White space before '.'
              out += (word[i]);
      }
      // Is ','
      if(notOutOfBounds && isCamma && nextIsDigit) { // If i is a ',' followed by a digit
        if(i!=0) {
          if(isdigit(word[i-1])) // Is there a nuber before ','
              out += (word[i]);
          else  // Is there something invalid before ','
              break;
        }
        if(i==0) // If a ',' starts a string, e.g., ",2000"
              break;
      }

      if(!nextIsDigit && (isPeriod || isCamma)) // i is a '.' and theres not a digit following, e.g., ".h"
        break;
    }
  }
}

void buildWord::punctuation(const string& word){
  for (unsigned int i = 0; ispunct(word[i]) && i < word.length(); ++i){
    if(word[i] != '\'')
      out += (word[i]);
    else break; // Not a '\''
  }
}

void buildWord::punctString(string& word){
  //  string out;
   while (word.length()){ // While there are still chars in the word.
      // Alphanumberic or (('.') || ('\'') || (','))
        alphanumbericPAC(word); // Populate out

      if (out.length()){ // If out is populated
        ++words;
        letters += out.length();

        int outLength = out.length();
        // Mark words with + if Upper case and start of sentence and not acronym or contain digit
        if (isupper(out[0]))
          mark();
        containsEOS = false;

        if(out.length()) {
          if(listContainsKey(out)) // If map already contains word
            ++list[out]; // Incriment Counter
          else
            listMapInsert(out, 1);
          word = word.substr(outLength, word.length());
          previous = out; // set previously added word to previous
          out.clear();
        }
      }

      if(word.length()){ // Parse punctuation
        // punctuation
        punctuation(word); // Populate out
        if(out.length()) {
          containsEOS = false; // Check if previous string contains '.' '!' or '?'
          for(unsigned int i = 0; i < out.length(); ++i){
            if(out[i] == '.' || out[i] == '!' || out[i] == '?')
              containsEOS = true;
            if(!ispunct(out[i])) // not a punctuation-only string
              containsEOS = false;
          }
          if(containsEOS)
            ++sentences;
          /*** DONT ADD PUNCTUATION STRINGS TO MAP
          if(listContainsKey(out)) // If map already contains word
            ++list[out]; // Incriment Counter
          else
            listMapInsert(out, 1);
          ***/
          word = word.substr(out.length(), word.length());
          previous = out;
          out.clear();
        }
      }
   }
}

bool buildWord::Read(istream& istr, readException& exceptionTable){
   istr >> std::ws; // Clear leading white space
   string word;

   letters = 0;
   words = 0;
   sentences = 0;

   if (istr.eof()) // eofbit : End-of-File reached on input operation
      return false;

   while (istr >> word){ // if the stream has already encountered eof
      if (istr.fail())           // failbit, badbit
         return false;
      else punctString(word); // Seperate String, and add it to the vector.
   }
   /** File ends in non-eos punctuation, therefore add at least one sentence.
   if(!containsEOS)
      ++sentences; */
   if(!words)
      return false;

   ExceptionCapital exCapital;
   exCapital.iterateList(list, sortedList, exceptionTable); // Handels capitals and stemming.
   if(sortedList.empty()) // File is empty after parsing
      return false;

   return true;
}

bool buildWord::Write(ostream& ostr) const{

  ostr << setprecision(7) << ColemanLiau() << endl;

  /* Write the word and frequencies for document

  for(auto it = sortedList.begin(); it != sortedList.end(); ++it ){
    ostr << it->first << " " << it->second << endl;
  }

  */
  return true;
}
