#!/bin/sh
# 公開リポジトリの後始末。ICPC_notebook のルートで実行する
set -e

# --- 成果物・作業ファイルを追跡から外す（ファイル自体は手元に残る）---
git rm --cached --ignore-unmatch a.out cf.cpp notebook.pdf cleanup.sh fix.sh > /dev/null

# --- 参照先が消えたテスト・ドキュメントを整理 ---
git rm -f --ignore-unmatch test/string/RollingHash.test.cpp > /dev/null
git rm -f --ignore-unmatch docs/string/RollingHash.md > /dev/null
git rm -f --ignore-unmatch test/string/Zalgorithm.test.cpp > /dev/null

mv_if() { [ -f "$1" ] && git mv -f "$1" "$2" || true; }
mv_if docs/data-structure/BIT.md  docs/data-structure/fenwick_tree.md
mv_if docs/string/Zalgorithm.md   docs/string/z_algorithm.md
mv_if docs/string/SuffixArray.md  docs/string/suffix_array.md

echo "done. git status で確認してください"
