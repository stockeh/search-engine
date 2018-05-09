#ifndef READCOUNTER
#define READCOUNTER

#include <iostream>
#include <vector>
#include <algorithm>
#include <readException.h>
#include <unordered_map>
#include <map>
using std::unordered_map;
using std::map;
using std::sort;
using std::istream;
using std::ostream;
using std::vector;
#include <string>
using std::string;


#include <iomanip>
using std::setprecision;
using std::fixed;
#include <iostream>
using std::cout;
using std::endl;

class buildWord{
public:
   bool Read(istream& istr, readException& execptionFile);
   bool Write(ostream& ostr) const;

   void punctString(string& word);
   void mark();
   bool containsUpperDigit(const int& start);
   void alphanumbericPAC(const string& word);
   void punctuation(const string& word);

   inline void listMapInsert(const string& key, const double& val)
   { list[key] = std::move(val); }

   inline bool listContainsKey(const string& key) const { return list.find(key) != list.end(); }
   inline double listGetValue(const string& key) const { return list.at(key); }

   inline unordered_map<string, double> getMap() const { return sortedList; }

   inline double L() const { return (letters/words)*100; }
   inline double S() const { return (sentences/words)*100; }
   inline double ColemanLiau() const { return 0.0588*L() - 0.296*S() - 15.8; }

   inline void setFileName(const string& name) { fileName = name; }
   inline string getFileName() const { return fileName; }

   void setBool(const unsigned int& i, const string& word);

protected:
   unordered_map<string, double> list;
   unordered_map<string, double> sortedList;
   string out;
   string previous;
   double letters;
   double words;
   double sentences;
   bool containsEOS;
   string fileName;

   bool nextIsDigit;
   bool notOutOfBounds;
   bool isPeriod;
   bool isCamma;

};
#endif
