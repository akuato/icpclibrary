// 幾何の最小核。使ったものだけを足していく
//
//   using D = double;  -> ll に変えると整数で動く（誤差ゼロ）
//   座標が整数で与えられる / 小数の桁数が決まっている なら ll
//   円・角度・回転が出てきたら double
//
// 判断基準: 掛けた後の値が 9e15 を超えるなら double は符号を
// 間違える。座標 10^9 だと積は 10^18 で確実に壊れる

using D = double;
struct Pt {
   D x, y;
};
Pt operator-(Pt a, Pt b) { return {a.x - b.x, a.y - b.y}; }
Pt operator+(Pt a, Pt b) { return {a.x + b.x, a.y + b.y}; }

// 外積。絶対値は平行四辺形の面積、符号は向き
D cross(Pt a, Pt b) { return a.x * b.y - b.x * a.y; }
// o から見て o->a から o->b が左なら正
D cross(Pt o, Pt a, Pt b) { return cross(a - o, b - o); }

// 符号付き面積の2倍。反時計回りなら正。凸でなくてよい
D area2(vector<Pt>& p) {
   D s = 0;
   rep(i, sz(p)) s += cross(p[i], p[(i + 1) % sz(p)]);
   return s;
}

// 読み込み
//   vector<Pt> p(n);
//   rep(i, n) cin >> p[i].x >> p[i].y;
// 整数化するとき（小数6桁なら）
//   double x, y; cin >> x >> y;
//   p[i] = {(D)llround(x * 1e6), (D)llround(y * 1e6)};
//
// 使用例
//   abs(cross(o, a, b))  三角形 oab の面積の2倍
//   cross(o, a, b) == 0  3点が一直線
//   abs(area2(p))        多角形 p の面積の2倍
//
// NAIPC 2019 A (Piece of Cake) はこの cross だけで解けた
