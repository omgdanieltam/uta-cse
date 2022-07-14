# Daniel Tam (1001724986)
# CSE 4309-001

import sys, statistics, math

class TrainingObjects:
    def __init__(self, classification, attr, value):
        self.classification = classification
        self.attr = attr
        self.value = value

class AttributeObjects:
    def __init__(self, attrID, values):
        self.attrID = attrID
        self.values = values
        self.prob = 0.0

class TrainingCalculations:
    def __init__(self, classID, attrID, mean, stddev):
        self.classID = classID
        self.attrID = attrID
        self.mean = mean
        self.stddev = stddev

class TestObjects:
    def __init__(self, id, true_class):
        self.id = id
        self.true_class = true_class
        self.values = list()
        self.x = 0.0
        self.acc = 0.0

def calculateAcc(prob, trueclass):
    maxlist = list()

    for i in range(len(prob)):
        if prob[i] == max(prob):
            maxlist.append(i+1)

    if len(maxlist) == 1:
        if maxlist[0] == trueclass:
            return 1
        else:
            return 0
    else:
        if trueclass in maxlist:
            return 1 / len(maxlist)
        else:
            return 0

def naive_bayes(training_file, test_file):

    # Open file
    trainingfile = open(training_file, 'r')
    lines = trainingfile.readlines()

    pos_classification = list() # List of possible classifications
    all_training = list() # List of all training classes
    training_calc = list()
    all_attr = list()
    overall = list()
    pos_attr = 0

    # Read line by line
    for line in lines:
        line = line.strip() # remove newline character
        splitLine = line.split() # split by whitespace

        # find the classication this line belongs to
        classification = int(splitLine[-1])

        # check to see if it's in our classification list
        if classification not in pos_classification:
            pos_classification.append(classification)

        # go through line adding each element to class and
        # the class to a list
        for i in range(len(splitLine)-1):
            all_training.append(TrainingObjects(classification, i+1, float(splitLine[i])))

    # sort classifications 
    pos_classification.sort()
    
    pos_attr = len(splitLine)

    # iterate through all possible classifications
    for i in range (len(pos_classification)):

        # iterate through all possible attributes
        for j in range (1, len(splitLine)):
            calculation = list() # temp list for calculations

            # iterate through all training objects
            for k in range(len(all_training)):
                # if the classification and attribute matches, add to list
                if all_training[k].classification == pos_classification[i] and all_training[k].attr == j:
                    calculation.append(all_training[k].value)

            
            # ensure standard deviation is not smaller than 0.01
            stddev = statistics.stdev(calculation)
            if stddev <  0.0001:
                stddev = 0.01

            mean = statistics.mean(calculation)

            # print
            print("Class %d, attribute %d, mean = %.2f, std = %.2f" % (pos_classification[i], j, mean, stddev))

            all_attr.append(AttributeObjects(j, calculation))
            training_calc.append(TrainingCalculations(pos_classification[i], j, mean, stddev))


    # get probability of each attribute
    for item in all_attr:
        item.prob = len(item.values) / len(lines)

    # Open file
    testfile = open(test_file, 'r')
    linesTest = testfile.readlines()

    index = 1

    for line in linesTest:
        line = line.strip() # remove newline character
        splitLine = line.split() # split by whitespace

        test_list = list()
        for item in splitLine:
            test_list.append(float(item))
        p = test_list.pop()

        testingObj = TestObjects(index, p)

        for i in range (len(pos_classification)):
            p1 = 1

            for j in training_calc:
                
                if j.classID == pos_classification[i]:
                    
                    listvalue = test_list.pop(0)
                    
                    # gaussian calculation
                    p2 = (1 / (j.stddev * math.sqrt(2 * math.pi)) * (math.exp(-1 * (((listvalue - j.mean)**2) / (2 * (j.stddev**2))))))
                    p1 = p1*p2
            
            testingObj.values.append(p1)

            # reset list
            for item in splitLine:
                test_list.append(float(item))
            test_list.pop()

        # calculate x
        index2 = 0
        for i in range(0, len(all_attr), pos_attr-1):
            testingObj.x += + (testingObj.values[index2] * all_attr[i].prob)
            
            index2 = index2+1

        prob = list()

        # calculate proability
        index2 = 0
        for i in range(0, len(all_attr), pos_attr-1):
            prob.append((testingObj.values[index2] * all_attr[i].prob) / testingObj.x)
            index2 = index2+1

        testingObj.acc = calculateAcc(prob, testingObj.true_class)

        # print
        print("ID=%5d, predicted=%3d, probability = %.4f, true=%3d, accuracy=%4.2f" % (testingObj.id, prob.index(max(prob))+1, max(prob), testingObj.true_class, testingObj.acc))

        index = index+1

        overall.append(testingObj)
    
    sums = 0.0
    for i in overall:
        sums = sums + i.acc

    print("classification accuracy=%6.4f" % (sums / len(overall)))

    

# Command line arguments
if len(sys.argv) != 3:
    print("Invalid arguments; must contain training and test files.\n ex: naive_bayes.py training.txt test.txt")
    exit()

# Run function
naive_bayes(sys.argv[1], sys.argv[2])