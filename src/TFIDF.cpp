#include <TFIDF.h>
#include <math.h>
#include <iostream>
#include <cmath>
#include <thread>
#include <functional>
using std::thread;
using std::cout;
using std::endl;

void countOccurance(const vector<unordered_map<string, double> >& documentMaps, vector< unordered_map<string, double> >& docIDF, const int& size, const int index) {
  unordered_map<string, double> list = documentMaps[index];
  for(auto it = list.begin(); it != list.end(); ++it ) { /* Iterate THROUGH each documentMap */
    double occurances = 0;
    const string first = it->first;
    for(int document = 0; document < size; ++document) { /* Find occurances of word in each documentMap */
      if(documentMaps[document].find(first) != documentMaps[document].end()) /* word is in doc */
        ++occurances;
    }
    list[first] = it->second * log10(size/occurances);
  }
  docIDF[index] = list;

}

bool TFIDF::computeIDF(const vector<unordered_map<string, double> >& documentMaps, const vector<buildWord>& documentVector) {
  const int size = documentMaps.size();
  vector< unordered_map<string, double> > docIDF;
  docIDF.resize(size);
  vector<thread> multiThreads;
  for(int index = 0; index < size; ++index) { /* Iterate OVER documentMap */
     /* The document in vector that will be used to check against the other documents */
    multiThreads.emplace_back(thread(countOccurance, std::ref(documentMaps), std::ref(docIDF), std::ref(size), index));
  }
  for(int index = 0; index < size; ++index) { // Join - Finished muli-threading
    if(multiThreads[index].joinable())
      multiThreads[index].join();
  }

  return computeTFIDF(docIDF, documentVector);
}

bool TFIDF::computeTFIDF(vector< unordered_map<string, double> >& docIDF, const vector<buildWord>& documentVector) const {
  const int N = docIDF.size(); /* Number of documents */
  int n = 1;
  string fileName = "";
  double previousSim = 0;
  while(N != n){
    if(lo <= documentVector[n].ColemanLiau() && documentVector[n].ColemanLiau() <= hi){
      double simularity = 0;
      for(auto it = docIDF[n].begin(); it != docIDF[n].end(); ++it) { /* Go through N */
        const string word = it->first;
        if(docIDF[0].find(word) != docIDF[n].end()) /* Is word in docVector[index-n] */
          simularity += docIDF[0][word] * docIDF[n][word];
        }
      /* Find document with highest simularity score, i.e., TFIDF*/
      if(n == 1){
        fileName = documentVector[1].getFileName();
        previousSim = simularity;
      }
      else if(simularity > previousSim){
        fileName = documentVector[n].getFileName();
        previousSim = simularity;
      }
    }
    ++n; /* Go to next document */
  }

  if(fileName.empty())
    return false;
  cout << fileName << endl;
  return true;
}
