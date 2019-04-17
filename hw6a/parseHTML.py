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

"""
filename +=".html"
try:
    ifile = open(filename, r)
except:
    print("I tried, I simply cannot find " + filename)
"""

ifile = open(filename, "r")
cdom = xml.parse(ifile)

table = cdom.getElementsByTagName("table")

for row in table:
    tr = row.getElementsByTagName("tr")

    for cell in tr:
        incel = cell.getElementsByTagName("td")

        for data in incel:
            if data.nodeType != data.TEXT_NODE:
                for a in data.getElementsByTagName("a"):
                    name = a.firstChild
                    print(name.nodeValue)
            print(data.firstChild.nodeValue)

#print(data)
cdom.unlink()
