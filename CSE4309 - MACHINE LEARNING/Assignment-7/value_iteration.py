import numpy, sys

actions = ['^', 'v', '<', '>']

def readfile(filename):
    # open and read file
    txt = open(filename, 'r')
    lines = txt.readlines()

    readlist = list()

    for line in lines:
        splitline = line.strip().split(',')
        readlist.append(splitline)

    return readlist

def value_iteration(environment_file, non_terminal_reward, gamma, K):
    data = readfile(environment_file)

    rows = len(data)
    columns = len(data[0])

    policy = numpy.empty([rows, columns], dtype=str)
    utility = numpy.zeros([rows, columns])

    for i in range(0, K):
        util =  utility.copy()

        for j in range(0, rows):
            for k in range(0, columns):
                # blocked state
                if data[j][k] == 'X':
                    utility[j][k] = 0
                    policy[j][k] = 'x'

                # non-terminal state
                elif data[j][k] == '.':
                    max_value = 0
                    for l in range(0, len(actions)):
                        value = best_move((j, k), util, rows, columns, policy, actions[l], data)
                        if value > max_value:
                            max_value = value

                        if value == max_value:
                            policy[j][k] = actions[l]

                    utility[j][k] = calculate_reward((j, k), data, non_terminal_reward) + gamma * max_value
                    
                # terminal states
                else:
                    utility[j][k] = float(data[j][k])
                    policy[j][k] = 'o'
    
    return policy, util

                    
def best_move(position, utility, rows, columns, policy, action, data):
    value = 0
    for i in range(0, rows):
        for j in range(0, columns):
            value = value + next_move((i, j), position, action, data) * utility[i][j]
    return value

def next_move(s, position, action, data):
    value = 0

    # possible actions
    up_move = (position[0]-1, position[1])
    down_move = (position[0]+1, position[1])
    left_move = (position[0], position[1]-1)
    right_move = (position[0], position[1]+1)

    # up action
    if action == '^':
        value = value + calculate_value(s, position, 0.8, up_move, data)
        value = value + calculate_value(s, position, 0.1, left_move, data)
        value = value + calculate_value(s, position, 0.1, right_move, data)

    # down action
    elif action == 'v':
        value = value + calculate_value(s, position, 0.8, down_move, data)
        value = value + calculate_value(s, position, 0.1, left_move, data)
        value = value + calculate_value(s, position, 0.1, right_move, data)

    # left action
    elif action == '<':
        value = value + calculate_value(s, position, 0.8, left_move, data)
        value = value + calculate_value(s, position, 0.1, up_move, data)
        value = value + calculate_value(s, position, 0.1, down_move, data)

    # right action
    elif action == '>':
        value = value + calculate_value(s, position, 0.8, right_move, data)
        value = value + calculate_value(s, position, 0.1, up_move, data)
        value = value + calculate_value(s, position, 0.1, down_move, data)

    return value

def calculate_value(s, position, value, pos_move, data):
    if not possible_move(pos_move, data):
        pos_move = position
    if pos_move == s:
        return value
    else:
        return 0

def possible_move(position, data):
    if position[0] < len(data) and position[0] >= 0:
        if position[1] < len(data[1]) and position[1] >= 0:
            if data[position[0]][position[1]] == 'X':
                return False
            return True
        return False

def calculate_reward(position, data, non_terminal_reward):
    value = data[position[0]][position[1]]
    if value == 'X':
        return 0
    elif value == '.':
        return non_terminal_reward
    else:
        return value

if len(sys.argv) == 5:
    policy, utilities = value_iteration(sys.argv[1], float(sys.argv[2]), float(sys.argv[3]), int(sys.argv[4]))

    print("utilities:")
    for i in range(0, len(utilities)):
        for j in range(0, len(utilities[0])):
            print('%6.3f ' % utilities[i][j], end=' ')
        print()

    print()
    print("policy:")
    for i in range(0, len(policy)):
        for j in range(0, len(policy[0])):
            print('%6s ' % policy[i][j], end=' ')
        print()
else:
    print("Invalid arguments.")
    exit()