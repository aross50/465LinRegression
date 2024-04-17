import numpy as np

def compute_parameters(X, y):
    X = np.array(X)
    y = np.array(y).reshape(-1, 1)  # y needs to be a column vector
    X = np.c_[np.ones(len(X)), X]  # Add a column of ones to X
    XT_X = X.T.dot(X)
    XT_X_inv = np.linalg.inv(XT_X)
    XT_X_inv_XT = XT_X_inv.dot(X.T)
    theta = XT_X_inv_XT.dot(y)
    return theta.flatten()  # Return a flat array

def predict(X, theta):
    X = np.c_[np.ones(len(X)), X]
    return X.dot(theta)

def euclidean_distance(true_values, pred_values):
    return np.sqrt((np.array(true_values) - np.array(pred_values)) ** 2)

def print_formatted_data(X, y_actual, predictions):
    distances = euclidean_distance(y_actual, predictions)
    print(f"{'Training data':<15}{'Prediction':<15}{'Euclidean distance':<15}")
    print(f"{'(x, y)':<15}{'Python':<15}{'':<15}")
    for i in range(len(X)):
        print(f"({X[i][0]:.1f}, {y_actual[i]:.1f})".ljust(15) +
              f"{predictions[i]:<15.5f}" +
              f"{distances[i]:<15.5f}")

def main():
    # Loading data
    X = np.array([-1.1, 0.1, 1.2, 2.3, 3.1, 4.1, 4.8, 5.7])
    y = np.array([-1.7, 2.4, 5.0, 7.3, 10.9, 12.5, 16.2, 19.7])
    
    # Compute the parameters
    theta = compute_parameters(X, y)
    print("Computed parameters:", theta)

    # Make predictions
    predictions = predict(X, theta)

    # Print the formatted data
    print_formatted_data(X.reshape(-1, 1), y, predictions)

if __name__ == "__main__":
    main()
