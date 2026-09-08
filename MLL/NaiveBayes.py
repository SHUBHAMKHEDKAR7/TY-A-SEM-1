"""
File : NaiveBayes.py
DATE : 2026-08-18
Day : Tuesday
author : Shubham Khedkar
assignment03 : Based on Naive Bayes Classifier 
"""

import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB
import matplotlib.pylab as plt
from sklearn.metrics import accuracy_score  , confusion_matrix , precision_score , recall_score , f1_score
from sklearn.metrics import ConfusionMatrixDisplay
df = pd.read_csv('diabetes_prediction_dataset.csv')
data = df[['gender' , 'age' , 'hypertension' , 'heart_disease' , 'bmi' ,'HbA1c_level' , 'blood_glucose_level' , 'diabetes']]
data['gender'] = data['gender'].map({'Male': 0, 'Female': 1 , 'Other': 2})
x = data.drop('diabetes', axis=1)
y = data['diabetes']
x_train, x_test, y_train, y_test = train_test_split(
    x,
    y,
    test_size=0.2,
    random_state=42
)
model = GaussianNB()
model.fit(x_train, y_train)
y_pred = model.predict(x_test)
print("\n")
confusion = confusion_matrix(y_test , y_pred)
print("Confusion Matrix:")
print(confusion)
print("\n")
accuracy = accuracy_score(y_test, y_pred)
print("Accuracy:", accuracy)
print("\n")
precision = precision_score(y_test , y_pred)
print("Precision:", precision)
print("\n")
recall = recall_score(y_test , y_pred)
print("Recall:" , recall)
print("\n")
f1 = f1_score(y_test , y_pred)
print("F1 Score:" , f1)
print("\n")

disp = ConfusionMatrixDisplay(confusion_matrix=confusion, display_labels=['No Diabetes', 'Diabetes'])
disp.plot(cmap=plt.cm.Blues)
plt.title("Confusion Matrix")
plt.show()