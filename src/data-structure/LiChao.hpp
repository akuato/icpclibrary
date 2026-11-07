// 直線 ax+b を足して、x での最小値を返す
// 最大値が欲しいときは LiChao<false>
//
// 要件
//   傾きの単調性は不要
//   query する x の候補を昇順・重複なしで、構築時に全部渡す
//
// 使い方
//   vll xs = {...};        昇順・重複なし
//   sort(all(xs));
//   xs.erase(unique(all(xs)), xs.end());
//   LiChao<true> c(xs);
//   c.add(a, b);           直線 ax+b を足す
//   c.query(x);            x は xs の値（assert で確認）
//
// add も query も O(log n)
// 傾きが単調なら cht / cht_monotone の方が軽い
template<bool isMin = true> struct LiChao {
   vll xs;
   vp t;
   LiChao(vll xs) : xs(xs), t(4 * sz(xs), P(0, inf)) {}
   ll f(P l, ll x) { return l.first * x + l.second; }
   void add(ll a, ll b) {
      if(!isMin) a = -a, b = -b;
      P l(a, b);
      int k = 1, lo = 0, hi = sz(xs) - 1;
      while(1) {
         int m = (lo + hi) / 2;
         bool bl = f(l, xs[lo]) < f(t[k], xs[lo]);
         bool bm = f(l, xs[m]) < f(t[k], xs[m]);
         if(bm) swap(t[k], l);
         if(lo == hi) return;
         if(bl != bm) hi = m, k = 2 * k;
         else lo = m + 1, k = 2 * k + 1;
      }
   }
   ll query(ll x) {  // x は xs に含まれる値
      int k = 1, lo = 0, hi = sz(xs) - 1;
      ll res = inf;
      while(1) {
         chmin(res, f(t[k], x));
         if(lo == hi) {
            assert(xs[lo] == x);  // x は xs に無いと答えが狂う
            return isMin ? res : -res;
         }
         int m = (lo + hi) / 2;
         if(x <= xs[m]) hi = m, k = 2 * k;
         else lo = m + 1, k = 2 * k + 1;
      }
   }
};
