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
int p_LISA__SetNumPermutations(SEXP xp, int num_perm)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<LISA> ptr(xp);

  // invoke the function
  return ptr->SetNumPermutations(num_perm);
}

//  [[Rcpp::export]]
int p_LISA__SetNumThreads(SEXP xp, int num_threads)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<LISA> ptr(xp);

  // invoke the function
  return ptr->SetNumThreads(num_threads);
}

//  [[Rcpp::export]]
std::vector<double> p_LISA__GetLISAValues(SEXP xp)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<LISA> ptr(xp);

  return ptr->GetLISAValues();
}

//  [[Rcpp::export]]
std::vector<double> p_LISA__GetLocalSignificanceValues(SEXP xp)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<LISA> ptr(xp);

  return ptr->GetLocalSignificanceValues();
}

//  [[Rcpp::export]]
std::vector<int> p_LISA__GetClusterIndicators(SEXP xp)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<LISA> ptr(xp);

  return ptr->GetClusterIndicators();
}

//  [[Rcpp::export]]
std::vector<int> p_LISA__GetNumNeighbors(SEXP xp)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<LISA> ptr(xp);

  return ptr->GetNumNeighbors();
}

//  [[Rcpp::export]]
void p_LISA__SetSignificanceCutoff(SEXP xp, double cutoff)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<LISA> ptr(xp);

  ptr->SetSignificanceCutoff(cutoff);
}

//  [[Rcpp::export]]
double p_LISA__GetFDR(SEXP xp)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<LISA> ptr(xp);

  return ptr->GetFDR();
}

//  [[Rcpp::export]]
double p_LISA__GetBO(SEXP xp)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<LISA> ptr(xp);

  return ptr->GetBO();
}

//  [[Rcpp::export]]
std::vector<std::string> p_LISA__GetLabels(SEXP xp)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<LISA> ptr(xp);

  return ptr->GetLabels();
}

//  [[Rcpp::export]]
std::vector<std::string> p_LISA__GetColors(SEXP xp)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<LISA> ptr(xp);

  return ptr->GetColors();
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

  Rcpp::XPtr<LISA> lisa_ptr(lisa, true);
  return lisa_ptr;
}

//  [[Rcpp::export]]
SEXP p_localgeary(SEXP xp_w, NumericVector data, int permutations, double significance_cutoff, int cpu_threads, int seed)
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

  LISA* lisa = gda_localgeary(w, data, undefs, significance_cutoff, cpu_threads, permutations, seed);

  Rcpp::XPtr<LISA> lisa_ptr(lisa, true);
  return lisa_ptr;
}

//  [[Rcpp::export]]
SEXP p_localmultigeary(SEXP xp_w, Rcpp::List& data, int permutations, double significance_cutoff, int cpu_threads, int seed)
{
  // grab the object as a XPtr (smart pointer) to GeoDaWeight
  Rcpp::XPtr<GeoDaWeight> ptr(xp_w);
  GeoDaWeight* w = static_cast<GeoDaWeight*> (R_ExternalPtrAddr(ptr));

  int n = w->GetNumObs();
  std::vector<bool> undefs(n, false);
  std::vector<std::vector<double> > raw_data;
  raw_data.resize(data.size());

  for (int i=0; i< data.size(); ++i) {
    Rcpp::NumericVector& tmp = data[i];
    raw_data[i].resize(n);
    for (int j=0; j< n; ++j) {
      raw_data[i][j] = tmp[j];
      undefs[i] = undefs[i] || tmp.is_na(i);
    }
  }

  LISA* lisa = gda_localmultigeary(w, raw_data, undefs, significance_cutoff, cpu_threads, permutations, seed);

  Rcpp::XPtr<LISA> lisa_ptr(lisa, true);
  return lisa_ptr;
}


//  [[Rcpp::export]]
SEXP p_localg(SEXP xp_w, NumericVector data, int permutations, double significance_cutoff, int cpu_threads, int seed)
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

  LISA* lisa = gda_localgeary(w, data, undefs, significance_cutoff, cpu_threads, permutations, seed);

  Rcpp::XPtr<LISA> lisa_ptr(lisa, true);
  return lisa_ptr;
}
