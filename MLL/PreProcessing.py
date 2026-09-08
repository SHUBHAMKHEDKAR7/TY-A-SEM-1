"""
DATE : 2026-07-14
author : Shubham Khedkar
assignment : preprocessing of data using pandas
"""
import pandas as pd
import matplotlib.pyplot as plt
df = pd.read_csv("Car data.csv")
print(df.head())
print("\n")
print("\n")
print(df.tail())
print("\n")
print("\n")
print(df.describe())
print("\n")
print("\n")
print(df.info())
print("\n")
print("\n")
print(df.isnull().sum())
print("\n")
print("\n")
print(df.columns)
print("\n")

