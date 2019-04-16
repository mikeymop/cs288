import os, sys, csv, time
import xml.dom.minidom as xml

def getDate():
    curtime = time.strftime("%Y-%m-%d-%H-%M-%S", time.localtime())
    return curtime

arg = sys.argv

try:
    filename = arg[1]
except:
    filename = str(getDate())
    print("File not found, assuming: ")

filename +=".html"

try:
ifile = open(filename, r)
except:
    print("I tried, I simply cannot find " + filename)

cdom = parse(ifile)
