//
// Created by Xun Li on 9/26/19.
//

#include <boost/algorithm/string.hpp>
#include "../weights/GalWeight.h"
#include "../GenUtils.h"
#include "cluster.h"
#include "maxp.h"
#include "maxp_wrapper.h"

maxp_wrapper::~maxp_wrapper() {

}

maxp_wrapper::maxp_wrapper(int local_search_method, GeoDaWeight *w,
                           const std::vector<std::vector<double> >& data,
                           int initial,
                           int tabu_length,
                           double cool_rate,
                           double *bound_vals,
                           double min_bound,
                           const std::vector<int>& seeds,
                           const std::string &distance_method,
                           int rnd_seed)
{
    num_obs = 0;

    if (w) {
        setrandomstate(rnd_seed);
        resetrandom();

        num_obs = w->num_obs;
        GalElement* gal = Gda::GetGalElement(w);
        if (gal) {
            // standardize data
            int n_cols = data.size();
            std::vector<std::vector<double> > matrix;
            matrix.resize(n_cols);
            for (size_t i=0; i<n_cols; ++i) {
                std::vector<double> vals = data[i];
                GenUtils::StandardizeData(vals);
                matrix[i] = vals;
            }
            std::vector<std::vector<double> > z(num_obs);
            for (size_t i=0; i<num_obs; i++) {
                z[i].resize(n_cols);
                for (size_t j=0; j<n_cols; j++) {
                    z[i][j] = matrix[j][i];
                }
            }
            // transform seeds
            std::vector<uint64_t> _seeds;
            if (seeds.size() == num_obs) {
                for (size_t i = 0; i < seeds.size(); ++i) {
                    _seeds.push_back(seeds[i]);
                }
            }
            // dist
            char dist = 'e';
            if (boost::iequals(distance_method, "manhattan")) dist = 'b';

            Maxp maxp(gal, z, min_bound, bound_vals, initial, _seeds, local_search_method, tabu_length, cool_rate,
                    rnd_seed, dist);
            cluster_ids = maxp.GetRegions();
        }
    }
}

const std::vector<std::vector<int> > maxp_wrapper::GetClusters() {
    return cluster_ids;
}
const std::vector<int> maxp_wrapper::GetFlatClusters() {
    std::sort(cluster_ids.begin(), cluster_ids.end(), GenUtils::less_vectors);
    int ncluster = cluster_ids.size();

    std::vector<int> clusters(num_obs, 0);
    for (int i=0; i < ncluster; i++) {
        int c = i + 1;
        for (int j=0; j<cluster_ids[i].size(); j++) {
            int idx = cluster_ids[i][j];
            clusters[idx] = c;
        }
    }

    return clusters;
}
