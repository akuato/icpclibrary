// https://github.com/KentaroMatsushita/icpc_library/blob/main/src/tree/hld.hpp
template<typename G> struct HLD {
   int n;
   G& g;
   vi sub, in, out, head, rev, par, d;
   HLD(G& g) : n((int)sz(g)), g(g), sub(n), in(n), out(n), head(n), rev(n), par(n), d(n) {}
   void dfs1(int x, int p) {
      par[x] = p;
      sub[x] = 1;
      if(sz(g[x]) and g[x][0] == p) swap(g[x][0], g[x].back());
      for(auto& e: g[x]) {
         if(e == p) continue;
         d[e] = d[x] + 1;
         dfs1(e, x);
         sub[x] += sub[e];
         if(sub[g[x][0]] < sub[e]) swap(g[x][0], e);
      }
   }
   void dfs2(int x, int p, int& t) {
      in[x] = t++;
      rev[in[x]] = x;
      for(auto& e: g[x]) {
         if(e == p) continue;
         head[e] = (g[x][0] == e ? head[x] : e);
         dfs2(e, x, t);
      }
      out[x] = t;
   }
   void build(int r = 0) {  // 根を指定する
      int t = 0;
      head[r] = r;
      dfs1(r, -1);
      dfs2(r, -1, t);
   }
   int la(int v, int k) {  // v の k 個上の祖先
      while(1) {
         int u = head[v];
         if(in[v] - k >= in[u]) return rev[in[v] - k];
         k -= in[v] - in[u] + 1;
         v = par[u];
      }
   }
   int lca(int u, int v) {
      for(;; v = par[head[v]]) {
         if(in[u] > in[v]) swap(u, v);
         if(head[u] == head[v]) return u;
      }
   }
   // パス u-v 上の集約。q(l,r) は [l,r) の積、f は結合。edge = true で辺に対応
   template<typename T, typename Q, typename F>
   T query(int u, int v, const T& e, const Q& q, const F& f, bool edge = false) {
      T l = e, r = e;
      for(;; v = par[head[v]]) {
         if(in[u] > in[v]) swap(u, v), swap(l, r);
         if(head[u] == head[v]) break;
         l = f(q(in[head[v]], in[v] + 1), l);
      }
      return f(f(q(in[u] + edge, in[v] + 1), l), r);
   }
   int dist(int u, int v) { return d[u] + d[v] - 2 * d[lca(u, v)]; }
   int jump(int s, int t, int i) {  // パス s-t の i 番目の頂点。届かなければ -1
      if(!i) return s;
      int l = lca(s, t);
      int dst = d[s] + d[t] - d[l] * 2;
      if(dst < i) return -1;
      if(d[s] - d[l] >= i) return la(s, i);
      i -= d[s] - d[l];
      return la(t, d[t] - d[l] - i);
   }
};
/* 以下、使い方（辺に重みがあり、1点更新とパスの和クエリ）
using S = ll;
S op(S a, S b) { return a + b; }
S e() { return 0ll; }

   vvi g(n);
   rep(i, m) { cin >> u[i] >> v[i] >> w[i], u[i]--, v[i]--;
      g[u[i]].push_back(v[i]), g[v[i]].push_back(u[i]); }
   HLD hld(g);
   hld.build();
   vi edgetoin(m);
   rep(i, m) {                      // 辺を子の in に対応させる
      int a = u[i], b = v[i];
      if(hld.par[b] == a) swap(a, b);
      edgetoin[i] = hld.in[a];
   }
   SegmentTree<S, op, e> seg(n);
   rep(i, m) seg.set(edgetoin[i], w[i]);
   auto query = [&](int l, int r) { return seg.prod(l, r); };
   // 辺 i の重みを x に:   seg.set(edgetoin[i], x);
   // パス a-b の和:        hld.query(a, b, e(), query, op, true);
*/
