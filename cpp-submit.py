#!/usr/bin/python

import sys, re, os

regex = re.compile(r'include "(.*)"')
included = []

def makeSubmitFile(fileAddr, basePath = ""):
    global included, submitFile
    if(os.path.join(basePath, fileAddr) in included): return 
    included.append( os.path.join(basePath, fileAddr) )
    print "Including " + os.path.join(basePath, fileAddr)
    cppFile = open(os.path.join(basePath, fileAddr), "r")
    for line in cppFile:
        includes = regex.findall(line)
        if len(includes):
            include = includes[0]
            (incPath, incFlie) = os.path.split(include)
            nxtBasePath = os.path.join(basePath, incPath)
            makeSubmitFile(incFlie, nxtBasePath)
            pass
        else:
            if not line.startswith("//"): submitFile.write(line)

if(len(sys.argv) < 1):
    print "Usage: python " + sys.argv[0] + " <read file> [<write file>]"

fileAddr = sys.argv[1]
if(len(sys.argv) > 2): submitFileAddr = sys.argv[2]
else: submitFileAddr = fileAddr+".submit"

submitFile = open(submitFileAddr, "w")

makeSubmitFile(fileAddr)
