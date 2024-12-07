function [retmap,retvisited,retsteps] =Dijkstra( mapfile,startlocation,targetlocation)

t1=textread(mapfile,'%s');
cols = length(t1{1});
[adjacentMap,nodeQueue] = toAdjacentMap(mapfile);
n = length(nodeQueue);

dis = zeros(1,n)+1000;

pred = zeros(1,n);
sourceNode = (startlocation(1)-1)*cols+startlocation(2);

index=findIndex(nodeQueue,sourceNode);
pred(index) = sourceNode;
dis(index) = 0;
neighbors = getNeighbors(adjacentMap , sourceNode);
for i = 1: size(neighbors,2)
    node = neighbors(i);
    nodeIndex = findIndex(nodeQueue,node);
    dis(nodeIndex) = 1;
    pred(nodeIndex) = sourceNode;
end

color = zeros(1,n);
color(index) = 2;

while any(color ==0)
    whiteIndx =findWhiteMin(color, dis);
    color(whiteIndx) = 2;
    whitenode = nodeQueue(whiteIndx);
    neighbors = getNeighbors(adjacentMap , whitenode);
    for i = 1: size(neighbors,2)
        childnode = neighbors(i);
        nodeIndex = findIndex(nodeQueue,childnode);
        if color(nodeIndex) ==0 && dis(nodeIndex)> dis(whiteIndx) +1
            dis(nodeIndex) = dis(whiteIndx) +1;
            pred(nodeIndex)= whitenode;
        end
    end
end

pred;
retsteps = generatePath(pred,startlocation,targetlocation,nodeQueue);
%retsteps =1;
retmap = map_convert(mapfile);
retvisited =2;

end

function index = findWhiteMin(color,dis)

minimum = 1000;
for k = 1:size(color,2)
    if color(k) == 0
        if dis(k) <= minimum 
            minimum = dis(k);
            index = k;
        end
    end
end
       
end




function index = findIndex(nodeQueue,node)

index = 1;
for n = 1:length(nodeQueue)
    if nodeQueue(n) == node
        index = n;
    end
end
end

function dis = findMinimum(firstInt, secondInt)

if firstInt <= secondInt
    dis = firstInt;
else
    dis = secondInt;

end
end


function neighbors = getNeighbors(adj_map , u)
j =0;
for i=1:length(adj_map)
    if adj_map(u,i) == 0
        j = j+1;
    end    
end
neighbors = zeros(1,j);
j = 1;
for i=1:length(adj_map)
    if adj_map(u,i) == 0
        neighbors(j) = i;
        j = j+1;
    end    
end
end



