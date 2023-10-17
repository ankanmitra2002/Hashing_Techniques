# Content for the README
readme_content = """
# Hashing Techniques Analysis

This project implements and analyzes various hashing techniques in C and provides visual insights into their performance at different load factors using bar plots.

## Hashing Techniques Implemented

The project implements the following hashing techniques:

- **Chaining**: Chaining is a collision resolution method where each hash table slot stores a linked list of key-value pairs.

- **Linear Probing**: Linear probing is a collision resolution method that involves probing linearly for the next available slot when a collision occurs.

- **Double Hashing**: Double hashing is a collision resolution method that uses a secondary hash function to calculate the next slot to probe when a collision occurs.

## Analysis

The project analyzes these hashing techniques with different load factors and visualizes the results in a bar plot. Load factors considered are 0.25, 0.5, 0.75, and 1. The analysis includes:

- Average search counts for different load factors and hashing techniques.
- Comparisons between the three hashing techniques in terms of search performance.

## Getting Started

To run and analyze the hashing techniques:

1. Compile and run the provided C code to generate a CSV file (`Hashing.csv`) containing the search counts.
2. Use the Python script in this repository to create bar plots for analysis.

## Dependencies

This project utilizes the following Python libraries:

- `pandas`
- `numpy`
- `matplotlib`

Install these libraries using pip:

```bash
pip install pandas numpy matplotlib
```
#Plotted Graph-
![hashing](https://github.com/ankanmitra2002/Hashing_Techniques/assets/136356039/30045c96-7a0e-4b63-a361-472c765da2d1)

