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

f= open('/home/alexa/Documents/micro-lab-3/output.csv', 'w+')

print('Connected to: ' + ser.portstr)
line = []

while True:
    for c in ser.read():
        c=chr(c)
        line.append(c)
        if c == '\n':
            print("Line: " + ''.join(line))
            str = ''.join(line)
            f.write(str)
            line=[]