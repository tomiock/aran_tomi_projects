### Heuristic Function

There are two main conditions that the function has to satisfy:
1. Admissible: It should never overestimate the cost to reach the goal. To be admissible the heuristic at the goal has to be exactly zero, it cannot be more because it would be an overestimation and it cannot be less because it would be a negative value.
2. Consistent:
$$
h(n) \leq c(n, a, n') + h(n')
$$
For an edge $(n, n')$.

In this case, the heuristic function cannot be computed directly (too costly) or estimated.

A possible heuristic would be to get a large dataset and make a function that approximates the distances between two nodes based on the index of the nodes. For example the distances between 3 and 5 would be smaller than the distances between 2 and 15, assuming that we have a graph with 20 nodes. This approach can be very imprecise because we do not have any guarantee that different datasets follow the same "rules" or the heuristic can easily be overestimated. And to not be overestimated in any circumstance, it would be even more imprecise.

A* is much more suited to problems on a tiled world (like a videogame) not in blind graph search. Without precomputed distances between nodes.

Assumptions that we need to make to create a heuristic function:
- The variance between of the mean weight between two edges need to be "small".
- Generally for a node $n$ and a node $n_1$ and $n_2$:

If $n > n_1$ and $n >> n_2$, then:
$$
d(n, n_1) << d(n, n_2)
$$
Where the nodes are indexes.

## Other algorithms

Dijkstra seems to work better for sparse graphs, since it calculate the shortest path from the source to all the nodes. The results of each run of the algorithm can be cached in order to save some computations.
