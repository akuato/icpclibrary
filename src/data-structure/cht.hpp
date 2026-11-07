// 直線 ax+b を足して、任意の x での最小値を返す
// 最大値が欲しいときは CHT<false>
//
// 要件
//   add する傾き a は減少のみ（最大版 <false> なら増加のみ）
//   query の x は任意の順でよい
//
// 傾きが逆向きのときは x を反転する
//   a*x + b = (-a)*(-x) + b
//   傾き増加なら add(-a, b) として query(-x) を呼ぶ
//
// 使い方
//   CHT<true> c;
//   c.add(a, b);    直線 ax+b を足す
//   c.query(x);     最小値。1本も無ければ inf（最大版は -inf）
//
// add 償却 O(1)、query O(log n)
// x も単調なら cht_monotone（query も O(1)）
template<bool isMin = true> struct CHT {
   vp d;
   bool bad(P x, P y, P z) {
      return (i128)(z.second - x.second) * (x.first - y.first)
             <= (i128)(y.second - x.second)
                    * (x.first - z.first);
   }
   ll val(P l, ll x) { return l.first * x + l.second; }
   void add(ll a, ll b) {
      if(!isMin) a = -a, b = -b;
      if(!d.empty()) assert(a <= d.back().first);
      P l(a, b);
      if(!d.empty() && d.back().first == a) {
         if(d.back().second <= b) return;
         d.pop_back();
      }
      while(sz(d) >= 2 && bad(d[sz(d) - 2], d[sz(d) - 1], l))
         d.pop_back();
      d.push_back(l);
   }
   ll query(ll x) {
      if(d.empty()) return isMin ? inf : -inf;
      int lo = 0, hi = sz(d) - 1;
      while(lo < hi) {
         int m = (lo + hi) / 2;
         if(val(d[m], x) >= val(d[m + 1], x)) lo = m + 1;
         else hi = m;
      }
      return isMin ? val(d[lo], x) : -val(d[lo], x);
   }
};
