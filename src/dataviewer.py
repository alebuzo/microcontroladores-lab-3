#!/usr/bin/python3

import serial 

ser = serial.Serial(
    port='/tmp/ttyS1',\
    baudrate=9600,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
    timeout=0\
)

f= open('./output.csv', 'w+')
f.write('Canal 1, Canal 2, Canal 3, Canal 4\n')

print('Connected to: ' + ser.portstr)
line = []
count = 0

while True:
    for c in ser.read():
        c=chr(c)
        line.append(c)
        if c == '\n':
            print("Line: " + ''.join(line))
            str = ''.join(line)
            str = str[:-2] + ','
            if(count < 3):
                f.write(str)
                count += 1
            elif(count == 3):
                f.write(str[:-1]+ "\n")
                count = 0
            line=[]
            