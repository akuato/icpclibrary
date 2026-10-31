// 型と要素数を入れると MB が出る。例:  int 44000000  ->  176.0 MB
// 型名の代わりに1要素のバイト数を直接書いてもよい。例:  12 1000000
// set/map/uset/umap は1要素あたりの実測値。row は vector<vector<>> の1行あたりの上乗せ。
// 他の上乗せ: reserve 無しの push_back はピーク2.5倍、実行ファイルと標準ライブラリで数MB。
// 目安: 256MB = int 6400万個 = long long 3200万個。
#include <bits/stdc++.h>
using namespace std;
int main() {
   map<string, double> B = {{"char", 1}, {"bool", 1}, {"short", 2}, {"int", 4}, {"float", 4},
                            {"ll", 8},   {"double", 8}, {"pair", 8}, {"ptr", 8}, {"i128", 16},
                            {"set", 40}, {"map", 40}, {"uset", 32}, {"umap", 32}, {"row", 30}};
   string t;
   double n;
   while(cin >> t >> n) {
      double b = B.count(t) ? B[t] : atof(t.c_str());
      printf("%s x %.0f = %.1f MB\n", t.c_str(), n, b * n / 1e6);
   }
}
