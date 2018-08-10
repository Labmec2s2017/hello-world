

n=300 // plot 300 data points from serial port "/dev/ttyACM0"
h=openserial("COM5","115200,n,8,1")
i=1;
while i<=n
data(i) = strtod(readserial(h)); // char to number
plot(i,data(i),'r-o'); // real time plot
drawnow(); // show data
i=i+1;
end
