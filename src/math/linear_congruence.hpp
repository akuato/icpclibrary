ll extgcd(ll a, ll b, ll& x, ll& y) {
   ll d = a;
   if(b != 0) {
      d = extgcd(b, a % b, y, x);
      y -= (a / b) * x;
   } else {
      x = 1;
      y = 0;
   }
   return d;
}
ll mod_inverse(ll a, ll m) {
   ll x, y;
   extgcd(a, m, x, y);
   return (m + x % m) % m;
}

P linear_congruence(vll& A, vll& B, vll& M) {
   ll x = 0, m = 1;
   rep(i, A.size()) {
      ll a = A[i] * m, b = B[i] - A[i] * x, d = gcd(M[i], a);
      if(b % d) return P(0, -1);
      ll t = (b / d) * mod_inverse(a / d, M[i] / d) % (M[i] / d);
      x = x + m * t;
      m *= M[i] / d;
   }
   return P((x % m + m) % m, m);
}