import statistics, sys

def file_stats(filename):
    # open and read file
    txt = open(filename, 'r')
    lines = txt.readlines()

    list = []

    for line in lines:
        list.append(float(line))

    # calculate our stats
    average = statistics.mean(list)
    stddev = statistics.stdev(list)

    return average, stddev


(avg, stdev) = file_stats('./numbers1.txt')
print('Average: \t\t', avg)
print('Standard Deviation: \t', stdev)