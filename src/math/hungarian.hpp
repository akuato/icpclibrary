// 割当問題（ハンガリアン法）
// 行 i をどれか 1 つの列に重複なく割り当て、合計を最小化する。
// 行数 <= 列数 の長方形でよい（列は余ってよい）
//
//   auto [cost, as] = hungarian(a);   a[i][j] は行 i を列 j に
//   as[i] = 行 i の割り当て先の列      割り当てる費用
//
// 最大化は符号を反転して渡す（-a[i][j]）。答えも反転して戻す
// 使えない組は十分大きい値を入れる。inf は足し算で溢れるので不可
// 負の費用があってもよい
// O(n^2 m)。n = m = 1000 で 0.4 秒
pair<ll, vi> hungarian(const vvll& a) {
   ll n = sz(a), m = sz(a[0]);
   const ll big = 4e18 / 8;
   vll u(n + 1), v(m + 1);
   vi p(m + 1), way(m + 1);
   repi(i, 1, n + 1) {
      p[0] = i;
      ll j0 = 0;
      vll minv(m + 1, big);
      vector<char> used(m + 1, 0);
      do {
         used[j0] = 1;
         ll i0 = p[j0], delta = big, j1 = 0;
         repi(j, 1, m + 1) if(!used[j]) {
            ll cur = a[i0 - 1][j - 1] - u[i0] - v[j];
            if(cur < minv[j]) minv[j] = cur, way[j] = j0;
            if(minv[j] < delta) delta = minv[j], j1 = j;
         }
         rep(j, m + 1) {
            if(used[j]) u[p[j]] += delta, v[j] -= delta;
            else minv[j] -= delta;
         }
         j0 = j1;
      } while(p[j0]);
      do {
         ll j1 = way[j0];
         p[j0] = p[j1];
         j0 = j1;
      } while(j0);
   }
   vi as(n);
   ll cost = 0;
   repi(j, 1, m + 1) if(p[j]) {
      as[p[j] - 1] = j - 1;
      cost += a[p[j] - 1][j - 1];
   }
   return {cost, as};
}
