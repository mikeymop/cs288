import os, sys, time
import xml.dom.minidom as xml
import mysql.connector

def getDate():
    curtime = time.strftime("%Y-%m-%d-%H-%M-%S", time.localtime())
    return str(curtime)

def writeLine(csvrow, ofile):
    i = 0
    while i < 5:
        ofile.write(str(csvrow[i]))
        ofile.write(",")
        i += 1
    ofile.write(csvrow[5])
    ofile.write("\n")

def insert_row(cursor, csvrow):
    exchange = csvrow[0] # variables for the sql statement
    rank = csvrow[1]
    symbol = csvrow[2]
    company = csvrow[3]
    volume = csvrow[4]
    price = csvrow[5]
    change = csvrow[6]
    # INSERT INTO stocks(rank, exchange, symbol, company, volume, price, chng)
    # VALUES (1, 'nasdaq', 'AMD','Advanced Micro Devices',71500381, 12.48, -01.12)
    # ON DUPLICATE KEY UPDATE 
    # rank = 2, exchange='nasdaq', symbol='AMD', company='Advanced Micro Devices',volume=71500380, price=12.48,chng=-01.12;
    query = """
        INSERT INTO stocks(exchange, ranks, symbol, company, volume, price, chng)
        VALUES ({0}, {1}, {2}, {3}, {4}, {5})
        ON DUPLICATE KEY UPDATE
        exchange={0}, rank={1},symbol={1},company={2},volume={3},price={4},change={5}
    """
arg = sys.argv

try:
    database = mysql.connector.connect(
      host="sql.njit.edu",
      user="md537",
      passwd="freshen77",
      database="md537"
    )
    cursor = database.cursor()
except mysql.connector.Error as err:
    print(err)
    database.close()
    sys.exit()

try:
    filename = arg[1]
except:
    filename = str(getDate())
    print("File not found, assuming: " + filename)

ifile = open(filename, "r")
cdom = xml.parse(ifile)

ofile = open(filename[:-6]+".csv", "w")
ofile.write("exchange,symbol,company,volume,price,change\n")

garbagetags = ["Issue", "Volume", "Price", "Chg", "% Chg", " "]
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
            csvrow.pop(4) # remove blank space
            #csvrow.pop(1) # remove rank number
            csvrow.pop(6) # dont need this table value
            csvrow[1] = csvrow[1].replace("(", "")
            csvrow[1] = csvrow[1].replace(")", "")
            writeLine(csvrow, ofile)
            #DB: print(csvrow), "\n")
        csvrow.clear()
        continue
ofile.close()
cdom.unlink()
