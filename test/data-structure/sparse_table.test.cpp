#define PROBLEM                              \
   "https://judge.u-aizu.ac.jp/onlinejudge/" \
   "description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#undef rep
#undef sz
#define rep(i, n) for(ll i = 0; i < (n); i++)
#define repi(i, a, b) for(ll i = (a); i < (b); i++)
#define sz(a) (ll)(size(a))
#include "src/data-structure/sparse_table.hpp"

int main() {
   mt19937_64 rng(20261127);
   rep(it, 3000) {
      ll n = 1 + rng() % 40;
      vector<ll> a(n);
      for(auto& x : a) x = (ll)(rng() % 2001) - 1000;
      SparseTable mn(a, [](ll x, ll y) { return min(x, y); });
      SparseTable mx(a, [](ll x, ll y) { return max(x, y); });
      SparseTable g(a, [](ll x, ll y) { return gcd(x, y); });
      rep(l, n) repi(r, l + 1, n + 1) {
         ll e1 = LLONG_MAX, e2 = LLONG_MIN, e3 = 0;
         repi(i, l, r) e1 = min(e1, a[i]), e2 = max(e2, a[i]),
                       e3 = gcd(e3, a[i]);
         assert(mn.prod(l, r) == e1);
         assert(mx.prod(l, r) == e2);
         assert(g.prod(l, r) == e3);
      }
   }
   puts("Hello World");
}
