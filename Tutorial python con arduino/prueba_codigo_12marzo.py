# Import libraries
from numpy import *
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import serial                          #se llama a la libreria serial

# crea el objeto serial con sus especificaciones--------------Create object serial port
portName = "COM3"                      #nombre del puerto com asignado de conexion de datos-------------------replace this port name by yours!
baudrate = 115200                      # tasa de baudrate debe ser igual a la del codigo en arduino.
ser = serial.Serial(portName,baudrate) #el objeto serial se llama ser

### START QtApp #####
app = QtGui.QApplication([])            # you MUST do this once (initialize things)
####################

win = pg.GraphicsWindow(title="Signal from serial port") # crea una ventana.------creates a window
p = win.addPlot(title="Realtime plot")  # creates empty space for the plot in the window
curve = p.plot()                        # create an empty "plot" (a curve to plot)

windowWidth = 500                       # width of the window displaying the curve
Xm = linspace(0,0,windowWidth)          # create array that will contain the relevant time series     
ptr = -windowWidth                      # set first x position

# Realtime data plot. Each time this function is called, the data display is updated
def update():
    global curve, ptr, Xm    
    Xm[:-1] = Xm[1:]                      # shift data in the temporal mean 1 sample left
    value = ser.readline()# read line (single value) from the serial port
    dataArray = value.split(',')         #yo agregue esta linea
    Xm[-1] = float(dataArray[1])          #antes tenia float(value)       # vector containing the instantaneous values      
    ptr += 1                              # update x position for displaying the curve
    curve.setData(Xm)                     # set the curve with this data
    curve.setPos(ptr,0)                   # set x position in the graph to 0
    QtGui.QApplication.processEvents()    # you MUST process the plot now

### MAIN PROGRAM #####    
# this is a brutal infinite loop calling your realtime data plot
while True: update()

### END QtApp ####
pg.QtGui.QApplication.exec_() # you MUST put this at the end
##################
