// Suffix Array。ACL と同じ使い方
//
//   vector<int> sa = suffix_array(s);   長さ n
//   s[sa[0]:] < s[sa[1]:] < … < s[sa[n-1]:]
//
// LCP が要るなら lcp_array.hpp も入れて
//   vector<int> lcp = lcp_array(s, sa);
//
// 空白・大文字・記号そのまま使える（byte で比較）
// O(n log n)。ACL の SA-IS より3倍遅いが 10^6 で 0.3 秒
// 参考: kactl
#define si(a) (int)(size(a))
vector<int> suffix_array(string s) {
   ll n = si(s) + 1, lim = 256;
   vector<ll> sa(n), x(n), y(n), ws(max(n, lim));
   // 末尾は番兵 0
   repi(i, 0, n - 1) x[i] = (unsigned char)s[i];
   iota(all(sa), 0);
   for(ll j = 0, p = 0; p < n; j = max(1LL, j * 2), lim = p) {
      p = j;
      iota(all(y), n - j);
      repi(i, 0, n) if(sa[i] >= j) y[p++] = sa[i] - j;
      fill(all(ws), 0);
      repi(i, 0, n) ws[x[i]]++;
      repi(i, 1, lim) ws[i] += ws[i - 1];
      for(ll i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
      swap(x, y);
      p = 1;
      x[sa[0]] = 0;
      repi(i, 1, n) {
         ll a = sa[i - 1], b = sa[i];
         x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1
                                                       : p++;
      }
   }
   return vector<int>(sa.begin() + 1, sa.end());  // 番兵を外す
}
