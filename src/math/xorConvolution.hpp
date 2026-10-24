// https://github.com/KentaroMatsushita/icpc_library/blob/main/src/math/xor-convolution.hpp
// sizeは２べき
int my_lg(int n) { return 31 - __builtin_clz(n); }
#define si(a) (int)(size(a))
#define fore(e, v) for(auto&& e : v)
template<typename T> void fwt(vector<T>& f, bool inv = false) {
   int n = si(f), m = my_lg(n);
   rep(i, m) {
      rep(b, n) {
         if(~b >> i & 1) {
            T x = f[b], y = f[b ^ 1 << i];
            f[b] = x + y, f[b ^ 1 << i] = x - y;
         }
      }
   }
   if(inv) {
      T iz = T(1) / T(si(f));
      fore(e, f) e *= iz;
   }
}
/*
void solve(int test){
    vm a={1,1,1};
    vm b={1,1,1};
    fwt<mint>(a);
    fwt<mint>(b);
    vm c=a;
    rep(i,c.size())c[i]=a[i]*b[i];
    fwt<mint>(c,true);
}
*/