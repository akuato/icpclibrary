// mod 2^61-1、基数はランダム。b と p は全インスタンスで共有されるので別の文字列同士も比較できる
using ull = unsigned long long;
struct RH {
   static constexpr ull M = (1ull << 61) - 1;
   static inline vector<ull> p = {1};
   static inline ull b = 0;
   vector<ull> h;
   static ull mul(ull x, ull y) {
      __uint128_t z = (__uint128_t)x * y;
      ull w = (ull)(z >> 61) + (ull)(z & M);
      return w >= M ? w - M : w;
   }
   static void ext(ll n) {
      if(!b) b = M / 2 + mt19937_64(chrono::steady_clock::now().time_since_epoch().count())() % (M / 2);
      while(sz(p) <= n) p.push_back(mul(p.back(), b));
   }
   static ull concat(ull x, ull y, ll ly) {  // x の後ろに、長さ ly のハッシュ y をつなぐ
      ext(ly);
      ull w = mul(x, p[ly]) + y;
      return w >= M ? w - M : w;
   }
   RH(const string& s) : h(sz(s) + 1) {
      ext(sz(s));
      for(ll i = 0; i < sz(s); i++) {
         h[i + 1] = mul(h[i], b) + s[i];
         if(h[i + 1] >= M) h[i + 1] -= M;
      }
   }
   ull get(ll l, ll r) {  // s[l,r)
      ull w = h[r] + M - mul(h[l], p[r - l]);
      return w >= M ? w - M : w;
   }
};
