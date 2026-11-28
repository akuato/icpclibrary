// 数値積分と三分探索
//
// integrate(f, a, b)   ∫_a^b f(x) dx。適応 Simpson 法
//   滑らかな区間ならほぼ厳密。折れ目・不連続・特異点があると
//   取りこぼすので、その点で区間を分けて足す
//   （例: 円の面積の和は、円の左右端の x で区切る）
//   二重積分は integrate の中で integrate を呼べばよい
//   eps は絶対誤差。丸め誤差より細かくは掘らない
//
// golden(a, b, f)      [a, b] で下に凸（単峰）な f の最小点。実数
// ternary_int(l, r, f) [l, r] で下に凸な f の最小点。整数
//   平らな部分が最小値以外にあると壊れる（凸なら大丈夫）
//   最大を取りたいときは -f を渡す
template<class F>
double asr(F& f, double a, double b, double fa, double fm,
           double fb, double whole, double eps, int dep) {
   double m = (a + b) / 2, lm = (a + m) / 2, rm = (m + b) / 2;
   double flm = f(lm), frm = f(rm);
   double L = (m - a) / 6 * (fa + 4 * flm + fm);
   double R = (b - m) / 6 * (fm + 4 * frm + fb);
   double err = fabs(L + R - whole);
   double noise = 1e-13 * (b - a)
                  * (fabs(fa) + fabs(fm) + fabs(fb));
   if(dep <= 0 || err <= 15 * eps || err <= noise)
      return L + R + (L + R - whole) / 15;
   return asr(f, a, m, fa, flm, fm, L, eps / 2, dep - 1)
          + asr(f, m, b, fm, frm, fb, R, eps / 2, dep - 1);
}
template<class F>
double integrate(F f, double a, double b, double eps = 1e-10) {
   double fa = f(a), fm = f((a + b) / 2), fb = f(b);
   double w = (b - a) / 6 * (fa + 4 * fm + fb);
   return asr(f, a, b, fa, fm, fb, w, eps, 30);
}
template<class F> double golden(double a, double b, F f) {
   const double g = (sqrt(5.0) - 1) / 2;
   double x1 = b - g * (b - a), x2 = a + g * (b - a);
   double f1 = f(x1), f2 = f(x2);
   rep(it, 200) {
      if(f1 < f2) {
         b = x2, x2 = x1, f2 = f1;
         x1 = b - g * (b - a), f1 = f(x1);
      } else {
         a = x1, x1 = x2, f1 = f2;
         x2 = a + g * (b - a), f2 = f(x2);
      }
   }
   return (a + b) / 2;
}
template<class F> ll ternary_int(ll l, ll r, F f) {
   while(l < r) {
      ll m = l + (r - l) / 2;
      if(f(m) <= f(m + 1)) r = m;
      else l = m + 1;
   }
   return l;
}
