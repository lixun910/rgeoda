#include <iostream>
#include <float.h>

#include "weights/GeodaWeight.h"
#include "sa/UniGeary.h"
#include "sa/UniG.h"
#include "sa/UniGstar.h"
#include "sa/UniJoinCount.h"
#include "sa/UniLocalMoran.h"
#include "sa/MultiGeary.h"
#include "sa/MultiJoinCount.h"
#include "sa/BatchLocalMoran.h"
#include "GenUtils.h"
#include "gda_sa.h"


LISA* gda_localg(GeoDaWeight *w,
                 const std::vector<double> &data,
                 const std::vector<bool> &undefs,
                 int nCPUs, int perm, int last_seed)
{
    if (w == 0) return 0;

    int num_obs = w->num_obs;

    std::vector<bool> copy_undefs = undefs;
    if (copy_undefs.empty()) {
        copy_undefs.resize(num_obs, false);
    }
    UniG* localg = new UniG(num_obs, w, data, copy_undefs, nCPUs, perm, last_seed);
    return localg;
}

LISA* gda_localgstar(GeoDaWeight *w,
                         const std::vector<double> &data,
                         const std::vector<bool> &undefs,
                     int nCPUs, int perm, int last_seed)
{
    if (w == 0) return 0;

    int num_obs = w->num_obs;

    std::vector<bool> copy_undefs = undefs;
    if (copy_undefs.empty()) {
        copy_undefs.resize(num_obs, false);
    }
    UniGstar* localgstar = new UniGstar(num_obs, w, data, copy_undefs, nCPUs, perm, last_seed);
    return localgstar;
}

LISA* gda_localmoran(GeoDaWeight *w,
                        const std::vector<double> &data,
                        const std::vector<bool> &undefs,
                     int nCPUs, int perm, int last_seed)
{
    if (w == 0) return 0;

    int num_obs = w->num_obs;

    std::vector<bool> copy_undefs = undefs;
    if (copy_undefs.empty()) {
        copy_undefs.resize(num_obs, false);
    }
    UniLocalMoran* lisa = new UniLocalMoran(num_obs, w, data, copy_undefs, nCPUs, perm, last_seed);
    return lisa;
}

BatchLISA* gda_batchlocalmoran(GeoDaWeight *w,
                     const std::vector<std::vector<double> > &data,
                     const std::vector<std::vector<bool> > &undefs,
                     int nCPUs, int perm, int last_seed)
{
    if (w == 0) return 0;

    int num_obs = w->num_obs;

    std::vector<std::vector<bool> > copy_undefs = undefs;
    if (undefs.empty()) {
        copy_undefs.resize(data.size());
        for (size_t i=0; i<data.size(); ++i) copy_undefs[i].resize(num_obs, false);
    }

    BatchLISA* bm = new BatchLocalMoran(num_obs, w, data, copy_undefs, nCPUs, perm, last_seed);
    return bm;
}

LISA* gda_geary(GeoDaWeight *w,
                    const std::vector<double> &data,
                    const std::vector<bool> &undefs,
                int nCPUs, int perm, int last_seed)
{
    if (w == 0) return 0;

    int num_obs = w->num_obs;

    std::vector<bool> copy_undefs = undefs;
    if (copy_undefs.empty()) {
        copy_undefs.resize(num_obs, false);
    }
    UniGeary* geary = new UniGeary(num_obs, w, data, copy_undefs, nCPUs, perm, last_seed);
    return geary;
}

LISA* gda_multigeary(GeoDaWeight *w,
                const std::vector<std::vector<double> > &data,
                const std::vector<std::vector<bool> > &undefs,
                     int nCPUs, int perm, int last_seed)
{
    if (w == 0) return 0;

    int num_obs = w->num_obs;

    MultiGeary* geary = new MultiGeary(num_obs, w, data, undefs, nCPUs, perm, last_seed);
    return geary;
}

LISA* gda_joincount(GeoDaWeight *w,
                            const std::vector<double> &data,
                            const std::vector<bool> &undefs,
                    int nCPUs, int perm, int last_seed)
{
    if (w == 0) return 0;

    int num_obs = w->num_obs;

    std::vector<bool> copy_undefs = undefs;
    if (copy_undefs.empty()) {
        copy_undefs.resize(num_obs, false);
    }
    UniJoinCount* jc= new UniJoinCount(num_obs, w, data, copy_undefs, nCPUs, perm, last_seed);
    return jc;
}

LISA* gda_multijoincount(GeoDaWeight *w,
                const std::vector<std::vector<double> > &data,
                const std::vector<std::vector<bool> > &undefs,
                         int nCPUs, int perm, int last_seed)
{
    if (w == 0) return 0;

    int num_obs = w->num_obs;

    MultiJoinCount* jc = new MultiJoinCount(num_obs, w, data, undefs, nCPUs, perm, last_seed);
    return jc;
}

double gda_fdr(LISA *lisa, double current_p) {
    if (lisa == 0) return 0;

    return lisa->GetFDR(current_p);
}

double gda_bo(LISA *lisa, double current_p) {
    if (lisa == 0) return 0;

    return lisa->GetBO(current_p);
}

LISA *gda_quantilelisa(GeoDaWeight *w, unsigned int k, unsigned int quantile, const std::vector<double> &data,
                       const std::vector<bool> &undefs,
                       int nCPUs, int perm, int last_seed)
{
    if (w == 0) return 0;

    int num_obs = w->num_obs;

    if (k< 1 || k>= num_obs) return 0;

    if (quantile < 0 || quantile > k) return 0;

    std::vector<bool> copy_undefs = undefs; //copy
    if (copy_undefs.empty()) {
        copy_undefs.resize(num_obs, false);
    }

    std::vector<double> breaks = GenUtils::QuantileBreaks(k, data, copy_undefs);

    quantile = quantile - 1;
    double break_left = DBL_MIN;
    double break_right = DBL_MAX;

    if (quantile == 0) {
        break_right = breaks[quantile];
    } else if (quantile == breaks.size()) {
        break_left = breaks[quantile - 1];
    } else {
        break_left = breaks[quantile - 1];
        break_right = breaks[quantile];
    }

    std::vector<double> bin_data(num_obs, 0);

    for (size_t i=0; i< num_obs; ++i) {
        if (data[i] >= break_left && data[i] < break_right) {
            bin_data[i] = 1;
        }
    }

    // apply local join count on binary data
    UniJoinCount* jc= new UniJoinCount(num_obs, w, bin_data, copy_undefs, nCPUs, perm, last_seed);

    return jc;
}
