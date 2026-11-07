# 空白を含む文字列の入力

`cin >> s` は空白で切れる。行をそのまま取るなら `getline`。

## 1行だけ読む

`>>` を一度も使っていないなら、そのまま呼ぶだけでよい。

```cpp
string s;
getline(cin, s);   // 空白を含む1行全体
```

`ignore` が要るのは `>>` と混ぜたときだけ。

## 個数を読んでから行を読む

```cpp
int n;
cin >> n;
cin.ignore(1000, '\n');   // cin >> が残した改行を捨てる
vector<string> v(n);
rep(i, n) getline(cin, v[i]);
```

`ignore` を忘れると **1本目が空文字列**になり、以降が1つずつ
ずれる。

`ignore` が要るのは **`>>` の直後に `getline` するときだけ**。
`getline` を続けて呼ぶ分には不要。

## ignore の形

- `cin.ignore()` は **1文字だけ**捨てる。`5   ` のように行末に
  空白があると改行に届かず、`getline` が `"  "` を拾う
- `cin.ignore(1000, '\n')` は改行を1つ捨てるまで読み飛ばす。
  厳密には `1000` の代わりに
  `numeric_limits<streamsize>::max()`

## cin >> ws との違い

`cin >> ws` でも改行は飛ぶが **空行も飛ばす**。空行が意味を持つ
入力では使わない。`ignore` は改行を1つだけ捨てるので安全。

## 行を単語に割る

```cpp
istringstream ss(s);
string w;
while(ss >> w) { /* w を使う */ }
```

個数が分からない整数列も同じ形で取れる。

```cpp
string line;
getline(cin, line);
istringstream ls(line);
ll x;
vll v;
while(ls >> x) v.push_back(x);
```

## 区切り文字を指定（CSV など）

```cpp
string line;
while(getline(cin, line)) {       // まず行で切る
   istringstream ls(line);
   string f;
   while(getline(ls, f, ',')) { /* f を使う */ }
}
```

`getline(cin, s, ',')` を直接回すと、行末のフィールドに改行が
入ってしまう。**行で切ってから分割**するのが安全。

## 行末の \r

Windows 由来の入力だと行末に `\r` が残り、長さが1大きくなる。

```cpp
if(!s.empty() && s.back() == '\r') s.pop_back();
```

## 空白入りの名前 + 数値

```cpp
string line;
getline(cin, line);
size_t q = line.rfind(' ');
string name = line.substr(0, q);
ll v = stoll(line.substr(q + 1));
```

`John  Smith Jr 42` -> 名前 `John  Smith Jr`、値 `42`。
前から読みたいなら `line.find(' ')` を使う。

## 行数が与えられないとき

```cpp
string s;
while(getline(cin, s)) { /* s を使う */ }
```

空行も `s = ""` として読まれ、EOF で止まる。

## 性質

- `getline` は先頭・末尾の空白も、連続する空白もそのまま残す
- 戻り値はストリームなので `while` の条件に直接書ける
- `cin.tie(0)` / `ios::sync_with_stdio(false)` と併用してよい
- ただし `scanf` / `printf` と混ぜない
- 1文字ずつ空白込みで読むなら `cin.get(c)`
