%% This is a shell that you will have to follow strictly. 
% You will use the plotmap() and viewmap() to display the outcome of your algorithm.

% Load sample_data_map_8, three variables will be created in your workspace. These were created as a 
% result of [m,v,s]=dfs('map_8.txt',[14,1],[1,18]);
% The solution can be viewed using 
% plotmap(m,s) 

% write your own function for the DFS algorithm.
function [retmap,retvisited,retsteps] = dfs( mapfile,startlocation,targetlocation)

t1=textread(mapfile,'%s');
cols = length(t1{1});

adjacentMap = toAdjacentMap(mapfile);

n = length(adjacentMap);

global white gray black color time_stamp d f pred cycle pre post cost      %#ok

white = 0; gray = 1; black = 2;
color = white*ones(1,n);

time_stamp = 0;

d = zeros(1,n);

f = zeros(1,n);

cost = zeros(1,n)+1000;

pred = zeros(1,n);

cycle = 0;

pre = [];
post = [];

start = (startlocation(1)-1)*cols+startlocation(2);
dfs_visit(start, adjacentMap, false);

for u=1:n
  if color(u)==white
    dfs_visit(u, adjacentMap, false);
  end
end


retsteps = generatePath(pred,startlocation,targetlocation);
first = retsteps{1}(1)
retmap = map_convert(mapfile);
retvisited = 2;

end


function dfs_visit(u, adj_mat, directed)

global white gray black color time_stamp d f pred cycle pre post

pre = [pre u];
color(u) = gray;
time_stamp = time_stamp + 1;
d(u) = time_stamp;
if directed
  ns = children(adj_mat, u);
else
  ns = getNeighbors(adj_mat, u);
  ns = setdiff(ns, pred(u)); % don't go back to visit the guy who called you!
end
for v=ns(:)'
  %fprintf('u=%d, v=%d, color(v)=%d\n', u, v, color(v))
  switch color(v)
    case white, % not visited v before (tree edge)
     pred(v)=u;
     dfs_visit(v, adj_mat, directed);
   case gray, % back edge - v has been visited, but is still open
    cycle = 1;
    %fprintf('cycle: back edge from v=%d to u=%d\n', v, u);
   case black, % v has been visited, but is closed
    % no-op
  end
end
color(u) = black;
post = [post u];
time_stamp = time_stamp + 1;
f(u) = time_stamp;
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

function retsteps = generatePath(pred,startlocation,targetlocation)
targetIndex =  (targetlocation(1)-1)*19+targetlocation(2);
currentIndex = targetIndex;
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



function adjacentMap =  toAdjacentMap(mapfile)
t1=textread(mapfile,'%s');
[r,c]=size(t1);
rows = r;
cols = length(t1{1});

adjacentMap = ones(rows*cols,rows*cols);
n = length(adjacentMap)

for i=1:rows
  line = t1{i};
  for j = 1:cols
      value = line(j)-'0';
      if value == 0
        
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



end

function placestep(position,i)
% This function will plot a insert yellow rectangle and also print a number in this rectangle. Use with plotmap/viewmap. 
position = [16-position(1) position(2)];
position=[position(2)+0.1 position(1)+0.1];
rectangle('Position',[position,0.8,0.8],'FaceColor','y');
c=sprintf('%d',i);
text(position(1)+0.2,position(2)+0.2,c,'FontSize',10);
end
