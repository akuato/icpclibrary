// 直線 ax+b を足して、x での最小値を返す
// 最大値が欲しいときは LiChaoDyn<false>
//
// 要件
//   傾きの単調性は不要。x の候補も事前に要らない
//   x のとりうる範囲 [lo, hi]（両端含む）だけ指定する
//
// 使い方
//   LiChaoDyn<true> c(-1000000000, 1000000000);
//   c.add(a, b);    直線 ax+b を足す
//   c.query(x);     最小値。1本も無ければ inf（最大版は -inf）
//
// add も query も O(log(hi-lo))
// ノードは必要な分だけ作る。1ノード 24 バイト
// 最悪 O(n log(hi-lo)) だが経路が重なるので実際は遥かに少ない
// 範囲 2*10^9 に 20 万本足して数千ノード（0.1 MB）だった
template<bool isMin = true> struct LiChaoDyn {
   vp t;
   vi lc, rc;
   ll L, R;
   LiChaoDyn(ll L, ll R) : L(L), R(R) { nw(); }
   int nw() {
      t.push_back(P(0, inf));
      lc.push_back(-1);
      rc.push_back(-1);
      return sz(t) - 1;
   }
   ll f(P l, ll x) { return l.first * x + l.second; }
   void add(ll a, ll b) {
      if(!isMin) a = -a, b = -b;
      P l(a, b);
      int k = 0;
      ll lo = L, hi = R;
      while(1) {
         ll m = lo + (hi - lo) / 2;
         bool bl = f(l, lo) < f(t[k], lo);
         bool bm = f(l, m) < f(t[k], m);
         if(bm) swap(t[k], l);
         if(lo == hi) return;
         if(bl != bm) {
            if(lc[k] < 0) lc[k] = nw();
            k = lc[k], hi = m;
         } else {
            if(rc[k] < 0) rc[k] = nw();
            k = rc[k], lo = m + 1;
         }
      }
   }
   ll query(ll x) {
      assert(L <= x && x <= R);
      int k = 0;
      ll lo = L, hi = R, res = inf;
      while(k >= 0) {
         chmin(res, f(t[k], x));
         if(lo == hi) break;
         ll m = lo + (hi - lo) / 2;
         if(x <= m) k = lc[k], hi = m;
         else k = rc[k], lo = m + 1;
      }
      return isMin ? res : -res;
   }
};
