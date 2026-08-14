"""
File : LogisticRegression.py
DATE : 2026-07-29
Day : Tuesday
author : Shubham Khedkar
assignment03 : Based on Logistic Regression 
"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import (
    accuracy_score, 
    confusion_matrix, 
    precision_score, 
    recall_score, 
    f1_score
)

# ==========================================
# 1. SETUP DATA WITH S-SHAPE RELATIONSHIP
# ==========================================
np.random.seed(52)
# Generate a single continuous feature (e.g., hours studied)
X_raw = np.random.uniform(-5, 5, size=(200, 1))

# Define an underlying mathematical probability using the sigmoid function formula
# P(y=1) = 1 / (1 + e^-x)
probabilities = 1 / (1 + np.exp(-1.5 * X_raw))

# Assign binary targets (0 or 1) based on these real probabilities
y_raw = (np.random.rand(200, 1) < probabilities).astype(int).ravel()

# Structure into standard Pandas formats
df_features = pd.DataFrame(X_raw, columns=['Feature'])
df_target = pd.Series(y_raw, name='Target')

# ==========================================
# 2. TRAIN-TEST SPLIT
# ==========================================
X_train, X_test, y_train, y_test = train_test_split(
    df_features, 
    df_target, 
    test_size=0.2, 
    random_state=42
)

# ==========================================
# 3. FEATURE SCALING
# ==========================================
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# ==========================================
# 4. INSTANTIATE & TRAIN THE MODEL
# ==========================================
model = LogisticRegression(random_state=42)
model.fit(X_train_scaled, y_train)

# ==========================================
# 5. GENERATE PREDICTIONS
# ==========================================
y_pred = model.predict(X_test_scaled)

# ==========================================
# 6. CALCULATE EVALUATION METRICS
# ==========================================
accuracy = accuracy_score(y_test, y_pred)
precision = precision_score(y_test, y_pred)
recall = recall_score(y_test, y_pred)
f1 = f1_score(y_test, y_pred)
conf_matrix = confusion_matrix(y_test, y_pred)

# Print execution results
print("=============================")
print("  LOGISTIC REGRESSION METRICS  ")
print("=============================")
print(f"Accuracy Score  : {accuracy:.4f}")
print(f"Precision Score : {precision:.4f}")
print(f"Recall Score    : {recall:.4f}")
print(f"F1 Score        : {f1:.4f}")
print("\nConfusion Matrix:")
print(conf_matrix)
print("=============================")

# ==========================================
# 7. GENERATE THE SCATTER PLOT WITH S-CURVE
# ==========================================
# Create a smooth range of values across the X-axis grid to build a clean S-curve line
X_curve = np.linspace(df_features['Feature'].min(), df_features['Feature'].max(), 300).reshape(-1, 1)
X_curve_scaled = scaler.transform(X_curve)

# Extract probabilities for the positive class (column index 1)
y_curve_probabilities = model.predict_proba(X_curve_scaled)[:, 1]

# Build visual elements
plt.figure(figsize=(10, 6))

# Scatter plot of actual real data points (separated visually by true class)
plt.scatter(df_features[df_target == 0]['Feature'], df_target[df_target == 0], 
            color='red', alpha=0.5, label='Actual Class 0', edgecolor='k')
plt.scatter(df_features[df_target == 1]['Feature'], df_target[df_target == 1], 
            color='blue', alpha=0.5, label='Actual Class 1', edgecolor='k')

# Line plot for the model's fitted Sigmoid Decision S-Curve
plt.plot(X_curve, y_curve_probabilities, color='black', linewidth=2.5, 
         label='Logistic Regression S-Curve (Probability)')

# Aesthetic adjustments
plt.axhline(0.5, color='gray', linestyle='--', linewidth=1, label='Decision Boundary (0.5)')
plt.title('Logistic Regression Feature vs Target with Sigmoid S-Curve', fontsize=14, pad=15)
plt.xlabel('Feature Value (X)', fontsize=12)
plt.ylabel('Probability / Binary Outcome (Y)', fontsize=12)
plt.legend(loc='center right')
plt.grid(True, alpha=0.3)

# Display the graphic canvas windows
plt.show()
