#define FOR(i, a, n) for(ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()

// x座標が相異なるn+1点(x_i,y_i)を通るn次以下の多項式f(x)を返す
// O(n^2)
vector<mint> lagrange_interpolation(vector<mint> x, vector<mint> y) {
   const ll n = x.size() - 1;
   REP(i, n + 1) {
      mint t = 1;
      REP(j, n + 1) if(i != j) t *= x[i] - x[j];
      y[i] /= t;
   }
   ll cur = 0, nxt = 1;
   vector<vector<mint>> dp(2, vector<mint>(n + 2));
   dp[0][0] = -1 * x[0], dp[0][1] = 1;
   FOR(i, 1, n + 1) {
      REP(j, n + 2) {
         dp[nxt][j] = dp[cur][j] * -1 * x[i];
         if(j >= 1) dp[nxt][j] += dp[cur][j - 1];
      }
      swap(nxt, cur);
   }
   vector<mint> xinv(n + 1);
   REP(i, n + 1) xinv[i] = x[i].inv();
   vector<mint> ret(n + 1);  // f(x)
   REP(i, n + 1) {
      if(y[i] == 0) continue;
      // 0割り対策の場合分け
      if(x[i] == 0) {
         REP(j, n + 1) ret[j] += dp[cur][j + 1] * y[i];
      } else {
         ret[0] -= dp[cur][0] * xinv[i] * y[i];
         mint pre = -1 * dp[cur][0] * xinv[i];
         FOR(j, 1, n + 1) {
            ret[j] -= (dp[cur][j] - pre) * xinv[i] * y[i];
            pre = -1 * (dp[cur][j] - pre) * xinv[i];
         }
      }
   }
   return ret;
}

mint lagrange_interpolationT(vector<mint> x, vector<mint> y, mint T) {
   const ll n = x.size() - 1;
   mint ret = 0;
   REP(i, n + 1) {
      mint t = 1;
      REP(j, n + 1) {
         if(i == j) continue;
         t *= T - x[j];
         t /= x[i] - x[j];
      }
      ret += t * y[i];
   }
   return ret;
}
