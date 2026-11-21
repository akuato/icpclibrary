// 有理数（比較だけ。約分しない）
// 割り算を避けたいとき。衝突時刻、傾き、交点の座標など
//
// b > 0 に正規化してから襷掛け。 a/b < c/d  <=>  a*d < c*b
// 約分しないので set / map では「a<b でも b<a でもない」= 同値となり、
// 1/3 と 2/6 は同じキーになる（sort では順序は不定、両方残る）
//
// オーバーフロー: |a|,|b| <= 3e9 までなら ll でも足りるが __int128 で潰す
// 四則演算は無い。必要なら a,b を直接触る（約分を忘れると桁が増える）
struct Frac {
   ll a, b;
   Frac(ll a_ = 0, ll b_ = 1) : a(a_), b(b_) {
      if(b < 0) {
         a = -a;
         b = -b;
      }
   }
   bool operator<(const Frac& o) const {
      return (__int128)a * o.b < (__int128)o.a * b;
   }
   bool operator>(const Frac& o) const { return o < *this; }
   bool operator==(const Frac& o) const {
      return !(*this < o) && !(o < *this);
   }
};
// 例: NWERC 2020 F。隣り合うドローンの衝突時刻 Frac(x[j]-x[i], v[i]-v[j])
//     を priority_queue に入れて早い順に処理

// ---- 比較関数の作り方 ----------------------------------------------
//
// 1. 型そのものに順序を入れる（使い回すならこれ）
//
//      struct T {
//         bool operator<(const T& o) const { ... }   // const を2つとも忘れない
//         bool operator>(const T& o) const { return o < *this; }
//      };
//
//    末尾の const と引数の const& が無いと set / sort が呼べない。
//    本体は < だけ書いて、> は < を使い回す。
//    これで sort / set<T> / map<T,X> / priority_queue<T> が全部動く。
//
// 2. priority_queue は < を使って「大きい順」に出す。小さい順が欲しければ
//
//      priority_queue<T, vector<T>, greater<>> pq;   // operator> が要る
//
// 3. 型を触らず、その場だけで決めたいとき（ラムダ）
//
//      auto cmp = [](const T& p, const T& q){ return ...; };
//      sort(all(v), cmp);
//      set<T, decltype(cmp)> s(cmp);
//      priority_queue<T, vector<T>, decltype(cmp)> pq(cmp);
//
// 4. 比較用の構造体を別に作る（operator< ではなく operator()）
//
//      struct Cmp { bool operator()(const T& p, const T& q) const { ... } };
//      set<T, Cmp> s;
//
// 注意: <= を返すと壊れる。必ず狭義。
//   set も sort も「a<b でも b<a でもない => 等しい」で動いているので、
//   a < a が真になると sort が落ちたり set が壊れたりする。
//
// 多段のタイブレークは tuple に詰めるのが早い。
//   return make_tuple(x, -y, z) < make_tuple(o.x, -o.y, o.z);
