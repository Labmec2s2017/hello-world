import serial #importo la libreria q permite comunicacion serial
import numpy
import matplotlib.pyplot as plt #importo lib q permite hacer graficas
from drawnow import * #importo lib q permite actualizar la grafica en tiempo real

tiempo = []  #cadena con datos del tiempo milisecond
veloz = []
arduinodata = serial.Serial('COM3',115200) #creo el objeto serial
plt.ion()
cnt=0

def makeFig():
    #plt.ylim(-10,10)
    plt.plot(veloz,'ro-', label='unidad x')
    plt.title('mi titulo')
    plt.grid(True)
    plt.xlabel('eje x')
    plt.ylabel('eje y')
    plt.legend(loc='upper left')
    
    
while True:
    while(arduinodata.inWaiting()==0):  #espera datos a recibir
        pass
    arduinoString = arduinodata.readline()
    dataArray = arduinoString.split(',')
    tiemp = float(dataArray[0])
    vz = float(dataArray[1])
    tiempo.append(tiemp)
    veloz.append(vz)
    drawnow(makeFig)
    plt.pause(.000001)
    cnt=cnt+1
    if (cnt>100):
        tiempo.pop(0)  #muevo la grafica para que no muestre todo desde el inicio
        veloz.pop(0)   #muevo la grafica para que no muestre todo desde el inicio


        
                
