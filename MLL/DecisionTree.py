"""# 1. Import Libraries
import pandas as pd

from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier

from sklearn.metrics import (
    accuracy_score,
    precision_score,
    recall_score,
    f1_score,
    confusion_matrix,
    classification_report
)


# 2. Load Dataset
data = pd.read_csv("dataset.csv")


# 3. Select Input Features
X = data[["feature1", "feature2", "feature3"]]


# 4. Select Target / Output
y = data["target"]


# 5. Split Dataset
X_train, X_test, y_train, y_test = train_test_split(
    X,
    y,
    test_size=0.2,
    random_state=42
)


# 6. Create Model
model = DecisionTreeClassifier()


# 7. Train Model
model.fit(X_train, y_train)


# 8. Prediction
y_pred = model.predict(X_test)


# 9. Evaluation Metrics

accuracy = accuracy_score(y_test, y_pred)

precision = precision_score(
    y_test,
    y_pred,
    average="weighted"
)

recall = recall_score(
    y_test,
    y_pred,
    average="weighted"
)

f1 = f1_score(
    y_test,
    y_pred,
    average="weighted"
)


# 10. Display Scores

print("Accuracy :", accuracy * 100, "%")

print("Precision:", precision * 100, "%")

print("Recall   :", recall * 100, "%")

print("F1 Score :", f1 * 100, "%")


# 11. Confusion Matrix

print("\nConfusion Matrix:")

print(
    confusion_matrix(
        y_test,
        y_pred
    )
)


# 12. Classification Report

print("\nClassification Report:")

print(
    classification_report(
        y_test,
        y_pred
    )
)


# 13. Predict New Data

new_data = [[value1, value2, value3]]

prediction = model.predict(new_data)

print("\nNew Prediction:", prediction)"""


# 1. Import Libraries
import pandas as pd

# 2. Load Dataset
df = pd.read_csv("breast-cancer-selected-columns.csv")

#Preprocessing

print(df.head())
print(df.shape)

print(df.isnull().sum())