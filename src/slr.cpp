//
// Created by tzuk on 6/8/23.
//

#include "slr.h"


slr::slr(std::vector<std::pair<double, double>> &data) : data(data) {}

void slr::calculateAlphaAndBeta() {
    Sy = sqrt(WN3 / double(sampleSize - 1));
    Sx = sqrt(WN2 / double(sampleSize - 1));
    beta = r * (Sy / Sx);
    alpha = ybar - beta * xbar;
}

void slr::calculateErrors() {
    residuals.reserve(sampleSize);
    for (int n = 0; n < sampleSize; n++) {
        yhat = alpha + (beta * data[n].first);
        SSE += pow((yhat - ybar), 2);
        SSR += pow((data[n].second - yhat), 2);
        residuals[n] = (data[n].second - yhat);
        if (residuals[n] > residualmax) {
            residualmax = residuals[n];
        }
        if (residuals[n] < residualmin) {
            residualmin = residuals[n];
        }
        residualmean += fabsf64(residuals[n]);
    }
    residualmean = (residualmean / double(sampleSize));
    SST = SSR + SSE;
    rsquared =
            SSE / SST;           //Can also be obtained by r ^ 2 for simple regression (i.e. 1 independent variable)

}

void slr::calculateTTestForBeta() {
    residualSE = sqrtf64(SSR / double(sampleSize - 2));
    SEBeta = (residualSE / (Sx * sqrt(sampleSize - 1)));
    t = beta / SEBeta;
}

std::pair<double, double> slr::mean() {
    double mean_x = 0.0;
    double mean_y = 0.0;
    for (auto &d: data) {
        mean_x += d.first;
        mean_y += d.second;
    }
    return {mean_x / double(sampleSize), mean_y / double(sampleSize)};
}

void slr::calculateRCorrelation() {
    for (int n = 0; n < sampleSize; ++n) {
        WN1 += (data[n].first - xbar) * (data[n].second - ybar);
        WN2 += pow((data[n].first - xbar), 2);
        WN3 += pow((data[n].second - ybar), 2);
    }
    WN4 = WN2 * WN3;
    r = WN1 / (sqrt(WN4));
}

void slr::compute() {
    //This is the main regression function that is called when a new SLR object is created.
    //Calculate means
    sampleSize = data.size();
    auto avg = mean();
    xMean = avg.first;
    yMean = avg.second;
    xbar = xMean;
    ybar = yMean;

    calculateRCorrelation();
    calculateAlphaAndBeta();
    calculateErrors();
    calculateTTestForBeta();

}