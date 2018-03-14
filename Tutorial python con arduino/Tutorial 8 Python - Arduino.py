from matplotlib import pyplot as plt #Importa pyplot para realizar la gráfica.
from matplotlib import animation  #Importa animation que permite actualizar la gráfica en intervalos concretos
# from matplotlib import style #Permite cambiar el estilo de nuestra gráfica.
import serial #Importa librería para trabajar con el puerto serie.


#style.use('fivethirtyeight')  #Cambia el estilo de nuestra gráfica.

fig = plt.figure() #Creamos un objeto para almacenar el la gráfica.



ax1 = fig.add_subplot(1,2,1) #Añadimos una "subgráfica" a nuestra ventana.

ax2 = fig.add_subplot(1,2,2) #Añadimos una "subgráfica" a nuestra ventana.


ser = serial.Serial('COM5', 115200) #Abrimos puerto Serie, sustituir 'dev/ttyUSB0', por 'COM2', 'COM3' o el puerto que use el Arduino en tu PC.


ser.readline()

def plotea (i):
     temperatura = []
     luz = []
     for i in range(0,100): #Bucle for para recibir 100 valores anets de pintarlos.
        
        datoString = ser.readline()  #Leemos una línea enviada (hasta que se recibe el carácter \n).
        
        datos = str(datoString).split(",")
        temperatura.append (datos[0] )#[2:])
        luz.append (datos[1])#[:-5])
        #print (temperatura[i] + " "+ luz[i])
       
     ax1.clear() #Limpiamos la gráfica para volver a pintar.
     ax1.set_ylim([0,50000]) #Ajustamos el límite vertical de la gráfica.
     ax2.clear() #Limpiamos la gráfica para volver a pintar.
     ax2.set_ylim([0,50000]) #Ajustamos el límite vertical de la gráfica.
     
     
     try:  #Nos permite comprobar si hay un error al ejecutar la siguiente instrucción.
         ax1.plot(range(0,100000), temperatura) # Plotea los datos en x de 0 a 100.
         ax2.plot(range(0,100000), luz) # Plotea los datos en x de 0 a 100.
     except UnicodeDecodeError: #Si se produce el error al plotear no hacemos nada y evitamos que el programa se pare.
        pass
         

ani = animation.FuncAnimation(fig, plotea, interval = 1) #Creamos animación para que se ejecute la función plotea con un intervalo de 1ms.

plt.show() #Muestra la gráfica.
    
