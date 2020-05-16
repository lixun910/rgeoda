//
// Created by Xun Li on 2019-11-27.
// lixun910@gmail.com
//

#ifndef GEODA_GDA_ALGORITHMS_H
#define GEODA_GDA_ALGORITHMS_H

#include <vector>
#include <string>

// APIs of some algorithms

class PCAResult {
public:
    PCAResult(const std::string &method);

    virtual ~PCAResult();

    void setMethod(const std::string &method);

    void setStandardDev(const std::vector<float> &standardDev);

    void setPropOfVar(const std::vector<float> &propOfVar);

    void setCumProp(const std::vector<float> &cumProp);

    void setThresh95(float thresh95);

    void setEigenValues(const std::vector<float> &eigenValues);

    void setScores(const std::vector<float> &scores);

    void setLoadings(const std::vector<std::vector<float> > &loadings);

    void setSqCorrelations(const std::vector<std::vector<float> > &sqCorrelations);

    void setPriComponents(const std::vector<std::vector<float> > &priComponents);

    std::string getMethod() const;

    std::vector<float> getStandardDev() ;

    std::vector<float> getPropOfVar() ;

    std::vector<float> getCumProp() ;

    float getThresh95() const;

    std::vector<float> getEigenValues() ;

    std::vector<std::vector<float> > getLoadings() ;

    std::vector<std::vector<float> > getSqCorrelations() ;

    std::vector<std::vector<float> > getPriComponents() ;

    std::vector<std::vector<float> > getKComponents(int k) ;

    void setKaiser(float kaiser);

    float getKaiser() const;

    int row_lim;

    int col_lim;

private:
    std::string method;

    std::vector<float> standard_dev;

    // Proportion of variance
    std::vector<float> prop_of_var;

    // Cumulative proportion
    std::vector<float> cum_prop;

    // Kaiser criterion
    float thresh95;

    float kaiser;

    // scores
    std::vector<float> scores;

    // Eigenvalues
    std::vector<float> eigen_values;

    // Variable Loadings
    std::vector<std::vector<float> > loadings;
    // Squared correlations:
    std::vector<std::vector<float> > sq_correlations;
    // PC
    std::vector<std::vector<float> > pri_components;
};

PCAResult* gda_pca(const std::vector<std::vector<double> > & data,
                   const std::string& method = "svd");

std::vector<std::vector<double> > gda_mds(const std::vector<std::vector<double> > & data,
                                          int k = 2,
                                          const std::string& dist_method = "euclidean",
                                          bool use_power_iteration = false,
                                          unsigned int power_max_iter = 100);

#endif //GEODA_GDA_ALGORITHMS_H
