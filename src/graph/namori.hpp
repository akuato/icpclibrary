// 無向なもり。各連結成分で 頂点数 = 辺数、閉路がちょうど1つ
// 非連結でもよい。木だけの成分があると assert で落ちる
//
// 使い方
//   vvi g(n);
//   rep(i, n) { cin >> u >> v; u--, v--;
//               g[u].eb(v), g[v].eb(u); }
//   Namori nm(g);
//   nm.oncyc[v]    v が閉路上か
//   nm.cid[v]      連結成分の番号
//   nm.cyc[c]      成分 c の閉路。隣接順に並ぶ
//   nm.idx[v]      閉路上なら cyc 内の位置
//   nm.root[v]     v が属する木の根（閉路上の頂点）
//   nm.dep[v]      root[v] から v までの距離
//   nm.par[v]      木の中での親。root なら -1
//   nm.cdist(a, b) 閉路上の2頂点の距離
//   nm.dist(u, v)  重みなし最短距離。別成分なら -1
//
// 構築 O(n)
// dist は root が違えば O(1)、同じ木の中は O(深さ)
// 自己ループは g[v] に v を2回入れる（閉路長1）
// 多重辺は閉路長2として扱われる
#define fore(e, v) for(auto&& e : v)
#define eb emplace_back
#define si(a) (int)(size(a))
template<typename G> struct Namori {
   int n;
   const G g;
   vi oncyc, cid, idx, root, dep, par;
   vector<vi> cyc;
   Namori(const G& g_)
       : n(si(g_)), g(g_), oncyc(n, 1), cid(n, -1), idx(n, -1),
         root(n, -1), dep(n), par(n, -1) {
      vi d(n), st;
      rep(v, n) d[v] = si(g[v]);
      rep(v, n) if(d[v] <= 1) oncyc[v] = 0, st.eb(v);
      while(!st.empty()) {
         int v = st.back();
         st.pop_back();
         fore(u, g[v]) if(oncyc[u] && --d[u] <= 1) {
            oncyc[u] = 0, st.eb(u);
         }
      }
      int c = 0;
      rep(s, n) {
         if(!oncyc[s] || cid[s] != -1) continue;
         cyc.eb();
         for(int v = s; v != -1;) {
            cid[v] = c, root[v] = v;
            idx[v] = si(cyc[c]), cyc[c].eb(v);
            int nx = -1;
            fore(u, g[v]) if(oncyc[u] && cid[u] == -1) {
               nx = u;
               break;
            }
            v = nx;
         }
         c++;
      }
      vi q;
      rep(v, n) if(oncyc[v]) q.eb(v);
      rep(i, si(q)) {
         int v = q[i];
         fore(u, g[v]) if(cid[u] == -1) {
            cid[u] = cid[v], root[u] = root[v], par[u] = v;
            dep[u] = dep[v] + 1, q.eb(u);
         }
      }
      rep(v, n) assert(cid[v] != -1);  // 木だけの成分がある
   }
   int cdist(int a, int b) {  // a, b は閉路上
      int L = si(cyc[cid[a]]), x = abs(idx[a] - idx[b]);
      return min(x, L - x);
   }
   int dist(int u, int v) {
      if(cid[u] != cid[v]) return -1;
      if(root[u] != root[v])
         return dep[u] + dep[v] + cdist(root[u], root[v]);
      int res = 0;  // 同じ木の中。LCA まで登る
      while(dep[u] > dep[v]) u = par[u], res++;
      while(dep[v] > dep[u]) v = par[v], res++;
      while(u != v) u = par[u], v = par[v], res += 2;
      return res;
   }
};
