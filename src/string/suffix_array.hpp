// lcp先頭変なのはいっていそう
//  returns pair{sa, lcp}
//  sa 長さ n : s[sa[0]:] < s[sa[1]:] < … < s[sa[n-1]:]
//  lcp 長さ n-1 : lcp[i] = LCP(s[sa[i]:], s[sa[i+1]:])
#define si(a) (int)(size(a))
auto SA(string s) {
   ll n = si(s) + 1, lim = 256;
   // assert(lim > ranges::max(s));
   vector<ll> sa(n), lcp(n), x(all(s) + 1), y(n), ws(max(n, lim)), rk(n);
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
         x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
      }
   }
   repi(i, 1, n) rk[sa[i]] = i;
   for(ll i = 0, k = 0; i < n - 1; lcp[rk[i++]] = k) {
      if(k) k--;
      while(s[i + k] == s[sa[rk[i] - 1] + k]) k++;
   }
   sa.erase(begin(sa));
   lcp.erase(begin(lcp));
   return pair{sa, lcp};
}
void solve(int test) {
   string s;
   cin >> s;
   int n = s.size();
   auto re = SA(s);
   auto sa = re.first, lcp = re.second;
   reverse(all(lcp));
   lcp.pop_back();
   reverse(all(lcp));
}
