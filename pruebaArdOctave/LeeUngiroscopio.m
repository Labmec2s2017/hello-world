%borrar previos
close all;
clear;
clc;
pkg load instrument-control
%%  delete(instrfind);
baudio=115200;
comm=('COM5');
%crear objeto serie
%s1 = serial(comm,'BaudRate',baudio,'Terminator','CR/LF');
s1 = serial(comm,baudio);
pause(1); 
if (exist("serial") == 3)   %verificar si el paquete instrument control se cargo
    disp("Serial: Supported")
else
    disp("Serial: Unsupported")
endif

% Optional Flush input and output buffers
srl_flush(s1);
% s1 = serial(comm,'BaudRate',baudio);
%%warning('off','MATLAB:serial:fscanf:unsuccessfulRead');
%abrir puerto
fopen(s1);

% parámetros de medidas
tmax = 1; % el producto de tmax*f = n datos por cada archivo notepad creado en las carpetas con fechas tiempo de captura en s
% f = 80; % resultado experimental (comprobar)
f = 80; % resultado experimental (comprobar)

% preparar la figura
%f = figure('Name','Captura');
%a = axes('XLim',[0 tmax],'YLim',[0 5.1]);
%l1 = line(nan,nan,'Color','r','LineWidth',2);
%l2 = line(nan,nan,'Color','b','LineWidth',2);

%xlabel('Tiempo (s)')
%ylabel('Voltaje (V)')
%title('Captura de voltaje en tiempo real con Arduino')
%grid on
%hold on

% inicializar
% v1 = zeros(1,tmax*f);
% v2 = zeros(1,tmax*f);
t = 0;

% ejecutar bucle cronometrado
%tic
%     v1(1)=1/f;
%     v2(1)=0.0;
% Reads line of bytes
a = str2num(ReadToTermination(s1))
a = str2num(ReadToTermination(s1))



%% Convert the integers to a string
%read_back_str = char(read_back_int)
%a=str2num(read_back_str)


%[VAL, COUNT, ERRMSG] = fscanf (s1,6,-1)%esto no funciono hay que revisar
   %a = str2num(ReadToTermination(s1))
   a = str2num(ReadToTermination(s1))
   display('Limpiado buffer ');
        Dire=datestr(now);
    ind=find(Dire==char(32));
    Dire(ind)='-';
    ind=find(Dire==char(58));
    Dire(ind)='-';
  b=[];    
mkdir(Dire);
tstart=tic();%inicio del contador de tiempo
while 1<2
    i = 1;
  v=[];

while i<tmax*f+1
   
   % t = toc;
    % leer del puerto serie
%     a = fscanf(s1)
%    a = fscanf(s1,'%f %f');
  a = str2num(ReadToTermination(s1)) ;
    %v1(i)=a(1)*5/1024;
    %v2(i)=a(2)*5/1024;
    v=[v;a];
    b=[b;a];
   t(i)=toc(tstart); %contador de tiempo
    %if a(2) <= -1000
    %    v2(i)=v2(i-1)
    %else v2(i)=a(2);
    %end
    % dibujar en la figura
   % x = linspace(0,1,tmax*f);
   % set(l1,'YData',v1(1:i),'XData',x);
    %set(l2,'YData',v2(1:i),'XData',x);
%    xlim([0 tmax]);
   plot(b(:,1)/1000,b(:,2),"*");
    title('titulo x');
    xlabel(' eje x tiempo en segundos ');
    ylabel(' eje y' );
    grid on
%     hold on; 
    drawnow;
    % seguir
    i = i+1;
end

close all;

% resultado del cronometro
% clc;
% fprintf('%g s de captura a %g cap/s \n',t,i/t);


% v=[v1' v2'];

    file=datestr(now);
    ind=find(file==char(32));
    file(ind)='-';
    ind=find(file==char(58));
    file(ind)='-';
    file(ind)='-';
    save([Dire '\' file],'v' );
end   
    %% Limpiar puerto serie
fclose(s1); delete(s1); clear s1;

%     save(file,'Data','Fs','TSimple');
% file=date;

% file=[file '.xlsx'];
% xlswrite(file,v,'Hoja1','A1');

