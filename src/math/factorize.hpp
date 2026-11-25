// 素数判定と素因数分解。n <= 9e18 まで確定で動く
// Miller-Rabin（決定的）+ Pollard's rho
//
// is_prime(n)    素数か
// factorize(n)   素因数を重複ありで昇順に返す。n = 1 なら空
//
// 1 個あたり n^(1/4) 程度。1e18 が 1000 個で 0.04 秒
//
// 使いどころ:
//   1e18 クラスの数を割りたい、約数を列挙したい
//   「素数の累乗か」 = factorize して種類が 1 つか

using u64 = uint64_t;
u64 mul_mod(u64 a, u64 b, u64 m) { return (__uint128_t)a * b % m; }
u64 pow_mod_u(u64 a, u64 n, u64 m) {
   u64 r = 1;
   a %= m;
   while(n) {
      if(n & 1) r = mul_mod(r, a, m);
      a = mul_mod(a, a, m);
      n >>= 1;
   }
   return r;
}
bool is_prime(u64 n) {
   if(n < 2) return false;
   for(u64 p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
      if(n % p == 0) return n == p;
   }
   u64 d = n - 1;
   ll s = 0;
   while(!(d & 1)) d >>= 1, s++;
   // この 12 個を試せば 2^64 未満は確定
   for(u64 a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
      u64 x = pow_mod_u(a, d, n);
      if(x == 1 || x == n - 1) continue;
      bool ok = false;
      rep(i, s - 1) {
         x = mul_mod(x, x, n);
         if(x == n - 1) {
            ok = true;
            break;
         }
      }
      if(!ok) return false;
   }
   return true;
}

// n の自明でない約数を 1 つ返す。n は合成数であること
//
// x と y を違う速さで動かして、差の積の gcd を見る。まとめて
// 掛けてから gcd を取ると速いが、まとめすぎて n の倍数に
// なることがあるので、その場合は 1 歩ずつ戻して探し直す
u64 pollard(u64 n) {
   if(!(n & 1)) return 2;
   for(u64 c = 1;; c++) {
      auto f = [&](u64 x) { return (mul_mod(x, x, n) + c) % n; };
      u64 x = 0, y = 0, prod = 1, g = 1;
      const ll B = 128;  // まとめて gcd を取る幅
      for(ll len = 1; g == 1; len <<= 1) {
         x = y;
         rep(i, len) y = f(y);
         for(ll k = 0; k < len && g == 1; k += B) {
            u64 save = y, p2 = prod;
            rep(i, min(B, len - k)) {
               y = f(y);
               prod = mul_mod(prod, x > y ? x - y : y - x, n);
            }
            g = gcd(prod, n);
            if(g != 1) {
               y = save, prod = p2, g = 1;
               rep(i, min(B, len - k)) {
                  y = f(y);
                  g = gcd(x > y ? x - y : y - x, n);
                  if(g != 1) break;
               }
               break;
            }
         }
      }
      if(g != n) return g;
   }
}
void factorize_rec(u64 n, vll& res) {
   if(n == 1) return;
   if(is_prime(n)) {
      res.push_back(n);
      return;
   }
   u64 d = pollard(n);
   factorize_rec(d, res);
   factorize_rec(n / d, res);
}
// 素因数を重複ありで昇順に。12 -> {2, 2, 3}
vll factorize(u64 n) {
   vll res;
   factorize_rec(n, res);
   sort(all(res));
   return res;
}
// 使った問題
// 2020-2021 ICPC Southern and Volga Russian L (Prime Divisors Selection)
//   1e18 以下の数が 1000 個。素数の累乗かどうかを判定する
//   （想定解は平方根と 1e6 以下の列挙だけで済ませているが、
//     これで殴っても間に合う）
