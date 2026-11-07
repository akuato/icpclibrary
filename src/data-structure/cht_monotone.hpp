// 直線 ax+b を足して、ある x での最小値を返す
// 最大値が欲しいときは CHTMonotone<false>
//
// 要件
//   add する傾き a は減少のみ（最大版 <false> なら増加のみ）
//   query の x も単調。増加なら qinc、減少なら qdec
//   qinc と qdec は混ぜない
//
// 傾きが逆向きのときは x を反転すれば同じことになる
//   a*x + b = (-a)*(-x) + b   なので傾きと x が同時に反転する
//   最小版での対応（最大版は「減少」と「増加」を入れ替え）
//     傾き減少 x増加 -> add(a, b)   qinc(x)
//     傾き減少 x減少 -> add(a, b)   qdec(x)
//     傾き増加 x減少 -> add(-a, b)  qinc(-x)
//     傾き増加 x増加 -> add(-a, b)  qdec(-x)
//
// 使い方
//   CHTMonotone<true> c;
//   c.add(a, b);   直線 ax+b を足す
//   c.qinc(x);     x が増えていくとき
//   c.qdec(x);     x が減っていくとき
//   1本も無ければ inf（最大版は -inf）
//
// add も query も償却 O(1)
// vector なので空なら確保ゼロ。10^5 個以上並べて持てる
// qinc は捨てた直線のメモリが戻らない（使用量は足した総数）
template<bool isMin = true> struct CHTMonotone {
   vp d;
   int h = 0;  // 生きている先頭
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
      if(sz(d) > h && d.back().first == a) {
         if(d.back().second <= b) return;
         d.pop_back();
      }
      while(sz(d) - h >= 2
            && bad(d[sz(d) - 2], d[sz(d) - 1], l))
         d.pop_back();
      d.push_back(l);
   }
   ll qinc(ll x) {  // x が増えていくとき
      if(h >= sz(d)) return isMin ? inf : -inf;
      while(sz(d) - h >= 2 && val(d[h], x) >= val(d[h + 1], x))
         h++;
      return isMin ? val(d[h], x) : -val(d[h], x);
   }
   ll qdec(ll x) {  // x が減っていくとき
      if(h >= sz(d)) return isMin ? inf : -inf;
      while(sz(d) - h >= 2
            && val(d[sz(d) - 1], x) >= val(d[sz(d) - 2], x))
         d.pop_back();
      ll v = val(d[sz(d) - 1], x);
      return isMin ? v : -v;
   }
};
