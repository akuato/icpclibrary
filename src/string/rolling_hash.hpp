// mod 2^61-1、基数はランダム
// b と p は全インスタンスで共有されるので
// 別の文字列同士も比較できる
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
      static mt19937_64 r(random_device{}());
      if(!b) b = M / 2 + r() % (M / 2);
      while(sz(p) <= n) p.push_back(mul(p.back(), b));
   }
   // x の後ろに、長さ ly のハッシュ y をつなぐ
   static ull concat(ull x, ull y, ll ly) {
      ext(ly);
      ull w = mul(x, p[ly]) + y;
      return w >= M ? w - M : w;
   }
   RH() : h{0} {}
   // string でも vi/vll でもよい
   // 値は 0 以上 2^61-1 未満
   // 負が混じるなら全体に下駄を履かせる
   // 0 を含む数列で長さの違う区間どうしを比べるなら
   // 全体に +1 しておくと安全
   template<class T> RH(const T& s) : h{0} {
      ext(sz(s));
      for(auto c : s) {
         ull w = mul(h.back(), b) + c;
         h.push_back(w >= M ? w - M : w);
      }
   }
   ull get(ll l, ll r) {  // s[l,r)
      ull w = h[r] + M - mul(h[l], p[r - l]);
      return w >= M ? w - M : w;
   }
};
