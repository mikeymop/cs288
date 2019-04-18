import os, sys, csv, time
import xml.dom.minidom as xml

def getDate():
    curtime = time.strftime("%Y-%m-%d-%H-%M-%S", time.localtime())
    return str(curtime)

garbagetags = ["Issue", "Volume", "Price", "Chg", "% Chg", " "]

arg = sys.argv

try:
    filename = arg[1]
except:
    filename = str(getDate())
    print("File not found, assuming: " + filename)

def writeLine(csvrow, ofile):
    i = 0
    while i < 6:
        ofile.write(str(csvrow[i]))
        i += 1
    ofile.write("\n")

"""
filename +=".html"
try:
    ifile = open(filename, r)
except:
    print("I tried, I simply cannot find " + filename)
"""

ifile = open(filename, "r")
cdom = xml.parse(ifile)

ofile = open(getDate()+".csv", "w")

table = cdom.getElementsByTagName("table")

csvrow = []
#csvrow[0] = "nasdaq"

for row in table:
    result = ""
    tr = row.getElementsByTagName("tr")

    for cell in tr:
        td = cell.getElementsByTagName("td")
        csvrow.append("nasdaq")

        for element in td[:]:
            if (element.nodeType != element.TEXT_NODE):
                for a in element.getElementsByTagName("a"):
                    name = str(a.firstChild.nodeValue).split("\n")
                    if (len(name) > 1):
                        symbol = str(repr(name[0])).strip('\'').split(' ')
                        symbol = str(repr(symbol[-1])).strip('\'')
                        name = name[0]

                        csvrow.append(str(symbol))
                        csvrow.append(str(name[:-6]))
                        #continue
                        #print(name[:-6])
                        #print(symbol)
                        #print(csvrow)
                        #print("\n")
                #continue
            values = str(element.firstChild.nodeValue).strip("\n")

            if(str(values) != "None"):
                if(values not in garbagetags and " " not in values):
                    if('$' in str(values)):
                        values = values.replace("$", "")
                    if(',' in str(values)):
                        values = values.replace(",", "")
                    csvrow.append(values)
                    #print(csvrow)
                    #continue
        #if(len(csvrow) == 6):
        #csvrow.remove(csvrow[1])
        if(len(csvrow) > 8):
            csvrow.pop(4)
            csvrow.pop(1)
            csvrow.pop(6)
            writeLine(csvrow, ofile)
            print(csvrow)
            print("\n")
        csvrow.clear()
        continue
ofile.close()
cdom.unlink()
