// https://github.com/YNUCPC/ynu-icpc-library/blob/main/src/datastructure/segtree.hpp
// ACL と同じ名前・同じ使い方
// segtree<S, op, e> seg(n) または seg(v)
template<class S, S (*op)(S, S), S (*e)()> struct segtree {
   int _n, size, log;
   vector<S> dat;
   void update(int k) {
      dat[k] = op(dat[2 * k], dat[2 * k + 1]);
   }
   segtree() : segtree(0) {}
   segtree(int n) : segtree(vector<S>(n, e())) {}
   segtree(const vector<S>& v) : _n(int(v.size())) {
      log = 0;
      while((1 << log) < _n) log++;
      size = 1 << log;
      dat = vector<S>(2 * size, e());
      for(int i = 0; i < _n; i++) dat[size + i] = v[i];
      for(int i = size - 1; i >= 1; i--) update(i);
   }
   // a[p] = x
   void set(int p, S x) {
      p += size;
      dat[p] = x;
      for(int i = 1; i <= log; i++) update(p >> i);
   }
   S get(int p) const { return dat[p + size]; }
   // op(a[l], ..., a[r-1])
   S prod(int l, int r) const {
      S sml = e(), smr = e();
      l += size, r += size;
      while(l < r) {
         if(l & 1) sml = op(sml, dat[l++]);
         if(r & 1) smr = op(dat[--r], smr);
         l >>= 1, r >>= 1;
      }
      return op(sml, smr);
   }
   S all_prod() const { return dat[1]; }

   // ===== ここから下は木上の二分探索。要らなければ打たない
   // f(op(a[l], ..., a[r-1])) == true となる最大の r
   template<bool (*f)(S)> int max_right(int l) const {
      return max_right(l, [](S x) { return f(x); });
   }
   template<class F> int max_right(int l, F f) const {
      assert(f(e()));
      if(l == _n) return _n;
      l += size;
      S sm = e();
      do {
         while(l % 2 == 0) l >>= 1;
         if(!f(op(sm, dat[l]))) {
            while(l < size) {
               l = 2 * l;
               if(f(op(sm, dat[l]))) sm = op(sm, dat[l]), l++;
            }
            return l - size;
         }
         sm = op(sm, dat[l]), l++;
      } while((l & -l) != l);
      return _n;
   }
   // f(op(a[l], ..., a[r-1])) == true となる最小の l
   template<bool (*f)(S)> int min_left(int r) const {
      return min_left(r, [](S x) { return f(x); });
   }
   template<class F> int min_left(int r, F f) const {
      assert(f(e()));
      if(r == 0) return 0;
      r += size;
      S sm = e();
      do {
         r--;
         while(r > 1 && (r % 2)) r >>= 1;
         if(!f(op(dat[r], sm))) {
            while(r < size) {
               r = 2 * r + 1;
               if(f(op(dat[r], sm))) sm = op(dat[r], sm), r--;
            }
            return r + 1 - size;
         }
         sm = op(dat[r], sm);
      } while((r & -r) != r);
      return 0;
   }
};
