% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/utils.R
\name{hinge30_breaks}
\alias{hinge30_breaks}
\title{(Box) Hinge30 Breaks}
\usage{
hinge30_breaks(data)
}
\arguments{
\item{data}{An input data}
}
\value{
A array contains values of computed breaks
}
\description{
Hinge30 breaks data into 6 groups like box plot groups (Lower outlier, < 25%, 25-50%, 50-75%, >75%, Upper outlier) with hinge=3.0
}
\examples{
guerry_path <- system.file("extdata", "Guerry.shp", package = "rgeoda")
guerry <- geoda_open(guerry_path)
guerry_df <- as.data.frame(guerry) # use as data.frame
crm_prs <- guerry_df['Crm_prs'][,1] # get values of variable "crm_prs"
hinge30_breaks(data=crm_prs)
}
