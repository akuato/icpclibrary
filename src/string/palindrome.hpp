vi manachar(string S) {
   int i = 0, j = 0;
   vi R(S.size());
   while(i < S.size()) {
      while(i - j >= 0 && i + j < S.size() && S[i - j] == S[i + j]) ++j;
      R[i] = j;
      int k = 1;
      while(i - k >= 0 && k + R[i - k] < j) R[i + k] = R[i - k], ++k;
      i += k;
      j -= k;
   }
   return R;
}
// 奇数,偶数の最大半径
pair<vi, vi> kaibun(string s) {
   vi l = manachar(s);
   string t = "";
   int n = s.size();
   rep(i, n) {
      t += s[i];
      if(i != n - 1) t += '@';
   }
   vi v = manachar(t);
   vi r;
   for(int i = 1; i < v.size(); i += 2) {
      if(i >= v.size()) break;
      r.push_back(v[i] / 2);
   }
   return make_pair(l, r);
}