// {998244353, 3}, {1811939329, 13}, {2013265921, 31}
mint g = 3;  // 原始根
void fft(vector<mint>& a) {
   ll n = sz(a), lg = __lg(n);
   assert((1 << lg) == n);
   vector<mint> b(n);
   repi(l, 1, lg + 1) {
      ll w = n >> l;
      mint s = 1, r = g.pow(mod >> l);
      for(ll u = 0; u < n / 2; u += w) {
         repi(d, 0, w) {
            mint x = a[u << 1 | d], y = a[u << 1 | w | d] * s;
            b[u | d] = x + y;
            b[n >> 1 | u | d] = x - y;
         }
         s *= r;
      }
      swap(a, b);
   }
}
vector<mint> conv(vector<mint> a, vector<mint> b) {
   if(a.empty() || b.empty()) return {};
   size_t s = sz(a) + sz(b) - 1, n = bit_ceil(s);
   // if(min(sz(a), sz(b)) <= 60) 愚直に掛け算
   a.resize(n);
   b.resize(n);
   fft(a);
   fft(b);
   mint inv = mint(n).inv();
   repi(i, 0, n) a[i] *= b[i] * inv;
   reverse(1 + all(a));
   fft(a);
   a.resize(s);
   return a;
}
