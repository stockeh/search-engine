/**
 * @file TFIDF.h
 * @author Jason Stock
 * @date 7 Nov 2017
 * @brief Header class for calculating term frequency
 * <br> inverse document frequency (TFIDF).
 *
 */

#ifndef TERMDOCFREQ
#define TERMDOCFREQ

#include <buildWord.h>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <string>
using std::vector;
using std::unordered_map;
using std::string;
/**
 * @brief My Term Frequency Inverse Document Frequency class.
 *
 * Calculates tfidf, and writes it to the console.
 * This takes the upper half of a matrix and uses inverse
 * to print it out.
 */
class TFIDF {
public:

   /**
     * @brief termDocFreq
     *
     * Calculates the term document frequency for each map in vector of ducuments.
     * @p documentMaps is the parameter.
     * This is a @c void function that does not return anything.
     *
     * @param documentMaps - termDocFreq takes one parameter, which is a referance to
     *                       a vector of unordered_map< </b>string, </b>double>
     * @return </b> void
     */

  bool computeIDF(const vector<unordered_map<string, double> >& documentMaps, const vector<buildWord>& documentVector);
  bool computeTFIDF(vector< unordered_map<string, double> >& docVector, const vector<buildWord>& documentVector) const;
  inline void setLoHi(const double& low, const double& high) {lo = low; hi = high;}

protected:
  // vector< unordered_map<string, double> > docIDF;
  double lo;
  double hi;

};
#endif
