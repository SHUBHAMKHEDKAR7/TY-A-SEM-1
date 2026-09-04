"""
PROBLEM STATEMENT:-

Select any real-world dataset of your choice and study the data properly. 
Choose suitable input features and target variables for both classification and regression problems. 
Apply the first four machine learning algorithms taught in class to both problems. 
Perform the required data preprocessing, train and test the models, compare their results using suitable evaluation measures, 
and find which algorithm gives the best performance for classification and regression."""


"""
File : Real_World_Problem.py
DATE : 2026-09-04
Day : Friday
author : Shubham Khedkar
"""
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression, LogisticRegression
from sklearn.metrics import mean_squared_error, mean_absolute_error ,r2_score, accuracy_score, confusion_matrix, precision_score, recall_score, f1_score
from sklearn.preprocessing import StandardScaler
from sklearn.naive_bayes import GaussianNB

df = pd.read_csv('wineQT.csv')
df.head()
data = df[['fixed acidity','volatile acidity','citric acid','residual sugar','chlorides','free sulfur dioxide','total sulfur dioxide','density','pH','sulphates','alcohol','quality']]

print("Linear Regression Model:\n")
x_reg = data.drop('quality', axis=1)
y_reg = data['quality']
x_train, x_test, y_train, y_test = train_test_split(
    x_reg,
    y_reg,
    test_size=0.2,
    random_state=42
)
model = LinearRegression()
model.fit(x_train, y_train)
y_pred = model.predict(x_test)
mse = mean_squared_error(y_test, y_pred)
mae = mean_absolute_error(y_test, y_pred)
rmse = np.sqrt(mse)
r2 = r2_score(y_test, y_pred)
print("Mean Squared Error :", mse)
print("Mean Absolute Error :", mae)
print("Root Mean Squared Error :", rmse)
print("R-squared :", r2)
print("\n")


print("Logistic Regression Model:\n")
data['quality_label'] = (data['quality'] >= 6).astype(int)


x_class = data.drop(['quality', 'quality_label'], axis=1)
y_class = data['quality_label']


x_train, x_test, y_train, y_test = train_test_split(
    x_class,
    y_class,
    test_size=0.2,
    random_state=42,
    stratify=y_class
)

scaler = StandardScaler()

x_train = scaler.fit_transform(x_train)
x_test = scaler.transform(x_test)

logistic_model = LogisticRegression()


logistic_model.fit(x_train, y_train)


y_pred_logistic = logistic_model.predict(x_test)

accuracy = accuracy_score(y_test, y_pred_logistic)
precision = precision_score(y_test, y_pred_logistic)
recall = recall_score(y_test, y_pred_logistic)
f1 = f1_score(y_test, y_pred_logistic)
confusion = confusion_matrix(y_test, y_pred_logistic)

print("Accuracy :", accuracy)
print("Precision :", precision)
print("Recall :", recall)
print("F1 Score :", f1)

print("Confusion Matrix:")
print(confusion)
print("\n")

print("Naive Bayes Model:\n")

naive_model = GaussianNB()

naive_model.fit(x_train, y_train)

y_pred_naive = naive_model.predict(x_test)

accuracy = accuracy_score(y_test, y_pred_naive)
precision = precision_score(y_test, y_pred_naive)
recall = recall_score(y_test, y_pred_naive)
f1 = f1_score(y_test, y_pred_naive)
confusion = confusion_matrix(y_test, y_pred_naive)


print("Accuracy :", accuracy)
print("Precision :", precision)
print("Recall :", recall)
print("F1 Score :", f1)

print("Confusion Matrix:")
print(confusion)