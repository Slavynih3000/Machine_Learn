import datasets
import matplotlib.pyplot as plt
import sys, numpy as np
import emnist
import keras
from keras import to_categorical

(x_train, y_train), (x_test, y_test) = emnist.load_data('digits')
for i in range(5):
    plt.subplot(1, 5, i + 1)
    plt.imshow(x_train[i], cmap='gray')
    plt.title(f"Label: {y_train[i]}")
plt.suptitle("Before Normalization")
plt.show()

images, labels = (x_train[0:1000].reshape(1000, 28 * 28) / 255, y_train[0:1000])

# Display the first five images after normalization
for i in range(5):
    plt.subplot(1, 5, i + 1)
    plt.imshow(images[i].reshape(28, 28), cmap='gray')
    plt.title(f"Label: {labels[i]}")
plt.suptitle("After Normalization")
plt.show()

one_hot_labels = np.zeros((len(labels),10))
for i,l in enumerate(labels):
    one_hot_labels[i][l] = 1
labels = one_hot_labels

test_images = x_test.reshape(len(x_test),28*28) / 255
test_labels = np.zeros((len(y_test),10))
for i,l in enumerate(y_test):
    test_labels[i][l] = 1
np.random.seed(1)
def relu(x):
  return (x >= 0) * x # returns x if x > 0
                        # returns 0 otherwise
def relu2deriv(output):
  return output >= 0 #returns 1 for input > 0

alpha, iterations, hidden_size = (0.005, 300, 100)
pixels_per_image, num_labels = (784, 10)

weights_0_1 = 0.2*np.random.random((pixels_per_image,hidden_size)) - 0.1
weights_1_2 = 0.2*np.random.random((hidden_size,num_labels)) - 0.1

train_errors = []
train_accuracies = []
test_errors = []
test_accuracies = []

for j in range(iterations):
  error, correct_cnt = (0.0,0)
  for i in range(len(images)):
    layer_0 = images[i:i+1]
    layer_1 = relu(np.dot(layer_0,weights_0_1))
    dropout_mask = np.random.randint(2, size=layer_1.shape)
    layer_1 *= dropout_mask * 2
    layer_2 = np.dot(layer_1,weights_1_2)

    error += np.sum((labels[i:i+1] - layer_2) ** 2)
    correct_cnt += int(np.argmax(layer_2) == np.argmax(labels[i:i+1]))
    layer_2_delta = (labels[i:i+1] - layer_2)
    layer_1_delta = layer_2_delta.dot(weights_1_2.T) * relu2deriv(layer_1)
    layer_1_delta *= dropout_mask

    weights_1_2 += alpha * layer_1.T.dot(layer_2_delta)
    weights_0_1 += alpha * layer_0.T.dot(layer_1_delta)

  if(j%10 == 0):
    test_error = 0.0
    test_correct_cnt = 0

    for i in range(len(test_images)):
      layer_0 = test_images[i:i+1]
      layer_1 = relu(np.dot(layer_0,weights_0_1))
      layer_2 = np.dot(layer_1, weights_1_2)

      test_error += np.sum((test_labels[i:i+1] - layer_2) ** 2)
      test_correct_cnt += int(np.argmax(layer_2) == np.argmax(test_labels[i:i+1]))

      train_errors.append(error / len(images))
      train_accuracies.append(correct_cnt / len(images))
      test_errors.append(test_error / len(test_images))
      test_accuracies.append(test_correct_cnt / len(test_images))

    sys.stdout.write("\n" + \
                    "I:" + str(j) + \
                    " Test-Err:" + str(test_error/ float(len(test_images)))[0:5] +\
                    " Test-Acc:" + str(test_correct_cnt/ float(len(test_images)))+\
                    " Train-Err:" + str(error/ float(len(images)))[0:5] +\
                    " Train-Acc:" + str(correct_cnt/ float(len(images))))
epochs = range(0, 3000000, 10)#30000=iterations
plt.figure(figsize=(12, 6))

# График ошибки
plt.subplot(1, 2, 1)
plt.plot(epochs, train_errors, label='Train Error')
plt.plot(epochs, test_errors, label='Test Error')
plt.xlabel('Epoch')
plt.ylabel('Error')
plt.legend()

# График точности
plt.subplot(1, 2, 2)
plt.plot(epochs, train_accuracies, label='Train Accuracy')
plt.plot(epochs, test_accuracies, label='Test Accuracy')
plt.xlabel('Epoch')
plt.ylabel('Accuracy')
plt.legend()

plt.show()
for i in range(11):
    layer_0 = test_images[i:i+1]
    layer_1 = relu(np.dot(layer_0, weights_0_1))
    layer_2 = np.dot(layer_1, weights_1_2)

    # The layer_2 contains the prediction for this input image
    prediction = layer_2

    # You can also find the predicted label by taking the argmax of the prediction
    predicted_label = np.argmax(prediction)

    # Now you can use the predicted_label for further processing or evaluation

    # If you want to compare the prediction to the ground truth label
    true_label = np.argmax(test_labels[i:i+1])

    print(f"Sample {i}: Predicted Label: {predicted_label}, True Label: {true_label}")