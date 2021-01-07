context("clustering.R")


testthat::test_that('azp_greedy', {
    guerry_path <- system.file("extdata", "Guerry.shp", package = "rgeoda")
    guerry <- geoda_open(guerry_path)
    guerry_df <- as.data.frame(guerry)
    queen_w <- queen_weights(guerry)
    data <- as.list(guerry_df[c('Crm_prs','Crm_prp','Litercy','Donatns','Infants','Suicids')])

    azp_clusters <- azp_greedy(5, queen_w, data)

    totalss <- total_sumofsquare( data )
    betweenss <- between_sumofsquare(azp_clusters, data)
    ratio <- betweenss / totalss

    testthat::expect_equal( ratio, 0.35985409831772192)
})

