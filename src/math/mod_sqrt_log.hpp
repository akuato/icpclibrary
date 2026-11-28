// mod の平方根と離散対数。mod は 2^31 未満（積が ll に収まる範囲）
//
// mod_sqrt(a, p)   x^2 ≡ a (mod p) の解の1つ。p は素数。無ければ -1
//                  もう一つの解は p - x。Tonelli-Shanks、O(log^2 p)
// mod_log(x, y, m) x^k ≡ y (mod m) となる最小の k >= 0。無ければ -1
//                  m は素数でなくてよい。0^0 = 1。BSGS、O(√m)
//                  k > 0 で探すなら mod_log_pos（x の位数 = mod_log_pos(x, 1, m)）
ll powmod(ll a, ll e, ll m) {
   ll r = 1 % m;
   a %= m;
   for(; e; e >>= 1, a = a * a % m)
      if(e & 1) r = r * a % m;
   return r;
}
ll mod_sqrt(ll a, ll p) {
   a %= p;
   if(a < 0) a += p;
   if(a == 0 || p == 2) return a;
   if(powmod(a, (p - 1) / 2, p) != 1) return -1;
   if(p % 4 == 3) return powmod(a, (p + 1) / 4, p);
   ll s = p - 1, n = 2;
   int r = 0, m;
   while(s % 2 == 0) r++, s /= 2;
   while(powmod(n, (p - 1) / 2, p) != p - 1) n++;
   ll x = powmod(a, (s + 1) / 2, p), b = powmod(a, s, p),
      g = powmod(n, s, p);
   for(;; r = m) {
      ll t = b;
      for(m = 0; m < r && t != 1; m++) t = t * t % p;
      if(m == 0) return x;
      ll gs = powmod(g, 1LL << (r - m - 1), p);
      g = gs * gs % p, x = x * gs % p, b = b * g % p;
   }
}
// k > 0 の最小。mod_log_pos(x, 1, m) は x の位数
ll mod_log_pos(ll x, ll y, ll m) {
   x %= m, y %= m;
   ll n = (ll)sqrt(m) + 1, e = 1, f = 1, j = 1;
   unordered_map<ll, ll> A;
   while(j <= n && (e = f = e * x % m) != y) A[e * y % m] = j++;
   if(e == y) return j;
   if(gcd(m, e) == gcd(m, y))
      repi(i, 2, n + 2) if(A.count(e = e * f % m)) return n * i
          - A[e];
   return -1;
}
ll mod_log(ll x, ll y, ll m) {
   if(y % m == 1 % m) return 0;
   return mod_log_pos(x, y, m);
}
