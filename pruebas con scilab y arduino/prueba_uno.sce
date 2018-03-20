h=openserial('COM3','115200');
for i=1:10000
    answer=h.serialread();
    answery=strtod(answer);
    plot2d3('gnn',i,answery);
    drawnow();
end
h.close();
