#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "test/template.hpp"
#include "src/string/rolling_hash.hpp"

int main() {
   cin.tie(0)->sync_with_stdio(0);
   string S;
   cin >> S;
   RH rh(S);
   const ll N = sz(S);
   auto LCP = [&](ll i, ll j) {
      ll ok = 0, ng = N + 1 - j;
      while(ng - ok > 1) {
         const ll mid = (ok + ng) / 2;
         (rh.get(i, i + mid) == rh.get(j, j + mid) ? ok : ng) = mid;
      }
      return ok;
   };
   rep(i, 0, N) cout << LCP(0, i) << " \n"[i + 1 == N];
}
