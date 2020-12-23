//' This file is used to wrap C++ classes and functions defines in RcppExports.R
//' All other R script files will use this file as a bridge to C++ classes and functions
//'
//' Author: lixun910@gmail.com
//' Changes:
//' 10/29/2020 init file

#include <Rcpp.h>
#include "libgeoda_src/libgeoda.h"
#include "libgeoda_src/gda_data.h"

using namespace Rcpp;

//' @title p_GeoDa__new
//'
//' @description Create an instance of GeoDa by loading a ESRI shapefile
//'
//' @param file_path The path of the spatial file (ESRI shapefile)
//' @return An externptr of GeoDa object
//  [[Rcpp::export]]
SEXP p_GeoDa__new(std::string file_path)
{
  // create a pointer to an GeoDa object and wrap it
  // as an external pointer
  Rcpp::XPtr<GeoDa> ptr( new GeoDa(file_path.c_str()), true );

  // return the external pointer to the R side
  return ptr;
}

//' @title p_GeoDa__new1
//'
//' @description Create an instance of GeoDa from sf object
//'
//' @param file_path The path of the spatial file (ESRI shapefile)
//' @return An externptr of GeoDa object
//  [[Rcpp::export]]
SEXP p_GeoDa__new1(std::string layer_name, std::string map_type, int num_features, RawVector wkbs, NumericVector wkb_bytes_len)
{
  std::vector<unsigned char> _wkbs = as<std::vector<unsigned char> >(wkbs);
  std::vector<int> _wkb_bytes_len = as<std::vector<int> >(wkb_bytes_len);

  // create a pointer to an GeoDa object and wrap it
  // as an external pointer
  Rcpp::XPtr<GeoDa> ptr( new GeoDa(layer_name, map_type, num_features, _wkbs.data(), _wkb_bytes_len),
                         true );

  // return the external pointer to the R side
  return ptr;
}

//' @title p_GeoDa__GetNumObs
//'
//' @description Get the number of obervations from GeoDa object
//' @return The number of observations
//  [[Rcpp::export]]
int p_GeoDa__GetNumObs(SEXP xp)
{
  // grab the object as a XPtr (smart pointer) to GeoDa
  Rcpp::XPtr<GeoDa> ptr(xp);

  // invoke the function
  int num_obs = ptr->GetNumObs();

  return num_obs;
}


//' @title p_GeoDa__GetNumCols
//'
//' @description Get the number of columns from GeoDa object
//' @return The number of columns
//  [[Rcpp::export]]
int p_GeoDa__GetNumCols(SEXP xp)
{
  // grab the object as a XPtr (smart pointer) to GeoDa
  Rcpp::XPtr<GeoDa> ptr(xp);

  // invoke the function
  int num_cols = ptr->GetNumCols();

  return num_cols;
}

//' @title p_GeoDa__GetMapType
//'
//' @description Get the map type from GeoDa object
//' , which has to be one of {point_type, polygon_type, line_type, unkonwn_type}
//'
//' @return The id of map type
//  [[Rcpp::export]]
int p_GeoDa__GetMapType(SEXP xp)
{
  // grab the object as a XPtr (smart pointer) to GeoDa
  Rcpp::XPtr<GeoDa> ptr(xp);

  // invoke the function
  int map_type = ptr->GetMapType();

  return map_type;
}

//' @title p_GeoDa__GetFieldNames
//'
//' @description Get the field names from GeoDa object
//'
//' @return A list of field names
//  [[Rcpp::export]]
StringVector p_GeoDa__GetFieldNames(SEXP xp)
{
  // grab the object as a XPtr (smart pointer) to GeoDa
  Rcpp::XPtr<GeoDa> ptr(xp);

  // invoke the function
  std::vector<std::string> field_nms = ptr->GetFieldNames();

  int n_fields = field_nms.size();

  // convert to Rcpp::StringVector
  StringVector sv_field_nms(n_fields);

  for (int i=0; i<n_fields; ++i) {
    sv_field_nms[i] = field_nms[i];
  }

  return sv_field_nms;
}

//' @title p_GeoDa__GetFieldTypes
//'
//' @description Get the field types from GeoDa object
//'
//' @return A list of field types
//  [[Rcpp::export]]
StringVector p_GeoDa__GetFieldTypes(SEXP xp)
{
  // grab the object as a XPtr (smart pointer) to GeoDa
  Rcpp::XPtr<GeoDa> ptr(xp);

  // invoke the function
  std::vector<std::string> field_tps = ptr->GetFieldTypes();

  int n_fields = field_tps.size();

  // convert to Rcpp::StringVector
  StringVector sv_field_tps(n_fields);

  for (int i=0; i<n_fields; ++i) {
    sv_field_tps[i] = field_tps[i];
  }

  return sv_field_tps;
}

//' @title p_GeoDa__GetNumericCol
//'
//' @description Get the values of a numeric col from GeoDa object
//'
//' @return A list of double values
//  [[Rcpp::export]]
NumericVector p_GeoDa__GetNumericCol(SEXP xp, std::string col_name)
{
  // grab the object as a XPtr (smart pointer) to GeoDa
  Rcpp::XPtr<GeoDa> ptr(xp);

  // invoke the function
  std::vector<double> vals = ptr->GetNumericCol(col_name);

  int n_rows = vals.size();

  // convert to Rcpp::StringVector
  NumericVector nv_vals(n_rows);

  for (int i=0; i<n_rows; ++i) {
    nv_vals[i] = vals[i];
  }

  return nv_vals;
}

//' @title p_GeoDa__GetIntegerCol
//'
//' @description Get the values of a integer col from GeoDa object
//'
//' @return A list of integer values
//  [[Rcpp::export]]
NumericVector p_GeoDa__GetIntegerCol(SEXP xp, std::string col_name)
{
  // grab the object as a XPtr (smart pointer) to GeoDa
  Rcpp::XPtr<GeoDa> ptr(xp);

  // invoke the function
  std::vector<long long> vals = ptr->GetIntegerCol(col_name);

  int n_rows = vals.size();

  // convert to Rcpp::StringVector
  NumericVector nv_vals(n_rows);

  for (int i=0; i<n_rows; ++i) {
    nv_vals[i] = vals[i];
  }

  return nv_vals;
}

//' @title p_GeoDa__GetStringCol
//'
//' @description Get the values of a string col from GeoDa object
//'
//' @return A list of string values
//  [[Rcpp::export]]
StringVector p_GeoDa__GetStringCol(SEXP xp, std::string col_name)
{
  // grab the object as a XPtr (smart pointer) to GeoDa
  Rcpp::XPtr<GeoDa> ptr(xp);

  // invoke the function
  std::vector<std::string> vals = ptr->GetStringCol(col_name);

  int n_rows = vals.size();

  // convert to Rcpp::StringVector
  StringVector sv_vals(n_rows);

  for (int i=0; i<n_rows; ++i) {
    sv_vals[i] = vals[i];
  }

  return sv_vals;
}

//' @title p_GeoDa__GetNullValues
//'
//' @description Get the null flags of a col from GeoDa object
//'
//' @return A list of string values
//  [[Rcpp::export]]
LogicalVector p_GeoDa__GetNullValues(SEXP xp, std::string col_name)
{
  // grab the object as a XPtr (smart pointer) to GeoDa
  Rcpp::XPtr<GeoDa> ptr(xp);

  // invoke the function
  std::vector<bool> vals = ptr->GetNullValues(col_name);

  int n_rows = vals.size();

  // convert to Rcpp::LogicalVector
  LogicalVector lv_vals(n_rows);

  for (int i=0; i<n_rows; ++i) {
    lv_vals[i] = vals[i];
  }

  return lv_vals;
}

//' @title p_gda_demean
//'
//' @description The mean for each variable is subtracting from each observation resulting in mean zero.
//' @param data An input data for median absolute deviation
//' @return A list of numeric vectors 
//  [[Rcpp::export]]
Rcpp::List p_gda_demean(Rcpp::List data) 
{
  std::vector<std::vector<double> > _data;
  for (int i=0; i< data.size(); ++i) {
    Rcpp::NumericVector tmp = data[i];
    std::vector<double> vals = as<std::vector<double> >(tmp);
    _data.push_back(vals);
  }

  std::vector<std::vector<double> > demean_data = gda_demean(_data);

  Rcpp::List out(data.size());
  for (int i=0; i< data.size(); ++i) {
    std::vector<double>& vals = demean_data[i];
    Rcpp::NumericVector tmp_vals(vals.begin(), vals.end());
    out[i] = tmp_vals;
  }

  return out;
}

//' @title p_gda_standardize
//'
//' @description Standarize data by transforming data to have zero mean and unit variance
//' @param data An input data for median absolute deviation
//' @return A list of numeric vectors 
//  [[Rcpp::export]]
Rcpp::List p_gda_standardize(Rcpp::List data) 
{
  std::vector<std::vector<double> > _data;
  for (int i=0; i< data.size(); ++i) {
    Rcpp::NumericVector tmp = data[i];
    std::vector<double> vals = as<std::vector<double> >(tmp);
    _data.push_back(vals);
  }

  std::vector<std::vector<double> > std_data = gda_standardize(_data);

  Rcpp::List out(data.size());
  for (int i=0; i< data.size(); ++i) {
    std::vector<double>& vals = std_data[i];
    Rcpp::NumericVector tmp_vals(vals.begin(), vals.end());
    out[i] = tmp_vals;
  }

  return out;
}

//' @title p_gda_standardize_mad
//'
//' @description Median absolute deviation to measure  measure of the variability of a univariate sample of quantitative data
//' @param data An input data for median absolute deviation
//' @return A list of numeric vectors 
//  [[Rcpp::export]]
Rcpp::List p_gda_standardize_mad(Rcpp::List data) 
{
  std::vector<std::vector<double> > _data;
  for (int i=0; i< data.size(); ++i) {
    Rcpp::NumericVector tmp = data[i];
    std::vector<double> vals = as<std::vector<double> >(tmp);
    _data.push_back(vals);
  }

  std::vector<std::vector<double> > std_data = gda_standardize_mad(_data);

  Rcpp::List out(data.size());
  for (int i=0; i< data.size(); ++i) {
    std::vector<double>& vals = std_data[i];
    Rcpp::NumericVector tmp_vals(vals.begin(), vals.end());
    out[i] = tmp_vals;
  }

  return out;
}

//' @title p_gda_naturalbreaks
//'
//' @description Median absolute deviation to measure  measure of the variability of a univariate sample of quantitative data
//' @param data An input data for median absolute deviation
//' @return A numeric vector
//  [[Rcpp::export]
Rcpp::NumericVector p_gda_naturalbreaks(int k, Rcpp::NumericVector& data)
{
  std::vector<double> vals = as<std::vector<double> >(data);
  std::vector<double> result = gda_naturalbreaks(k, vals);

  Rcpp::NumericVector out(result.begin, result.end);
  return out;
}