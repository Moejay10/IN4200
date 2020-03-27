# Web graph

The code reads a .txt file which must be formatted in the following way:
```
# Directed graph (each unordered pair of nodes is saved once): web-NotreDame.txt
# University of Notre Dame web graph from 1999 by Albert, Jeong and Barabasi
# Nodes: 325729 Edges: 1497134
# FromNodeId	ToNodeId
0	0
0	1
0	2
```

* The first two lines both start with the # symbol and contain free text
(listing the name of the data file, authors etc.);
* Line 3 is of the form “# Nodes: integer1 Edges: integer2”, where
integer1 is the total number of webpages, and integer2 is the total
number of links. (Here, nodes mean the same as webpages, and edges
mean the same as links.)
* Line 4 is of the form “# FromNodeId ToNodeId”;
* The remaining part of the file consists of a number of lines, the total
number equals the number of links. Each line simply contains two integers:
the index of the outbound webpage and the index of the inbound webpage;
* Some of the links can be self-links (same outbound as inbound), these
should be excluded (not used in the data storage later);
* Note: the webpage indices start from 0 (C convention).


# Compilation

Compile the code by:
```
$ make all
```

You execute the serialized program by:
```
$ ./program.exe filename.txt
```

And you execute the parallelized program by:
```
$ ./omp_program.exe filename.txt num_threads
```
