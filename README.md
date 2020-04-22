# Simple Linear Regression (C++)
This is a C++ class for calculating a simple linear regression model and producing the results as an object. In the code file there is also a main function to demonstrate an example of usage.

# Usage 
 - Data should be given in the format of arrays of float, along with sample size, for example: "slr regression (samplesize, datax, datay);" where "slr" is the name of the class, "regression" is the name of the object we want to create with the results, "samplesize" is an int, "datax" and "datay" are arrays of float. 
 - Results are provided as public variables within the regression object, as follows: 
   - .sample = the sample size 
   - .xbar = the mean of the x values
   - .ybar = the mean of the y values
   - .r = the Pearson Correlation between x and y (r)
   - .rsquared = the r-squared for the model
   - .alpha = the alpha coefficient
   - .beta = the beta coefficient
   - .SEBeta = the standard error for beta
   - .t = the t-value for beta
   - .residualSE = the standard error for the residuals
   - .residualmean = the average distance between observed values of y and predicted values of y (will always be positive)
   - .residualmax = the largest residual difference
   - .residualmin = the smallest residual difference
   - .SSR = the sum of squares for the residuals
   - .SSE = the sum of squares explained by the model
   - .SST = the total sum of squares
   - .residuals[] = an array of float (equal in size to the sample) containing individual residual values
 
# About 
This class was constructed by George Maier from the London School of Economics. Twitter: @GeorgeMaier
