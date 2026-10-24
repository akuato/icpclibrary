#!/bin/sh
# ICPC_notebook の整理。リポジトリのルートで実行する
set -e

# --- macOS のゴミ ---
find . -name '.DS_Store' -delete 2>/dev/null || true
git rm --cached -r --ignore-unmatch '*.DS_Store' > /dev/null 2>&1 || true

# --- 重複・壊れているファイルを削除 ---
for f in \
   src/string/Zalgorithm.hpp \
   src/string/suffix_array.hpp \
   src/graph/scc_yokohama.hpp \
   src/graph/Trie_yokohama.hpp \
   src/graph/lca_me.hpp \
   src/data-structure/ConvexHullTrick2.hpp \
   src/memo/dynamic_convex_hull_trick.hpp \
   src/memo/Dynamic-Li-Chao-Tree.hpp \
   src/memo/fps.hpp \
   src/memo/bostanmori.hpp \
   src/string/RollingHash.hpp
do
   git rm -f --ignore-unmatch "$f" > /dev/null
done
rmdir src/others 2>/dev/null || true

# --- ライブラリ名らしくないものを改名 ---
mv_if() { [ -f "$1" ] && git mv "$1" "$2" || true; }
mv_if src/string/SuffixArray_spped_star.hpp src/string/suffix_array.hpp
mv_if src/math/gyouretsukiteiri.hpp          src/math/matrix_tree.hpp
mv_if src/graph/gyouretsukiteiri.hpp         src/graph/matrix_tree.hpp
mv_if src/math/gensikon.hpp                  src/math/primitive_root.hpp
mv_if src/math/mathtemplate.hpp              src/math/math_template.hpp
mv_if src/string/kaibun.hpp                  src/string/palindrome.hpp
mv_if src/template/vim_setteing.sh           src/template/vim_settings.sh
mv_if src/graph/CentroidDecomposition.cpp    src/graph/centroid_decomposition.hpp

echo "done. git status で確認してください"
