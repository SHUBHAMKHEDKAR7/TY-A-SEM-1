"""
DATE : 2026-07-14
author : Shubham Khedkar
assignment : Implement bar Chart using Matplotlib
"""
import matplotlib.pyplot as plt

student = ["a" , "b" , "c"  ]
Marks = [90, 80, 70]

plt.bar(student, Marks, color=["red", "green", "black"])
plt.title("Student Marks")
plt.xlabel("Students")
plt.ylabel("Marks")
plt.show()