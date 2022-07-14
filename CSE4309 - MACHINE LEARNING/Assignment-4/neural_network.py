# Daniel Tam (1001724986)
# CSE 4309-001

import numpy, sys, math

# Data arrays
features = list()
labels = list()
columns = 0
features_normalized = list()
max_value = 0.0
weight_all = []
learning = 1.0
layer_out = []
layer_out_bias = []
layer_error = []
predicted = []

def model_training(features_data, layers):

    bias = numpy.ones((1, features_data.shape[0]))
    features_data = numpy.concatenate((bias, features_data), axis=1)

    layer_out.clear()
    layer_out.append(features_data)
    layer_out_bias.clear()
    layer_out_bias.append(features_data)

    for k in range(layers+1):
        features_data = numpy.dot(features_data, weight_all[k].T)
        features_data = (1 / (1 + numpy.exp(-features_data)))
        layer_out.append(features_data)
        
        if k != layers:
            bias = numpy.ones((1, features_data.shape[0]))
            features_data = numpy.concatenate((bias, features_data), axis=1)

        layer_out_bias.append(features_data)

    return features_data

def valid(predicted, labels_test, max_value):
    for i in range(0, len(predicted)):
        if max_value == predicted[i] and predicted[i] == labels_test:
            return True
    return False

def neural_network(training_file, test_file, layers, units_per_layer, rounds):  

    # Open file
    trainingfile = open(training_file, 'r')
    lines = trainingfile.readlines()

    # Read line by line
    for line in lines:
        temp = list()
        line = line.strip() # remove newline character
        splitLine = line.split() # split by whitespace

        labels.append(splitLine[-1])
        columns = len(splitLine)-1
        
        for i in range(0, len(splitLine)-1):
            temp.append((float(splitLine[i])))

        features.append(temp)

    # Get absolute max value
    max_value = 0.0
    for i in features:
        for j in i:
            if abs(j) > max_value:
                max_value = abs(j)

    # Normalize
    features_normalized = features[:]
    for i in range(0, len(features_normalized)):
        for j in range(0, len(features_normalized[i])):
            features_normalized[i][j] = features_normalized[i][j] / max_value

    # Unique labels
    labels_unique = numpy.unique(labels)

    if units_per_layer == -1 and len(sys.argv) == 5:
        units_per_layer = len(labels_unique)

    # Weights
    numpy.random.seed()
    weights = numpy.zeros((units_per_layer, columns+1))
    for i in range(0, units_per_layer):
        for j in range(0, columns+1):
            weights[i][j] = numpy.random.uniform(low=-0.05, high=0.05)
    weight_all.append(weights)

    for i in range(1, layers): 
        weights = numpy.zeros((units_per_layer, units_per_layer+1))
        for i in range(0, units_per_layer):
            for j in range(0, units_per_layer+1):
                weights[i][j] = numpy.random.uniform(low=-0.05, high=0.05)
        weight_all.append(weights)
    if(layers != 0): 
        weights = numpy.zeros((len(labels_unique), units_per_layer+1))
        for i in range(0, len(labels_unique)):
            for j in range(0, units_per_layer+1):
                weights[i][j] = numpy.random.uniform(low=-0.05, high=0.05)
        weight_all.append(weights)

    # Calculate
    learning = 1.0
    for i in range(0, rounds):
        for j in range(0, len(features)):
            features_data = numpy.array(features[j])
            features_data = features_data[numpy.newaxis, : ]
            features_data = model_training(features_data, layers)

            layer_error.clear()
            encoding = numpy.zeros((1, len(labels_unique)))
            encoding_index = 0
            for k in range (0, len(labels_unique)):
                if labels[j] == labels_unique[k]:
                    encoding_index = k
            encoding[0][encoding_index] = 1

            p1 = (features_data - encoding)
            p2 = (1 - features_data) * features_data
            layer_error.append(p1 * p2)

            for k in range(layers, 0, -1):
                weight_bias = numpy.delete(weight_all[k], 0 , axis=1)
                du = (numpy.dot(layer_error[0], weight_bias))
                di = du * (layer_out[k] * (1 - layer_out[k]))
                layer_error.insert(0, di)

            for k in range(len(weight_all)):
                weight_all[k] = weight_all[k] - (learning * (numpy.dot(numpy.array(layer_error[k]).T, layer_out_bias[k])))

        learning = learning * 0.98
        
    # Data arrays
    features_test = list()
    labels_test = list()
    columns_test = 0
    features_normalized_test = list()

    # Open file (Testing)
    testfile = open(test_file, 'r')
    lines = testfile.readlines()

    # Read line by line
    for line in lines:
        temp = list()
        line = line.strip() # remove newline character
        splitLine = line.split() # split by whitespace

        labels_test.append(splitLine[-1])
        columns_test = len(splitLine)-1
        
        for i in range(0, len(splitLine)-1):
            temp.append((float(splitLine[i])))

        features_test.append(temp)

    # Get absolute max value
    for i in features_test:
        for j in i:
            if abs(j) > max_value:
                max_value = abs(j)

    # Normalize
    features_normalized_test = features_test[:]
    for i in range(0, len(features_normalized_test)):
        for j in range(0, len(features_normalized_test[i])):
            features_normalized_test[i][j] = features_normalized_test[i][j] / max_value

    # Calculate
    for j in range(0, len(features_test)):
        features_data = numpy.array(features_test[j])
        features_data = features_data[numpy.newaxis, : ]
        features_data = model_training(features_data, layers)
        predicted.append(features_data)

    # Calculate Accuracy
    testing_labels = []
    testing_acc = []
    acc = 0

    for i in range(len(predicted)):
        max_value = numpy.amax(predicted[i])
        max_ct = numpy.count_nonzero(predicted[i] == max_value)

        if max_ct == 1:
            index = numpy.argmax(predicted[i])
            label = labels_unique[index]

            if label == labels_test[i]:
                acc = acc+1
        else:
            if valid(predicted[i], labels_test[i], max_value):
                index = numpy.argmax(predicted[i])
                label = labels_unique[numpy.random.choice(index)]
                acc = acc+1 / max_ct

        testing_labels.append(label)
        testing_acc.append(acc / len(labels_test))
        
        print('ID=%5d, predicted=%10s, true=%10s, accuracy=%4.2f\n'% (i+1, label, testing_labels[i], testing_acc[i]))
    print("classification accuracy=%6.4f\n" %(acc / len(testing_labels)))


        

# Command line arguments
if len(sys.argv) == 6:
    neural_network(sys.argv[1], sys.argv[2], int(sys.argv[3])-2, int(sys.argv[4]), int(sys.argv[5]))
elif len(sys.argv) == 5:
    neural_network(sys.argv[1], sys.argv[2], int(sys.argv[3])-2, -1, int(sys.argv[4]))
else:
    print("Invalid arguments.")
    exit()
