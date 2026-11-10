// 下限付きフロー。maxflow.hpp が要る
// 流すのは普通の最大流で、やっているのは辺の貼り方だけ
//
// 使い方
//   LowerBound g(n);
//   g.add(u, v, lo, hi);      lo <= 流量 <= hi
//   ---- 辺を全部足してから、下の1つだけを呼ぶ ----
//   bool ok = g.feasible();   s,t を決めず、全頂点で保存則を
//                             満たす流れがあるか
//   ll f = g.max_flow(s, t);  下限を満たす最大流。無理なら -1
//   ll f = g.min_flow(s, t);  下限を満たす最小流。無理なら -1
//   ---- そのあと ----
//   g.val(i);                 i 番目に足した辺の流量
//
// 仕組み: 辺 (u,v,lo,hi) を容量 hi-lo にして、下限ぶんの lo を
// 「v に湧き出し、u に吸い込み」として超頂点に預ける。
// 預けた量を全部流し切れたら、下限を満たせている
//
// max_flow / min_flow は s に入る辺・t から出る辺が無い素直な
// ネットワークを前提にしている
struct LowerBound {
   ll n, S, T;
   mf_graph g;
   vll d, from, id, low;
   LowerBound(ll n)
       : n(n), S(n), T(n + 1), g(n + 2), d(n + 2, 0) {}
   void add(ll u, ll v, ll lo, ll hi) {
      from.push_back(u), low.push_back(lo);
      id.push_back(g.add_edge(u, v, hi - lo));
      d[v] += lo, d[u] -= lo;
   }
   ll val(ll i) {  // i 番目の辺の流量
      auto& e = g.g[from[i]][id[i]];
      return low[i] + g.g[e.to][e.rev].cap;
   }
   bool feasible() {  // 超頂点を繋ぎ、預けた量を流し切れるか
      ll need = 0;
      rep(v, n + 2) {
         if(d[v] > 0) g.add_edge(S, v, d[v]), need += d[v];
         if(d[v] < 0) g.add_edge(v, T, -d[v]);
      }
      return g.flow(S, T) == need;
   }
   ll st(ll s, ll t, bool mx) {
      ll i = g.add_edge(t, s, inf);  // 先に閉じる辺を張る
      if(!feasible()) return -1;
      auto& e = g.g[t][i];
      ll f = g.g[s][e.rev].cap;  // t->s に流れた量
      e.cap = 0, g.g[s][e.rev].cap = 0;  // その辺を外す
      return mx ? f + g.flow(s, t) : f - g.flow(t, s);
   }
   ll max_flow(ll s, ll t) { return st(s, t, true); }
   ll min_flow(ll s, ll t) { return st(s, t, false); }
};
