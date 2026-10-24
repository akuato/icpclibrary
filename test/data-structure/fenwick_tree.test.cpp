#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#undef rep
#undef sz
#define rep(i, n) for(ll i = 0; i < (n); i++)
#define repi(i, a, b) for(ll i = (a); i < (b); i++)
#define sz(a) (ll)(size(a))
using vll = vector<ll>;
#include "src/data-structure/fenwick_tree.hpp"

int main() {
   mt19937_64 rng(20261022);

   // 1) add / sum を全探索と突き合わせ（負の値も含む）
   rep(it, 3000) {
      ll n = 1 + rng() % 30;
      fenwick_tree b(n);
      vll v(n, 0);
      rep(q, 60) {
         if(rng() % 2) {
            ll i = rng() % n, x = (ll)(rng() % 41) - 20;
            v[i] += x, b.add(i, x);
         } else {
            ll l = rng() % (n + 1), r = rng() % (n + 1);
            if(l > r) swap(l, r);
            ll e = 0;
            repi(j, l, r) e += v[j];
            assert(b.sum(l, r) == e);
            assert(b.sum(r) == accumulate(v.begin(), v.begin() + r, 0LL));
         }
      }
   }

   // 2) lower_bound を全探索と突き合わせ（A[i] >= 0）
   rep(it, 5000) {
      ll n = 1 + rng() % 30;
      fenwick_tree b(n);
      vll v(n, 0);
      rep(i, n) {
         ll x = rng() % 5;
         v[i] = x, b.add(i, x);
      }
      ll tot = accumulate(all(v), 0LL);
      repi(x, -2, tot + 3) {
         ll e = n, s = 0;
         rep(i, n) {
            s += v[i];
            if(s >= x) {
               e = i;
               break;
            }
         }
         if(x <= 0) e = 0;  // 累積和 0 >= x なので先頭
         assert(b.lower_bound(x) == e);
      }
   }

   // 3) k 番目の要素を取り出す使い方（多重集合）
   rep(it, 2000) {
      ll n = 1 + rng() % 20;
      fenwick_tree b(n);
      vll cnt(n, 0);
      rep(i, 1 + rng() % 30) {
         ll v = rng() % n;
         cnt[v]++, b.add(v, 1);
      }
      vll sorted;
      rep(i, n) rep(j, cnt[i]) sorted.push_back(i);
      rep(k, sz(sorted)) assert(b.lower_bound(k + 1) == sorted[k]);
   }

   // 4) 端のケース
   {
      fenwick_tree b(1);
      assert(b.sum(0, 1) == 0);
      assert(b.lower_bound(1) == 1);  // 全部足しても届かない
      b.add(0, 5);
      assert(b.lower_bound(5) == 0);
      assert(b.lower_bound(6) == 1);
   }

   puts("Hello World");
}
