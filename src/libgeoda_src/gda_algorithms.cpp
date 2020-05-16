//
// Created by Xun Li on 2019-11-27.
//
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "clustering/pca.h"
#include "GenUtils.h"
#include "clustering/mds.h"
#include "clustering/cluster.h"
#include "gda_algorithms.h"

PCAResult::PCAResult(const std::string &method)
: method(method), thresh95(0), col_lim(0), row_lim(0) {

}

PCAResult::~PCAResult() {

}

std::string PCAResult::getMethod() const {
    return method;
}

std::vector<float> PCAResult::getStandardDev(){
    return standard_dev;
}

std::vector<float> PCAResult::getPropOfVar() {
    return prop_of_var;
}

std::vector<float> PCAResult::getCumProp() {
    return cum_prop;
}

float PCAResult::getThresh95() const {
    return thresh95;
}

std::vector<float> PCAResult::getEigenValues() {
    return eigen_values;
}

std::vector<std::vector<float> > PCAResult::getLoadings() {
    return loadings;
}

std::vector<std::vector<float> > PCAResult::getSqCorrelations() {
    return sq_correlations;
}

std::vector<std::vector<float> > PCAResult::getPriComponents() {
    return pri_components;
}

void PCAResult::setMethod(const std::string &method) {
    PCAResult::method = method;
}

void PCAResult::setStandardDev(const std::vector<float> &standardDev) {
    standard_dev = standardDev;
}

void PCAResult::setPropOfVar(const std::vector<float> &propOfVar) {
    prop_of_var = propOfVar;
}

void PCAResult::setCumProp(const std::vector<float> &cumProp) {
    cum_prop = cumProp;
}

void PCAResult::setThresh95(float thresh95) {
    PCAResult::thresh95 = thresh95;
}

void PCAResult::setEigenValues(const std::vector<float> &eigenValues) {
    eigen_values = eigenValues;
}

void PCAResult::setScores(const std::vector<float> &_scores) {
    scores = _scores;
}

void PCAResult::setLoadings(const std::vector<std::vector<float> > &loadings) {
    PCAResult::loadings = loadings;
}

void PCAResult::setSqCorrelations(const std::vector<std::vector<float> > &sqCorrelations) {
    sq_correlations = sqCorrelations;
}

void PCAResult::setPriComponents(const std::vector<std::vector<float> > &priComponents) {
    pri_components = priComponents;
}

std::vector<std::vector<float> >  PCAResult::getKComponents(int k) {
    std::vector<std::vector<float> > vals(k);

    if (row_lim > 0 && col_lim > 0) {
        for (unsigned int j = 0; j < k; ++j) {
            vals[j].resize(row_lim);
            for (unsigned int i = 0; i < row_lim; ++i) {
                vals[j][i] = float(scores[j + col_lim*i]);
            }
        }
    }

    return vals;
}

float PCAResult::getKaiser() const {
    return kaiser;
}

void PCAResult::setKaiser(float kaiser) {
    PCAResult::kaiser = kaiser;
}


PCAResult* gda_pca(const std::vector<std::vector<double> > &data, const std::string &method)
{
    size_t ncols = data.size();
    if (ncols == 0)
        return 0;

    size_t nrows = data[0].size();

    Pca pca(data, nrows, ncols);
    int init_result = 0;

    if (boost::iequals(method, "svd")) {
        init_result = pca.CalculateSVD();
    } else {
        init_result = pca.Calculate();
    }

    if (0 != init_result) {
#ifdef __DEBUG__
        std::string msg = "There is an error during PCA calculation. Please check if the data is valid.";
        std::cout << msg << std::endl;
#endif
        return 0;
    }

    int max_components = min(nrows, ncols);
    PCAResult* result = new PCAResult(method);

    std::vector<float> scores = pca.scores();
    result->setScores(scores);

    size_t row_lim = nrows;
    size_t col_lim = ncols;

    if (scores.size() != nrows * ncols) {
        row_lim = (nrows < ncols)? nrows : ncols;
        col_lim = (ncols < nrows)? ncols : nrows;
    }

    result->row_lim = row_lim;
    result->col_lim = col_lim;

    // principle components
    std::vector<std::vector<float> > vals(max_components);

    for (int j = 0; j < max_components; ++j) {
        vals[j].resize(row_lim);
        for (unsigned int i = 0; i < row_lim; ++i) {
            vals[j][i] = float(scores[j + col_lim*i]);
        }
    }
    result->setPriComponents(vals);

    result->setStandardDev(pca.sd());
    result->setPropOfVar(pca.prop_of_var());
    result->setCumProp(pca.cum_prop());
    result->setThresh95(pca.thresh95());
    result->setKaiser(pca.kaiser());

    // eigen values
    std::vector<float> eigens(pca.eigen_values.data(),
            pca.eigen_values.data() +  pca.eigen_values.rows() * pca.eigen_values.cols());
    result->setEigenValues(eigens);

    // eigen vectors
    std::vector<std::vector<float> > ev;
    for (int i=0; i<pca.eigen_vectors.rows(); ++i) {
        const float* begin = &(pca.eigen_vectors.row(i).data()[0]);
        ev.push_back(std::vector<float>(begin, begin+pca.eigen_vectors.cols()));
    }
    result->setLoadings(ev);

    // squared correlations
    int num_pc = col_lim;
    std::vector<std::vector<double> > pc_data(num_pc);
    for (unsigned int i=0; i<col_lim; i++ ) {
        pc_data[i].resize(row_lim);
        for (unsigned int j=0; j<row_lim; j++ ) {
            pc_data[i][j] = scores[i + col_lim*j];
        }
    }

    std::vector<int> col_size(num_pc, 0);
    std::vector<std::vector<float> > corr_matrix(ncols);
    double corr, corr_sqr;
    for (int i=0; i<ncols; i++) {
        std::vector<double> col_data;
        for (int j=0; j<nrows; j++) col_data.push_back(data[i][j]);
        corr_matrix[i].resize(num_pc);
        for (int j=0; j<num_pc; j++) {
            corr = GenUtils::Correlation(col_data, pc_data[j]);
            corr_sqr = corr * corr;
            corr_matrix[i][j] = corr_sqr;
        }
    }
    result->setSqCorrelations(corr_matrix);

    return result;
}

std::vector<std::vector<double> >
gda_mds(const std::vector<std::vector<double> > &data, int k, const std::string& dist_method, bool use_power_iteration, unsigned int power_max_iter)
{
    char dist = 'e';
    if (!boost::iequals(dist_method, "euclidean")) dist = 'b';


    if (use_power_iteration) {
        std::vector<std::vector<double> > distances = DataUtils::DistanceMatrix(data, dist);
        FastMDS mds(distances, k, power_max_iter);
        return mds.GetResult();

    } else {
        int columns = data.size();
        if (columns == 0)  return std::vector<std::vector<double> >();
        int rows = data[0].size();
        if (rows== 0) return std::vector<std::vector<double> >();

        int transpose = 0; // row wise

        double* weight = new double[columns];
        for (int i=0; i<columns; ++i) weight[i] = 1;

        int** mask = 0;
        double** input_data = new double*[rows];
        mask = new int*[rows];
        for (int i=0; i<rows; i++) {
            input_data[i] = new double[columns];
            mask[i] = new int[columns];
            for (int j=0; j<columns; j++) {
                input_data[i][j] = data[j][i];
                mask[i][j] = 1;
            }
        }

        double** rst = mds(rows, columns, input_data,  mask, weight, transpose, dist,  NULL, k);

        std::vector<std::vector<double> > result(k);
        for (int i=0; i<k; i++) {
            result[i].resize(rows);
            for (int j = 0; j < rows; ++j) {
                result[i][j] = rst[j][i];
            }
        }
        for (int j = 0; j < rows; ++j) {
            delete[] rst[j];
            delete[] mask[j];
        }
        delete[] rst;
        delete[] mask;
        return result;
    }

}

