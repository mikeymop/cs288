import os, sys, time
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
    while i < 5:
        ofile.write(str(csvrow[i]))
        ofile.write(",")
        i += 1
    ofile.write(csvrow[5])
    ofile.write("\n")

ifile = open(filename, "r")
cdom = xml.parse(ifile)

ofile = open(filename[:-6]+".csv", "w")
ofile.write("exchange,symbol,company,volume,price,change\n")

csvrow = []

table = cdom.getElementsByTagName("table")
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

            values = str(element.firstChild.nodeValue).strip("\n")

            if(str(values) != "None"):
                if(values not in garbagetags and " " not in values):
                    if('$' in str(values)):
                        values = values.replace("$", "")
                    if(',' in str(values)):
                        values = values.replace(",", "")
                    csvrow.append(values)

        if(len(csvrow) > 8):
            csvrow.pop(4) # ugly code
            csvrow.pop(1) # resides here
            csvrow.pop(6)
            writeLine(csvrow, ofile)
            #DB: print(csvrow), "\n")
        csvrow.clear()
        continue
ofile.close()
cdom.unlink()
