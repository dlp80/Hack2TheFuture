import time
import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from IPython import display

#This code is derived from the Arduino_RealTimePlot python script created by
#GitHub user WaveShapePlay. All credit to the organization and outline of this code
#is attributed to them and their publicly available repository.
#Many thanks!

class AnimationPlot:

    def animate(self, i, dataList, ser):
        ser.write(b'g')                                     # Transmit the char 'g' to receive the Arduino data point
        arduinoData_string = ser.readline().decode('ascii') # Decode receive Arduino data as a formatted string
        #print(i)                                           # 'i' is a incrementing variable based upon frames = x argument

        try:
            arduinoData_float = float(arduinoData_string)   # Convert to float
            dataList.append(arduinoData_float)              # Add to the list holding the fixed number of points to animate

        except:                                             # Pass if data point is bad                               
            pass

        dataList = dataList[-50:]                           # Fix the list size so that the animation plot 'window' is x number of points
        
        ax.clear()                                          # Clear last data frame
        
        self.getPlotFormat()
        ax.plot(dataList)                                   # Plot new data frame
        

    def getPlotFormat(self):
        ax.set_ylim([0, 350])                              # Set Y axis limit of plot
        ax.set_title("Speech Data")                        # Set title of figure
        ax.set_ylabel("Volume")                              # Set title of y axis

dataList = []                                           # Create empty list variable for later use
                                                        
fig = plt.figure()                                      # Create Matplotlib plots fig is the 'higher level' plot window
ax = fig.add_subplot(111)                               # Add subplot to main fig window

realTimePlot = AnimationPlot()

#ser = serial.Serial("COM4", 9600)                       # Establish Serial object with COM port and BAUD rate to match Arduino Port/rate
ser = serial.Serial("COM4", 9600)
time.sleep(2)                                           # Time delay for Arduino Serial initialization 

#ani function will resolve the realtime plot of things 
ani = animation.FuncAnimation(fig, realTimePlot.animate, frames=100, fargs=(dataList, ser), interval=100) 


plt.show()                                              # Keep Matplotlib plot persistent on screen until it is closed

ani.save('myanimation.gif')
ser.close()

plt.close()
  

print("success!")