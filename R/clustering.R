
############################################################
#' @title Princinple Components Analysis
#' @description Apply princinple components analysis on original data
#' @param data A 2d numeric list of selected variables
#' @return A PCAResult object containing the details of PCA
#' @export
pca <- function(data) {
  return (gda_pca(data))
}

############################################################
#' @title Summary of Princinple Components Analysis Result
#' @description Override the summary() function for a PCA result
#' @param object A PCAResult object
#' @param ... summary optional parameters
#' @return A summary  description of PCA object
#' @export
summary._p_PCAResult <- function(object, ...) {
  output <-
    list("PCA method: " = object$getMethod(),
         "Standard Deviation:" = object$getStandardDev(),
         "Proportion of variance:" = object$getPropOfVar(),
         "Cumulative proportion:" = object$getCumProp(),
         "Kaiser criterion:" = object$getKaiser(),
         "95% threshold criterion:" = object$getThresh95(),
         "Eigen Values:" = object$getEigenValues(),
         "Variable Loadings:" = object$getLoadings(),
         "Squared Correlations:" = object$getSqCorrelations()
    )
  print(output)
}

############################################################
#' @title Get first k components from PCA
#' @description Get first k components from PCA
#' @param pca_r An object return from pca() function
#' @param k A numeric value
#' @return A PCAResult object containing the details of PCA
#' @export
get_kcomponents <- function(pca_r, k) {
  return (pca_r$getKComponents(k))
}

############################################################
#' @title Multi Dimensional Scaling
#' @description Apply multi dimensional scaling to project original data on to a low dimension (k) space
#' @param data A 2d numeric list of selected variables
#' @param k The number of clusters
#' @return A 2d list represents a group of clusters
#' @export
mds <- function(data, k) {
  return (gda_mds(data, k))
}

############################################################
#' @title Spatial C(K)luster Analysis by Tree Edge Removal
#' @description SKATER forms clusters by spatially partitioning data that has similar values for features of interest.
#' @param k The number of clusters
#' @param w An instance of Weight class
#' @param data A 2d numeric list of selected variable
#' @param bound_vals (optional) A 1-d vector of selected bounding variable
#' @param min_bound (optional) A minimum value that the sum value of bounding variable int each cluster should be greater than
#' @param distance_method (optional) The distance method used to compute the distance betwen observation i and j. Defaults to "euclidean". Options are "euclidean" and "manhattan"
#' @param random_seed (int,optional) The seed for random number generator. Defaults to 123456789.
#' @return A 2d list represents a group of clusters
#' @export
skater <- function(k, w, data, bound_vals = c(0), min_bound = 0, distance_method = "Euclidean",
                   random_seed = 123456789){

  if (w$num_obs < 1) {
    stop("The weights is not valid.")
  }
  if (k <1 && k > w$num_obs) {
    stop("The number of clusters should be a positive integer number, which is less than the number of observations.")
  }
  if (length(data) < 1) {
    stop("The data from selected variable is empty.")
  }
  return(gda_skater(k, w$gda_w, data, distance_method, bound_vals, min_bound, random_seed))
}


############################################################
#' @title Regionalization with dynamically constrained agglomerative clustering and partitioning
#' @description REDCAP (Regionalization with dynamically constrained agglomerative
#' clustering and partitioning) is developed by D. Guo (2008). Like SKATER, REDCAP
#' starts from building a spanning tree with 3 different ways (single-linkage, average-linkage,
#' and the complete-linkage). The single-linkage way leads to build a minimum spanning tree.
#' Then,REDCAP provides 2 different ways (first‐order and full-order constraining) to
#' prune the tree to find clusters. The first-order approach with a minimum spanning tree is
#' exactly the same with SKATER. In GeoDa and pygeoda, the following methods are provided:
#' \* First-order and Single-linkage
#' \* Full-order and Complete-linkage
#' \* Full-order and Average-linkage
#' \* Full-order and Single-linkage
#' @param k The number of clusters
#' @param w An instance of Weight class
#' @param data A 2d numeric list of selected variable
#' @param method {"firstorder-singlelinkage", "fullorder-completelinkage", "fullorder-averagelinkage","fullorder-singlelinkage"}
#' @param bound_vals (optional) A 1-d vector of selected bounding variable
#' @param min_bound (optional) A minimum value that the sum value of bounding variable int each cluster should be greater than
#' @param distance_method (optional) The distance method used to compute the distance betwen observation i and j. Defaults to "euclidean". Options are "euclidean" and "manhattan"
#' @param random_seed (int,optional) The seed for random number generator. Defaults to 123456789.
#' @return A 2d list represents a group of clusters
#' @export
redcap <- function(k, w, data, method, bound_vals = c(0), min_bound = 0, distance_method = "Euclidean",
                   random_seed = 123456789){

  if (w$num_obs < 1) {
    stop("The weights is not valid.")
  }
  if (k <1 && k > w$num_obs) {
    stop("The number of clusters should be a positive integer number, which is less than the number of observations.")
  }
  if (length(data) < 1) {
    stop("The data from selected variable is empty.")
  }
  method_cands <- c("firstorder-singlelinkage", "fullorder-completelinkage", "fullorder-averagelinkage","fullorder-singlelinkage")
  if (!(method %in% method_cands)) {
    stop("The REDCAP method has to be one of ", method_cands)
  }
  return(gda_skater(k, w$gda_w, data, distance_method, bound_vals, min_bound, random_seed))
}


############################################################
#' @title An algorithm to solve the max-p-region problem
#' @description The max-p-region problem is a special case of constrained clustering where a finite number of geographical areas, n, are aggregated into the maximum number of regions, p, such that each region satisfies the following const raints: 1. The areas within a region must be geographically connected.
#' @param w An instance of Weight class
#' @param data A 2d numeric list of selected variable
#' @param bound_vals A 1-d vector of selected bounding variable
#' @param min_bound A minimum value that the sum value of bounding variable int each cluster should be greater than
#' @param local_search The name of the heurist algorithm to find a optimal solution. Default to "greedy". Options are "greedy", "tabu" and "sa" (simulated annealing)
#' @param distance_method (optional) The distance method used to compute the distance betwen observation i and j. Defaults to "euclidean". Options are "euclidean" and "manhattan"
#' @param random_seed (optional) The seed for random number generator. Defaults to 123456789.
#' @param initial (optional): The number of iterations of greedy algorithm. Defaults to 99.
#' @param tabu_length (optional): The length of a tabu search heuristic of tabu algorithm. Defaults to 95.
#' @param cool_rate (optional): The cooling rate of a simulated annealing algorithm. Defaults to 0.85
#' @param init_seeds (optional): The initial clusters that the local search starts with, e.g. one can assign the LISA cluster as the init_seeds for max-p method. Default is empty. means the local search starts with a random process to "grow" clusters
#' @return A 2d list represents a group of clusters
#' @export
maxp <- function(w, data, bound_vals, min_bound, local_search, distance_method = "Euclidean",
                 random_seed = 123456789, initial = 99, tabu_length = 95, cool_rate = 0.85,
                 init_seeds = c(0)) {

  if (w$num_obs < 1) {
    stop("The weights is not valid.")
  }
  if (length(data) < 1) {
    stop("The data from selected variable is empty.")
  }
  if (length(bound_vals) != w$num_obs) {
    stop("The bound_vals has to be a list of numeric values, e.g. a column of input table.")
  }
  if (min_bound <= 0) {
    stop("The min_bound has to be a positive numeric value.")
  }
  return(gda_maxp(w$gda_w, data, bound_vals, min_bound, local_search, initial, tabu_length, cool_rate, init_seeds, distance_method, random_seed))
}

############################################################
#' @title Between Sum of Square
#' @description Compute between sum of square value of a group of clusters
#' @param clusters A 2d list which returns from spatial clustering methods, e.g. skater()
#' @param data A 2d list which is used in spatial clustering methods, e.g. skater(k, w, data)
#' @return A value of between sum of square value
#' @export
between_sumofsquare <- function(clusters, data) {
  return(gda_betweensumofsquare(clusters, data))
}


############################################################
#' @title Total Sum of Square
#' @description Compute total sum of square value of a 2d tuple data
#' @param data A 2d list which is used in spatial clustering methods, e.g. skater(k, w, data)
#' @return A value of total sum of square value
#' @export
total_sumofsquare <- function(data) {
  return(gda_totalsumofsquare(data))
}

############################################################
#' @title Within Sum of Square
#' @description Compute within sum of square value of a group of clusters
#' @param clusters A 2d list which returns from spatial clustering methods, e.g. skater()
#' @param data A 2d list which is used in spatial clustering methods, e.g. skater(k, w, data)
#' @return A value of within sum of square value
#' @export
within_sumofsquare <- function(clusters, data) {
  return(gda_totalsumofsquare(clusters, data))
}

