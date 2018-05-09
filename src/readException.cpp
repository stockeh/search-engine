#include <readException.h>

bool readException::Read(ifstream& estr) {
   if (estr.eof())  // eofbit : End-of-File reached on input operation
      return false;

   string line;
   string first;
   string second;
   string third;

   while (std::getline(estr, line)){
     estr >> std::ws;
     if(!line.empty()){
       if (estr.fail())          // failbit, badbit
          return false;
       istringstream iss(line);
       if (!(iss >> first >> second))
          return false; // too few words in line
       if (iss >> third)
          return false; // too many words in line
       exceptoinMapInsert(first, second);
      }
    }

   return true;
}
