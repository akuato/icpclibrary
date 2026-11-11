// https://github.com/KentaroMatsushita/icpc_library/blob/main/src/flow/bipartite-matching.hpp
// 二部マッチング Hopcroft-Karp
//
// 使い方
//   Bimatch bm(nl, nr);   左の頂点数、右の頂点数
//   bm.add(u, v);         左 u と右 v を結ぶ（0-indexed）
//   int m = bm.match();   最大マッチングの本数
//   bm.mc[v]              右 v の相手の左頂点。-1 なら未マッチ
//
// 左右で番号空間が別なので、元の番号をそのまま渡さないこと
// O(E √V)
struct Bimatch {
   vector<vi> g;
   vi d, mc, used, vv;
   Bimatch(int n, int m) : g(n), mc(m, -1), used(n) {}
   void add(int u, int v) { g[u].emplace_back(v); }
   void bfs() {
      d.assign(sz(g), -1);
      queue<int> q;
      rep(i, sz(g)) {
         if(!used[i]) {
            q.emplace(i);
            d[i] = 0;
         }
      }
      while(!q.empty()) {
         int x = q.front();
         q.pop();
         for(auto& e : g[x]) {
            int c = mc[e];
            if(c >= 0 and d[c] == -1) {
               d[c] = d[x] + 1;
               q.emplace(c);
            }
         }
      }
   }

   bool dfs(int x) {
      vv[x] = true;
      for(auto& e : g[x]) {
         int c = mc[e];
         if(c < 0 or (!vv[c] and d[c] == d[x] + 1 and dfs(c))) {
            mc[e] = x;
            used[x] = true;
            return true;
         }
      }
      return false;
   }
   int match() {
      int ret = 0;
      while(true) {
         bfs();
         vv.assign(sz(g), false);
         int f = 0;
         rep(i, sz(g)) if(!used[i] and dfs(i)) f++;
         if(!f) return ret;
         ret += f;
      }
   }
};
