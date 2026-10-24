// modint を u32 にして加減算を真面目にやると速い
mint g = 3;  // 原始根
void fft(vector<mint>& a) {
   ll n = sz(a), lg = __lg(n);
   static auto z = [] {
      vector<mint> z(30);
      mint s = 1;
      repi(i, 2, 32) {
         z[i - 2] = s * g.pow(mod >> i);
         s *= g.inv().pow(mod >> i);
      }
      return z;
   }();
   repi(l, 0, lg) {
      ll w = 1 << (lg - l - 1);
      mint s = 1;
      repi(k, 0, 1 << l) {
         ll o = k << (lg - l);
         repi(i, o, o + w) {
            mint x = a[i], y = a[i + w] * s;
            a[i] = x + y;
            a[i + w] = x - y;
         }
         s *= z[countr_zero<uint64_t>(~k)];
      }
   }
}
// コピペ
void ifft(vector<mint>& a) {
   ll n = sz(a), lg = __lg(n);
   static auto z = [] {
      vector<mint> z(30);
      mint s = 1;
      repi(i, 2, 32) {  // g を逆数に
         z[i - 2] = s * g.inv().pow(mod >> i);
         s *= g.pow(mod >> i);
      }
      return z;
   }();
   for(ll l = lg; l--;) {  // 逆順に
      ll w = 1 << (lg - l - 1);
      mint s = 1;
      repi(k, 0, 1 << l) {
         ll o = k << (lg - l);
         repi(i, o, o + w) {
            mint x = a[i], y = a[i + w];  // *s を下に移動
            a[i] = x + y;
            a[i + w] = (x - y) * s;
         }
         s *= z[countr_zero<uint64_t>(~k)];
      }
   }
}
vector<mint> conv(vector<mint> a, vector<mint> b) {
   if(a.empty() || b.empty()) return {};
   size_t s = sz(a) + sz(b) - 1, n = bit_ceil(s);
   // if(min(sz(a), sz(b)) <= 60) 愚直に掛け算
   a.resize(n);
   b.resize(n);
   fft(a);
   fft(b);
   mint inv = mint(n).inv();
   repi(i, 0, n) a[i] *= b[i] * inv;
   ifft(a);
   a.resize(s);
   return a;
}
