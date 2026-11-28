#define PROBLEM                              \
   "https://judge.u-aizu.ac.jp/onlinejudge/" \
   "description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#undef rep
#undef sz
#define rep(i, n) for(ll i = 0; i < (n); i++)
#define repi(i, a, b) for(ll i = (a); i < (b); i++)
#define sz(a) (ll)(size(a))
#include "src/modint/modint.hpp"
#include "src/math/gauss.hpp"

using Mat = vector<vector<mint>>;
mt19937_64 rng(20261127);
Mat rnd(int h, int w,
        int range) {  // 小さい値にしてランク落ちを起こしやすく
   Mat a(h, vector<mint>(w));
   for(auto& r : a)
      for(auto& x : r) x = rng() % range;
   return a;
}
vector<mint> mul(const Mat& a, const vector<mint>& x) {
   vector<mint> y(sz(a));
   rep(i, sz(a)) rep(j, sz(x)) y[i] += a[i][j] * x[j];
   return y;
}
bool eq(const vector<mint>& a, const vector<mint>& b) {
   rep(i, sz(a)) if(a[i].x != b[i].x) return false;
   return true;
}
// 置換の和で行列式を計算（n <= 6）
mint det_brute(const Mat& a) {
   int n = sz(a);
   vector<int> p(n);
   iota(all(p), 0);
   mint s = 0;
   do {
      mint t = 1;
      int inv = 0;
      rep(i, n) rep(j, i) if(p[j] > p[i]) inv++;
      rep(i, n) t *= a[i][p[i]];
      s += inv % 2 ? mint(0) - t : t;
   } while(next_permutation(all(p)));
   return s;
}
int main() {
   // det（mod）
   rep(it, 3000) {
      int n = 1 + rng() % 6;
      Mat a = rnd(n, n, 1 + rng() % 4);
      assert(det(a).x == det_brute(a).x);
   }
   // solve_linear（mod）: 解が a x = b を満たす、基底が a v = 0 を満たし独立
   rep(it, 3000) {
      int h = 1 + rng() % 5, w = 1 + rng() % 5;
      Mat a = rnd(h, w, 1 + rng() % 3);
      vector<mint> x0(w);
      for(auto& v : x0) v = rng() % 3;
      vector<mint> b = rng() % 3 ? mul(a, x0) : rnd(1, h, 3)[0];
      Mat basis;
      auto x = solve_linear(a, b, &basis);
      // 解の有無を全探索で（値 0..2 の範囲では探しきれないので、ランクで判定）
      Mat ab = a;
      rep(i, h) ab[i].push_back(b[i]);
      Mat aa = a;
      bool solvable = gauss(aa, w) == gauss(ab, w + 1);
      assert(solvable == !x.empty());
      if(x.empty()) continue;
      assert(eq(mul(a, x), b));
      Mat a2 = a;
      int rk = gauss(a2, w);
      assert(sz(basis) == w - rk);
      for(auto& v : basis)
         assert(eq(mul(a, v), vector<mint>(h)));
      if(sz(basis)) {
         Mat B = basis;
         assert(gauss(B, w) == sz(basis));
      }
   }
   // inverse（mod）
   rep(it, 2000) {
      int n = 1 + rng() % 5;
      Mat a = rnd(n, n, 1 + rng() % 3), b = a;
      bool ok = inverse(b);
      assert(ok == (det(a).x != 0));
      if(!ok) continue;
      rep(i, n) rep(j, n) {
         mint s = 0;
         rep(k, n) s += a[i][k] * b[k][j];
         assert(s.x == (i == j));
      }
   }
   // double
   rep(it, 2000) {
      int n = 1 + rng() % 6;
      vector<vector<double>> a(n, vector<double>(n));
      for(auto& r : a)
         for(auto& x : r) x = (double)(rng() % 2001) / 100 - 10;
      vector<double> x0(n), b(n);
      for(auto& v : x0) v = (double)(rng() % 201) / 10 - 10;
      rep(i, n) rep(j, n) b[i] += a[i][j] * x0[j];
      auto x = solve_linear(a, b);
      if(fabs(det(a)) < 1e-3) continue;
      assert(!x.empty());
      rep(i, n) assert(fabs(x[i] - x0[i]) < 1e-6);
      auto inv = a;
      assert(inverse(inv));
      rep(i, n) rep(j, n) {
         double s = 0;
         rep(k, n) s += a[i][k] * inv[k][j];
         assert(fabs(s - (i == j)) < 1e-6);
      }
   }
   puts("Hello World");
}
