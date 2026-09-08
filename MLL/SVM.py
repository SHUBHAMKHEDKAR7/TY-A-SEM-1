import pandas as pd
import matplotlib.pyplot as plt

from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score

df = pd.read_csv('breast-cancer-selected-columns.csv')

x = df[['radius_mean', 'texture_mean']]
y = df['diagnosis']

y = y.map({'B': 0, 'M': 1})

x_train, x_test, y_train, y_test = train_test_split(
    x, y, test_size=0.2, random_state=42
)

model = SVC(kernel='linear')
model.fit(x_train, y_train)

y_pred = model.predict(x_test)

print("Accuracy:", accuracy_score(y_test, y_pred))

plt.scatter(x['radius_mean'], x['texture_mean'], c=y)

# Hyperplane
w = model.coef_[0]
b = model.intercept_[0]

x_values = x['radius_mean']
y_values = -(w[0] * x_values + b) / w[1]

plt.plot(x_values, y_values)

plt.xlabel('Radius Mean')
plt.ylabel('Texture Mean')
plt.title('SVM Hyperplane')

plt.show()