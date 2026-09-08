import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, mean_absolute_error

X = np.array([[1], [2], [3], [4], [5]])
Y = np.array([3, 4, 2, 5, 6])

model = LinearRegression()
model.fit( X, Y )

y_pred = model.predict( X )

plt.scatter( X, Y, color = 'blue', label = 'Actual Data')
plt.plot( X, y_pred, color = 'red', label = 'Fit Line')

for xi, yi, ypi in zip( X.flatten(), Y, y_pred ) :
    plt.vlines( x = xi, ymin = yi, ymax = ypi, color = 'gray', linestyle = 'dashed')


plt.xlabel('X (Independent)')
plt.ylabel('Y (Dependent)')
plt.title('Scatter plot with regression line and residuals')
plt.legend()
plt.show()

print("Intercept (b0) : ", model.intercept_)
print("Slope (b1) : ", model.coef_[0])
print("MSE : ", mean_squared_error( Y, y_pred))
print("MAE : ", mean_absolute_error( Y, y_pred))