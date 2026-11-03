# cf.cpp(解法) / naive.cpp(愚直) / gen.cpp(乱数入力) を置いて  sh stress_test.sh
# 出力の食い違いだけでなく、範囲外アクセス・UB・異常終了でも止まる（ASan の出力がそのまま画面に出る）
F="-std=gnu++20 -g -O1 -fsanitize=address,undefined -fno-sanitize-recover=all -Wall -Wextra -Wshadow"
for f in cf naive gen; do g++ $F -o $f $f.cpp || exit; done
ulimit -s 65532 2> /dev/null
i=0
while ./gen > in; do i=$((i + 1)); ./cf < in > o1 && ./naive < in > o2 && cmp -s o1 o2 || break; done
echo "case $i"; cat in o1 o2
