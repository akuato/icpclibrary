// 乱数で入力を1つ出すだけ。seed は毎回変わる。stress_test.sh から使う
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
mt19937_64 rng(random_device{}());
ll rnd(ll l, ll r) { return l + rng() % (r - l + 1); }  // [l, r]
int main() {
   ll n = rnd(1, 5);  // ここから下だけ問題ごとに書く
   cout << n << "\n";
   for(ll i = 0; i < n; i++) cout << rnd(-4, 4) << " ";
}
