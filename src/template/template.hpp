// https://github.com/akuato/icpclibrary
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i <(n); i++)
#define repi(i, a, b) for(ll i = (a); i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define arr(x) (x).rbegin(), (x).rend()
template<typename T, typename S> bool chmin(T& a, const S& b) { return a > b ? a = b, 1 : 0; }
template<typename T, typename S> bool chmax(T& a, const S& b) { return a < b ? a = b, 1 : 0; }
using vi = vector<int>;
using P = pair<ll, ll>;
using vvi = vector<vi>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vp = vector<P>;
using i128 = __int128_t;
#define sz(a) (ll)(size(a))
const ll inf = 2e18;

void solve(int test) {}
int main() {
   cin.tie(0);
   ios::sync_with_stdio(false);
   int t = 1;  // cin >>t;
   rep(test, t) solve(test);
}
