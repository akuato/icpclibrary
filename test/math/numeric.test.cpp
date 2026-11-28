#define PROBLEM                              \
   "https://judge.u-aizu.ac.jp/onlinejudge/" \
   "description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#undef rep
#undef sz
#define rep(i, n) for(ll i = 0; i < (n); i++)
#define repi(i, a, b) for(ll i = (a); i < (b); i++)
#define sz(a) (ll)(size(a))
#include "src/math/numeric.hpp"

int main() {
   const double PI = acos(-1);
   mt19937_64 rng(20261127);
   // 多項式（Simpson は 3 次まで厳密）と滑らかな関数
   rep(it, 2000) {
      double c[6];
      for(auto& v : c) v = (double)(rng() % 201) / 10 - 10;
      double a = (double)(rng() % 201) / 10 - 10,
             b = a + (double)(rng() % 100) / 10;
      auto f = [&](double x) {
         double s = 0, p = 1;
         rep(i, 6) s += c[i] * p, p *= x;
         return s;
      };
      auto F = [&](double x) {
         double s = 0, p = x;
         rep(i, 6) s += c[i] * p / (i + 1), p *= x;
         return s;
      };
      double e = F(b) - F(a), g = integrate(f, a, b);
      assert(fabs(e - g) <= 1e-6 * max(1.0, fabs(e)));
   }
   assert(fabs(integrate([](double x) { return sin(x); }, 0, PI)
               - 2)
          < 1e-9);
   assert(fabs(integrate([](double x) { return exp(x); }, 0, 3)
               - (exp(3) - 1))
          < 1e-8);
   // 半円の面積（端で微分が発散する）
   double semi = integrate(
       [](double x) { return sqrt(max(0.0, 1 - x * x)); }, -1,
       1);
   assert(fabs(semi - PI / 2) < 1e-6);
   // 二重積分: 単位円板上の x^2 の積分 = π/4
   double dbl = integrate(
       [&](double x) {
          double h = sqrt(max(0.0, 1 - x * x));
          return integrate([&](double
                                   y) { return x * x + 0 * y; },
                           -h, h);
       },
       -1, 1);
   assert(fabs(dbl - PI / 4) < 1e-6);
   // golden
   rep(it, 2000) {
      double p = (double)(rng() % 2001) / 100 - 10,
             q = 0.1 + (double)(rng() % 100) / 10;
      double x = golden(-20, 20, [&](double x) {
         return q * (x - p) * (x - p) + fabs(x - p);
      });
      assert(fabs(x - p) < 1e-6);
   }
   // ternary_int（凸関数。最小値が複数あるものも含む）
   rep(it, 5000) {
      ll l = (ll)(rng() % 41) - 20, r = l + rng() % 40;
      ll p = (ll)(rng() % 61) - 30, w = rng() % 3,
         k = 1 + rng() % 3;
      auto f = [&](ll x) {
         return k * max(0LL, llabs(x - p) - w);
      };
      ll x = ternary_int(l, r, f), best = LLONG_MAX;
      repi(y, l, r + 1) best = min(best, f(y));
      assert(f(x) == best && l <= x && x <= r);
   }
   puts("Hello World");
}
