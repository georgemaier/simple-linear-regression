#include <iostream>
#include <math.h>

using namespace std;

float mean(int samplesize, float data[samplesize]) {
    float x = 0;
    for (int n = 0; n < samplesize; n++){
        x = x + data[n];
    }
    x = x / samplesize;
    return x; 
}

class slr {
    private: 
        float WN1 = 0, WN2 = 0, WN3 = 0, WN4 = 0, Sy = 0, Sx = 0;

    public:
        float r = 0, rsquared = 0, alpha = 0, beta = 0, x = 0, y = 0;
        float yhat = 0, ybar = 0, xbar = 0;
        float SSR = 0, SSE = 0, SST = 0;
        float residualSE = 0, residualmax = 0, residualmin = 0, residualmean = 0, t = 0; 
        float SEBeta = 0, sample = 0, residuals[];

        slr (int samplesize,float datax[samplesize],float datay[samplesize]){
            //This is the main regression function that is called when a new SLR object is created. 

            //Calculate means
            sample = samplesize;
            xbar = mean(samplesize, datax);
            ybar = mean(samplesize, datay);
            
            //Calculate r correlation
            for (int n = 0; n < samplesize; ++n){
                WN1 += (datax[n]-xbar)*(datay[n]-ybar);
                WN2 += pow((datax[n]-xbar), 2);
                WN3 += pow((datay[n]-ybar), 2);
            }
            WN4 = WN2 * WN3;
            r = WN1 / (sqrt(WN4));

            //Calculate alpha and beta
            Sy = sqrt(WN3/(samplesize-1));
            Sx = sqrt(WN2/(samplesize-1));
            beta = r*(Sy/Sx);
            alpha = ybar - beta*xbar;

            //Calculate SSR, SSE, R-Squared, residuals
            residuals[samplesize];
            for (int n = 0; n < samplesize; n++){
                yhat = alpha + (beta * datax[n]);
                SSE += pow((yhat - ybar), 2);
                SSR += pow((datay[n] - yhat), 2);
                residuals[n] = (datay[n] - yhat);
                if (residuals[n] > residualmax){
                    residualmax = residuals[n];
                }
                if (residuals[n] < residualmin){
                    residualmin = residuals[n];
                }
                residualmean += fabsf(residuals[n]);
            }
            residualmean = (residualmean/samplesize);
            SST = SSR + SSE; 
            rsquared = SSE / SST;           //Can also be obtained by r ^ 2 for simple regression (i.e. 1 independent variable)
            
            //Calculate T-test for Beta
            residualSE = sqrtf(SSR/(samplesize-2));
            SEBeta = (residualSE/(Sx * sqrt(samplesize-1)));
            t = beta / SEBeta;
        }
};

int main() {
    cout << "Simple Linear Regression Calculator - George Maier 2020 \n \n";
	
    //Data should be given in the form of arrays of float in the respective variables
    float datax [25] = {3, 2, 4, 5, 3, 6, 2, 6, 5, 5, 4, 7, 8, 9, 10, 10, 7, 9, 12, 14, 16, 13, 12, 14, 16};
    float datay [25] = {1, 3, 2, 4, 6, 4, 4, 6, 5, 3, 6, 8, 7, 10, 8, 12, 9, 9, 13, 12, 13, 13, 11, 12, 16};
	
    //Determines sample size from the size of the datax array. 
    int samplesize = sizeof(datax)/sizeof(*datax);

    //Runs regression 
    slr regression (samplesize, datax, datay);

    //Print Results 
    cout << "Data descriptions -----------------------------------------------------------------\n";
    cout << "Sample Size: " << regression.sample << "     X mean: " << regression.xbar << ";      Y mean: " << regression.ybar << "\n";
    cout << "Pearson correlation (r): " << regression.r << "\n\n";
    cout << "Regression Model  -----------------------------------------------------------------\n";
    cout << "R squared:           " << regression.rsquared << "\n";
    cout << "Alpha Coefficient:   " << regression.alpha << "\n";
    cout << "Beta Coefficient:    " << regression.beta << "     Std. Error (B):  " << regression.SEBeta << "     t-value:   " << regression.t << "\n\n";
    cout << "Residuals         -----------------------------------------------------------------\n";
    cout << "Residual Std. Error: " << regression.residualSE << " on " << (regression.sample-2) << " degrees of freedom\n";
    cout << "Mean Residual Dist.: " << regression.residualmean << "\n";
    cout << "Max. Residual:       " << regression.residualmax << "\n";
    cout << "Min. Residual:       " << regression.residualmin << "\n \n";
    cout << "Additional Stats  -----------------------------------------------------------------\n";
    cout << "SSResiduals          " << regression.SSR << "\n";
    cout << "SSExplained          " << regression.SSE << "\n";
    cout << "SSTotal              " << regression.SST << "\n\n";
}
	