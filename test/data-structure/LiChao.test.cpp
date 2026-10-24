#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
// src/template/template.hpp 側のマクロ・型に合わせる
#undef rep
#undef sz
#define rep(i, n) for(ll i = 0; i < (n); i++)
#define repi(i, a, b) for(ll i = (a); i < (b); i++)
#define sz(a) (ll)(size(a))
using P = pair<ll, ll>;
using vp = vector<P>;
using vll = vector<ll>;
const ll inf = 2e18;
#include "src/data-structure/LiChao.hpp"

int main() {
   mt19937_64 rng(20261022);

   // 1) 追加とクエリを任意の順で混ぜて、全探索と一致（小さい値域）
   rep(it, 20000) {
      vll xs;
      repi(x, -20, 21) xs.push_back(x);
      LiChao lc(xs);
      vp ls;
      rep(q, 1 + rng() % 12) {
         if(ls.empty() || rng() % 2) {
            ll a = (ll)(rng() % 21) - 10, b = (ll)(rng() % 21) - 10;
            ls.push_back(P(a, b)), lc.add(a, b);
         } else {
            ll x = xs[rng() % sz(xs)], e = inf;
            for(P l : ls) chmin(e, l.first * x + l.second);
            assert(lc.query(x) == e);
         }
      }
   }

   // 2) |a|, |b|, |x| <= 1e9（オーバーフロー確認）
   rep(it, 2000) {
      vll xs;
      rep(i, 40) xs.push_back((ll)(rng() % 2000000001) - 1000000000);
      sort(all(xs)), xs.erase(unique(all(xs)), xs.end());
      LiChao lc(xs);
      vp ls;
      rep(q, 30) {
         if(ls.empty() || rng() % 2) {
            ll a = (ll)(rng() % 2000000001) - 1000000000, b = (ll)(rng() % 2000000001) - 1000000000;
            ls.push_back(P(a, b)), lc.add(a, b);
         } else {
            ll x = xs[rng() % sz(xs)], e = inf;
            for(P l : ls) chmin(e, l.first * x + l.second);
            assert(lc.query(x) == e);
         }
      }
   }

   // 3) 直線 0 本 / 候補 x が 1 点だけ
   {
      vll xs = {5};
      LiChao lc(xs);
      assert(lc.query(5) == inf);
      lc.add(2, 3);
      assert(lc.query(5) == 13);
   }

   // 4) 最大値は (-a, -b) を入れて符号反転
   rep(it, 3000) {
      vll xs;
      repi(x, -15, 16) xs.push_back(x);
      LiChao lc(xs);
      vp ls;
      rep(q, 1 + rng() % 8) {
         ll a = (ll)(rng() % 21) - 10, b = (ll)(rng() % 21) - 10;
         ls.push_back(P(a, b)), lc.add(-a, -b);
      }
      for(ll x : xs) {
         ll e = -inf;
         for(P l : ls) chmax(e, l.first * x + l.second);
         assert(-lc.query(x) == e);
      }
   }

   puts("Hello World");
}
