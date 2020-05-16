## ---- include = FALSE----------------------------------------------------
knitr::opts_chunk$set(
  collapse = TRUE,
  comment = "#>"
)

## ----setup---------------------------------------------------------------
library(rgeoda)

## ------------------------------------------------------------------------
guerry_path <- system.file("extdata", "Guerry.shp", package = "rgeoda")
guerry <- geoda_open(guerry_path)

## ------------------------------------------------------------------------
guerry_df <- as.data.frame(guerry)

## ------------------------------------------------------------------------
cat("\nnumber of columns:", ncol(guerry_df))
cat("\nnumber of observations:", nrow(guerry_df))
cat("\nfield names:", names(guerry_df))
cat("\nfield types:", str(guerry_df))

## ------------------------------------------------------------------------
guerry_df[,1]

## ------------------------------------------------------------------------
guerry_df[1,]

## ------------------------------------------------------------------------
guerry_df[,c(3,5)]

## ------------------------------------------------------------------------
guerry_df['Crm_prs']

## ------------------------------------------------------------------------
crm_prs <- guerry_df['Crm_prs'][,1]

## ------------------------------------------------------------------------
crm_prs_prp <- guerry_df[c('Crm_prs', 'Crm_prp')]

## ------------------------------------------------------------------------
queen_w <- queen_weights(guerry)
summary(queen_w)

## ------------------------------------------------------------------------
is_symmetric(queen_w)

## ------------------------------------------------------------------------
has_isolates(queen_w)

## ------------------------------------------------------------------------
weights_sparsity(queen_w)

## ------------------------------------------------------------------------
weights_density(queen_w)

## ------------------------------------------------------------------------
nbrs <- get_neighbors(queen_w, idx = 1)
cat("\nNeighbors of 1-st observation are:", nbrs)

## ------------------------------------------------------------------------
lag0 <- spatial_lag(queen_w, idx = 1, values = crm_prs)
cat("\nSpatial lag of 1-st observation is:", lag0)

## ------------------------------------------------------------------------
rook_w <- rook_weights(guerry)
summary(rook_w)

## ------------------------------------------------------------------------
save_weights(rook_w, out_path = '/Users/xun/Downloads/Guerry_r.gal', 
             layer_name = 'Guerry', 
             id_name = 'CODE_DE', 
             id_values = as.integer(guerry_df['CODE_DE'][,1]))

## ------------------------------------------------------------------------
dist_thres <- min_distthreshold(guerry)
dist_w <- distance_weights(guerry, dist_thres)
summary(dist_w)

## ------------------------------------------------------------------------
knn6_w <- knn_weights(guerry, 6)
summary(knn6_w)

## ------------------------------------------------------------------------
bandwidth <- min_distthreshold(guerry)
kernel_w <- kernel_weights(guerry, bandwidth, kernel_method = "uniform")
summary(kernel_w)

## ------------------------------------------------------------------------
adptkernel_w = kernel_knn_weights(guerry, 6, "uniform")

summary(adptkernel_w)

