#ifndef _STEMMING_
#define _STEMMING_

#include <string>
using std::string;

class Stemming {
public:
   void setValues(string& word);
   bool isVowel(const string& word, const int& index) const;
   bool yVowel(const string& word, const int& index) const;
   string Region(const string& wd);
   void stepOne(string& word);
   void stepTwo(string& word);
   void stepThree(string& word);
   void stepThreeCheck(string& word, const string& suffix);
   void stepFour(string& word);
   void stepFive(string& word);
   void stepSix(string& word);
   void stepSeven(string& word);
   void stepEight(string& word);
   bool Suffix(const string& wd, const string& suffix) const;
   bool isShort(const string& wd);
   bool shortSyllable(const string& wd) const;
   bool liEnding(const char& c) const;

   // tests for stepFive
   bool seven5(string& word);
   bool six5(string& word);
   bool five5(string& word);
   bool four5(string& word);
   bool three5(string& word);
   void two5(string& word);

   // tests for stepSeven
   bool five7(string& word, string& region2);
   bool four7(string& word, string& region2);
   bool three7(string& word, string& region2);
   void two7(string& word, string& region2);

protected:
   string region1;
   string region2;

};
#endif
