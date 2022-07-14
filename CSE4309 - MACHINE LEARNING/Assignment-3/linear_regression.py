# Daniel Tam (1001724986)
# CSE 4309-001

import numpy, sys, math

def linear_regression(training_file, test_file, degree, lambda_in):
    
    # Data arrays
    features = list()
    labels = list()
    columns = 0
    
    # Open file
    trainingfile = open(training_file, 'r')
    lines = trainingfile.readlines()

    # Read line by line
    for line in lines:
        line = line.strip() # remove newline character
        splitLine = line.split() # split by whitespace

        labels.append(float(splitLine[-1]))
        columns = len(splitLine)-1
        
        for i in range(0, len(splitLine)-1):
            features.append((float(splitLine[i])))

    rows = int(len(features)/columns)
    a = numpy.zeros(shape=(rows, int(degree)*columns))
    b = [1] * rows
    b = numpy.array(b)

    count = 0
    row = 0
    for i in range(0, len(features)):
        a[row][count] = features[i]
        count = count+1

        for j in range(2, int(degree)+1):
            a[row][count] = math.pow(features[i], j)
            count = count+1

        if count == columns*int(degree):
            row = row+1
            count = 0

    a = numpy.column_stack((b, a))

    if int(lambda_in) > 0:
        otar = numpy.dot(numpy.transpose(a), labels)
        otar_o = numpy.dot(numpy.transpose(a), a)
        identity = numpy.identity(len(otar_o))
        identitynew = [rows * float(lambda_in) for rows in identity]
        d = numpy.linalg.inv(identitynew + otar_o)
        w = numpy.dot(d,otar)
    else:
        w = numpy.dot(numpy.linalg.pinv(numpy.dot(numpy.transpose(a), a)), numpy.dot(numpy.transpose(a), labels))

    weight = numpy.array(w)

    for i in range(0, len(w)):
        print("W%d=%.4f"%(i, weight[i]))

    
    wtranspose = numpy.transpose(w)

    # Clear previous data
    features.clear()
    labels.clear()
    del a
    del b
    columns = 0

    # Open file
    testfile = open(test_file, 'r')
    lines = testfile.readlines()

    # Read line by line
    for line in lines:
        line = line.strip() # remove newline character
        splitLine = line.split() # split by whitespace

        labels.append(float(splitLine[-1]))
        columns = len(splitLine)-1
        
        for i in range(0, len(splitLine)-1):
            features.append((float(splitLine[i])))

    rows = int(len(features)/columns)
    a = numpy.zeros(shape=(rows, int(degree)*columns))
    b = [1] * rows
    b = numpy.array(b)

    count = 0
    row = 0
    for i in range(0, len(features)):
        a[row][count] = features[i]
        count = count+1

        for j in range(2, int(degree)+1):
            a[row][count] = math.pow(features[i], j)
            count = count+1

        if count == columns*int(degree):
            row = row+1
            count = 0
    
    
    a = numpy.column_stack((b, a))

    labels = numpy.array(labels)
    a = numpy.array(a)
    out = numpy.dot(a, wtranspose)

    for i in range(0, rows):
        print("ID=%5d, output=%14.4f, target value = %10.4f, squared error = %.4f"%(i+1, out[i], labels[i], math.pow((out[i]-labels[i]), 2)))


# Command line arguments
if len(sys.argv) != 5:
    print("Invalid arguments; must contain training file, test file, degree, and lambda.\n ex: linear_regression.py training.txt test.txt 1 0")
    exit()

# Run function
linear_regression(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])