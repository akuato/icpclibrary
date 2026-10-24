ll pow_pow(ll x, ll n, ll mod) {
   if(n == 0) return 1;
   x %= mod;
   ll res = pow_pow(x * x % mod, n / 2, mod);
   if(n & 1) res = res * x % mod;
   return res;
}
ll gcdll(ll x, ll y) {
   if(y == 0) return x;
   return gcdll(y, x % y);
}
ll INFF = 1000100100100100100;
ll lcmll(ll x, ll y) {
   ll X = (x / gcdll(x, y)), Y = y;
   if(X <= INFF / Y) return X * Y;
   else return INFF;
}