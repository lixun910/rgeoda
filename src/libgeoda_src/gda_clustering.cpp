
#include <boost/algorithm/string.hpp>
#include "weights/GeodaWeight.h"
#include "clustering/maxp_wrapper.h"
#include "clustering/redcap_wrapper.h"
#include "GenUtils.h"
#include "gda_clustering.h"


const std::vector<std::vector<int> > gda_maxp(GeoDaWeight *w,
                                              const std::vector<std::vector<double> > &data,
                                              const std::vector<double> &in_bound_vals,
                                              double min_bound,
                                              const std::string& local_search_method,
                                              int initial,
                                              int tabu_length,
                                              double cool_rate,
                                              const std::vector<int> &seeds,
                                              const std::string &distance_method,
                                              int rand_seed)
{
    std::vector<std::vector<int> > result;

    int search_method = 0;
    if (boost::iequals(local_search_method, "greedy")) {
        search_method = 0;
    } else if (boost::iequals(local_search_method, "tabu")) {
        search_method = 1;
    } else if (boost::iequals(local_search_method, "sa")) {
        search_method = 2;
    }

    if (w == 0) return result;

    if (search_method == 0 || search_method == 1 || search_method == 2) {
        double* bound_vals = 0;
        if (in_bound_vals.size() == w->num_obs) {
            bound_vals = new double[w->num_obs];
            for (size_t i = 0; i < w->num_obs; ++i) {
                bound_vals[i] = in_bound_vals[i];
            }
        }
        maxp_wrapper maxp(search_method, w, data, initial, tabu_length, cool_rate, bound_vals, min_bound, seeds,
                          distance_method, rand_seed);
        delete[] bound_vals;
        return maxp.GetClusters();
    }

    return result;
}

const std::vector<std::vector<int> > gda_redcap(unsigned int k,
                                                GeoDaWeight *w,
                                                const std::vector<std::vector<double> > &data,
                                                const std::string &redcap_method,
                                                const std::string &distance_method,
                                                const std::vector<double>& bound_vals,
                                                double min_bound,
                                                int rand_seed)
{
    std::vector<std::vector<int> > result;
    unsigned int method = 0;
    if (boost::iequals(redcap_method, "firstorder-singlelinkage")) {
        method = 0;
    } else if  (boost::iequals(redcap_method, "fullorder-completelinkage")){
        method = 1;
    } else if  (boost::iequals(redcap_method, "fullorder-averagelinkage")) {
        method = 2;
    } else if  (boost::iequals(redcap_method, "fullorder-singlelinkage")) {
        method = 3;
    }

    if (w == 0 ||  method > 3) return result;

    if (k > w->num_obs || k < 1) return result;

    redcap_wrapper redcap(k, w, data, method, distance_method, bound_vals, min_bound, rand_seed);
    return redcap.GetClusters();
}

const std::vector<std::vector<int> > gda_skater(unsigned int k,
                                                GeoDaWeight *w,
                                                const std::vector<std::vector<double> > &data,
                                                const std::string &distance_method,
                                                const std::vector<double>& bound_vals,
                                                double min_bound,
                                                int rand_seed)
{
    return gda_redcap(k, w, data, "firstorder-singlelinkage", distance_method, bound_vals, min_bound, rand_seed);
}


double gda_sumofsquares(const std::vector<double>& vals)
{
    std::vector<double> data = vals;
    return  GenUtils::SumOfSquares(data);
}

double gda_totalsumofsquare(const std::vector<std::vector<double> >& vals)
{
    double ssq = 0;
    for (size_t i=0; i<vals.size(); ++i) {
        std::vector<double> data = vals[i];
        GenUtils::StandardizeData(data);
        double ss = gda_sumofsquares(data);
        ssq += ss;
    }
    return ssq;
}

double gda_withinsumofsquare(const std::vector<std::vector<int> >& solution,
                             const std::vector<std::vector<double> >& _data)
{
    double ssq = 0;
    size_t cols = _data.size();

    // standardize data
    std::vector<std::vector<double> > data(cols);
    for (size_t c=0; c<cols; ++c) {
        data[c] = _data[c];
        GenUtils::StandardizeData(data[c]);
    }

    for (size_t c=0; c<cols; ++c) {
        for (size_t i=0; i<solution.size(); ++i) {
            std::vector<double> vals;
            for (size_t j = 0; j < solution[i].size(); ++j) {
                size_t r = solution[i][j];
                vals.push_back(data[c][r]);
            }
            double ss = gda_sumofsquares(vals);
            ssq += ss;
        }
    }
    return ssq;
}

double gda_betweensumofsquare(const std::vector<std::vector<int> >& solution,
                              const std::vector<std::vector<double> >& data)
{
    double totss = gda_totalsumofsquare(data);
    double totwithiness = gda_withinsumofsquare(solution, data);
    double betweenss = totss - totwithiness;
    return betweenss;
}