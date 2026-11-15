// Aliens（λ の二分探索）
// 「ちょうど k 個」の制約を λ に置き換えて外す
//
//   最小化: G(λ) = min( F(k) + λk )  ->  F(k) = G(λ) - λk
//   最大化: G(λ) = max( F(k) - λk )  ->  F(k) = G(λ) + λk
//
// 条件
//   F(k) が凸。最小化なら差分が広義単調増加、最大化なら
//     広義単調減少。破ると黙って
//     違う値を返す。全域木・森なら保証、DP なら実験で確かめる
//   f は「その λ での最適解のうち個数が最大のもの」を返す
//   [lo, hi] は値域 C に対して [-C-1, C+1]
//   呼ぶ前に f(lo).second >= k >= f(hi).second を確かめる（else -1）
//
// 対応外: 凸でない / 実数コスト / 構成を出す / オーバーフロー
// 同じ傾きが並ぶのは対応済み
//
// f(lam) -> {最適値, 使った個数}。返り値はちょうど k 個のときの最適値
template<class F> ll aliens(ll lo, ll hi, ll k, bool mx, F f) {
   ll best = lo;
   while(lo <= hi) {
      ll mid = lo + (hi - lo) / 2;
      if(f(mid).second >= k) best = mid, lo = mid + 1;
      else hi = mid - 1;
   }
   auto [v, c] = f(best);
   return mx ? v + best * k : v - best * k;
}
// 例: NAIPC 2017 E。全域木で特別-非特別の辺をちょうど w 本、最小
//     mixed 辺にだけ λ を足して Kruskal。f の中でソートし直さない
