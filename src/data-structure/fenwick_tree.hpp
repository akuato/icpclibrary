struct fenwick_tree {
   vector<ll> a;
   fenwick_tree(ll n) : a(n + 1) {}
   void add(ll i, ll x) {  // A[i] += x
      i++;
      while(i < sz(a)) {
         a[i] += x;
         i += i & -i;
      }
   }
   ll sum(ll r) {
      ll s = 0;
      while(r) {
         s += a[r];
         r -= r & -r;
      }
      return s;
   }
   ll sum(ll l, ll r) {  // sum of A[l, r)
      return sum(r) - sum(l);
   }
   ll lower_bound(ll x) {  // sum(i+1) >= x となる最小の i。無ければ n。A[i] >= 0 が前提
      ll i = 0, n = sz(a) - 1, k = 1;
      while(k * 2 <= n) k *= 2;
      for(; k; k /= 2)
         if(i + k <= n && a[i + k] < x) i += k, x -= a[i];
      return i;
   }
};
