import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Read the CSV file into a pandas DataFrame
df = pd.read_csv('Hashing.csv')

# Group the data by load factor and hashing type
grouped = df.groupby(['Load-Factor', 'Hashing-type'])

# Calculate the mean search count for each group
result = grouped['Search-count'].mean().reset_index()

# Create a pivot table to separate hashing techniques
pivot_table = result.pivot_table(index='Load-Factor', columns='Hashing-type', values='Search-count')

# Create a bar plot for different hashing techniques and load factors
pivot_table.plot(kind='bar', figsize=(10, 6))

# Set plot labels and title
plt.xlabel('Load Factor')
plt.ylabel('Average Search Count')
plt.title('Analysis of Hashing Techniques with Different Load Factors')

# Show the plot
plt.legend(title='Hashing Technique')

# Show the plot
plt.show()
