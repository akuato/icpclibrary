// 最小費用流 O(FElogV)。コストは非負
struct mcf_graph {
   struct edge { int to; ll cap, cost; int rev; };
   ll V;
   vector<vector<edge>> g;
   vll h, dis, pv, pe;
   mcf_graph(ll v) : V(v), g(v), dis(v), pv(v), pe(v) {}
   void add_edge(ll a, ll b, ll cap, ll cost) {
      g[a].push_back({(int)b, cap, cost, (int)sz(g[b])});
      g[b].push_back({(int)a, 0, -cost, (int)sz(g[a]) - 1});
   }
   ll min_cost_flow(ll s, ll t, ll f) {
      ll res = 0;
      h.assign(V, 0);
      while(f > 0) {
         priority_queue<P, vp, greater<P>> q;
         dis.assign(V, inf), dis[s] = 0;
         q.push({0, s});
         while(sz(q)) {
            auto [d, v] = q.top();
            q.pop();
            if(dis[v] < d) continue;
            rep(i, sz(g[v])) {
               auto& e = g[v][i];
               ll nd = dis[v] + e.cost + h[v] - h[e.to];
               if(e.cap > 0 && dis[e.to] > nd) dis[e.to] = nd, pv[e.to] = v, pe[e.to] = i, q.push({nd, e.to});
            }
         }
         if(dis[t] == inf) return -1;
         rep(i, V) h[i] += dis[i];
         ll d = f;
         for(ll v = t; v != s; v = pv[v]) chmin(d, g[pv[v]][pe[v]].cap);
         f -= d, res += d * h[t];
         for(ll v = t; v != s; v = pv[v]) {
            auto& e = g[pv[v]][pe[v]];
            e.cap -= d, g[v][e.rev].cap += d;
         }
      }
      return res;
   }
};
