"""
DATE : 2026-07-14
author : Shubham Khedkar
assignment : Implement Scatter Plot using Matplotlib
"""
import matplotlib.pyplot as plt

x = [50, 70, 80, 90, 60, 70, 80, 90, 100, 60, 70, 80, 90, 100]
y = [50, 70, 80, 90, 60, 70, 80, 90, 100, 60, 70, 80, 90, 100]
plt.scatter(x, y, color="blue", linewidth=1.5)
plt.title("Scatter Plot")
plt.xlabel("X Values")
plt.ylabel("Y Values")
plt.show()


