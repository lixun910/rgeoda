//
// Created by Xun Li on 9/27/19.
//

#ifndef GEODA_REDCAP_WRAPPER_H
#define GEODA_REDCAP_WRAPPER_H

#include <vector>
#include <string>

class GeoDaWeight;

class redcap_wrapper {
public:
    redcap_wrapper(unsigned int k,
                   GeoDaWeight *w,
                   const std::vector<std::vector<double> > &data,
                   unsigned int redcap_method = 0,
                   const std::string &distance_method = "euclidean",
                   const std::vector<double>& bound_vals = std::vector<double>(),
                   double min_bound = 0,
                   int rand_seed = 123456789);

    virtual ~redcap_wrapper();

    const std::vector<int> GetFlatClusters();

    const std::vector<std::vector<int> > GetClusters();

private:
    int num_obs;

    std::vector<std::vector<int> > cluster_ids;
};


#endif //GEODA_REDCAP_WRAPPER_H
