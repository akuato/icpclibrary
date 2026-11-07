// 整数キーのハッシュマップ
// unordered_map より速く、狙い撃ちもされない
//
// 要件
//   キーは 64bit 整数なら何でもよい。値は型引数 V
//   削除は無い（線形探索なので消すと穴が空く）
//
// 使い方
//   HashMap<int> m;        // 値が int
//   m[key] += 1;           // 無ければ V() で作られる
//   if(m.count(key)) ...
//   V* p = m.find(key);    // 無ければ nullptr
//   m.len()                // 個数。sz マクロと衝突するので
//                          // size ではなく len
//   HashMap<int> m(1 << 20);   // 入る個数が分かるなら先に確保
//
// 容量が半分埋まると倍に広げる。償却 O(1)
// シードが実行ごとに変わるので O(n^2) に落とされない
// 素の unordered_map は 17 万キーの insert が 36 秒になる
using ull = unsigned long long;
template<class V> struct HashMap {
   vector<ull> k;
   vector<V> v;
   vector<char> u;
   ll n = 0;
   ull msk;
   static inline ull R = chrono::steady_clock::now()
                             .time_since_epoch()
                             .count();
   HashMap(ll cap = 16) {
      ll s = 1;
      while(s < cap * 2) s <<= 1;
      k.assign(s, 0), v.assign(s, V()), u.assign(s, 0);
      msk = s - 1;
   }
   static ull h(ull x) {
      x += R;
      x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
      x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
      return x ^ (x >> 31);
   }
   ll pos(ull key) const {
      ull i = h(key) & msk;
      while(u[i] && k[i] != key) i = (i + 1) & msk;
      return i;
   }
   void grow() {
      vector<ull> ok = k;
      vector<V> ov = v;
      vector<char> ou = u;
      ll s = sz(k) * 2;
      k.assign(s, 0), v.assign(s, V()), u.assign(s, 0);
      msk = s - 1;
      rep(i, sz(ok)) if(ou[i]) {
         ll j = pos(ok[i]);
         u[j] = 1, k[j] = ok[i], v[j] = ov[i];
      }
   }
   V& operator[](ull key) {
      if(n * 2 >= sz(k)) grow();
      ll i = pos(key);
      if(!u[i]) u[i] = 1, k[i] = key, n++;
      return v[i];
   }
   V* find(ull key) {
      ll i = pos(key);
      return u[i] ? &v[i] : nullptr;
   }
   bool count(ull key) { return u[pos(key)]; }
   // sz() マクロがメンバの size() を拾ってしまうので len()
   ll len() const { return n; }
};
