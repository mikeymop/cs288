import os, sys, csv, time
import xml.dom.minidom as xml

def getDate():
    curtime = time.strftime("%Y-%m-%d-%H-%M-%S", time.localtime())
    return curtime

garbagetags = ["Issue", "Volume", "Price", "Chg", "% Chg", " "]

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

csvrow = ""

for row in table:
    result = ""
    tr = row.getElementsByTagName("tr")

    for cell in tr:
        td = cell.getElementsByTagName("td")
        i = 1
        for element in td[:]:
            if (element.nodeType != element.TEXT_NODE):
                for a in element.getElementsByTagName("a"):
                    name = str(a.firstChild.nodeValue).split("\n")
                    if (len(name) > 1):
                        print(str(repr(name[0])).strip('\''))

                values = str(element.firstChild.nodeValue).strip("\n")

                if(len(values) > 0 and str(values) != "None" and len(values) > 1):
                    if(values not in garbagetags and " " not in values):
                        print(len(values), values)

cdom.unlink()
