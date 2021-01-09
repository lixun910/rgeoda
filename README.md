# rgeoda

rgeoda is a R package for spatial data analysis based on libgeoda and GeoDa.
  
    
### Tutorials

https://lixun910.github.io/rgeoda

    
### Installation

NOTE: we are working to make rgeoda avaiable in CRAN. Once it's available on CRAN, one could install it using

```R
install.packages("rgeoda")
```

[Status]: NOT AVAILABLE

#### Build and install from source code

In R console, one can use devtools to install rgeoda from its **source pacakge**:

```R
devtools::install_github("lixun910/rgeoda")
```

#### Mac

For Mac users, the “Xcode Command Line Tools” needs to be installed for installing rgeoda. It is a free software provided by Apple, which can be installed by using the following command in a terminal:
```
xcode-select --install 
```

#### Windows

On Windows, the `Rtools` needs to be installed first. https://cran.r-project.org/bin/windows/Rtools/

#### Linux

For Linux users, the “Build Essential Tools” needs to be installed first.
```
sudo apt-get update
sudo apt-get install build-essential
```

## Current version 0.0.6

* Map Classification
   * NaturalBreaks
   * QuantileBreaks
   * Hinge15Breaks
   * Hinge30Breaks
   * PercentileBreaks
   * StddevBreaks
   
* Spatial Weights
    * Queen
    * Rook
    * Distance based
    * K-Nearest Neighbor
    * Kernel
    
* Spatial Autocorrelation
    * Local Moran
    * Local Geary
    * Local Getis-Ord 
    * Local Join Count
    * Multivariate Local Geary
    * Multivariate Local Join Count
    * Quantile LISA
    * False Discovery Rate (FDR)

* Spatial Clustering
    * SKATER
    * REDCAP
      * First-order and Single-linkage
      * Full-order and Complete-linkage
      * Full-order and Average-linkage
      * Full-order and Single-linkage
      * Full-order and Wards-linkage
    * AZP
      * greedy
      * Tabu Search
      * Simulated Annealing
    * Max-p
      * greedy
      * Tabu Search
      * Simulated Annealing
      
* Data
  * Demean standardize
  * Standardize data (Z)
  * Median absolute deviation

