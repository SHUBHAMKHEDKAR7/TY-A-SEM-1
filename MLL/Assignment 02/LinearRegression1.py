"""
DATE : 2026-07-28
author : Shubham Khedkar
assignment : Based on Linear Regression 
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

# 1. Load your local dataset
df = pd.read_csv('house_data.csv')

# Drop any rows with empty cells to prevent training errors
df = df.dropna()

# 2. Define multiple independent variables (X) and single target variable (y)
X = df[['area', 'bedrooms', 'bathrooms', 'age', 'parking']].values  
y = df['price'].values

# 3. Split data into training (80%) and testing (20%) sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 4. Initialize and Train the model
model = LinearRegression()
model.fit(X_train, y_train)

# 5. Make Predictions
y_pred = model.predict(X_test)

# 6. Evaluate the Model
mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

print(f"Mean Squared Error (MSE): {mse:.4f}")
print(f"R-squared Score (R²): {r2:.4f}")

# 7. Print Model Weights (Coefficients) for transparency
print("\nModel Weights:")
features = ['area', 'bedrooms', 'bathrooms', 'age', 'parking']
for feat, coef in zip(features, model.coef_):
    print(f"{feat}: {coef:.2f}")
print(f"Intercept: {model.intercept_:.2f}")

# 8. Corrected Plotting: Actual vs Predicted Prices
plt.figure(figsize=(8, 6))
plt.scatter(y_test, y_pred, color='blue', alpha=0.6, label='Predicted vs Actual')

# Draw a perfect diagonal reference line (where y_test == y_pred)
perfect_line = np.linspace(min(y_test), max(y_test), 100)
plt.plot(perfect_line, perfect_line, color='red', linestyle='--', linewidth=2, label='Perfect Prediction Line')

plt.title('Multiple Linear Regression: Actual vs Predicted House Prices')
plt.xlabel('Actual Price')
plt.ylabel('Predicted Price')
plt.legend()
plt.grid(True)
plt.show()