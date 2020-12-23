context("utils.R")

vec1 <- c(1,2,3,4,5,6,7)
vec2 <- c(1.1,2.2,3.3,4.4,5.5)
c<data <- list(vec1, vec2)

testthat::test_that('utils', {
    testthat::expect_equal(
        demean(data),
        "[[1]]
[1] -3 -2 -1  0  1  2  3

[[2]]
[1] -2.2 -1.1  0.0  1.1  2.2"
    )
})

