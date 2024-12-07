%This is the main file
startloc = [14,1];
targetloc = [1,18];
% startloc = [3,18];
% targetloc = [14,6];


[m, v, s] = Astar('map_8.txt',startloc,targetloc);

%Here   'm' is the map file returned as a matrix