#include <iostream>
#include <math.h>
#include <vector>
#define DATASIZE 25

class slr {
private:
    double WN1 = 0, WN2 = 0, WN3 = 0, WN4 = 0, Sy = 0, Sx = 0;

    std::pair<double, double> mean(std::vector<std::pair<double, double>> &data) const {
        double mean_x = 0.0;
        double mean_y = 0.0;
        for (auto &d: data) {
            mean_x += d.first;
            mean_y += d.second;
        }
        return {mean_x / double(sampleSize), mean_y / double(sampleSize)};
    }

public:
    double r = 0, rsquared = 0, alpha = 0, beta = 0, x = 0, y = 0;
    double yhat = 0, ybar = 0, xbar = 0;
    double yMean = 0, xMean = 0;
    double SSR = 0, SSE = 0, SST = 0;
    double residualSE = 0, residualmax = 0, residualmin = 0, residualmean = 0, t = 0;
    double SEBeta = 0;
    unsigned long sampleSize = 0;
    std::vector<double> residuals;

    explicit slr(std::vector<std::pair<double, double>> &data) {
        //This is the main regression function that is called when a new SLR object is created.
        //Calculate means
        sampleSize = data.size();
        auto avg = mean(data);
        xMean = avg.first;
        yMean = avg.second;
        xbar =xMean;
        ybar = yMean;
        //Calculate r correlation
        for (int n = 0; n < sampleSize; ++n) {
            WN1 += (data[n].first - xbar) * (data[n].second - ybar);
            WN2 += pow((data[n].first - xbar), 2);
            WN3 += pow((data[n].second - ybar), 2);
        }
        WN4 = WN2 * WN3;
        r = WN1 / (sqrt(WN4));

        //Calculate alpha and beta
        Sy = sqrt(WN3 / double(sampleSize - 1));
        Sx = sqrt(WN2 / double(sampleSize - 1));
        beta = r * (Sy / Sx);
        alpha = ybar - beta * xbar;

        //Calculate SSR, SSE, R-Squared, residuals

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

        //Calculate T-test for Beta
        residualSE = sqrtf64(SSR / double(sampleSize - 2));
        SEBeta = (residualSE / (Sx * sqrt(sampleSize - 1)));
        t = beta / SEBeta;
    }
};

int main() {
    std::cout << "Simple Linear Regression Calculator - George Maier 2020, Tzuk Polinsky version 2023" << std::endl;

    //Data should be given in the form of arrays of double in the respective variables
    double datax[DATASIZE] = {3, 2, 4, 5, 3, 6, 2, 6, 5, 5, 4, 7, 8, 9, 10, 10, 7, 9, 12, 14, 16, 13, 12, 14, 16};
    double datay[DATASIZE] = {1, 3, 2, 4, 6, 4, 4, 6, 5, 3, 6, 8, 7, 10, 8, 12, 9, 9, 13, 12, 13, 13, 11, 12, 16};
    std::vector<std::pair<double, double>> data;
    data.reserve(DATASIZE);
    for (int i = 0; i < DATASIZE; ++i) {
        data.emplace_back(datax[i], datay[i]);
    }
    //Runs regression 
    slr regression(data);
    //Print Results 
    std::cout << "Data descriptions -----------------------------------------------------------------" << std::endl;
    std::cout << "sampleSize Size: " << regression.sampleSize << "     X mean: " << regression.xbar << ";      Y mean: "
              << regression.ybar << std::endl;
    std::cout << "Pearson correlation (r): " << regression.r << std::endl;
    std::cout << "Regression Model  -----------------------------------------------------------------" << std::endl;
    std::cout << "R squared:           " << regression.rsquared << std::endl;
    std::cout << "Alpha Coefficient:   " << regression.alpha << std::endl;
    std::cout << "Beta Coefficient:    " << regression.beta << "     Std. Error (B):  " << regression.SEBeta
              << "     t-value:   " << regression.t << std::endl;
    std::cout << "Residuals         -----------------------------------------------------------------" << std::endl;
    std::cout << "Residual Std. Error: " << regression.residualSE << " on " << (regression.sampleSize - 2)
              << " degrees of freedom" << std::endl;
    std::cout << "Mean Residual Dist.: " << regression.residualmean << std::endl;
    std::cout << "Max. Residual:       " << regression.residualmax << std::endl;
    std::cout << "Min. Residual:       " << regression.residualmin << std::endl;
    std::cout << "Additional Stats  -----------------------------------------------------------------" << std::endl;
    std::cout << "SSResiduals          " << regression.SSR << std::endl;
    std::cout << "SSExplained          " << regression.SSE << std::endl;
    std::cout << "SSTotal              " << regression.SST << std::endl;
}
	