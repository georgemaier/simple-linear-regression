//
// Created by tzuk on 6/8/23.
//

#ifndef SIMPLE_LINEAR_REGRESSION_SLR_H
#define SIMPLE_LINEAR_REGRESSION_SLR_H

#include <vector>
#include <math.h>

class slr {
private:
    double WN1 = 0, WN2 = 0, WN3 = 0, WN4 = 0, Sy = 0, Sx = 0;

    void mean();

    void calculateRCorrelation();

    void calculateAlphaAndBeta();

    void calculateErrors();

    void calculateTTestForBeta();

public:
    slr(std::vector<std::pair<double, double>> &data);

    double r = 0, rsquared = 0, alpha = 0, beta = 0;
    double yhat = 0, ybar = 0, xbar = 0;
    double SSR = 0, SSE = 0, SST = 0;
    double residualSE = 0, residualmax = 0, residualmin = 0, residualmean = 0, t = 0;
    double SEBeta = 0;
    unsigned long sampleSize = 0;
    std::vector<double> residuals;
    std::vector<std::pair<double, double>> data;

    void compute();
};


#endif //SIMPLE_LINEAR_REGRESSION_SLR_H
