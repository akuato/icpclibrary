# 使い方:
#   sh compile.sh a.cpp     デバッグ（ASan + UBSan + 警告）
#   sh compile.sh a.cpp r   提出前（ジャッジと同じ -O2 のみ）
#   sh compile.sh a.cpp t   計測（-O2 でビルドして ./a < in を実行、時間と最大メモリ）

f=${1:-a.cpp}
o=$(basename "$f" .cpp)
S="-std=gnu++20"
ulimit -s 65532 2> /dev/null

case "$2" in
r) g++ $S -O2 -o "$o" "$f" ;;
t) g++ $S -O2 -o "$o" "$f" || exit
   python3 -c '
import subprocess, resource, sys, time, platform
t = time.time()
p = subprocess.run(["./" + sys.argv[1]], stdin=open("in"))
el = time.time() - t
r = resource.getrusage(resource.RUSAGE_CHILDREN).ru_maxrss
mb = r / 1048576 if platform.system() == "Darwin" else r / 1024
print("時間 %.3f s   最大メモリ %.1f MB" % (el, mb), file=sys.stderr)
sys.exit(p.returncode)' "$o" ;;
*) g++ $S -g -O1 -fsanitize=address,undefined -fno-sanitize-recover=all \
      -Wall -Wextra -Wshadow -o "$o" "$f" ;;
esac
