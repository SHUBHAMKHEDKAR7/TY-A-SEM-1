"""
DATE : 2026-07-14
author : Shubham Khedkar
assignment : Implement Pie Chart using Matplotlib
"""
import matplotlib.pyplot as plt

Subject = ["Math", "Science", "English"]
Marks = [90, 80, 70]

plt.pie(Marks, labels=Subject, autopct="%1.1f%%", startangle=90)
plt.title("Subject Marks")
plt.xlabel("Subjects")
plt.ylabel("Marks")
plt.show()