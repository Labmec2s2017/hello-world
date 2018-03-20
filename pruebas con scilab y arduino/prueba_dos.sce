%borrar previos
clear;
clc;
comm1='COM3';

baudios=115200;

delete(instrfind({'Port'},{comm1}));

%crear objeto serie

s1 = serial(comm1,'BaudRate',baudios,'Terminator','CR/LF');

warning('off','MATLAB:serial:fscanf:unsuccessfulRead');
%abrir puerto
fopen(s1);

display('configura port');
%parametros de medidas
tmax = 5.0; % tiempo de captura en s

f = 80; % resultado experimental (comprobar)

% inicializar
j=0;
%ejecutar bucle cronometrado
%tic
    a1 = fscanf(s1) %borra encabezados
    clear(a1);
    a2 = fscanf(s2) %borra encabezados
    clear(a2);
    a3 = fscanf(s1) %borra encabezados
    a4 = fscanf(s2) %borra encabezados
%------------------------------------------------
    Dire=datestr(now);
    ind=find(Dire==char(32));
    Dire(ind)='-';
    ind=find(Dire==char(58));
    Dire(ind)='-';
    mkdir(Dire);
%------------------------------------------------
oldb1=0;
oldb2=0;
    tstart = tic;
while 1<2
    a1=[];
    a2=[];

i=1;
while i<tmax*f+1
   % t = toc;
    % leer del puerto serie
    b1 = fscanf(s1,'%f');
    
%     b = fscanf(s1,'%int16,%int16,%int16,%int16,%int16,%int16');
%     b = fscanf(s1);
    if (max(size(b1))>1 && i>1), b1=a1(end);%else b1=oldb1;
        display ('error b1  '), b1, end
    a1=[a1;b1];
    
    a2=[a2;b2];
    t(i)=toc(tstart);
    i = i+1;
    oldb1=b1;
    oldb2=b2;
end
% resultado del cronometro
j=j+1;
%figure(1);plot(t',a);title(['Fuerza  ' int2str(j)]);drawnow;
figure(1);plot(t,[a1 a2]);title(['Fuerza kp  muestra  ' int2str(j)]);grid;ylim([-1 50]);drawnow;
%figure(2);plot(t',a(:,4:6));title(['angul x y z  ' int2str(j)]);drawnow;
    file=datestr(now);
    ind=find(file==char(32));
    file(ind)='-';
    ind=find(file==char(58));
    file(ind)='-';
%     file(ind)='_';
    save([Dire '\' file],'t','a1','a2');
%     save(file,'Data','Fs','TSimple');
% file=date;
%clear(a);
end
%% Limpiar puerto serie
fclose(s1);
delete(s1);
clear s1;
