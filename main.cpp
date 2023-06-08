#include <iostream>
#include <vector>
#include "slr.h"

#define DATASIZE 25


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
    regression.compute();
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
	