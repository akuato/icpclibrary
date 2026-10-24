# 出典とライセンス

このリポジトリは競技プログラミング用のライブラリ集です。自作のコードと、
他リポジトリから引用したコード、生成AIで作成したコードが混在しています。

---

## 1. 生成AIを用いて作成・編集したコード

AtCoder の生成AI対策ルール（https://info.atcoder.jp/entry/llm-rules-ja ）に基づく開示です。
いずれもコンテスト外で作成し、本リポジトリで公開しています。

### 新規に作成したもの

| ファイル | 備考 |
| --- | --- |
| `src/graph/TreeHash.hpp` | 根付き木のハッシュ |
| `src/data-structure/LiChao.hpp` | Li Chao tree |
| `src/data-structure/fenwick_tree.hpp` | `lower_bound` を追加 |
| `src/template/hash.sh` | ハッシュ確認用スクリプト |
| `src/template/compile.sh` | コンパイル用スクリプト |

### 既存コードを書き換えたもの

| ファイル | 書き換えの内容 | 元の出典 |
| --- | --- | --- |
| `src/flow/maxflow.hpp` | 辺の表現を `vector<vector<vector<ll>>>` から `struct` に変更 | YNUCPC/ynu-icpc-library (MIT) |
| `src/flow/mincostflow.hpp` | 同上 | YNUCPC/ynu-icpc-library (MIT) |

### 機械的な修正のみを行ったもの

マクロの引数数と型名の不整合を直したものです。アルゴリズムは変更していません。

- `src/FPS/FFT.hpp`
- `src/FPS/FFT_fast.hpp`
- `src/data-structure/FastSet.hpp`
- `src/string/KMP.hpp`
- `src/math/BinaryGCD.hpp`
- `src/modint/BarrettReduction.hpp`

---

## 2. 他リポジトリから引用したコード

### YNUCPC/ynu-icpc-library — MIT License

https://github.com/YNUCPC/ynu-icpc-library

ライセンス全文は `licenses/ynu-icpc-library-LICENSE` に収録しています。

- `src/data-structure/lazy_segtree.hpp`
- `src/data-structure/segtree.hpp`
- `src/flow/maxflow.hpp` （書き換え済み。上記 1 を参照）
- `src/flow/mincostflow.hpp` （同上）
- `src/graph/lca.hpp`
- `src/string/lcp_array.hpp`
- `src/string/rolling_hash.hpp`
- `src/string/suffix_array.hpp`
- `src/string/z_algorithm.hpp`

### ei1333/library (Luzhiled's Library) — Unlicense

https://github.com/ei1333/library

パブリックドメイン相当のため、表示の義務はありません。

- `src/data-structure/ConvexHullTrick.hpp`

### KentaroMatsushita/icpc_library — Unlicense

https://github.com/KentaroMatsushita/icpc_library

パブリックドメイン相当のため、表示の義務はありません。

- `src/data-structure/ConvexHullTrick2.hpp`
- `src/flow/bipartite-matching.hpp`
- `src/graph/hld.hpp`
- `src/graph/lowlink.hpp`
- `src/graph/scc.hpp`
- `src/math/xorConvolution.hpp`
- `src/modint/convolution.hpp`

### その他

- `src/graph/eulertrail.hpp` — https://kokiymgch.hatenablog.com/entry/2017/12/07/193238
- `src/math/Matrix.hpp` — 解説動画を参考に実装（ファイル内にURLを記載）
- `build/` 一式 — https://github.com/tatyam-prime/ICPC_notebook (Unlicense) を基にしています

---

## 3. 出典が未記載のファイル

以下のファイルには出典コメントがありません。自作のものと、引用元を記録し忘れた
ものが混在している可能性があります。確認中です。

（確認後にこの節を埋める）

---

## 4. このリポジトリ自身のライセンス

自作部分のライセンスは `LICENSE` に記載しています。引用部分には元のライセンスが
適用されます。
