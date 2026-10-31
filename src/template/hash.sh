# 使い方:
#   sh hash.sh          コピペ -> Ctrl + D でその場のコードをハッシュ
#   sh hash.sh --all    src/ 以下を全部ハッシュして src/template/hash_values.txt を作り直す
#
# 本番で打つのはこれだけでよい（手で打つコードにコメントは無いので）:
#   tr -d '[:space:]' | md5sum | cut -c-6

MD5() { command -v md5sum > /dev/null 2>&1 && md5sum || md5; }
# コメント・空白・改行を削除して md5。コンパイラに依存しない
H() { perl -0777 -pe 's{//[^\n]*|/\*.*?\*/}{}gs' | tr -d '[:space:]' | MD5 | cut -c-6; }

if [ "$1" != "--all" ]; then H; exit; fi

R=$(cd "$(dirname "$0")/../.." && pwd)
O="$R/src/template/hash_values.txt"
{
   echo "# 本番でハッシュを確認するコマンド（打ったコードにコメントは無いので、空白を消すだけでよい）"
   echo "#   tr -d '[:space:]' | md5sum | cut -c-6"
   echo "#   -> 貼り付け -> Ctrl + D"
   echo "# 手元でこの表を作り直すコマンド"
   echo "#   sh src/template/hash.sh --all"
   echo
   cd "$R/src" || exit
   for f in $(find . -name '*.hpp' | sed 's|^\./||' | sort); do
      printf '%-45s %s\n' "$f" "$(H < "$f")"
   done
} > "$O"
echo "$O を更新しました"
