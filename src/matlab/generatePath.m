function retsteps = generatePath(pred,startlocation,targetlocation,nodeQueue)
targetIndex =  (targetlocation(1)-1)*19+targetlocation(2);
currentIndex = targetIndex;
startIndex = (startlocation(1)-1)*19+startlocation(2);
j = 2;

while currentIndex ~= startIndex
    indx = findIndex(nodeQueue,currentIndex);
    currentIndex = pred(indx);
    j = j+1;
end

retsteps = {};
retsteps{1} = [startlocation(1),startlocation(2)];

currentIndex = targetIndex;
while currentIndex ~= startIndex
    rownumber = fix( currentIndex / 19 ) + 1;
    colmnumber = currentIndex - (rownumber -1) *19;
    
    indx = findIndex(nodeQueue,currentIndex);  
    currentIndex = pred(indx);
    j = j-1;
    retsteps{j} = [rownumber,colmnumber];
end
retsteps
end


function index = findIndex(nodeQueue,node)

index = 1;
for n = 1:length(nodeQueue)
    if nodeQueue(n) == node
        index = n;
    end
end
end