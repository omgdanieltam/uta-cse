# Daniel Tam
# 1001724986

import numpy, sys, math, collections, random

class node:
    def __init__(self, attribute, threshold, gain):
        self.attribute = attribute
        self.threshold = threshold
        self.gain = gain

        self.left  = None
        self.right = None
        self.distribution = list() 

def get_data(input_file):
    data = list()
    opened_file = open(input_file, 'r')
    lines = opened_file.readlines()

    for line in lines:
        temp = list()
        line = line.strip()
        split = line.split()

        for i in range(0, len(split)):
            temp.append(float(split[i]))

        data.append(temp)

    return numpy.asarray(data)   

def DTL_TopLevel(examples):
    attributes = []

    for i in range(0, len(examples[0][:-1])):
        attributes.append(i)

    default  = distribution(examples)

    return DTL(examples, attributes, default)

def DTL(examples, attribute, default):
    unique_len = len(numpy.unique(examples[:,-1]))

    if len(examples)-1 < prune_threshold:
        tree = node(-1, -1, 0)
        tree.distribution = default        
    elif unique_len == 1:
        tree = node(0, 0, 0)
        for i in range(0, len(classes_unique)):
            if examples[0, -1] != i:
                tree.distribution.append(0)
            else:
                tree.distribution.append(1)     
    else:
        best_attribute, best_threshold, max_gain = choose_attributes(examples, attribute)
        tree = node(best_attribute, best_threshold, max_gain)
        examples_left = examples[examples[:, best_attribute] < best_threshold]
        examples_right = examples[examples[:, best_attribute] >= best_threshold]  
        tree.left = DTL(examples_left, attribute, distribution(examples))
        tree.right = DTL(examples_right, attribute, distribution(examples))
    
    return tree

def distribution(examples):
    if (len(examples)-1) == 0:
        return [0]
    
    classes = list(examples[:,-1])

    probability = []
    for i in range(0, len(classes_unique)):
        probability.append(classes.count(classes_unique[i]))

    return numpy.asarray(probability) / len(classes)

def choose_attributes(examples, attributes):
    max_gain = -1
    best_attribute = -1
    best_threshold = -1
    
    if option == 'optimized':
        for A in attributes:
            attribute_values = examples[:,A]
            L = min(attribute_values)
            M = max(attribute_values)

            for K in range(1, 51):
                threshold = L + K * (M-L) / 51
                gain = information_gain(examples, A, threshold)

                if gain > max_gain:
                    best_attribute = A
                    best_threshold = threshold
                    max_gain = gain
    else:
        random_attribute = random.choice(attributes)
        attribute_values = examples[:,random_attribute]
        L = min(attribute_values)
        M = max(attribute_values)

        for K in range(1, 51):
            threshold = L + K * (M-L) / 51
            gain = information_gain(examples, random_attribute, threshold)
            
            if gain > max_gain:           
                best_attribute = random_attribute
                best_threshold = threshold
                max_gain = gain
        
    return best_attribute, best_threshold, max_gain

def information_gain(examples, attributes, threshold):
    target = list(examples[:,-1])
    base = collections.Counter(target)
    target = numpy.unique(numpy.asarray(target))
    base_entropy = 0
    for i in range(0, len(target)):
        if base[target[i]] > 0:
            base_entropy = base_entropy - ((base[target[i]]) / (len(examples)-1)) * math.log((base[target[i]]/(len(examples)-1)), 2 )

    left = examples[examples[:,attributes] < threshold]
    dict_left = collections.Counter(left[:,-1])
    target_left = numpy.unique(numpy.asarray(left))
    left_entropy = 0
    for i in range(0, len(target_left)):
        if dict_left[target_left[i]] > 0:
            left_entropy = left_entropy - ((dict_left[target_left[i]])/len(left)) * math.log(((dict_left[target_left[i]]) / len( left ) ), 2 )

    right = examples[examples[:,attributes] >= threshold]
    dict_right = collections.Counter(right[:,-1])
    target_right = numpy.unique(numpy.asarray(right))
    right_entropy = 0
    for i in range(0, len(target_right)):
        if dict_right[target_right[i]] > 0:
            right_entropy = right_entropy - ((dict_right[target_right[i]]) / len( right ) ) * math.log(((dict_right[target_right[i]])/len(right)),2)

    gain = base_entropy - (len(left)/(len(examples)-1) * left_entropy) - (len(right)/(len(examples)-1) * right_entropy)
    
    return gain

def label_out(test, trees, id, node):
    distribution_list =[]

    print('tree=%2d, node=%3d, feature=%2d, thr=%6.2f, gain=%f'%( id, node, trees.attribute, trees.threshold, trees.gain))
    
    if trees.left is None and trees.right is None:
        distribution_list = list(trees.distribution)
        labels = distribution_list.index(max(distribution_list)) + min(classes_unique)
        return labels
    else:
        node = node+1
        if trees.right is None or test[trees.attribute] < trees.threshold:
            return label_out(test, trees.left, id, node)
        else:
            return label_out(test, trees.right, id, node)

def output(forest, test_data):
    output = []
    labels = []
    accuracy = []

    for tree in range(len(forest)):
        for j in range(0, len(test_data[:, :-1])):
            t = label_out(test_data[j], forest[tree], tree+1,j+1)
            labels.append(t)

        for k in range(0, len(test_data)):

            if isinstance(labels[k], float):
                if labels[k] == test_data[k,-1]:
                    accuracy = numpy.append(accuracy, 1)
                else:
                    accuracy = numpy.append(accuracy, 0)
                  
            else:
                if test_data[k,-1] in labels[k]:
                    accuracy = numpy.append(accuracy, 1/len(labels[k]))
                else:
                    accuracy = numpy.append(accuracy, 0)
            
            print('ID=%5d, predicted=%3d, true=%3d, accuracy=%4.2f' %(k+1, labels[k], test_data[k, -1], accuracy[-1]))
        
        accuracy = numpy.asarray(accuracy)
        out = numpy.sum(accuracy) / len(accuracy)
        output.append(out)
        print('classification accuracy=%6.4f\n' %(out))

def decision_tree(training_file, test_file):
    training_data = get_data(training_file)
    test_data = get_data(test_file)
    
    global classes_unique
    classes_unique = numpy.unique(training_data[:,-1])

    count = 1
    if option == 'forest3':
        count = 3
    elif option == 'forest15':
        count = 15

    forest = list()
    for i in range(count):
        forest.append(DTL_TopLevel(training_data))

    output(forest, test_data)
    
# Command line arguments
if len(sys.argv) == 5:
    if sys.argv[3] == "optimized" or sys.argv[3] == "randomized" or sys.argv[3] == "forest3" or sys.argv[3] == "forest15":
        option = sys.argv[3]
        prune_threshold = int(sys.argv[4])
        decision_tree(sys.argv[1], sys.argv[2])
    else:
        print("Invalid arguments.")
        exit()
else:
    print("Invalid arguments.")
    exit()
