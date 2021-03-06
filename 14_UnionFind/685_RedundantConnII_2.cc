// 685. Redundant Connection II
// Hard.
// Usage of union find (disjoint set).
// There are two types of anomalies. Loop and multiple input.
// We use disjoint set to detect both anomalies. But only use union find to
// detect loop.
// TC: O(N^2) worst case
// SC: O(N)
class Solution {
 public:
  std::vector<int> DisjointSet;
  // Returns the root node of current disjoint set or itself.
  int ds_find(int i) {
    int r = i;
    while (DisjointSet[r] > 0) r = DisjointSet[r];
    return r;
  }
  
  vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
    // The edges that will cause anomaly. These two edges are not added to the
    // graph.
    std::vector<int> multi_input_edge, loop_edge;
    DisjointSet.assign(edges.size() + 1, -1);
    for (const auto &tmp: edges) {
      if (DisjointSet[tmp[1]] == -1) {
        if (ds_find(tmp[0]) == tmp[1]) { // Loop detected.
	  // Multi-input already detected.
	  if (!multi_input_edge.empty())
	    return {DisjointSet[multi_input_edge[1]], multi_input_edge[1]};
	  loop_edge = tmp;
        } else {
	  DisjointSet[tmp[1]] = tmp[0];
	}
      } else { // Multi-input detected.
	// Loop already detected.
	if (!loop_edge.empty()) return {DisjointSet[tmp[1]], tmp[1]};

	// We are sure the current edge is redundant and it's a later edge.
	// We don't need to check it now because ds_find is time consuming.
	// if (ds_find(tmp[1]) == ds_find(tmp[0])) return tmp;
	
	// We cannot be sure which one is redundant.
	multi_input_edge = tmp;
      }
    }
    // Only one anomoly detected.
    if (loop_edge.empty()) return multi_input_edge;
    return loop_edge;
};
