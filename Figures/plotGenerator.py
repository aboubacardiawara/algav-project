import matplotlib.pyplot as plt

import numpy as np
import os
import re


currentDir = os.path.abspath(os.path.dirname(__file__))

plt.ylabel("Number of Boolean Functions")
plt.ticklabel_format(style='sci', axis='y', scilimits=(0, 0))


def get_line_value(line):
    return float(re.findall('([0-9]+(.[0-9]+)?)', line)[0][0])


def parse_file(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    file.close()
    nbVar = get_line_value(lines[0])
    YnbFunction = []
    XnodeCount = []

    i = 5
    while (i != len(lines)):
        YnbFunction.append(get_line_value(lines[i]))
        XnodeCount.append(get_line_value(lines[i+1]))
        i += 2
    generateFigure(nbVar, YnbFunction, XnodeCount)


def generateFigure(nbVar, YnbFunction, XnodeCount):
    data = list(zip(XnodeCount, YnbFunction))
    data = sorted(data, key=lambda x: x[0])
    XnodeCount, YnbFunction = list(map(list, zip(*data)))

    plt.xlabel("ROBDD node count for " + str(nbVar) + " Variables")
    plt.plot(XnodeCount, YnbFunction, 'ko-')
    plt.savefig(currentDir + "/Figure_" + str(nbVar) + "Variables.jpeg")
    plt.clf()


testDirFiles = os.listdir(currentDir +
                          "/../Visualisation/ExaustiveTestResults")
testDirFiles = [
    currentDir+"/../Visualisation/ExaustiveTestResults/" + elm for elm in testDirFiles if elm.endswith(".txt")]
for file in testDirFiles:
    parse_file(file)
