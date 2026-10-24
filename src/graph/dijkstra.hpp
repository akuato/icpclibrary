auto f = [&](int s) {
   vll dist(n, inf);
   priority_queue<P, vector<P>, greater<P>> q;
   dist[s] = 0;
   q.push(P(dist[s], s));
   while(!q.empty()) {
      int v = q.top().second;
      ll d = q.top().first;
      q.pop();
      if(dist[v] < d) continue;
      for(auto u : g[v]) {
         if(chmin(dist[u.to], dist[v] + u.cost)) { q.push(P(dist[u.to], u.to)); }
      }
   }
};