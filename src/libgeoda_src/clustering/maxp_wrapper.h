//
// Created by Xun Li on 9/26/19.
//

#ifndef GEODA_MAXP_WRAPPER_H
#define GEODA_MAXP_WRAPPER_H


#include <vector>

class GeoDa;
class GalElement;
class GeoDaWeight;

class maxp_wrapper {
public:
    maxp_wrapper(int local_search_method,
                 GeoDaWeight *w,
                 const std::vector<std::vector<double> >& data,
                 int initial = 99,
                 int tabu_length = 85,
                 double cool_rate = 0.85,
                 double *bound_vals = 0,
                 double min_bound = 0,
                 const std::vector<int>& seeds = std::vector<int>(),
                 const std::string &distance_method = "euclidean",
                 int rnd_seed = -1);


    virtual ~maxp_wrapper();

    const std::vector<int> GetFlatClusters();

    const std::vector<std::vector<int> > GetClusters();

private:
    int num_obs;

    std::vector<std::vector<int> > cluster_ids;
};


#endif //GEODA_MAXP_WRAPPER_H
