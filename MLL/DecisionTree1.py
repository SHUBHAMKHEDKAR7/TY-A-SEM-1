import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier

df = pd.read_csv("breast-cancer-selected-columns.csv")

X = df[
    [
        "radius_mean",
        "texture_mean",
        "perimeter_mean",
        "area_mean",
        "smoothness_mean",
        "compactness_mean",
        "concavity_mean",
        "concave points_mean"
    ]
]

y = df["diagnosis"]

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = DecisionTreeClassifier(random_state=42)

model.fit(X_train, y_train)

y_pred = model.predict(X_test)

entropy_model = DecisionTreeClassifier(
    criterion="entropy",
    random_state=42
)

entropy_model.fit(X_train, y_train)

print("Entropy Tree Accuracy:",
      entropy_model.score(X_test, y_test))

gini_model = DecisionTreeClassifier(
    criterion="gini",
    random_state=42
)

gini_model.fit(X_train, y_train)

print("Gini Tree Accuracy:",
      gini_model.score(X_test, y_test))

information_gain_model = DecisionTreeClassifier(
    criterion="entropy",
    random_state=42
)

information_gain_model.fit(X_train, y_train)

print("Information Gain Tree Accuracy:",
      information_gain_model.score(X_test, y_test))