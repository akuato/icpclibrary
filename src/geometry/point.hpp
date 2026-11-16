// 幾何の最小核。整数で持つのが既定（誤差ゼロ）
//
//   using D = ll;      座標が整数 / 小数の桁数が決まっている
//   using D = double;  円・角度・回転が出てきたとき
//
// 判断基準: 掛けた後の値が 9e15 を超えると double は符号を間違える。
// 座標 1e9 だと積は 1e18 で確実に壊れる。整数なら壊れない
//
// 以下の整数版は座標 1e4 程度まで安全（cross^2 が 6e17）。
// それより大きいときは D を __int128 にする

using D = ll;
struct Pt {
   D x, y;
};
Pt operator-(Pt a, Pt b) { return {a.x - b.x, a.y - b.y}; }
Pt operator+(Pt a, Pt b) { return {a.x + b.x, a.y + b.y}; }
bool operator==(Pt a, Pt b) { return a.x == b.x && a.y == b.y; }

// 外積。絶対値は平行四辺形の面積、符号は向き
D cross(Pt a, Pt b) { return a.x * b.y - b.x * a.y; }
// o から見て o->a より o->b が左なら正
D cross(Pt o, Pt a, Pt b) { return cross(a - o, b - o); }
D dot(Pt a, Pt b) { return a.x * b.x + a.y * b.y; }
D dot(Pt o, Pt a, Pt b) { return dot(a - o, b - o); }
D dist2(Pt a, Pt b) { return dot(b - a, b - a); }  // 距離の2乗

// a->b に対する c の位置
//   1 左 / -1 右 / 2 c-a-b の順 / -2 a-b-c の順 / 0 a-c-b の順
int ccw(Pt a, Pt b, Pt c) {
   D z = cross(a, b, c);
   if(z > 0) return 1;
   if(z < 0) return -1;
   if(dot(a, b, c) < 0) return 2;
   if(dist2(a, b) < dist2(a, c)) return -2;
   return 0;
}
bool on_seg(Pt a, Pt b, Pt p) { return ccw(a, b, p) == 0; }

// 点 p と線分 ab の距離が d 以下か。整数のまま厳密に判定する。
// sqrt を通さないので「ちょうど d」も正しく拾える
bool seg_dist_le(Pt a, Pt b, Pt p, D d) {
   if(a == b) return dist2(a, p) <= d * d;
   if(dot(a, b, p) >= 0
      && dot(b, a, p) >= 0) {  // 垂線の足が内側
      D c = cross(a, b, p);
      return c * c <= d * d * dist2(a, b);
   }
   return min(dist2(a, p), dist2(b, p)) <= d * d;
}

// 値が要るとき。こちらは誤差が出る
double seg_dist(Pt a, Pt b, Pt p) {
   if(!(a == b) && dot(a, b, p) >= 0 && dot(b, a, p) >= 0)
      return abs((double)cross(a, b, p))
             / sqrt((double)dist2(a, b));
   return sqrt((double)min(dist2(a, p), dist2(b, p)));
}

// 多角形と点。0 外 / 1 辺上 / 2 内。凸でなくてよい。頂点を通る
// 場合も y の半開区間で処理されるので場合分けは要らない
int contains(vector<Pt>& q, Pt p) {
   bool in = false;
   rep(i, sz(q)) {
      Pt a = q[i] - p, b = q[(i + 1) % sz(q)] - p;
      if(cross(a, b) == 0 && dot(a, b) <= 0) return 1;
      if(a.y > b.y) swap(a, b);
      if(a.y <= 0 && 0 < b.y && cross(a, b) < 0) in = !in;
   }
   return in ? 2 : 0;
}

// 符号付き面積の2倍。反時計回りなら正。凸でなくてよい
D area2(vector<Pt>& p) {
   D s = 0;
   rep(i, sz(p)) s += cross(p[i], p[(i + 1) % sz(p)]);
   return s;
}

// 使った問題
//   NAIPC 2019 A   cross だけ
//   Seoul 2026 E   contains, seg_dist_le
