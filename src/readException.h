#ifndef READEXCEPTION
#define READEXCEPTION

#include <sstream>
#include <fstream>
#include <unordered_map>
using std::ifstream;
using std::string;
using std::istringstream;
using std::unordered_map;

class readException {
public:
   bool Read(ifstream& estr);

   inline void exceptoinMapInsert(const string& key, const string& val)
   { exceptionFile.insert(std::pair<string, string>(key, val)); }

   inline bool containsKey(const string& key) const { return exceptionFile.find(key) != exceptionFile.end(); }
   inline string getValue(const string& key) const { return exceptionFile.at(key); }

protected:
   unordered_map<string, string> exceptionFile;
};
#endif
