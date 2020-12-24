// This file is used to wrap C++ classes and functions defines in RcppExports.R
// All other R script files will use this file as a bridge to C++ classes and functions
//
// Author: lixun910@gmail.com
// Changes:
// 12/23/2020 init rcpp_lisa.cpp

#include <Rcpp.h>
#include "libgeoda_src/weights/GeodaWeight.h"
#include "libgeoda_src/sa/LISA.h"
#include "libgeoda_src/gda_sa.h"

using namespace Rcpp;

//  [[Rcpp::export]]
int p_LISA__Run(SEXP xp)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<LISA> ptr(xp);

  // invoke the function
  return ptr->Run();
}

//  [[Rcpp::export]]
int p_LISA__SetPermutations(SEXP xp, int num_perm)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<LISA> ptr(xp);

  // invoke the function
  return ptr->SetPermutations(num_perm);
}

//  [[Rcpp::export]]
int p_LISA__SetThreads(SEXP xp, int num_perm)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<LISA> ptr(xp);

  // invoke the function
  return ptr->SetPermutations(num_perm);
}

//  [[Rcpp::export]]
SEXP p_localmoran(SEXP xp_w, NumericVector data, int permutations, double significance_cutoff, int cpu_threads, int seed)
{
  // grab the object as a XPtr (smart pointer) to GeoDaWeight
  Rcpp::XPtr<GeoDaWeight> ptr(xp_w);
  GeoDaWeight* w = static_cast<GeoDaWeight*> (R_ExternalPtrAddr(ptr));

  int n = data.size();
  std::vector<double> raw_data(n);
  std::vector<bool> undefs(n, false);

  for (int i=0; i< data.size(); ++i) {
    raw_data[i] = data[i];
    undefs[i] = data.is_na(i);
  }

  LISA* lisa = gda_localmoran(w, data, undefs, significance_cutoff, cpu_threads, permutations, seed);
}