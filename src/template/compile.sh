# 使い方: sh compile.sh a.cpp      デバッグ用（ASan + UBSan + 警告）-> ./a
#         sh compile.sh a.cpp r    提出前（ジャッジと同じ）        -> ./a
f=${1:-a.cpp}
o=$(basename "$f" .cpp)

if [ "$2" = "r" ]; then
   g++ -std=gnu++20 -O2 -o "$o" "$f"
else
   g++ -std=gnu++20 -g -O1 \
      -fsanitize=address,undefined -fno-sanitize-recover=all \
      -Wall -Wextra -Wshadow \
      -o "$o" "$f"
fi
