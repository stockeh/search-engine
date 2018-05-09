#include <stemming.h>

bool Stemming::yVowel(const string& word, const int& index) const{
  if(word[index+1] != 'y' && index == 0) return true; // cahnged from false to true
  char c = word[index];
  if(c == 'y')
    return isVowel(word, index-1);
  if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
    return false;
  else return true;
}

bool Stemming::isVowel(const string& word, const int& index) const{
  if(index == -1) return true;
  char c = word[index]; // Grab char at index
  if((c == 'y') && index == 0) // 'y' is first letter in word.
    return false;
  if(c == 'y') // recursivly check if it follows a vowel or not
    return yVowel(word, index-1); // true if does not follow vowel
  else
   return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool Stemming::shortSyllable(const string& wd) const{
  if(wd.length() > 2){ // ends with non-vowel followed by vowel followed by non-vowel that is not 'w' | 'x' | 'y'
    if (!isVowel(wd, wd.length() - 3) && isVowel(wd, wd.length() - 2) && !isVowel(wd, wd.length() - 1)) {
           if(wd[wd.length() - 1] == 'w' || wd[wd.length() - 1] == 'x' || wd[wd.length() - 1] == 'y')
             return false; // It ends with 'w' || 'x' || 'y'
           else
             return true; // It does NOT ends with 'w' || 'x' || 'y'
    }
    else return false; // it just isnt a shortSyllable
  }
  else if(wd.length() == 2) // two character string, vowel followed by non-vowel
    return isVowel(wd, wd.length() - 2) && !isVowel(wd, wd.length() - 1);
  else return false; // it just isnt a shortSyllable
}

bool Stemming::isShort(const string& wd){
  region1 = Region(wd);
  return shortSyllable(wd) && region1.empty();
}

bool Stemming::liEnding(const char& c) const{
   return c == 'c' || c == 'd' || c == 'e' || c == 'g' || c == 'h'
          || c == 'k' || c == 'm' || c == 'n' || c == 'r' || c == 't';
}

string Stemming::Region(const string& wd){
   // Region1(definition) is inition.
  unsigned int start = 0;
  bool isY = false;

  if (wd.length() > 2){
    if(wd[0] == 'y' && !region1.empty())
      isY = true;
    for (unsigned index = 1; index < wd.length(); ++index){
      if (!isVowel(wd, index) && (isVowel(wd, index - 1) || isY)){
        start = index + 1;
          break;
      }
    }
  }
  if (start)
    return wd.substr(start, string::npos); // start to end of string
  return "";
}

bool Stemming::Suffix(const string& wd, const string& suffix) const{
   return wd.length() >= suffix.length() &&
          wd.compare(wd.length() - suffix.length(), suffix.length(), suffix) == 0;
}

void Stemming::stepOne(string& word){
  if(word[0] == '\'')
    word = word.substr(1, string::npos);
  if(Suffix(word, "\'s\'"))
    word = word.substr(0, word.length()-3);
  else if(Suffix(word, "\'s"))
    word = word.substr(0, word.length()-2);
  else if(Suffix(word, "\'"))
    word = word.substr(0, word.length()-1);
}

void Stemming::stepTwo(string& word){
  if(Suffix(word, "sses")) // Replace with ss
    word = word.substr(0, word.length()-2);
  else if(Suffix(word, "ied") || Suffix(word, "ies")){
    if(word.length() > 4)
      word = word.substr(0, word.length()-2);
    else
      word = word.substr(0, word.length()-1);
  }
  else if(Suffix(word, "us"))
    word = word.substr(0, word.length()-2) + "us";
  else if(Suffix(word, "ss"))
    word = word.substr(0, word.length()-2) + "ss";
  else if(word.length() > 1)
  if(Suffix(word, "s")){
    bool containsVowel = false;
      for(unsigned index = 0; index < word.length() - 2; ++index){
        if(isVowel(word, index)){
          containsVowel = true;
          break;
        }
      }
    if(containsVowel)
      word = word.substr(0, word.length() - 1);
  }
}

void Stemming::stepThree(string& word){

  if(Suffix(word, "eedly")){
    region1 = Region(word);
    if(region1.find("eedly",0) != string::npos)
      word = word.substr(0, word.length()-3);
    region1 = "";
  }
  else if(Suffix(word, "ingly"))
    stepThreeCheck(word, "ingly");
  else if(Suffix(word, "edly"))
    stepThreeCheck(word, "edly");
  else if(Suffix(word, "eed")){
    region1 = Region(word);
    if(region1.find("eed",0) != string::npos)
      word = word.substr(0, word.length()-1);
    region1 = "";
  }
  else if(Suffix(word, "ing"))
    stepThreeCheck(word, "ing");
  else if(Suffix(word, "ed"))
    stepThreeCheck(word, "ed");

}

void Stemming::stepThreeCheck(string& word, const string& suffix){
   string pre           = word.substr(0, word.length() - suffix.length()); // preceder
   bool   containsVowel = false;

   for (unsigned index = 0; index < pre.length(); ++index){
      if (isVowel(pre, index)){
         containsVowel = true;
         break;
      }
   }
   if (containsVowel){
      if (Suffix(pre, "at") || Suffix(pre, "bl") || Suffix(pre, "iz"))
         word = word.substr(0, pre.length()) + "e";
      else if (Suffix(pre, "bb") || Suffix(pre, "dd") || Suffix(pre, "ff")
               || Suffix(pre, "gg") || Suffix(pre, "mm") || Suffix(pre, "nn")
               || Suffix(pre, "pp") || Suffix(pre, "rr") || Suffix(pre, "tt"))
         word = word.substr(0, pre.length() - 1);
      else if (isShort(pre))
         word = word.substr(0, pre.length()) + "e";
      else
         word = word.substr(0, pre.length());
   }
}

void Stemming::stepFour(string& word){
  if(Suffix(word, "y") && word.length() > 2 && !isVowel(word, word.length()-2))
    word = word.substr(0, word.length() - 1) + "i";
}

// Begin tests for stepFive
bool Stemming::seven5(string& word){
  if(Suffix(word, "ization")){
    word = word.substr(0, word.length() - 5) + "e";
    return true; }
  else if(Suffix(word, "ational")){
    word = word.substr(0, word.length() - 5) + "e";
    return true; }
  else if(Suffix(word, "fulness")){
    word = word.substr(0, word.length() - 4);
    return true; }
  else if(Suffix(word, "ousness")){
    word = word.substr(0, word.length() - 4);
    return true; }
  else if(Suffix(word, "iveness")){
    word = word.substr(0, word.length() - 4);
    return true; }
  return false;
}

bool Stemming::six5(string& word){
  if(Suffix(word, "tional")){
    word = word.substr(0, word.length() - 2);
    return true; }
  else if(Suffix(word, "biliti")){
    word = word.substr(0, word.length() - 5) + "le";
    return true; }
  else if(Suffix(word, "lessli")){
    word = word.substr(0, word.length() - 2);
    return true; }
  return false;
}

bool Stemming::five5(string& word){
  if(Suffix(word, "entli")){
    word = word.substr(0, word.length() - 2);
    return true; }
  else if(Suffix(word, "ation")){
    word = word.substr(0, word.length() - 3) + "e";
    return true; }
  else if(Suffix(word, "alism")){
    word = word.substr(0, word.length() - 3);
    return true; }
  else if(Suffix(word, "aliti")){
    word = word.substr(0, word.length() - 3);
    return true; }
  else if(Suffix(word, "ousli")){
    word = word.substr(0, word.length() - 2);
    return true; }
  else if(Suffix(word, "iviti")){
    word = word.substr(0, word.length() - 3) + "e";
    return true; }
  else if(Suffix(word, "fulli")){
    word = word.substr(0, word.length() - 2);
    return true; }
  return false;
}

bool Stemming::four5(string& word){
  if(Suffix(word, "enci")){
    word = word.substr(0, word.length() - 1) + "e";
    return true; }
  else if(Suffix(word, "anci")){
    word = word.substr(0, word.length() - 1) + "e";
    return true; }
  else if(Suffix(word, "abli")){
    word = word.substr(0, word.length() - 1) + "e";
    return true; }
  else if(Suffix(word, "izer")){
    word = word.substr(0, word.length() - 1);
    return true; }
  else if(Suffix(word, "ator")){
    word = word.substr(0, word.length() - 2) + "e";
    return true; }
  else if(Suffix(word, "alli")){
    word = word.substr(0, word.length() - 2);
    return true; }
  return false;
}

bool Stemming::three5(string& word){
  if(Suffix(word, "bli")){
    word = word.substr(0, word.length() - 1) + "e";
    return true; }
  else if(Suffix(word, "logi")){ // Suffix preceded by l
    word = word.substr(0, word.length() - 1);
    return true; }
  else if(Suffix(word, "bli")){
    word = word.substr(0, word.length() - 1) + "e";
    return true; }
  return false;
}

void Stemming::two5(string& word){
  if(Suffix(word, "li")) {
    if(word.length() > 2){
      if(liEnding(word[word.length() - 3]))
        word = word.substr(0, word.length() - 2);
    }
  }
}

void Stemming::stepFive(string& word){
  char c = word.back();
  int length = word.length();
  if((c == 'n' || c == 'l' || c == 's') && length >= 7) {
    if(seven5(word))
      return;
  }
  if((c == 'i' || c == 'l') && length >= 6) {
    if(six5(word))
      return;
  }
  if((c == 'n' || c == 'i' || c == 'm') && length >= 5) {
    if(five5(word))
      return;
  }
  if((c == 'i' || c =='r') && length >= 4) {
    if(four5(word))
      return;
  }
  if((c == 'i') && length >= 3) {
    if(three5(word))
      return;
  }
    two5(word); // Preceder ends in a valid liEnding
}

// StepSix
void Stemming::stepSix(string& word){
  region1 = Region(word);
  region2 = Region(region1);
  if(Suffix(word, "ational")){
    if(region1.find("ational",0) != string::npos)
      word = word.substr(0, word.length() - 7) + "ate";
  }
  else if(Suffix(word, "tional")){
    if(region1.find("tional",0) != string::npos)
      word = word.substr(0, word.length() - 2);
  }
  else if(Suffix(word, "alize")){
    if(region1.find("alize",0) != string::npos)
      word = word.substr(0, word.length() - 3);
  }
  else if(Suffix(word, "ative")){
    if(region2.find("ative",0) != string::npos)
      word = word.substr(0, word.length() - 5);
  }
  else if(Suffix(word, "icate")){
    if(region1.find("icate",0) != string::npos)
      word = word.substr(0, word.length() - 3);
  }
  else if(Suffix(word, "iciti")){
    if(region1.find("iciti",0) != string::npos)
      word = word.substr(0, word.length() - 3);
  }
  else if(Suffix(word, "ical")){
    if(region1.find("ical",0) != string::npos)
      word = word.substr(0, word.length() - 2);
  }
  else if(Suffix(word, "ness")){
    if(region1.find("ness",0) != string::npos)
      word = word.substr(0, word.length() - 4);
  }
  else if(Suffix(word, "ful")){
    if(region1.find("ful",0) != string::npos)
      word = word.substr(0, word.length() - 3);
  }

  region1 = "";
  region2 = "";
}

// Begin tests for stepSeven
bool Stemming::five7(string& word, string& region2){
  if(Suffix(word, "ement")){
    if(region2.find("ement",0) != string::npos)
      word = word = word.substr(0, word.length() - 5);
    return true;
  }
  return false;
}

bool Stemming::four7(string& word, string& region2){
  if(Suffix(word, "ance")){
    if(region2.find("ance",0) != string::npos)
      word = word = word.substr(0, word.length() - 4);
    return true;
  }
  else if(Suffix(word, "ence")){
    if(region2.find("ence",0) != string::npos)
      word = word = word.substr(0, word.length() - 4);
    return true;
  }
  else if(Suffix(word, "able")){
    if(region2.find("able",0) != string::npos)
      word = word = word.substr(0, word.length() - 4);
    return true;
  }
  else if(Suffix(word, "ible")){
    if(region2.find("ible",0) != string::npos)
      word = word = word.substr(0, word.length() - 4);
    return true;
  }
  else if(Suffix(word, "ment")){
    if(region2.find("ment",0) != string::npos)
      word = word = word.substr(0, word.length() - 4);
    return true;
  }
  return false;
}

bool Stemming::three7(string& word, string& region2){
  if(Suffix(word, "ant")){
    if(region2.find("ant",0) != string::npos)
      word = word = word.substr(0, word.length() - 3);
    return true;
  }
  else if(Suffix(word, "ent")){
    if(region2.find("ent",0) != string::npos)
      word = word = word.substr(0, word.length() - 3);
    return true;
  }
  else if(Suffix(word, "ism")){
    if(region2.find("ism",0) != string::npos)
      word = word = word.substr(0, word.length() - 3);
    return true;
  }
  else if(Suffix(word, "ate")){
    if(region2.find("ate",0) != string::npos)
      word = word = word.substr(0, word.length() - 3);
    return true;
  }
  else if(Suffix(word, "iti")){
    if(region2.find("iti",0) != string::npos)
      word = word = word.substr(0, word.length() - 3);
    return true;
  }
  else if(Suffix(word, "ous")){
    if(region2.find("ous",0) != string::npos)
      word = word = word.substr(0, word.length() - 3);
    return true;
  }
  else if(Suffix(word, "ive")){
    if(region2.find("ive",0) != string::npos)
      word = word = word.substr(0, word.length() - 3);
    return true;
  }
  else if(Suffix(word, "ize")){
    if(region2.find("ize",0) != string::npos)
      word = word = word.substr(0, word.length() - 3);
    return true;
  }
  else if(Suffix(word, "ion")){ // suffix in R2 and preceder end in s
    if(region2.find("ion",0) != string::npos){ // and length > 4
      if((word[word.length()-4] == 's') || (word[word.length()-4] == 't'))
        word = word = word.substr(0, word.length() - 3);
    }
  }
  return false;
}

void Stemming::two7(string& word, string& region2){
  if(Suffix(word, "al")){
    if(region2.find("al",0) != string::npos)
      word = word = word.substr(0, word.length() - 2);
  }
  else if(Suffix(word, "er")){
    if(region2.find("er",0) != string::npos)
      word = word = word.substr(0, word.length() - 2);
  }
  else if(Suffix(word, "ic")){
    if(region2.find("ic",0) != string::npos)
      word = word = word.substr(0, word.length() - 2);
  }
}

void Stemming::stepSeven(string& word){
  region1 = Region(word);
  region2 = Region(region1);
  char c = word.back();
  int length = word.length();
  if((c == 't') && length >= 5) {
    if(five7(word, region2))
      return;
  }
  if((c == 'e' || c == 't') && length >= 4) {
    if(four7(word, region2))
      return;
  }
  if((c == 't' || c == 'm' || c == 'e' || c == 'i' || c == 's' || c == 'n') && length >= 3) {
    if(three7(word, region2))
      return;
  }
    two7(word, region2);

  region1 = "";
  region2 = "";
}

void Stemming::stepEight(string& word){
  region1 = Region(word);
  region2 = Region(region1);
  if(Suffix(word, "e")){
    if(region2.find("e",0) != string::npos) // Suffix(region2, "e")
      word = word = word.substr(0, word.length() - 1);
    else if(region1.find("e",0) != string::npos) {
      if(!shortSyllable(word.substr(0, word.length() - 1))) // double check
        word = word = word.substr(0, word.length() - 1);
    }
  }
  else if(Suffix(word, "l")){
    if(region2.find("l",0) != string::npos && Suffix(word, "ll"))
      word = word = word.substr(0, word.length() - 1);
  }
  region1 = "";
  region2 = "";
}

void Stemming::setValues(string& word){
   stepOne(word);
   stepTwo(word);
   stepThree(word);
   stepFour(word);
   if(word.length() > 2)
    stepFive(word);
   stepSix(word);
   if(word.length() > 2)
    stepSeven(word);
   stepEight(word);
}
