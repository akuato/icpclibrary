#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "test/template.hpp"
#define repi(i, a, b) for(ll i = (a); i < (b); i++)
#include "src/string/suffix_array.hpp"

int main() {
   cin.tie(0)->sync_with_stdio(0);
   string S;
   cin >> S;
   const ll N = sz(S);
   auto [sa, lcp] = SA(S);
   rep(i, 0, N) cout << sa[i] << " \n"[i + 1 == N];
}
