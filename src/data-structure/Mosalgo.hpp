int n;                   // 数列の長さ
int q;                   // クエリ数
vector<int> l(q), r(q);  // クエリの[l,r)
/* 入力 */

// ソート
int sq = max(1, int(n / sqrt(q)));
vector<int> qi(q);
for(int i = 0; i < q; ++i) qi[i] = i;
sort(qi.begin(), qi.end(), [&](int i, int j) {  // クエリの順番をpair(l/sq,r)でソート
   if(l[i] / sq != l[j] / sq) return l[i] < l[j];
   return r[i] < r[j];
});

// クエリの処理
// add(i)は追加操作、del(i)は削除操作
int nl = 0, nr = 0;  // [nl,nr)
for(int i : qi) {
   while(nl > l[i]) --nl, add(nl);
   while(nr < r[i]) add(nr), ++nr;
   while(nl < l[i]) del(nl), ++nl;
   while(nr > r[i]) --nr, del(nr);
   /* クエリの結果計算 */
}