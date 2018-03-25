import serial
import numpy
import matplotlib.pyplot as plt


tiempo=[]
veloz=[]
arduinodata = serial.Serial('COM6',115200)


while True:
    while (arduinodata.inWaiting()==0):
        pass
    arduinoString = arduinodata.readline()
    dataArray = arduinoString.split(',')
    tiemp = float(dataArray[0])
    vz = float (dataArray[1])
    tiempo.append(tiemp)
    veloz.append(vz)
    print tiempo



    
