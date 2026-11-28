#define PROBLEM                              \
   "https://judge.u-aizu.ac.jp/onlinejudge/" \
   "description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#undef rep
#undef sz
#define rep(i, n) for(ll i = 0; i < (n); i++)
#define repi(i, a, b) for(ll i = (a); i < (b); i++)
#define sz(a) (ll)(size(a))
#include "src/math/mod_sqrt_log.hpp"

int main() {
   mt19937_64 rng(20261127);
   vector<ll> ps = {2,    3,     5,     7,         13,
                    17,   41,    97,    193,       257,
                    7681, 12289, 65537, 998244353, 1000000007};
   for(ll p : ps) {
      int cnt = p < 100000 ? (int)p : 3000;
      rep(i, cnt) {
         ll a = p < 100000 ? i : (ll)(rng() % p);
         ll x = mod_sqrt(a, p);
         bool has;
         if(p < 100000) {
            has = false;
            rep(y, p) if(y * y % p == a) has = true;
         } else has = a == 0 || powmod(a, (p - 1) / 2, p) == 1;
         assert((x >= 0) == has);
         if(x >= 0) assert(x * x % p == a);
      }
   }
   // mod_log を全探索と突き合わせ（m は合成数も）
   repi(m, 1, 200) rep(x, m) rep(y, m) {
      ll e = -1, v = 1 % m;
      rep(k, 2 * m + 2) {
         if(v == y) {
            e = k;
            break;
         }
         v = v * x % m;
      }
      assert(mod_log(x, y, m) == e);
   }
   rep(it, 2000) {
      ll m = 1 + rng() % 1000000000, x = rng() % m,
         k = rng() % 1000;
      ll y = powmod(x, k, m), r = mod_log(x, y, m);
      assert(r >= 0 && r <= k && powmod(x, r, m) == y);
   }
   puts("Hello World");
}
