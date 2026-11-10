// 最大流 Dinic
//
// 使い方
//   mf_graph g(n);
//   ll id = g.add_edge(from, to, cap);  g[from] 内の番号が返る
//   ll f = g.flow(s, t);                流せるだけ流す
//   ll f = g.flow(s, t, lim);           lim まで流す
//   vi c = g.min_cut(s);                c[v]=1 なら v は s 側
//   g.g[from][id].cap で残容量が見える
//
// O(V^2 E)。容量が全部 1 なら O(E √E)
// 二部マッチングなら O(E √V)
// dfs は再帰。深さは最大 V なので、深いなら ulimit -s 65532
struct mf_graph {
   struct edge {
      int to;
      ll cap;
      int rev;
   };
   ll V;
   vector<vector<edge>> g;
   vll dis, nxt;
   mf_graph(ll v) : V(v), g(v) {}
   ll add_edge(ll a, ll b, ll cap) {
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
         for(auto& e : g[v])
            if(e.cap > 0 && dis[e.to] < 0)
               dis[e.to] = dis[v] + 1, q.push(e.to);
      }
   }
   ll dfs(ll v, ll t, ll f) {
      if(v == t) return f;
      for(ll& i = nxt[v]; i < sz(g[v]); i++) {
         auto& e = g[v][i];
         if(e.cap > 0 && dis[v] < dis[e.to]) {
            ll d = dfs(e.to, t, min(f, e.cap));
            if(d > 0) {
               e.cap -= d, g[e.to][e.rev].cap += d;
               return d;
            }
         }
      }
      return 0;
   }
   ll flow(ll s, ll t, ll lim = inf) {
      ll res = 0;
      while(res < lim) {
         bfs(s);
         if(dis[t] < 0) break;
         nxt.assign(V, 0);
         ll f;
         while(res < lim && (f = dfs(s, t, lim - res)) > 0)
            res += f;
      }
      return res;
   }
   // flow を呼んだあとに使う。残余グラフで s から行ける側が 1
   vi min_cut(ll s) {
      vi c(V, 0);
      queue<ll> q;
      q.push(s), c[s] = 1;
      while(sz(q)) {
         ll v = q.front();
         q.pop();
         for(auto& e : g[v])
            if(e.cap > 0 && !c[e.to]) c[e.to] = 1, q.push(e.to);
      }
      return c;
   }
};
