# DFA-suffix-doubling

Authors: Sung-Hwan Kim, Francisco Olivares, Nicola Prezza

Cite as: S.-H. Kim, F. Olivares, N. Prezza, "Faster Prefix-Sorting Algorithms for Deterministic Finite Automata," CPM 2023.

### Description

This code co-lexicographically sorts DFA nodes according to strings labelling their source-to-node walks.

### Download

To clone the repository, run:

> git clone http://github.com/regindex/DFA-suffix-doubling

### Compile

You can compile with make:

> make

### Input

Each line of the input indicates an edge represented as a triplet (u,v,c) where u and v are (0-indexed) node IDs, and c is a character.
For example:

>0 1 a\
0 5 c\
1 2 a\
1 5 c\
2 3 c\
2 7 a\
3 3 c\
3 4 a\
4 9 a\
5 6 c\
6 7 a\
7 2 a\
7 8 c\
8 9 a

### Run

After compiling, run:

> cat edgelist.txt | ./convert-format | ./graph-sort > interval.txt

This command will compute the intervals corresponding to co-lex order of the nodes of the DFA stored in a text file "edgelist.txt" and will store the result as "interval.txt" in which each line indicates the left and right end of an interval.

The following command will partition the node set by coloring the interval graph: 

> ./interval-graph-coloring < interval.txt

The output will be generated to STDOUT with the third column (color ID) added.

#### Sorting Pan-genome graph

The following command will download the Human genome dataset, and run the program.

> cd expr
> ./script.sh


### Funding

This project has received funding from the European Research Council (ERC) under the European Union’s Horizon Europe research and innovation programme, project REGINDEX, grant agreement No 101039208
