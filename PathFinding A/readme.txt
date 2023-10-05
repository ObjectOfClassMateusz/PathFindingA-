An algorithm that calculates the shortest route from point S(x,y) to point E(x,y).
 A* uses points containing the distances from this point to the beginning of the path 
and from this point to the end of the path, as well as their sum. Thanks to these 
parameters, the algorithm calculates the fastest route. However, in the final 
stage of designing it, I ran out of new connections between previously discovered
 points and later discovered points next to each other.

Attention . The program does not have a control module. 
To edit paths, you need to change the code and compile it again