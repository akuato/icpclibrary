// https://github.com/KentaroMatsushita/icpc_library/blob/main/src/tree/hld.hpp
#define si(a) (int)(size(a))
#define fore(e, v) for(auto&& e : v)
template<typename G> struct HLD {
   int n;
   G& g;
   vector<int> sub, in, out, head, rev, par, d;
   HLD(G& g) : n(si(g)), g(g), sub(n), in(n), out(n), head(n), rev(n), par(n), d(n) {}
   void dfs1(int x, int p) {
      par[x] = p;
      sub[x] = 1;
      if(g[x].size() and g[x][0] == p) swap(g[x][0], g[x].back());
      fore(e, g[x]) {
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
      fore(e, g[x]) {
         if(e == p) continue;
         head[e] = (g[x][0] == e ? head[x] : e);
         dfs2(e, x, t);
      }
      out[x] = t;
   }
   void build() {
      int t = 0;
      head[0] = 0;
      dfs1(0, -1);
      dfs2(0, -1, t);
   }
   int la(int v, int k) {
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
   int jump(int s, int t, int i) {
      if(!i) return s;
      int l = lca(s, t);
      int dst = d[s] + d[t] - d[l] * 2;
      if(dst < i) return -1;
      if(d[s] - d[l] >= i) return la(s, i);
      i -= d[s] - d[l];
      return la(t, d[t] - d[l] - i);
   }
};
// 以下、使い方
using S = ll;
S op(S a, S b) { return a + b; }
S e() { return 0ll; }
void solve(int test) {
   int n;
   cin >> n;
   int m = n - 1;
   vi u(m), v(m), w(m);
   vvi g(n);
   rep(i, m) {
      cin >> u[i] >> v[i] >> w[i];
      u[i]--, v[i]--;
      g[u[i]].push_back(v[i]);
      g[v[i]].push_back(u[i]);
   }
   HLD hld(g);
   hld.build();
   vi edgetoin(m);
   rep(i, m) {
      // 辺を子のinに対応させる
      int a = u[i], b = v[i];
      if(hld.par[b] == a) swap(a, b);
      edgetoin[i] = hld.in[a];
   }
   SegmentTree<S, op, e> seg(n);
   rep(i, m) { seg.set(edgetoin[i], w[i]); }
   auto query = [&](int l, int r) { return seg.prod(l, r); };
   int q;
   cin >> q;
   rep(qi, q) {
      int t;
      cin >> t;
      if(t == 1) {
         int i, x;
         cin >> i >> x;
         i--;
         w[i] = x;
         seg.set(edgetoin[i], w[i]);
      } else {
         int a, b;
         cin >> a >> b;
         a--;
         b--;
         auto res = hld.query(a, b, e(), query, op, true);
         cout << res << endl;
      }
   }
}
int main() {
   cin.tie(0);
   ios::sync_with_stdio(false);
   int t = 1;  // cin >>t;
   rep(test, t) solve(test);
}
