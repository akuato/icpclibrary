// Sparse Table。静的な配列の区間クエリを O(1) で返す
// 演算は冪等（f(x, x) = x）で結合的なもの: min, max, gcd, and, or
// 和や xor は区間が重なるので不可。更新もできない
//
// 使い方
//   SparseTable st(a, [](ll x, ll y) { return min(x, y); });
//   st.prod(l, r)   [l, r) の結果。l < r であること
//
// 構築 O(n log n)、メモリ n log n
template<class T, class F> struct SparseTable {
   vector<vector<T>> d;
   F f;
   SparseTable(const vector<T>& a, F f) : d(1, a), f(f) {
      for(int k = 1; (1 << k) <= sz(a); k++) {
         d.emplace_back(sz(a) - (1 << k) + 1);
         rep(i, sz(d[k]))
             d[k][i] = f(d[k - 1][i],
                         d[k - 1][i + (1 << (k - 1))]);
      }
   }
   T prod(int l, int r) {
      int k = __lg(r - l);
      return f(d[k][l], d[k][r - (1 << k)]);
   }
};
