using ull = unsigned long long;
struct TreeHash {
   const vvi& g;
   vector<ull> h, rnd;
   vi ht;
   mt19937_64 mt{(ull)chrono::steady_clock::now().time_since_epoch().count()};
   TreeHash(const vvi& g) : g(g), h(sz(g)), ht(sz(g)) {}
   ull operator()(vi& ng, int r) {
      int sv = ng[r];
      ng[r] = 1, dfs(ng, r), ng[r] = sv;
      return h[r];
   }
   void dfs(vi& ng, int v) {
      h[v] = 1, ht[v] = 0;
      for(int u : g[v]) if(!ng[u]) {
         ng[u] = 1, dfs(ng, u), ng[u] = 0;
         while(sz(rnd) <= ht[u]) rnd.push_back(mt());
         h[v] *= (h[u] + rnd[ht[u]]) | 1;
         chmax(ht[v], ht[u] + 1);
      }
   }
};
