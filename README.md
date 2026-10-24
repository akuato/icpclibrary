# icpclibrary

競技プログラミング用のライブラリです。ICPC 用のノート（PDF）を生成できます。

出典とライセンスは [NOTICE.md](NOTICE.md) を参照してください。
生成AIを用いて作成・編集したコードもそこに明記しています
（[AtCoder 生成AI対策ルール](https://info.atcoder.jp/entry/llm-rules-ja) に基づく開示）。

## 構成

| | |
| --- | --- |
| `src/` | ライブラリ本体。ジャンルごとにフォルダ分け |
| `test/` | 検証用。`judge.yosupo.jp` などに提出する形 |
| `docs/` | 各ライブラリの説明 |
| `build/` | PDF 生成用（CSS 組版） |
| `licenses/` | 引用元のライセンス |

`src/template/template.hpp` が提出時のテンプレートです。

## 手元で動かす

事前に必要なもの。

```sh
brew install node clang-format
npm install -g @vivliostyle/cli
npm install
pip3 install online-judge-verify-helper   # verify を使うなら
```

```sh
make build    # notebook.pdf を生成
make verify   # oj-verify で検証
make serve    # oj-verify のページを生成
```

## ツール

| | |
| --- | --- |
| `src/template/compile.sh` | `sh compile.sh a.cpp` でデバッグ用ビルド（ASan + UBSan + 警告）、`sh compile.sh a.cpp r` で提出前ビルド |
| `src/template/hash.sh` | `sh hash.sh` のあとコードを貼って Ctrl+D。コメントと空白を除いた md5 の先頭6文字。本番でノートから写したコードの照合用 |
| `src/template/stress_test.sh` | ストレステスト |

## 元になったテンプレート

PDF 生成の仕組みは [tatyam-prime/ICPC_notebook](https://github.com/tatyam-prime/ICPC_notebook) (Unlicense) を使わせてもらっています。
