"""
DATE : 2026-07-14
author : Shubham Khedkar
assignment : Implement Histogram using Matplotlib
"""
import matplotlib.pyplot as plt

mark = [50, 70, 80, 90, 60 , 70, 80, 90, 100, 60, 70, 80, 90, 100]
plt.hist(mark, bins=5 , edgecolor="Black" , color = "blue" , linewidth = 1.5) 
plt.title("Histogram")
plt.xlabel("Marks")
plt.ylabel("Frequency")
plt.show()