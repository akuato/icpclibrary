// LCP Array。ACL と同じ使い方
//
//   vector<int> sa  = suffix_array(s);
//   vector<int> lcp = lcp_array(s, sa);   長さ n-1
//   lcp[i] = LCP(s[sa[i]:], s[sa[i+1]:])
//
// O(n)
vector<int> lcp_array(const string& s, const vector<int>& sa) {
   int n = s.size(), h = 0;
   vector<int> rk(n), lcp(max(0, n - 1));
   for(int i = 0; i < n; i++) rk[sa[i]] = i;
   for(int i = 0; i < n; i++) {
      if(h) h--;
      if(rk[i] == 0) continue;
      int j = sa[rk[i] - 1];
      while(j + h < n && i + h < n && s[j + h] == s[i + h]) h++;
      lcp[rk[i] - 1] = h;
   }
   return lcp;
}
