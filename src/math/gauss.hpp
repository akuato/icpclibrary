// ガウスの消去法。T は double か mint（modint.hpp）
//   gauss(a, w)          a を既約階段形にする。先頭 w 列だけ見る。ランクを返す
//   det(a)               行列式。O(n^3)
//   solve_linear(a, b)   a x = b の解を1つ。無ければ空。basis に解空間の基底
//   inverse(a)           a を逆行列に置き換える。正則でなければ false
//
// double のときは絶対値最大の行を軸に選ぶ（誤差対策）。EPS は値の大きさに合わせる
// mint の 0 判定は .x で見ている
const double GAUSS_EPS = 1e-9;
template<class T> bool is0(const T& x) {
   if constexpr(is_floating_point_v<T>)
      return fabs(x) < GAUSS_EPS;
   else return x.x == 0;
}
// 行 r 以降で列 c の軸に使う行。無ければ -1
template<class T>
int piv_row(vector<vector<T>>& a, int r, int c) {
   int p = -1;
   repi(i, r, sz(a)) if(!is0(a[i][c])) {
      if(p < 0) p = i;
      if constexpr(is_floating_point_v<T>)
         if(fabs(a[i][c]) > fabs(a[p][c])) p = i;
   }
   return p;
}
template<class T> int gauss(vector<vector<T>>& a, int w) {
   int h = sz(a), r = 0;
   rep(c, w) {
      if(r == h) break;
      int p = piv_row(a, r, c);
      if(p < 0) continue;
      swap(a[r], a[p]);
      T iv = T(1) / a[r][c];
      for(auto& x : a[r]) x *= iv;
      rep(i, h) if(i != r && !is0(a[i][c])) {
         T t = a[i][c];
         rep(j, sz(a[i])) a[i][j] -= t * a[r][j];
      }
      r++;
   }
   return r;
}
template<class T> T det(vector<vector<T>> a) {
   int n = sz(a);
   T res = 1;
   rep(c, n) {
      int p = piv_row(a, c, c);
      if(p < 0) return 0;
      if(p != c) swap(a[p], a[c]), res = -res;
      res *= a[c][c];
      T iv = T(1) / a[c][c];
      repi(i, c + 1, n) {
         T t = a[i][c] * iv;
         repi(j, c, n) a[i][j] -= t * a[c][j];
      }
   }
   return res;
}
template<class T>
vector<T> solve_linear(vector<vector<T>> a, vector<T> b,
                       vector<vector<T>>* basis = nullptr) {
   int h = sz(a), w = sz(a[0]);
   rep(i, h) a[i].push_back(b[i]);
   int r = gauss(a, w);
   repi(i, r, h) if(!is0(a[i][w])) return {};  // 矛盾
   vector<T> x(w, 0);
   vector<int> col(r), piv(w, -1);
   rep(i, r) {
      int c = 0;
      while(is0(a[i][c])) c++;
      col[i] = c, piv[c] = i, x[c] = a[i][w];
   }
   if(basis) {
      basis->clear();
      rep(f, w) if(piv[f] < 0) {
         vector<T> v(w, 0);
         v[f] = 1;
         rep(i, r) v[col[i]] = T(0) - a[i][f];
         basis->push_back(v);
      }
   }
   return x;
}
template<class T> bool inverse(vector<vector<T>>& a) {
   int n = sz(a);
   rep(i, n) {
      a[i].resize(2 * n, 0);
      a[i][n + i] = 1;
   }
   if(gauss(a, n) < n) return false;
   rep(i, n) a[i].erase(a[i].begin(), a[i].begin() + n);
   return true;
}
