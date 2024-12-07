function [parent,v,s] = Astar(mapfile, startloc, targetloc)
[m]=map_convert(mapfile);

[nrows,ncols] = size(m);
%map - a table keeps track of the state of each grid cell
map = zeros(nrows,ncols);
v = zeros(nrows,ncols);

start_node = sub2ind(size(map), startloc(1), startloc(2));
target_node = sub2ind(size(map), targetloc(1), targetloc(2));


%Cost array
Cost = ones(size(m));
    if startloc(1) > targetloc(1)
        Cost(startloc(1)-1,startloc(2)) = 1000;
    elseif startloc(1) < targetloc(1)
        Cost(startloc(1) + 1,startloc(2)) = 1000;

    elseif startloc(2) > targetloc(2)
        Cost(startloc(1),startloc(2)-1) = 1000;
    elseif startloc(2) < targetloc(2)
        Cost(startloc(1),startloc(2)+1) = 1000;
    end

     Cost(targetloc(1),targetloc(2)) = 0;
     Cost(startloc(1), startloc(2)) = 0;
    

    High_Cost = 100; % setting cells close to obstacles with high cost 10

    for node = 1: numel(m)
        %check for obstacle cells
        %if true then it is obstacle so set its neighbor at High_Cost
        if(m(node))
            [row, col] = ind2sub(size(map), node);
            for n = 1 : 4
                if n == 1
                    neighbor_row = row - 1; neighbor_col = col;
                elseif n == 2
                    neighbor_row = row + 1; neighbor_col = col;
                elseif n == 3
                    neighbor_row = row; neighbor_col = col - 1;
                else
                    neighbor_row = row; neighbor_col = col + 1;
                end

                %check neighbor is inside the map
                if(neighbor_row < 1 || neighbor_row > size(m,1))
                    continue;
                elseif(neighbor_col < 1 || neighbor_col > size(m,2))
                    continue;
                end

                neighbor = sub2ind(size(map), neighbor_row, neighbor_col);


                %skip if barrier OR target_node OR start_node
                if(m(neighbor) == 1)
                    continue;
                end

                if(neighbor == start_node)
                    continue;
                end

                if(neighbor == target_node)
                    continue;
                end
                Cost(neighbor) = High_Cost;

             end
        end
    end

%Cost array
H_func = zeros(size(m));

for node = 1 : numel(m)
    [node_coords(1), node_coords(2)] = ind2sub(size(H_func), node);
    H_func(node) = abs(targetloc(1) - node_coords(1)) + abs(targetloc(2) - node_coords(2));
end

%Initialize distance array as inf in each cell
F_node = Inf(nrows,ncols);%This is F array

%Calculate F(start node)
F_node(start_node) = H_func(start_node) + Cost(start_node); % cost of start node is just its H_func value

%For each grid cell this array holds the ID of its parent
parent = zeros(nrows,ncols);

%Keep track of numner of nodes expanded

step = 0;

%Main Loop

% nodeFrom = [];

while true
   parent(startloc(1),startloc(2)) = 5;

    %Find the node with the minimum F(node) = H(node) + Cost(node)
    %min is the value of min F
    %current_frontier is the ID of the first main value(in case there are
    %more than one min
    [min_F, current_frontier] = min(F_node(:));

    %isinf True for infinite elements. isinf(X) returns an array that
    %contains 1's where the elements of X are +Inf or -Inf and 0's where
    %they are not.
    %For example, isinf(pi NaN Inf -Inf) is  [ 0 0 1 1]
    if((current_frontier == target_node) || isinf(min_F))
        break;
    end

    map(current_frontier) = 3; %mark current node as visited (red)
    v(current_frontier) = 1; % mark for visited(for output)

    F_node(current_frontier) = Inf; %remove this node from futher consideration

    %compute row, col coordinates of current_frontier node
    [i,j] = ind2sub(size(F_node), current_frontier);

    %Visit each neighbor of the current node and update the map and parent
    %tables appropriately.

   
    for n = 1 : 4 %each cell usually has 4 neighbors
        %1 Visit each neighbor of the current_frontier node
        
        if n == 1
            row = i - 1; col = j;
        elseif n == 2
            row = i + 1; col = j;
        elseif n == 3
            row = i; col = j - 1;
        else
            row = i; col = j + 1;
        end

        %skip if outside the map
        if(row < 1 || row > size(m,1))
            continue
        elseif(col < 1 || col > size(m,2))
            continue
        end

        %for easy handling get ID out of coords
        neighbor = sub2ind(size(map),row,col);

        %skip if visited before
        if(map(neighbor) > 1 && map(neighbor) ~= 4)
            continue
        end

        %skip if barrier
        if(m(neighbor) == 1)
            continue
        end

        %if not obstacle, outside map, visited before, or not previous
        %frontier then update this node distance(or cost) from start and
        %set its parent as current_frontier
        F_node(neighbor) = Cost(current_frontier) + Cost(neighbor) + H_func(neighbor);
        
        parent(neighbor) = current_frontier;
        m(neighbor) = current_frontier;


        
        step = step + 1;

        if(map(neighbor) ~= 4)
            map(neighbor) = 6; 
        end
    
    end
    
    
   
end
  



%Construct route from start to end by following the parent links


if(isinf(F_node(target_node)))
        route = [];
else 
        noden = target_node;
        route = [noden];
        routeFrom = [];
        sFrom = [];
        s = [];
    
     while(noden ~= start_node)
          nodeFrom = [];
    %     for node = node : numel(parent)
             for n = 1 : 4 %each cell usually has 4 neighbors
                %1 Visit each neighbor of the current_frontier node
                [ni,nj] = ind2sub(size(F_node), noden);
                
        
                if n == 1
                    rown = ni - 1; coln = nj;
                elseif n == 2
                    rown = ni + 1; coln = nj;
                elseif n == 3
                    rown = ni; coln = nj - 1;
                else
                    rown = ni; coln = nj + 1;
                end
        
                %skip if outside the map
                if(rown < 1 || rown > size(m,1))
                    continue
                elseif(coln < 1 || coln > size(m,2))
                    continue
                end
        
                neighbor2 = sub2ind(size(parent),rown,coln);
        
                nodeFrom = noden;
        
                %skip if barrier
                if(parent(neighbor2) == 0)
                    continue
                end
        
                
               
                if(parent(neighbor2) == nodeFrom)
                    continue;
                else
                    map(neighbor2) = 10;
                    [ri,rj] = ind2sub(size(F_node), neighbor2);
                    sFrom{end+1} = [ri,rj];
                
                     
                    routeFrom(end+1) = neighbor2;
                    noden = neighbor2;
                end
             
             end
            
         
            
     end

     for i = 1:length(routeFrom)
         route(i) = routeFrom(length(routeFrom)+1 -i);
         s{i} = sFrom{1,(length(sFrom)+1-i)} ;
         
         
     end
     route(end+1) = target_node;
     s{end+1} = [targetloc(1), targetloc(2)];
%      s = cell2mat(s);
    

      
 end
plotmap(m,startloc,targetloc, route);


       
        
end
