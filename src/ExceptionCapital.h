#ifndef EXCEPTIONCAPITAL
#define EXCEPTIONCAPITAL

#include <string>
#include <vector>
#include <readException.h>
#include <map>
#include <unordered_map>
using std::unordered_map;
using std::map;
using std::vector;
using std::string;

class ExceptionCapital {
public:
  void iterateList(unordered_map<string, double>& list, unordered_map<string, double>& sortedList, readException& exceptionTable);
  bool containsUpperDigit(int start, string& word) const;
  void resolveAmbiguity(const unordered_map<string, double>& list, string& word) const;

protected:
  bool notUpperDigit;
  bool indexTwoNotUpperDigit;
  bool lenOfTwo;

};
#endif
