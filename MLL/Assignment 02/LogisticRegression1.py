import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
#from sklearn.metrics import accuracy_score, confusion_matrix, precision_score, recall_score, f1_score

df = pd.read_csv('Titanic-Dataset.csv')
data = df.drop(['PassengerId', 'Name', 'Ticket', 'Cabin'], axis=1)

x = df.drop(['Survived'], axis=1  )
y = df['Survived']

x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, random_state=42)

model = LogisticRegression()
model.fit(x_train, y_train)

#y_pred = model.predict(x_test)

