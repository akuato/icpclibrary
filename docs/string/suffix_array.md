---
title: Suffix Array
documentation_of: //src/string/suffix_array.hpp
---
- 参考実装：[kactl](https://github.com/kth-competitive-programming/kactl/blob/431a6ef4ec6c04cf4c17e065089b7c4d451ea9cf/content/strings/SuffixArray.h)

## 使い方

ACL と同じインタフェースです．

- `vector<int> suffix_array(string s)`：長さ $n$．`[0, 1, …, n-1].sort(key=(i => s[i:]))`
    - $O(n \log n)$ 時間
- `vector<int> lcp_array(const string& s, const vector<int>& sa)`：長さ $n-1$．`lcp[i] = LCP(s[sa[i]:], s[sa[i+1]:])`
    - $O(n)$ 時間

空白・大文字・記号もそのまま扱えます（byte で比較）．

## ベンチマーク

| $n = 2^{20}$ の SA + LCP | 所要時間 |
| --- | --- |
| これ | 310 ms |
| [AC Library](https://github.com/atcoder/ac-library/blob/d8ca7f26686f6c78d15d13ca438ea866526e87fb/atcoder/string.hpp) | 100 ms |
