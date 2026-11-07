# 本番で打つコマンド集。このファイル自体は打たない / 実行しない
# 環境: Ubuntu 24.04 / g++ 13 / /bin/sh は dash
#   dash に time は無い。/usr/bin/time も入っていない

# デバッグ（範囲外・UB を行番号つきで出す）
g++ -std=gnu++20 -g -O1 -fsanitize=address,undefined \
    -Wall -Wextra -Wshadow -o a a.cpp

# 提出前（ジャッジと同じ）。compileg++ a.cpp でも同じ
g++ -x c++ -g -O2 -std=gnu++20 -static -o a a.cpp

# 時間（ms）
s=$(date +%s%N); ./a < in; e=$(date +%s%N)
echo $(((e - s) / 1000000))

# 256MB に収まるか。0 以外なら超過
# ASan 版では使えないので -O2 版で試す
(ulimit -v 262144; ./a < in); echo $?

# 深い再帰。シェルに1回だけ
ulimit -s 65532

# 手打ちしたライブラリの照合。貼り付け -> Ctrl + D
# 出た6文字を hash_values.txt と見比べる
tr -d '[:space:]' | md5sum | cut -c-6

# メモリ見積り: 個数 x バイト数 / 10^6 = MB
#   char,bool 1 / short 2 / int,float 4
#   ll,double,pair<int,int>,ptr 8 / i128 16
#   set,map 40 / uset,umap 32
#   vector<vector<>> は1行あたり +30
#   reserve なしの push_back はピーク 2.5 倍
#   256MB = int 6400万 = ll 3200万
