import matplotlib.pyplot as plt
import csv
import numpy as np

def read_data(file_path):
    x_values, y_values = [], []
    with open(file_path, 'r') as csv_file:
        csv_reader = csv.reader(csv_file)
        for row in csv_reader:
            x_values.append(float(row[0]))
            y_values.append(float(row[1]))
    return x_values, y_values

def calculate_linear_regression_coefficients(x_data, y_data):
    n = len(x_data)
    sum_x = np.sum(x_data)
    sum_y = np.sum(y_data)
    sum_xy = np.sum(np.multiply(x_data, y_data))
    sum_x_squared = np.sum(np.square(x_data))
    slope = (n * sum_xy - sum_x * sum_y) / (n * sum_x_squared - sum_x**2)
    intercept = (sum_y - slope * sum_x) / n
    return intercept, slope

def plot_original_data(x_data, y_data, title):
    plt.scatter(x_data, y_data, marker='o', color='g', s=15, alpha=0.5)
    plt.xlabel('barometr')
    plt.ylabel('hydra L1')
    plt.title(title)

def plot_linear_fit(x_data, y_data, slope, intercept, label):
    plt.scatter(y_data, x_data, marker='o', color='r', s=15)
    plt.plot([slope * x + intercept for x in x_data], x_data, color='b', linewidth=0.5, label=label)
    plt.xlabel('Baromert')
    plt.ylabel('Hydra L1')
    plt.legend()


file_path = 'input.csv'

x_data, y_data = read_data(file_path)

intercept, slope = calculate_linear_regression_coefficients(x_data, y_data)

plt.figure(figsize=(12, 6))

plt.subplot(1, 2, 1)
plot_original_data(x_data, y_data, 'original Data')

plt.subplot(1, 2, 2)
plot_linear_fit(x_data, y_data, slope, intercept, 'aproximation')

plt.tight_layout()
plt.show()

# Print linear regression coefficients
print( intercept, slope)


