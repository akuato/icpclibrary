constexpr int MAX = 10;
ll fact[MAX], finv[MAX], invv[MAX];
void initcomb() {
   fact[0] = fact[1] = 1;
   finv[0] = finv[1] = 1;
   invv[1] = 1;
   for(int i = 2; i < MAX; i++) {
      fact[i] = fact[i - 1] * i % mod;
      invv[i] = mod - invv[mod % i] * (mod / i) % mod;
      finv[i] = finv[i - 1] * invv[i] % mod;
   }
}
ll comb(ll n, ll k) {
   if(n < k) return 0;
   if(n < 0 || k < 0) return 0;
   return fact[n] * (finv[k] * finv[n - k] % mod) % mod;
}