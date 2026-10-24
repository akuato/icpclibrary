# 使い方: sh hash.sh -> コピペ -> Ctrl + D
# コメント・空白・改行を削除して md5 でハッシュする。コンパイラに依存しない
perl -0777 -pe 's{//[^\n]*|/\*.*?\*/}{}gs' \
  | tr -d '[:space:]' \
  | { command -v md5sum > /dev/null 2>&1 && md5sum || md5; } \
  | cut -c-6
