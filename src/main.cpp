#include <buildWord.h>
#include <readException.h>
#include <TFIDF.h>
#include <thread>
#include <functional>


using std::istringstream;
using std::thread;
using std::cout;
using std::cerr;
using std::endl;
/* Used for Search Query - argv[0] */
void buildDocumentsArgs(buildWord& document, const char* arguments, int& minusOne, readException& exceptionTable){
  ifstream istr(arguments);
  if (istr.fail()) {
    cerr << "Could not open argument: " << endl;
    minusOne = -1;
  }

  if(!document.Read(istr, exceptionTable)) {
    cerr << "Input file contains errors or is empty" << endl;
    minusOne = -1;
  }
}

void buildDocuments(buildWord& document, string& inputFile, int& minusOne, readException& exceptionTable){
  ifstream istr(inputFile);
  if(!istr.is_open()) {
    cerr << "Couldnt open string file." << endl;
    minusOne = -1;
  } else {
    if (istr.fail()) {
      cerr << "Could not open argument: " << endl;
      minusOne = -1;
    }
    document.setFileName(inputFile);
    if(!document.Read(istr, exceptionTable)) {
      cerr << "Input file contains errors or is empty" << endl;
      minusOne = -1;
    }
    istr.close();
  }
}

int main(int argc, char const *argv[]) {
  if(argc != 5) {
    cerr << "Must have 5 arguments, i.e., PA8 queryFile libraryFile loInt hiInt" << endl;
    return -1;
  }

  istringstream readinglo(argv[3]);
  istringstream readinghi(argv[4]);

  double lo;
  double hi;

  readinglo >> lo;
  readinghi >> hi;
  if(readinglo.fail() || readinghi.fail()){
    cerr << "reading level range can't be read" << endl;
    return -1;
  }

  if(lo > hi){ // lo cant be greater than hi
    cerr << "lo cant be greater than hi" << endl;
    return -1;
  }
  /** Read in file names from argv[2] */
  vector<string> stringFiles;
  ifstream lib(argv[2]);

  if (lib.fail()) {
    cerr << "Could not open argument: " << endl;
    return -1;
  }
  lib >> std::ws; // Clear leading white space
  string inputFile;
  if (lib.eof()){
    cerr << "eofbit : End-of-File reached on input operation" << endl;
    return -1;
 }
  while (lib >> inputFile){
     if (lib.fail()){
       cerr << "// failbit, badbit" << endl;
       return -1;
     }
     else stringFiles.emplace_back(inputFile); // Add name of files to vector. [0] holds exceptionFile.
  }

  /** Done reading filenames from argv[2]
  *   -- Now reading exceptionTable --
  */

  readException exceptionTable;
  ifstream estr(stringFiles[0]);

  if(!estr.is_open()) {
    cerr << "Couldnt open exception string file." << endl;
    return -1;
  }

  if (estr.fail()) {
    cerr << "Could not open exception file" << endl;
    return -1;
  }

  if(!exceptionTable.Read(estr)) {
    cerr << "Exception file contains errors" << endl;
    return -1;
  }
  estr.close();

  vector<unordered_map<string, double> > documentMaps;
  vector<buildWord> documentVector(stringFiles.size(), buildWord());
  vector<thread> muliThreads;
  int minusOne = 0;

  for(unsigned int index = 0; index < stringFiles.size(); ++index) { // Start muli-threading
    if(index == 0)
      muliThreads.emplace_back(thread(buildDocumentsArgs, std::ref(documentVector.at(index)), argv[1], std::ref(minusOne), std::ref(exceptionTable)));
    else
    muliThreads.emplace_back(thread(buildDocuments, std::ref(documentVector.at(index)), std::ref(stringFiles[index]), std::ref(minusOne), std::ref(exceptionTable)));
  }

  for(unsigned int index = 0; index < stringFiles.size(); ++index) { // Join - Finished muli-threading
    if(muliThreads[index].joinable())
      muliThreads[index].join();
  }

  if(minusOne) // Exception was found during muli-threading
    return -1;

  vector<string> newdocumentVector;
  for(unsigned int index = 0; index < stringFiles.size(); ++index){ // Get Maps from each document
    documentMaps.emplace_back(documentVector[index].getMap());
  }

  TFIDF calculate;
  calculate.setLoHi(lo, hi);
  if(!calculate.computeIDF(documentMaps, documentVector)){  // Calculate TFIDF score, print most relevent document.
    cerr << "There are no documents within the Coleman-Liau index." << endl;
    return -1;
  }
  return 0;
}
