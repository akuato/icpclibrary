// 最小費用流。コストは非負であること（負だと壊れる）
//
// 使い方
//   mcf_graph g(n);
//   g.add_edge(from, to, cap, cost);
//   auto [f, c] = g.flow(s, t);         流せるだけ流す
//   auto [f, c] = g.flow(s, t, lim);    lim まで流す
//   f が欲しい量に届かなければ実現不可
//
// O(F E log V)。F は流量なので、F が大きいと効かない
// 1回の flow で使い切り。続けて呼ぶと残容量から再開する
struct mcf_graph {
   struct edge {
      int to;
      ll cap, cost;
      int rev;
   };
   ll V;
   vector<vector<edge>> g;
   vll h, dis, pv, pe;
   mcf_graph(ll v) : V(v), g(v), h(v), dis(v), pv(v), pe(v) {}
   void add_edge(ll a, ll b, ll cap, ll cost) {
      g[a].push_back({(int)b, cap, cost, (int)sz(g[b])});
      g[b].push_back({(int)a, 0, -cost, (int)sz(g[a]) - 1});
   }
   P flow(ll s, ll t, ll lim = inf) {  // {流せた量, 費用}
      ll fl = 0, res = 0;
      h.assign(V, 0);
      while(fl < lim) {
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
               if(e.cap > 0 && dis[e.to] > nd)
                  dis[e.to] = nd, pv[e.to] = v, pe[e.to] = i,
                  q.push({nd, e.to});
            }
         }
         if(dis[t] == inf) break;
         // 到達できない頂点は触らない。inf を足すと溢れる
         rep(i, V) if(dis[i] != inf) h[i] += dis[i];
         ll d = lim - fl;
         for(ll v = t; v != s; v = pv[v])
            chmin(d, g[pv[v]][pe[v]].cap);
         fl += d, res += d * h[t];
         for(ll v = t; v != s; v = pv[v]) {
            auto& e = g[pv[v]][pe[v]];
            e.cap -= d, g[v][e.rev].cap += d;
         }
      }
      return {fl, res};
   }
};
