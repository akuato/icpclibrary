// 強連結成分分解。ACL と同じ使い方
//
// 使い方
//   SCC g(n);
//   g.add(u, v);        有向辺 u -> v
//   vvi grp = g.scc();  成分ごとの頂点。トポロジカル順
//   g.comp[v]           v の成分番号。scc() を呼んだあと
//   g.num               成分の個数
//
// 辺 u -> v があれば必ず comp[u] <= comp[v]
// 縮約してDAGを作るなら grp をそのまま前から見ればよい
//
// O(n + m)。再帰を使っていないので深さで落ちない
struct SCC {
   int n, num = 0;
   vi comp;
   vvi g;
   SCC(int n) : n(n), comp(n, -1), g(n) {}
   void add(int u, int v) { g[u].push_back(v); }
   vvi scc() {
      vi ord(n, -1), low(n), on(n, 0), st;
      vp call;  // (頂点, 次に見る辺の番号)
      int k = 0;
      num = 0;
      rep(s, n) {
         if(ord[s] != -1) continue;
         ord[s] = low[s] = k++, st.push_back(s), on[s] = 1;
         call.push_back({s, 0});
         while(!call.empty()) {
            auto [v, i] = call.back();
            if(i < sz(g[v])) {
               call.back().second++;
               int u = g[v][i];
               if(ord[u] == -1) {
                  ord[u] = low[u] = k++;
                  st.push_back(u), on[u] = 1;
                  call.push_back({u, 0});
               } else if(on[u]) chmin(low[v], ord[u]);
               continue;
            }
            call.pop_back();
            if(low[v] == ord[v]) {
               while(1) {
                  int u = st.back();
                  st.pop_back(), on[u] = 0, comp[u] = num;
                  if(u == v) break;
               }
               num++;
            }
            if(!call.empty())
               chmin(low[call.back().first], low[v]);
         }
      }
      rep(v, n) comp[v] = num - 1 - comp[v];
      vvi grp(num);
      rep(v, n) grp[comp[v]].push_back(v);
      return grp;
   }
};
