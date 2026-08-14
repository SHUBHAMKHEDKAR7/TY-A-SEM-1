"""
DATE : 2026-07-28
author : Shubham Khedkar
assignment : Based on Linear Regression 
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error , mean_absolute_error

df = pd.read_csv("house_data.csv")

x = np.array([[1] , [2] , [3] , [4] , [5]])
y = np.array([3 , 4 , 2 , 5 , 6])

#Train Linear Regression Model 

Model = LinearRegression()
Model.fit(x , y)

#Prediction 

Y_pred = Model.predict(x)


#Scatter Plot And Regresstion Line 
plt.scatter(x , y , color = 'blue' , label = 'Actual Data')
plt.scatter(x , Y_pred , color = 'red' , label = 'Fit Line')

#Residual Lines
for xi , yi , ypi in zip(x.flatten() , y , Y_pred):
    plt.vlines(x = xi , ymin = yi , ymax = ypi , color = 'gray' , linestyle= 'dashed')


plt.xlabel('X(Indeoendent)')
plt.ylabel('Y(Dependent)')
plt.title('Scatter Plot wih Regression Line and Residuals')
plt.legend()
plt.show()

#model Parameters and Error Matrics 
print("Intercept(b0):" , Model.intercept_)
print("Slope(b1):" , Model.coef_[0])
print("MSE" , mean_squared_error(y , Y_pred))
print("MAE" , mean_absolute_error(y , Y_pred))