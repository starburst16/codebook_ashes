const int INF = 1e9;
struct Match {  // O( ( V + E ) * sqrt( V ) )
  vector<vector<int>> G;
  vector<int> match, dist;
  int n, m;
  // n: number of nodes on left side, nodes are numbered 1 to n
  // m: number of nodes on right side, nodes are numbered n to n+m
  // G = NIL[0] ∪ G1[G[1---n]] ∪ G2[G[n+1---n+m]]
  Match (int _n, int _m) : n(_n), m(_m), G(_n+_m+1), match(_n+_m+1), dist(_n+_m+1) {}
  bool BFS() {
    queue< int > Q;
    for ( int i = 1; i <= n; i++ ) {
      if ( match[ i ] == 0 ) {
        dist[ i ] = 0;
        Q.push( i );
      }
      else
        dist[ i ] = INF;
    }
    dist[ 0 ] = INF;
    while ( !Q.empty() ) {
      int u = Q.front();
      Q.pop();
      if ( dist[ u ] < dist[ 0 ] )
        for ( int v : G[ u ] )
          if ( dist[ match[ v ] ] == INF ) {
            dist[ match[ v ] ] = dist[ u ] + 1;
            Q.push( match[ v ] );
          }
    }
    return ( dist[ 0 ] != INF );
  }
  bool DFS( int u ) {
    if ( u != 0 ) {
      for ( int v : G[ u ] )
        if ( dist[ match[ v ] ] == dist[ u ] + 1 && DFS( match[ v ] ) ) {
          match[ v ] = u;
          match[ u ] = v;
          return true;
        }
      dist[ u ] = INF;
      return false;
    }
    return true;
  }
  int Max_Match() {
    int matching = 0;
    fill_n( match.begin(), n + m + 1, 0 );
    while ( BFS() )
      for ( int i = 1; i <= n; i++ )
        if ( match[ i ] == 0 && DFS( i ) ) matching++;
    return matching;
  }
  void AddEdge( int u, int v ) { G[ u ].push_back( n + v ); }
  void DFS2( int u ) {
	if (dist[u]) return;
    dist[ u ] = 1;
    for ( int v : G[ u ] )
      if ( v != match[ u ] ) {
        dist[ v ] = 1;
        if ( match[ v ] != 0 ) DFS2( match[ v ] );
      }
  }
  vector<int> Min_Vertex_Cover( ) {
    // after calling Max_Match
    fill_n( dist.begin() + 1, n + m + 1, 0 );
    for ( int i = 1; i <= n; i++ )
      if ( match[ i ] == 0 ) DFS2( i );
    vector<int> res(n);
    for ( int i = 1; i <= n; i++ )
      if ( dist[ i ] == 0 ) res[i-1] = true;
    for ( int i = n + 1; i <= n + m; i++ )
      if ( dist[ i ] == 1 ) res[i-n-1] = true;
    return res;
  }
};