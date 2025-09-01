#include "Rcpp.h"
#include <random>
#include "aarand/aarand.hpp"

//[[Rcpp::export(rng=false)]]
Rcpp::NumericVector aa_runif(int n, int seed) {
    Rcpp::NumericVector output(n);
    std::mt19937_64 eng(seed);
    for (int i = 0; i < n; ++i) {
        output[i] = aarand::standard_uniform(eng);
    }
    return output;
}

//[[Rcpp::export(rng=false)]]
Rcpp::NumericVector aa_rnorm(int n, int seed) {
    Rcpp::NumericVector output(n);
    std::mt19937_64 eng(seed);

    int halfn = n / 2;
    bool extra = n % 2 == 1;
    for (int i = 0; i < halfn; ++i) {
        auto found = aarand::standard_normal(eng);
        output[2 * i] = found.first;
        output[2 * i + 1] = found.second;
    }

    if (extra) {
        output[n - 1] = aarand::standard_normal(eng).first;
    }

    return output;
}

//[[Rcpp::export(rng=false)]]
Rcpp::NumericVector aa_rexp(int n, int seed) {
    Rcpp::NumericVector output(n);
    std::mt19937_64 eng(seed);
    for (int i = 0; i < n; ++i) {
        output[i] = aarand::standard_exponential(eng);
    }
    return output;
}

//[[Rcpp::export(rng=false)]]
Rcpp::IntegerVector aa_shuffle(Rcpp::IntegerVector input, int seed) {
    Rcpp::IntegerVector output = Rcpp::clone(input);
    std::mt19937_64 eng(seed);
    aarand::shuffle(output.begin(), output.size(), eng);
    return output;
}

//[[Rcpp::export(rng=false)]]
Rcpp::IntegerVector aa_sample(Rcpp::IntegerVector input, int s, int seed) {
    Rcpp::IntegerVector output(s);
    std::mt19937_64 eng(seed);
    aarand::sample(input.begin(), static_cast<int>(input.size()), s, output.begin(), eng);
    return output;
}

//[[Rcpp::export(rng=false)]]
Rcpp::IntegerVector aa_sample_n(int n, int s, int seed) {
    Rcpp::IntegerVector output(s);
    std::mt19937_64 eng(seed);
    aarand::sample(n, s, output.begin(), eng);
    return output;
}
