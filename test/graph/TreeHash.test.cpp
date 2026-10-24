#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "test/template.hpp"
#undef rep
#undef sz
#define rep(i, n) for(ll i = 0; i < (n); i++)
#define repi(i, a, b) for(ll i = (a); i < (b); i++)
#define sz(a) (ll)(size(a))
using vi = vector<int>;
using vvi = vector<vi>;
#include "src/graph/TreeHash.hpp"

// 正解判定用の AHU。部分木の形に一意な ID を振るので衝突しない
map<vi, int> ahump;
int ahu(const vvi& g, vi& ng, vi& id, int v) {
   int sv = ng[v];
   ng[v] = 1;
   vi ch;
   for(int u : g[v]) if(!ng[u]) ch.push_back(ahu(g, ng, id, u));
   sort(all(ch));
   ng[v] = sv;
   return id[v] = ahump.emplace(ch, ahump.size()).first->second;
}

int main() {
   mt19937 rng(20261022);
   auto mk = [&](ll n) {
      vvi r(n);
      for(ll v = 1; v < n; v++) {
         ll p = rng() % v;
         r[v].push_back(p), r[p].push_back(v);
      }
      return r;
   };

   // 1) 木として。ハッシュの一致が AHU の一致と完全に対応する
   rep(it, 20000) {
      ll n = 1 + rng() % 9;
      vvi a = mk(n), b = mk(n);
      if(rng() % 2) {
         vi p(n);
         iota(all(p), 0);
         shuffle(all(p), rng);
         vvi c(n);
         rep(v, n) for(int u : a[v]) c[p[v]].push_back(p[u]);
         b = c;
      }
      ll ra = rng() % n, rb = rng() % n;
      vector<ull> ha(n), hb(n);
      vi nga(n, 0), ngb(n, 0), ia(n), ib(n);
      treehash(a, nga, ha, ra), treehash(b, ngb, hb, rb);
      ahu(a, nga, ia, ra), ahu(b, ngb, ib, rb);
      assert((ha[ra] == hb[rb]) == (ia[ra] == ib[rb]));
   }

   // 2) 同じ木の中の部分木どうし
   rep(it, 3000) {
      ll n = 1 + rng() % 12;
      vvi a = mk(n);
      vector<ull> h(n);
      vi ng(n, 0), id(n);
      treehash(a, ng, h, 0), ahu(a, ng, id, 0);
      rep(u, n) rep(v, n) assert((h[u] == h[v]) == (id[u] == id[v]));
   }

   // 3) 閉路つきグラフ。閉路の頂点を ng にして、各頂点にぶら下がる木だけを辿る
   rep(it, 3000) {
      ll c = 3 + rng() % 5, n = c;
      vvi g(c);
      rep(i, c) {
         ll j = (i + 1) % c;
         g[i].push_back(j), g[j].push_back(i);
      }
      rep(i, c) {
         ll k = rng() % 4;
         rep(t, k) {
            g.push_back(vi());
            ll p = (rng() % 2 && n > c) ? c + rng() % (n - c) : i;
            g[p].push_back(n), g[n].push_back(p), n++;
         }
      }
      vi ng(n, 0);
      rep(i, c) ng[i] = 1;
      vi orig = ng, id(n);
      vector<ull> h(n);
      rep(i, c) {
         treehash(g, ng, h, i);
         assert(ng == orig);  // 呼び出し後も ng が元のまま
         ahu(g, ng, id, i);
         ull x = h[i];
         int xi = id[i];
         rep(j, c) {
            treehash(g, ng, h, j), ahu(g, ng, id, j);
            assert((x == h[j]) == (xi == id[j]));
         }
         treehash(g, ng, h, i), ahu(g, ng, id, i);
      }
   }

   // 4) n 頂点の非同型な根付き木の本数と一致する (OEIS A000081)
   const int expect[9] = {0, 1, 1, 2, 4, 9, 20, 48, 115};
   repi(n, 1, 9) {
      set<ull> s;
      vi par(n, 0);
      while(true) {
         vvi g(n);
         repi(v, 1, n) g[v].push_back(par[v]), g[par[v]].push_back(v);
         vector<ull> h(n);
         vi ng(n, 0);
         treehash(g, ng, h, 0);
         s.insert(h[0]);
         ll i = 1;
         while(i < n && par[i] == i - 1) par[i++] = 0;
         if(i == n) break;
         par[i]++;
      }
      assert(sz(s) == expect[n]);
   }

   // 5) 根の取り方で形が変わる（3 頂点のパス）
   {
      vvi g = {{1}, {0, 2}, {1}};
      vector<ull> h(3);
      vi ng(3, 0);
      treehash(g, ng, h, 0);
      ull x = h[0];
      treehash(g, ng, h, 1);
      assert(x != h[1]);
   }

   puts("Hello World");
}
