// https://github.com/KentaroMatsushita/icpc_library/blob/main/src/graph/lowlink.hpp
template<typename G> struct LL {
   int n;
   const G g;
   vi ord, low, arti;
   vp bridge;

   LL(G g) : n(sz(g)), g(g), ord(sz(g), -1), low(sz(g), -1) {
      int k = 0;
      rep(i, n) {
         if(ord[i] == -1) k = dfs(i, k, -1);
      }
   }

   int dfs(int x, int k, int p) {
      low[x] = (ord[x] = k++);
      int cnt = 0;
      bool is_arti = false, second = false;
      for(auto& e : g[x]) {
         if(ord[e] == -1) {
            cnt++;
            k = dfs(e, k, x);
            chmin(low[x], low[e]);
            is_arti |= (p != -1) && (low[e] >= ord[x]);
            if(ord[x] < low[e]) bridge.emplace_back(minmax(x, e));
         } else if(e != p or second) {
            chmin(low[x], ord[e]);
         } else {
            second = true;
         }
      }
      is_arti |= p == -1 && cnt > 1;
      if(is_arti) arti.emplace_back(x);
      return k;
   }
};