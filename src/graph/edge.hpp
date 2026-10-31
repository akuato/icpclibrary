struct edge {
   int to;
   ll cost;
   int id;
   edge(int to, ll cost = 1, int id = -1) : to(to), cost(cost), id(id) {}
};
using vve = vector<vector<edge>>;
