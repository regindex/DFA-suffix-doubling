# DFA-suffix-doubling

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

> 0 1 a \
1 2 b \
1 5 a \
2 3 b \
3 3 b \
3 4 a \
5 6 b \
6 7 a \
4 7 a \
7 8 b

### Run

After compiling, run:

> ./graph-sort < input.txt > interval.txt

This command will compute the intervals corresponding to co-lex order of the nodes of the DFA stored in a text file "input.txt" and will store the result as "interval.txt" in which each line indicates the left and right end of an interval.

The following command will partition the node set by coloring the interval graph: 

> ./interval-graph-coloring < interval.txt

The output will be generated to STDOUT with the third column (color ID) added.

### Funding

This project has received funding from the European Research Council (ERC) under the European Union’s Horizon Europe research and innovation programme, project REGINDEX, grant agreement No 101039208
