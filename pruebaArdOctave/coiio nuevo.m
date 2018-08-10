pkg load instrument-control;
pkg load signal;

s1 = serial("com5");
set(s1,'baudrate',115200);
set(s1, 'bytesize',8);
set(s1,'parity','n');
set(s1,'stopbits',1);
set(s1,'timeout',-1); %10.0 seconds

sleep(0.5);
srl_flush(s1);

datax = [];
datay = [];
%dataz = [];
negativex = false;
negativey = false;
%negativez = false;
xd = 0;
yd = 0;
%zd = 0;
delaytime = 1000; %delay time in microseconds (us)

hold on;
for i = 1:500
  srl_write(s1,"x");
  %pause(delaytime);
  usleep(delaytime);
  xd = str2num(char(srl_read(s1,6)));
  srl_write(s1,"s");
  %pause(delaytime);
  usleep(delaytime);

  srl_write(s1,"y");
  %pause(delaytime);
  usleep(delaytime);
  yd = str2num(char(srl_read(s1,6)));
  srl_write(s1,"s");
  %pause(delaytime);
  usleep(delaytime);

  %srl_write(s1,"z");
  %usleep(delaytime);
  %zd = str2num(char(srl_read(s1,6)));
  %srl_write(s1,"s");
  %usleep(delaytime);

  datax = [datax xd];
  datay = [datay yd];
  %dataz = [dataz zd];

  if mod(i, 10) == 0
    hold off;
    plot(datax,'r');
    hold on;
    plot(datay,'b');
    %plot(dataz,'g');
    drawnow;
  endif
endfor
%