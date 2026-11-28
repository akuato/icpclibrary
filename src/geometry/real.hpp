// double で使う幾何。point.hpp を using D = double にして使う
//
// halfplane(hs)    半平面の共通部分（凸多角形、反時計回り）
//   HP{a, b} は a->b の左側（境界を含む）。a != b であること
//   空・面積 0・非有界なら空を返す。非有界になりうるときは
//   十分大きい箱の4辺を足しておく
//   O(n log n)
// min_circle(p)    最小包含円 {中心, 半径}。期待 O(n)
const double EPS = 1e-9;
Pt operator*(Pt a, double k) { return {a.x * k, a.y * k}; }
double len(Pt a) { return sqrt(dot(a, a)); }

struct HP {
   Pt a, b;
   Pt d() const { return b - a; }
   bool out(Pt p) const { return cross(d(), p - a) < -EPS; }
};
Pt inter(const HP& s, const HP& t) {
   double c = cross(s.d(), t.d());
   return s.a + s.d() * (cross(t.a - s.a, t.d()) / c);
}
vector<Pt> halfplane(vector<HP> hs) {
   auto ang = [](const HP& h) {
      return atan2(h.d().y, h.d().x);
   };
   sort(all(hs), [&](const HP& s, const HP& t) {
      double x = ang(s), y = ang(t);
      if(fabs(x - y) > EPS) return x < y;
      return cross(t.d(), s.a - t.a)
             > 0;  // 同じ向きは内側を先に
   });
   deque<HP> q;
   rep(i, sz(hs)) {
      if(i && fabs(ang(hs[i]) - ang(hs[i - 1])) <= EPS)
         continue;
      HP h = hs[i];
      while(sz(q) >= 2
            && h.out(inter(q[sz(q) - 1], q[sz(q) - 2])))
         q.pop_back();
      while(sz(q) >= 2 && h.out(inter(q[0], q[1])))
         q.pop_front();
      Pt u = sz(q) ? q.back().d() : h.d(), v = h.d();
      if(sz(q) && fabs(cross(u, v)) <= EPS * len(u) * len(v)
         && dot(u, v) < 0)
         return {};  // 逆向きの平行で挟まれた
      q.push_back(h);
   }
   while(sz(q) >= 3
         && q[0].out(inter(q[sz(q) - 1], q[sz(q) - 2])))
      q.pop_back();
   while(sz(q) >= 3 && q.back().out(inter(q[0], q[1])))
      q.pop_front();
   if(sz(q) < 3) return {};
   vector<Pt> res;
   rep(i, sz(q)) res.push_back(inter(q[i], q[(i + 1) % sz(q)]));
   double s = 0;  // 空のときに1点へ潰れた形が残るので面積で弾く
   rep(i, sz(res)) s += cross(res[i], res[(i + 1) % sz(res)]);
   if(s <= EPS) return {};
   return res;
}

pair<Pt, double> min_circle(vector<Pt> p) {
   shuffle(all(p), mt19937(1));
   auto cc = [](Pt a, Pt b, Pt c) {  // 外心
      Pt u = b - a, v = c - a;
      double d = 2 * cross(u, v);
      return a
             + Pt{v.y * dot(u, u) - u.y * dot(v, v),
                  u.x * dot(v, v) - v.x * dot(u, u)}
                   * (1 / d);
   };
   Pt o = p[0];
   double r = 0;
   auto outside = [&](Pt x) {
      return len(x - o) > r * (1 + EPS) + EPS;
   };
   rep(i, sz(p)) if(outside(p[i])) {
      o = p[i], r = 0;
      rep(j, i) if(outside(p[j])) {
         o = (p[i] + p[j]) * 0.5, r = len(o - p[i]);
         rep(k, j) if(outside(p[k])) {
            o = cc(p[i], p[j], p[k]), r = len(o - p[i]);
         }
      }
   }
   return {o, r};
}
