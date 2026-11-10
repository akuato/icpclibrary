// 下限付き最小費用流。mincostflow.hpp が要る
// 辺の貼り方は lowerbound.hpp と同じ。コストが付くだけ
//
// 使い方
//   LowerBoundMCF g(n);
//   g.add(u, v, lo, hi, cost);  lo <= 流量 <= hi、1 単位 cost
//   ll c = g.flow(s, t, F);     s->t にちょうど F 流すときの
//                               最小費用。無理なら -1
//   ll c = g.flow(0, 0, 0);     s,t 無しで成立するかだけ見る
//   g.val(i);                   i 番目に足した辺の流量
//
// 流すのは1回だけ。コストは非負であること
struct LowerBoundMCF {
   ll n, S, T, base = 0;
   mcf_graph g;
   vll d, from, id, low;
   LowerBoundMCF(ll n)
       : n(n), S(n), T(n + 1), g(n + 2), d(n + 2, 0) {}
   void add(ll u, ll v, ll lo, ll hi, ll cost) {
      from.push_back(u), low.push_back(lo);
      id.push_back(g.add_edge(u, v, hi - lo, cost));
      d[v] += lo, d[u] -= lo, base += lo * cost;
   }
   ll val(ll i) {
      auto& e = g.g[from[i]][id[i]];
      return low[i] + g.g[e.to][e.rev].cap;
   }
   ll flow(ll s, ll t, ll F) {  // 最小費用。無理なら -1
      d[s] += F, d[t] -= F;     // 下限 F 上限 F の t->s 辺と同じ
      ll need = 0;
      rep(v, n + 2) {
         if(d[v] > 0) g.add_edge(S, v, d[v], 0), need += d[v];
         if(d[v] < 0) g.add_edge(v, T, -d[v], 0);
      }
      auto [f, c] = g.flow(S, T);
      return f == need ? base + c : -1;
   }
};
