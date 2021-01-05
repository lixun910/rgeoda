// This file is used to wrap C++ classes and functions defines in RcppExports.R
// All other R script files will use this file as a bridge to C++ classes and functions
//
// Author: lixun910@gmail.com
// Changes:
// 1/4/2021 init rcpp_clustering.cpp

#include <Rcpp.h>
using namespace Rcpp;

#include "libgeoda_src/gda_clustering.h"

//  [[Rcpp::export]]
double p_betweensumofsquare(Rcpp::List& solution, Rcpp::List& data)
{
  std::vector<std::vector<int> > raw_sol;
  std::vector<std::vector<double> > raw_data;

  for (int i=0; i< solution.size(); ++i) {
    Rcpp::NumericVector tmp = solution[i];
    std::vector<int> vals = as<std::vector<int> >(tmp);
    raw_sol.push_back(vals);
  }

  for (int i=0; i< data.size(); ++i) {
    Rcpp::NumericVector tmp = data[i];
    std::vector<double> vals = as<std::vector<double> >(tmp);
    raw_data.push_back(vals);
  }

  double out = gda_betweensumofsquare(raw_sol, raw_data);
  return out;
}

//  [[Rcpp::export]]
double p_totalsumofsquare(Rcpp::List& data)
{
  std::vector<std::vector<double> > raw_data;

  for (int i=0; i< data.size(); ++i) {
    Rcpp::NumericVector tmp = data[i];
    std::vector<double> vals = as<std::vector<double> >(tmp);
    raw_data.push_back(vals);
  }

  double out = gda_totalsumofsquare(raw_data);
  return out;
}

//  [[Rcpp::export]]
double p_withinsumofsquare(Rcpp::List& solution, Rcpp::List& data)
{
  std::vector<std::vector<int> > raw_sol;
  std::vector<std::vector<double> > raw_data;

  for (int i=0; i< solution.size(); ++i) {
    Rcpp::NumericVector tmp = solution[i];
    std::vector<int> vals = as<std::vector<int> >(tmp);
    raw_sol.push_back(vals);
  }

  for (int i=0; i< data.size(); ++i) {
    Rcpp::NumericVector tmp = data[i];
    std::vector<double> vals = as<std::vector<double> >(tmp);
    raw_data.push_back(vals);
  }

  double out = gda_withinsumofsquare(raw_sol, raw_data);
  return out;
}

//  [[Rcpp::export]]
Rcpp::List p_skater(int k, SEXP xp_w, Rcpp::List& data, std::string distance_method, 
                    NumericVector& bound_vals, double min_bound, int seed)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<GeoDaWeight> ptr(xp_w);
  GeoDaWeight* w = static_cast<GeoDaWeight*> (R_ExternalPtrAddr(ptr));

  std::vector<std::vector<double> > raw_data;
  for (int i=0; i< data.size(); ++i) {
    Rcpp::NumericVector tmp = data[i];
    std::vector<double> vals = as<std::vector<double> >(tmp);
    raw_data.push_back(vals);
  }

  std::vector<double> raw_bound = as<std::vector<double> >(bound_vals);
  std::vector<std::vector<int> > clusters = gda_skater(k, w, raw_data, distance_method, raw_bound, min_bound, seed);

  Rcpp::List out(clusters.size());
  for (int i=0; i< clusters.size(); ++i) {
    std::vector<int>& vals = clusters[i];
    Rcpp::NumericVector tmp_vals(vals.begin(), vals.end());
    out[i] = tmp_vals;
  }

  return out;
}

//  [[Rcpp::export]]
Rcpp::List p_redcap(int k, SEXP xp_w, Rcpp::List& data, std::string redcap_method, std::string distance_method, 
                    NumericVector& bound_vals, double min_bound, int seed)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<GeoDaWeight> ptr(xp_w);
  GeoDaWeight* w = static_cast<GeoDaWeight*> (R_ExternalPtrAddr(ptr));

  std::vector<std::vector<double> > raw_data;
  for (int i=0; i< data.size(); ++i) {
    Rcpp::NumericVector tmp = data[i];
    std::vector<double> vals = as<std::vector<double> >(tmp);
    raw_data.push_back(vals);
  }

  std::vector<double> raw_bound = as<std::vector<double> >(bound_vals);
  std::vector<std::vector<int> > clusters = gda_redcap(k, w, raw_data, redcap_method, distance_method, raw_bound, min_bound, seed);

  Rcpp::List out(clusters.size());
  for (int i=0; i< clusters.size(); ++i) {
    std::vector<int>& vals = clusters[i];
    Rcpp::NumericVector tmp_vals(vals.begin(), vals.end());
    out[i] = tmp_vals;
  }

  return out;
}

//  [[Rcpp::export]]
Rcpp::List p_maxp(SEXP xp_w, Rcpp::List& data, NumericVector& bound_vals, double min_bound,  
                  std::string local_search, int iterations, int tabu_length, int conv_tabu, 
                  double cool_rate, int sa_maxit, NumericVector& init_regions, 
                  std::string distance_method, int seed)
{
  // grab the object as a XPtr (smart pointer) to LISA 
  Rcpp::XPtr<GeoDaWeight> ptr(xp_w);
  GeoDaWeight* w = static_cast<GeoDaWeight*> (R_ExternalPtrAddr(ptr));

  std::vector<std::vector<double> > raw_data;
  for (int i=0; i< data.size(); ++i) {
    Rcpp::NumericVector tmp = data[i];
    std::vector<double> vals = as<std::vector<double> >(tmp);
    raw_data.push_back(vals);
  }

  std::vector<double> raw_bound = as<std::vector<double> >(bound_vals);
  std::vector<int> raw_init_regions = as<std::vector<int> >(init_regions);

  std::vector<std::vector<int> > clusters = gda_maxp(w, raw_data, raw_bound, min_bound, local_search, iterations, tabu_length, cool_rate, raw_init_regions, distance_method, seed);

  Rcpp::List out(clusters.size());
  for (int i=0; i< clusters.size(); ++i) {
    std::vector<int>& vals = clusters[i];
    Rcpp::NumericVector tmp_vals(vals.begin(), vals.end());
    out[i] = tmp_vals;
  }

  return out;
}