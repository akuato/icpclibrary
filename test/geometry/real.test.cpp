#define PROBLEM                              \
   "https://judge.u-aizu.ac.jp/onlinejudge/" \
   "description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#undef rep
#undef sz
#define rep(i, n) for(ll i = 0; i < (n); i++)
#define repi(i, a, b) for(ll i = (a); i < (b); i++)
#define sz(a) (ll)(size(a))
// point.hpp は D = ll なので、double 版の最小部分をここに書く
using D = double;
struct Pt {
   D x, y;
};
Pt operator-(Pt a, Pt b) { return {a.x - b.x, a.y - b.y}; }
Pt operator+(Pt a, Pt b) { return {a.x + b.x, a.y + b.y}; }
bool operator==(Pt a, Pt b) { return a.x == b.x && a.y == b.y; }
D cross(Pt a, Pt b) { return a.x * b.y - b.x * a.y; }
D dot(Pt a, Pt b) { return a.x * b.x + a.y * b.y; }
#include "src/geometry/real.hpp"

mt19937_64 rng(20261127);
double rd(int r) {
   return (double)((ll)(rng() % (2 * r + 1)) - r);
}
double area(const vector<Pt>& p) {
   double s = 0;
   rep(i, sz(p)) s += cross(p[i], p[(i + 1) % sz(p)]);
   return s / 2;
}
// 凸多角形を半平面で切る（全探索用）
vector<Pt> cut(const vector<Pt>& p, const HP& h) {
   vector<Pt> r;
   rep(i, sz(p)) {
      Pt a = p[i], b = p[(i + 1) % sz(p)];
      double ca = cross(h.d(), a - h.a),
             cb = cross(h.d(), b - h.a);
      if(ca >= 0) r.push_back(a);
      if(ca * cb < 0)
         r.push_back(a + (b - a) * (ca / (ca - cb)));
   }
   return r;
}
int main() {
   // halfplane: 箱 + ランダムな半平面。面積と頂点の内包を全探索の切断と比べる
   rep(it, 20000) {
      double B = 100;
      vector<HP> hs = {{{-B, -B}, {B, -B}},
                       {{B, -B}, {B, B}},
                       {{B, B}, {-B, B}},
                       {{-B, B}, {-B, -B}}};
      int n = rng() % 8;
      rep(i, n) {
         Pt a{rd(10), rd(10)}, b{rd(10), rd(10)};
         if(a == b) continue;
         hs.push_back({a, b});
         if(rng() % 4 == 0) hs.push_back({a, b});  // 重複
         if(rng() % 4 == 0) {
            HP h{b + Pt{rd(2), rd(2)}, a + Pt{rd(2), rd(2)}};
            if(!(h.a == h.b)) hs.push_back(h);
         }
      }
      vector<Pt> poly = {{-B, -B}, {B, -B}, {B, B}, {-B, B}};
      for(auto& h : hs) poly = cut(poly, h);
      double e = sz(poly) >= 3 ? area(poly) : 0;
      vector<Pt> res = halfplane(hs);
      double g = sz(res) >= 3 ? area(res) : 0;
      if(fabs(e - g) > 1e-6) {
         printf("NG e=%.9f g=%.9f n=%d\n", e, g, (int)sz(hs));
         for(auto& h : hs)
            printf("  (%g,%g)->(%g,%g)\n", h.a.x, h.a.y, h.b.x,
                   h.b.y);
         return 1;
      }
      for(auto& p : res)
         for(auto& h : hs)
            assert(cross(h.d(), p - h.a) > -1e-6 * len(h.d()));
   }
   // min_circle: 全探索（2点・3点で作る円のうち全点を含む最小）
   rep(it, 3000) {
      int n = 1 + rng() % 12;
      vector<Pt> p(n);
      for(auto& q : p) q = {rd(20), rd(20)};
      if(rng() % 3 == 0)
         for(auto& q : p) q = {q.x, 2 * q.x + 1};  // 一直線
      auto [o, r] = min_circle(p);
      for(auto& q : p) assert(len(q - o) <= r + 1e-6);
      double best = 1e18;
      auto test = [&](Pt c) {
         double rr = 0;
         for(auto& q : p) rr = max(rr, len(q - c));
         best = min(best, rr);
      };
      rep(i, n) rep(j, n) test((p[i] + p[j]) * 0.5);
      rep(i, n) rep(j, i) rep(k, j) {
         Pt u = p[j] - p[i], v = p[k] - p[i];
         double d = 2 * cross(u, v);
         if(fabs(d) < 1e-9) continue;
         test(p[i]
              + Pt{v.y * dot(u, u) - u.y * dot(v, v),
                   u.x * dot(v, v) - v.x * dot(u, u)}
                    * (1 / d));
      }
      assert(fabs(best - r) < 1e-6);
   }
   puts("Hello World");
}
