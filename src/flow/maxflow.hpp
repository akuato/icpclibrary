// Dinic法 O(V^2E)
struct mf_graph {
   struct edge { int to; ll cap; int rev; };
   ll V;
   vector<vector<edge>> g;
   vll dis, nxt;
   mf_graph(ll v) : V(v), g(v) {}
   ll add_edge(ll a, ll b, ll cap) {  // 返り値は辺のindex。あとで g[a][id].cap を変更できる
      g[a].push_back({(int)b, cap, (int)sz(g[b])});
      g[b].push_back({(int)a, 0, (int)sz(g[a]) - 1});
      return sz(g[a]) - 1;
   }
   void bfs(ll s) {
      dis.assign(V, -1), dis[s] = 0;
      queue<ll> q;
      q.push(s);
      while(sz(q)) {
         ll v = q.front();
         q.pop();
         for(auto& e : g[v]) if(e.cap > 0 && dis[e.to] < 0) dis[e.to] = dis[v] + 1, q.push(e.to);
      }
   }
   ll dfs(ll v, ll t, ll f) {
      if(v == t) return f;
      for(ll& i = nxt[v]; i < sz(g[v]); i++) {
         auto& e = g[v][i];
         if(e.cap > 0 && dis[v] < dis[e.to]) {
            ll d = dfs(e.to, t, min(f, e.cap));
            if(d > 0) { e.cap -= d, g[e.to][e.rev].cap += d; return d; }
         }
      }
      return 0;
   }
   ll max_flow(ll s, ll t) {
      ll res = 0;
      while(1) {
         bfs(s);
         if(dis[t] < 0) return res;
         nxt.assign(V, 0);
         ll f;
         while((f = dfs(s, t, inf)) > 0) res += f;
      }
   }
};
