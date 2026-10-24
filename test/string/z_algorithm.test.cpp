#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "test/template.hpp"
#include "src/string/z_algorithm.hpp"

int main() {
   cin.tie(0)->sync_with_stdio(0);
   string S;
   cin >> S;
   auto z = z_algorithm(S);
   rep(i, 0, sz(S)) cout << z[i] << " \n"[i + 1 == sz(S)];
}
