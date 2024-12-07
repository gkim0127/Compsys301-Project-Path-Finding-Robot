function [retmap,retvisited,retsteps] =shortestPath( mapfile,startlocation,targetlocation)

t1=textread(mapfile,'%s');
cols = length(t1{1});
adjacentMap = toAdjacentMap(mapfile);
n = length(adjacentMap);

queueNode = (1:n);
dis = zeros(1,n)+1000;
queueWeight = zeros(1,n)+1000;
pred = zeros(1,n);

sourceNode = (startlocation(1)-1)*cols+startlocation(2);
dis(sourceNode) = 0;
queueWeight(sourceNode) = 0;



while size(queueNode,2) ~= 0
    [index ,minCost,node]= smallestCostIndex(queueNode,queueWeight,size(queueNode,2));
    
    LeadNode = node;
    
    rownumber = fix( LeadNode / 19 ) + 1;
    colmnumber = LeadNode - (rownumber -1) *19;
    retsteps = [rownumber,colmnumber]
    
    neighbors = getNeighbors(adjacentMap , LeadNode);
    if size(neighbors,2) ~= 0
        for j = 1:size(neighbors,2)
            TargetNode = neighbors(j);
            newDistance = minCost + 1;
            
        
        if(newDistance <dis(TargetNode))
            dis(TargetNode) = newDistance;
            queueWeight(TargetNode) = newDistance;
            pred(TargetNode) = LeadNode;
        end
        end
        queueNode(index) = [];
        queueWeight(index) = [];
    else
        queueNode(index) = [];
        queueWeight(index) = [];

    end

end
pred;
retsteps = generatePath(pred,startlocation,targetlocation);
retmap = map_convert(mapfile);
retvisited =1;
end

function [queNode,queWeight]= filter(queueNode, queueWeight, adj_map)

n = length(adj_map);

for i=1:rows
  line = t1{i};
  for j = 1:cols
      value = line(j)-'0';
      if value == 1
          queueNode() = [];

      end
  end
end
queNode = 1;
queWeight = 2;
end







function index = findIndexByNode(queueNode, node)
index = 1 ;
for i = size(queueNode,2)
    if queueNode(i) == node
        index = i;
    end

end
end


function [index, minCost, node] = smallestCostIndex(queueNode,queueWeight,n)
index = 1;
minCost = queueWeight(1);
for i = 1: n
    if queueWeight(i) <minCost
        minCost = queueWeight(i);
        index = i;
        node = queueNode(index);
    end

end
end


function retsteps = generatePath(pred,startlocation,targetlocation)
targetIndex =  (targetlocation(1)-1)*19+targetlocation(2);
currentIndex = targetIndex
startIndex = (startlocation(1)-1)*19+startlocation(2);
j = 2;

while currentIndex ~= startIndex
    currentIndex = pred(currentIndex);
    j = j+1;
end

retsteps = {};
retsteps{1} = [startlocation(1),startlocation(2)];

currentIndex = targetIndex;
while currentIndex ~= startIndex
    rownumber = fix( currentIndex / 19 ) + 1;
    colmnumber = currentIndex - (rownumber -1) *19;

    currentIndex = pred(currentIndex);
    j = j-1;
    retsteps{j} = [rownumber,colmnumber];
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



