struct LiChao {
   vll xs;
   vp t;
   LiChao(vll xs) : xs(xs), t(4 * sz(xs), P(0, inf)) {}
   ll f(P l, ll x) { return l.first * x + l.second; }
   void add(ll a, ll b) {
      P l(a, b);
      int k = 1, lo = 0, hi = sz(xs) - 1;
      while(1) {
         int m = (lo + hi) / 2;
         bool bl = f(l, xs[lo]) < f(t[k], xs[lo]), bm = f(l, xs[m]) < f(t[k], xs[m]);
         if(bm) swap(t[k], l);
         if(lo == hi) return;
         if(bl != bm) hi = m, k = 2 * k;
         else lo = m + 1, k = 2 * k + 1;
      }
   }
   ll query(ll x) {
      int k = 1, lo = 0, hi = sz(xs) - 1;
      ll res = inf;
      while(1) {
         chmin(res, f(t[k], x));
         if(lo == hi) return res;
         int m = (lo + hi) / 2;
         if(x <= xs[m]) hi = m, k = 2 * k;
         else lo = m + 1, k = 2 * k + 1;
      }
   }
};
