// 凸包（Andrew's monotone chain）。反時計回りに返す
// point.hpp が必要（Pt, cross, D）
//
// 一直線上に並んだ点は落とす（<= 0）。残したいときは < 0 にする
// 点が 0〜2 個のときは、重複を除いたものをそのまま返す
//
// 使いどころ:
//   「ある向きで一番外にいる点」しか効かない最適化 → 候補は凸包の頂点だけ
//   原点が凸包の内部か ⇔ 原点を通る直線で全点を片側に寄せられない
vector<Pt> convex_hull(vector<Pt> p) {
   sort(all(p), [](Pt a, Pt b) {
      return a.x != b.x ? a.x < b.x : a.y < b.y;
   });
   p.erase(unique(all(p)), p.end());
   ll n = sz(p);
   if(n <= 2) return p;
   vector<Pt> h(2 * n);
   ll k = 0;
   rep(i, n) {
      while(k >= 2 && cross(h[k - 2], h[k - 1], p[i]) <= 0) k--;
      h[k++] = p[i];
   }
   for(ll i = n - 2, t = k + 1; i >= 0; i--) {
      while(k >= t && cross(h[k - 2], h[k - 1], p[i]) <= 0) k--;
      h[k++] = p[i];
   }
   h.resize(k - 1);
   return h;
}

// 使った問題
// 2025 ICPC Asia Taichung I (Birthday)
//   原点が凸包の内部に無ければ中心を通る直線で切れる。
//   内部にあるときは、凸包の各線分と原点の距離の最小値が切り口の距離になる
