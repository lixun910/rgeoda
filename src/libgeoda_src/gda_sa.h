#ifndef __JSGEODSA_GDA_SA__
#define __JSGEODSA_GDA_SA__

#include <string>
#include <vector>

class GeoDaWeight;
class LISA;
class BatchLISA;

// APIs of local spatial autocorrelation
/**
 *
 * @param w
 * @param data
 * @param undefs
 * @return
 */
LISA* gda_localmoran(GeoDaWeight *w, const std::vector<double> &data, const std::vector<bool> &undefs = std::vector<bool>(), int nCPUs = 6, int permutations = 999, int last_seed_used = 123456789);

/**
 *
 * @param w
 * @param data
 * @param undefs
 * @return
 */
BatchLISA* gda_batchlocalmoran(GeoDaWeight *w, const std::vector<std::vector<double> > &data,
                     const std::vector<std::vector<bool> > &undefs = std::vector<std::vector<bool> >(),
                     int nCPUs = 6, int permutations = 999, int last_seed_used = 123456789);

/**
 *
 * @param w
 * @param data
 * @param undefs
 * @return
 */
LISA* gda_geary(GeoDaWeight *w, const std::vector<double> &data,
                    const std::vector<bool> &undefs = std::vector<bool>(),
                int nCPUs = 6, int permutations = 999, int last_seed_used = 123456789);

/**
 *
 * @param w
 * @param data
 * @param undefs
 * @return
 */
LISA* gda_multigeary(GeoDaWeight *w, const std::vector<std::vector<double> > &data,
                    const std::vector<std::vector<bool> > &undefs = std::vector<std::vector<bool> >(),
                     int nCPUs = 6, int permutations = 999, int last_seed_used = 123456789);

/**
 *
 * @param w
 * @param data
 * @param undefs
 * @return
 */
LISA* gda_joincount(GeoDaWeight *w, const std::vector<double> &data,
                            const std::vector<bool> &undefs = std::vector<bool>(),
                    int nCPUs = 6, int permutations = 999, int last_seed_used = 123456789);

LISA* gda_multijoincount(GeoDaWeight *w, const std::vector<std::vector<double> > &data,
                const std::vector<std::vector<bool> > &undefs = std::vector<std::vector<bool> >(),
                         int nCPUs = 6, int permutations = 999, int last_seed_used = 123456789);
/**
 *
 * @param w
 * @param data
 * @param undefs
 * @return
 */
LISA* gda_localg(GeoDaWeight *w, const std::vector<double> &data,
                 const std::vector<bool> &undefs = std::vector<bool>(),
                 int nCPUs = 6, int permutations = 999, int last_seed_used = 123456789);

/**
 *
 * @param w
 * @param data
 * @param undefs
 * @return
 */
LISA* gda_localgstar(GeoDaWeight *w, const std::vector<double> &data,
                         const std::vector<bool> &undefs = std::vector<bool>(),
                     int nCPUs = 6, int permutations = 999, int last_seed_used = 123456789);

/**
 *
 * @param w
 * @param quantile
 * @param data
 * @param undefs
 * @return
 */
LISA* gda_quantilelisa(GeoDaWeight* w, unsigned int k,  unsigned int quantile, const std::vector<double> &data,
                       const std::vector<bool> &undefs = std::vector<bool>(),
                       int nCPUs = 6, int permutations = 999, int last_seed_used = 123456789);

/**
 *
 * @param lisa
 * @param current_p
 * @return
 */
double gda_fdr(LISA* lisa, double current_p);

/**
 *
 * @param lisa
 * @param current_p
 * @return
 */
double gda_bo(LISA* lisa, double current_p);

#endif
