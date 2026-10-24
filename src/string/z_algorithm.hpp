// https://github.com/YNUCPC/ynu-icpc-library/blob/main/src/string/z_algorithm.hpp
vector<int> z_algorithm(string& s) {
   int n = int(s.size());
   vector<int> z(n);
   z[0] = n;
   for(int i = 1, l = 0, r = 0; i < n; i++) {
      int& k = z[i];
      k = (r <= i ? 0 : min(r - i, z[i - l]));
      while(i + k < n && s[k] == s[i + k]) k++;
      if(r < i + k) l = i, r = i + k;
   }
   return z;
}