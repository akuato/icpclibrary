// https://github.com/akuato/icpclibrary
#include <bits/stdc++.h>
#include <cassert>  // 環境によっては bits/stdc++.h に入っていない
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (n); i++)
#define repi(i, a, b) for(ll i = (a); i < (b); i++)
#define all(a) (a).begin(), (a).end()
#define arr(a) (a).rbegin(), (a).rend()
#define sz(a) (ll)(size(a))
template<typename T, typename S> bool chmin(T& a, const S& b) {
   return a > b ? a = b, 1 : 0;
}
template<typename T, typename S> bool chmax(T& a, const S& b) {
   return a < b ? a = b, 1 : 0;
}
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<ll, ll>;
using vp = vector<P>;
using i128 = __int128_t;
const ll inf = 2e18;

void solve(int test) {}
int main() {
   cin.tie(0);
   ios::sync_with_stdio(false);
   int t = 1;  // cin >>t;
   rep(test, t) solve(test);
}
