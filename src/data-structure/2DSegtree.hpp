#pragma once

template<typename T, typename F> struct SegmentTree2D {
   private:
   int id(int h, int w) const { return h * 2 * W + w; }

   public:
   int H, W;
   vector<T> seg;
   const F f;
   const T I;

   SegmentTree2D(int h, int w, F _f, const T& i) : f(_f), I(i) { init(h, w); }

   void init(int h, int w) {
      H = W = 1;
      while(H < h) H <<= 1;
      while(W < w) W <<= 1;
      seg.assign(4 * H * W, I);
   }

   // build にのみ呼ぶ
   void set(int h, int w, const T& x) { seg[id(h + H, w + W)] = x; }

   void build() {
      // w in [W, 2W)
      for(int w = W; w < 2 * W; w++) {
         for(int h = H - 1; h; h--) { seg[id(h, w)] = f(seg[id(2 * h + 0, w)], seg[id(2 * h + 1, w)]); }
      }
      // h in [0, 2H)
      for(int h = 0; h < 2 * H; h++) {
         for(int w = W - 1; w; w--) { seg[id(h, w)] = f(seg[id(h, 2 * w + 0)], seg[id(h, 2 * w + 1)]); }
      }
   }

   T get(int h, int w) const { return seg[id(h + H, w + W)]; }
   T operator()(int h, int w) const { return seg[id(h + H, w + W)]; }

   void update(int h, int w, const T& x) {
      h += H, w += W;
      seg[id(h, w)] = x;
      for(int i = h >> 1; i; i >>= 1) { seg[id(i, w)] = f(seg[id(2 * i + 0, w)], seg[id(2 * i + 1, w)]); }
      for(; h; h >>= 1) {
         for(int j = w >> 1; j; j >>= 1) { seg[id(h, j)] = f(seg[id(h, 2 * j + 0)], seg[id(h, 2 * j + 1)]); }
      }
   }

   T _inner_query(int h, int w1, int w2) {
      T res = I;
      for(; w1 < w2; w1 >>= 1, w2 >>= 1) {
         if(w1 & 1) res = f(res, seg[id(h, w1)]), w1++;
         if(w2 & 1) --w2, res = f(res, seg[id(h, w2)]);
      }
      return res;
   }

   // [ (h1,w1), (h2,w2) ) 半開
   T query(int h1, int w1, int h2, int w2) {
      if(h1 >= h2 || w1 >= w2) return I;
      T res = I;
      h1 += H, h2 += H, w1 += W, w2 += W;
      for(; h1 < h2; h1 >>= 1, h2 >>= 1) {
         if(h1 & 1) res = f(res, _inner_query(h1, w1, w2)), h1++;
         if(h2 & 1) --h2, res = f(res, _inner_query(h2, w1, w2));
      }
      return res;
   }
};

/**
 * @brief 二次元セグメント木
 * @docs docs/data-structure-2d/2d-segment-tree.md
 */

// 使い方
int main() {
   cin.tie(0);
   ios::sync_with_stdio(false);
   int h, w, h1, w1, h2, w2;
   cin >> h >> w >> h1 >> w1 >> h2 >> w2;
   chmin(h2, h1);
   chmin(w2, w1);
   SegmentTree2D seg(h + 1, w + 1, [](ll a, ll b) { return max(a, b); }, 0ll);
   vvll a(h + 1, vll(w + 1));
   repi(i, 1, h + 1) repi(j, 1, w + 1) cin >> a[i][j];
   vvll sum(h + 1, vll(w + 1)), sumt(h + 1, vll(w + 1)), suma(h + 1, vll(w + 1));
   repi(i, 1, h + 1) repi(j, 1, w + 1) sum[i][j] = sum[i][j - 1] + a[i][j];
   repi(j, 1, w + 1) repi(i, 1, h + 1) sum[i][j] += sum[i - 1][j];
   repi(i, h1, h + 1) repi(j, w1, w + 1) sumt[i][j] = sum[i][j] - sum[i - h1][j] - sum[i][j - w1] + sum[i - h1][j - w1];
   repi(i, h2, h + 1) repi(j, w2, w + 1) suma[i][j] = sum[i][j] - sum[i - h2][j] - sum[i][j - w2] + sum[i - h2][j - w2];
   repi(i, 1, h + 1) repi(j, 1, w + 1) seg.set(i, j, suma[i][j]);
   seg.build();
   ll ans = -inf;
   repi(i, h1, h + 1) repi(j, w1, w + 1) {
      ll now = sumt[i][j];
      now -= seg.query(i - (h1 - h2), j - (w1 - w2), i + 1, j + 1);
      chmax(ans, now);
   }
   cout << ans << endl;
}
