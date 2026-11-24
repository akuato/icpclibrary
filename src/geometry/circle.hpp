// 円まわり。double で持つ
//
// 半径 r の円を、中心から符号つき距離 d の直線で切ったときの
// 「直線の向こう側」の面積
//   d = 0    → 半円
//   d >= r   → 0
//   d <= -r  → 円全体
// 中心から遠ざけるほど小さくなる。d だけで決まり、直線の向きには依らない
double circle_cut(double r, double d) {
   const double PI = acos(-1.0);
   if(d >= r) return 0;
   if(d <= -r) return PI * r * r;
   return r * r * acos(d / r) - d * sqrt(r * r - d * d);
}

// 使った問題
// 2025 ICPC Asia Taichung I (Birthday)
