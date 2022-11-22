all: graph-sort interval-graph-coloring

graph-sort: DFA.cpp graph-sort.cpp graph-sort--doubling--general-dfa.cpp graph-sort--propagation.cpp 
	g++ $^ -o $@ -O3

interval-graph-coloring: interval-graph-coloring.cpp
	g++ $^ -o $@ -O3