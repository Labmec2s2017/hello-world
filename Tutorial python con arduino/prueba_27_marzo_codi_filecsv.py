from matplotlib import pyplot as plt #Importa pyplot para realizar la gráfica.
from matplotlib import animation  #Importa animation que permite actualizar la gráfica en intervalos concretos
#from matplotlib import style  #Permite cambiar el estilo de nuestra gráfica.
import serial #Importa librería para trabajar con el puerto serie.
import csv

import itertools

with open("output.csv", "wb") as f:
      writer = csv.writer(f)
      writer.writerows(itertools.izip(*l))
      
#style.use('fivethirtyeight')  #Cambia el estilo de nuestra gráfica.

fig = plt.figure() #Creamos un objeto para almacenar el la gráfica.



ax1 = fig.add_subplot(1,2,1) #Añadimos una "subgráfica" a nuestra ventana.

ax2 = fig.add_subplot(1,2,2) #Añadimos una "subgráfica" a nuestra ventana.


ser = serial.Serial('COM8', 115200) #Abrimos puerto Serie, sustituir 'dev/ttyUSB0', por 'COM2', 'COM3' o el puerto que use el Arduino en tu PC.


ser.readline()

def plotea (i):
     peso = []
     ADC = []
     with open('some.csv', 'wb') as f:
         writer = csv.writer(f)
     for i in range(0,50): #Bucle for para recibir 100 valores anets de pintarlos.
        
        datoString = ser.readline()  #Leemos una línea enviada (hasta que se recibe el carácter \n).
        
        datos = datoString.split(",")
        pes = float(datos[0])
        ad = float(datos[1])
        print pes
        peso.append(pes) ##(datos[0][2:])
        ADC.append(ad) ##(datos[1][:-5])
        #print (temperatura[i] + " "+ luz[i])
       
     ax1.clear() #Limpiamos la gráfica para volver a pintar.
     ##ax1.set_ylim([-10,10]) #Ajustamos el límite vertical de la gráfica.
     ax2.clear() #Limpiamos la gráfica para volver a pintar.
     ##ax2.set_ylim([-400000,400000]) #Ajustamos el límite vertical de la gráfica.


     
     try:  #Nos permite comprobar si hay un error al ejecutar la siguiente instrucción.
         ax1.plot( peso) # Plotea los datos en x de 0 a 100.
         ax1.set_ylim((-10, 2000))
         ax2.plot( ADC) # Plotea los datos en x de 0 a 100.
         writer.write(peso)
        # ax1.plot(range(0,20), peso) # Plotea los datos en x de 0 a 100.
        # ax2.plot(range(0,20), ADC) # Plotea los datos en x de 0 a 100.
     except UnicodeDecodeError: #Si se produce el error al plotear no hacemos nada y evitamos que el programa se pare.
        pass
         

ani = animation.FuncAnimation(fig, plotea, interval = 1) #Creamos animacion para que se ejecute la funcion plotea con un intervalo de 1ms.

plt.show() #Muestra la grafica.
    
