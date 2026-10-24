struct Trie {
   int cz;
   vvi g;
   int size;
   vll dp;
   Trie(int cz = 26) : cz(cz), g(1, vi(cz)), size(1), dp(1) {}
   void add(vi& s) {
      int si = s.size();
      int id = 0;
      rep(j, si) {
         if(g[id][s[j]]) {
            id = g[id][s[j]];
         } else {
            g[id][s[j]] = size;
            id = size;
            size++;
            g.push_back(vi(cz));
            dp.push_back(0);
         }
         dp[id]++;
      }
   }
};