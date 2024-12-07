function [adjacentMap,queueNode] =  toAdjacentMap(mapfile)
t1=textread(mapfile,'%s');
[r,c]=size(t1);
rows = r;
cols = length(t1{1});

adjacentMap = ones(rows*cols,rows*cols);

numOfValid = 0;
for i=1:rows
  line = t1{i};
  for j = 1:cols
      value = line(j)-'0';
      if value == 0
          numOfValid = numOfValid+1;
          if i>1
              if t1{i-1}(j) -'0' == 0
                  adjacentMap(((i-1)*cols) +j ,((i-2)*cols) +j) = 0; 
              end
             
          end
          if t1{i+1}(j) -'0' == 0
             adjacentMap(((i-1)*cols) +j,((i)*cols) +j) = 0;  
          end
          if t1{i}(j+1) -'0' == 0
             adjacentMap(((i-1)*cols) +j,((i-1)*cols) +j+1) = 0;  
          end          
          if j >1
              if t1{i}(j-1) -'0' == 0
                  adjacentMap(((i-1)*cols) +j,((i-1)*cols) +j-1) = 0;  
              end   
          end
          
      end
  end
end

queueNode = (1:numOfValid);
numOfValid = 1;
for i=1:rows
  line = t1{i};
  for j = 1:cols
      value = line(j)-'0';
      if value == 0
          queueNode(numOfValid) = ((i-1)*cols) +j ;
          numOfValid = numOfValid+1;
      end
  end
end

end