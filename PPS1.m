% Variable description
% kk is the heat transfer matrix
% T is the heat transfer matrix at nodes
% Q is the g/k matrix, P is the result matrix
% g is the constant heat transfer rate
% k is the coefficient of thermal conductivity
% h is the heat transfer coefficient
% L is the thickness of the uranium plate
% T_en is the Environment temperature
node = input('Number of nodes: '); 
% node la so nut
l = input('Thickness of Uranium plate(m): ');
g = input('Constant heat transfer rate g(constant)(W/m3): ');
k = input('Coefficient of thermal conductivity k(W/m): ');
h = input('Heat transfer coefficient h(W/m2): ');
T_en = input('Environment temperature(°C): ');
% Khoi tao ma tran kk,T,Q,P
kk = zeros(node-1,node);
T = zeros(node-1,1);
Q = zeros(node-1,1);
P = zeros(node-1,1);
% Khoang cach giua cac phan tu 
delta_x = l/(node-1);
% Input heat transfer matrix
for i = 1: node-2   
    for j=1: node       
        if j == i           
            kk(i,j)= 1;
        elseif j == i+1           
            kk(i,j)= -2;       
        elseif j == i+2           
            kk(i,j) = 1;       
        else
            kk(i,j)=0;       
        end
    end
end
        % At node n which make contact with the environment
        for i=1:node
        if i == node -1        
            kk(node-1,i) = 1;    
        elseif i == node        
            kk(node-1,i) = -(1+ h*delta_x/k);    
        end
 end% Q matrix
 for i=1:node-1    
     if i==node-1        
         Q(i,1) = 0;    
     else
         Q(i,1)= g*delta_x*delta_x/k;    
     end
 end
 % P matrix 
 for i=1:node-1    
     if i==node-1        
         P(i,1) = -h*delta_x*T_en/k - g*delta_x*delta_x/(2*k);    
     else
         P(i,1) = 0;    
     end
 end
 % Print heat transfer matrix 
 for i =1:node-1    
     kk(i,:);
 end
 kk
 % Find matrices at nodes
 Y = P-Q;
 for i =1:node-1    
     Y(i,1);
 end
 Y
 T = linsolve(kk,Y);
 for i =1:node    
     T(i,1);
 end
 T
 % Draw the line plot of the plate's temperature
 x = 0:denta_x:l;
 plot(x,T);