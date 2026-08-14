import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score  , confusion_matrix , precision_score

df = pd.read_csv('Titanic-Dataset.csv')
data = df[['Survived', 'Pclass', 'Sex', 'SibSp', 'Parch', 'Fare']]
data['Sex'] = data['Sex'].map({'male': 0, 'female': 1})
x = data.drop('Survived', axis=1)
y = data['Survived']
x_train, x_test, y_train, y_test = train_test_split(
    x,
    y,
    test_size=0.2,
    random_state=42
)

model = LogisticRegression()
model.fit(x_train, y_train)
y_pred = model.predict(x_test)
print("\n")
accuracy = accuracy_score(y_test, y_pred)
print("Accuracy:", accuracy)
print("\n")
confusion = confusion_matrix(y_test , y_pred)
print("Confusion Matrix:")
print(confusion)
print("\n")
precision = precision_score(y_test , y_pred)
print("Precision:", precision)