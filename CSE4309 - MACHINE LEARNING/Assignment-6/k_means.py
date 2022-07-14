# Daniel Tam
# 1001724986

import numpy, sys, random

def initialize_means (data, k, initialization):
    means = []

    if len(data.shape) == 2:
        col_one = data[:, 0]
        col_two = data[:, 1]

        for i in range(0, k):
            if initialization == 'round_robin':
                new_one = []
                new_two = []

                for j in range(i, len(data), k):
                    new_one.append(col_one[j])
                    new_two.append(col_two[j])

                means.append((sum(new_one) / len(new_one), sum(new_two) / len(new_two)))
            else:
                means.append((random.random(), random.random()))

    else:
        for i in range(0, k):
            if initialization == 'round_robin':
                new = []
                for j in range(i, len(data), k):
                    new.append(data[j])
                means.append(sum(new)/len(new))
            else:
                random_list = list(numpy.random.randint(low=1, high=4, size=len(data)))
                for i in range (1, k+1):
                    new = []
                    for j in range(0, len(data)):
                        if i == random_list[j]:
                            new.append(data[j])

                    means.append(sum(new)/len(new))
                return means

    return means

def calculate(data, means, k):
    cluster_id = list(numpy.ones(len(data), dtype=int))

    while True:
        clusters = list(cluster_id)
                    
        for i in range(0, len(data)):
            distance = []

            for j in means:
                dist = numpy.linalg.norm(j - data[i])
                distance.append(dist)
            
            cluster_id[i] = distance.index(min(distance))+1

        for i in range(1, k+1):
            index = []
            results = []
            
            for j in range(0, len(cluster_id)):
                if cluster_id[j] == (i):
                    index.append(j)

            for j in range(0, len(cluster_id)):
                if cluster_id[j] == (i):
                    index.append(j)

            for j in range(0, len(index)):
                    results.append(data[index[j]])

            if len(data.shape) == 1:
                means[i-1] = (sum(results)/len(results))
            else:
                col_one = []
                col_two = []

                for j in range(0, len(results)):
                    col_one.append(results[j][0])

                for j in range(0, len(results)):
                    col_two.append(results[j][1])

                means[i-1] = (sum(col_one)/0.01 if len(col_one) == 0 else len(col_one), sum(col_two)/0.01 if len(col_two) == 0 else len(col_two))

        if cluster_id == clusters:
            break

    return cluster_id

def output(data, cluster_id):
    for i in range(len(data)):
        if len(data.shape) == 1:
            print('%10.4f --> cluster %d' % ( data[i], cluster_id[i]))
        else:
            print('(%10.4f, %10.4f) --> cluster %d' % ( data[i][0], data[i][1], cluster_id[i]))
            
def k_means(data_file, k, initialization):
    data = numpy.loadtxt(data_file)
    data = numpy.asarray(data)
    means = initialize_means(data, k, initialization)
    cluster_id = calculate(data, means, k)
    output(data, cluster_id)

# Command line arguments
if len(sys.argv) == 4:
    k_means(sys.argv[1], int(sys.argv[2]), sys.argv[3])
else:
    print("Invalid arguments.")
    exit()

