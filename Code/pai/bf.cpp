#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define dep(i, l, r) for (int i = r; i >= l; --i)
typedef long long ll; 
const int N = 5e5 + 5, P = 1e9 + 7;
const ll inf = 1e18; 
struct node { ll x, y, z; } A[N], B[N]; 
int n, m, ans, cL, cR, cnt, a[4][N]; ll d[N], ld[N], rd[N], dis[4][N][4];  

int inc (int a, int b) { return (a += b) >= P ? a - P : a; }
int dec (int a, int b) { return (a -= b) < 0 ? a + P : a; }
int mul (int a, int b) { return 1ll * a * b % P; }

namespace FT {
  int n, c1[N], c2[N]; 

  void reset (int N) {
    n = N; 
    rep(i, 1, n) c1[i] = c2[i] = 0; 
  }
  void add (int p, int k) {
    for (int i = p; i <= n; i += (i & (-i))) {
      ++c1[i]; 
      c2[i] = inc(c2[i], k); 
    }
  }
  int qry1 (int p) {
    int ans = 0; 
    for (int i = p; i; i -= (i & (-i))) 
      ans += c1[i]; 
    return ans; 
  }
  int qry2 (int p) {
    int ans = 0; 
    for (int i = p; i; i -= (i & (-i)))
      ans = inc(ans, c2[i]); 
    return ans; 
  }
}

void calc () {
  rep(i, 1, cL) ans = inc(ans, mul(A[i].x % P, cR)); 
  rep(i, 1, cR) ans = inc(ans, mul(B[i].x % P, cL));
  sort(A + 1, A + cL + 1, [&](node a, node b) {
    return a.z - a.y < b.z - b.y; 
  });  
  sort(B + 1, B + cR + 1, [&](node a, node b) {
    return a.y - a.z < b.y - b.z; 
  }); 
  rep(i, 1, cR) d[i] = B[i].y - B[i].x;
  sort(d + 1, d + cR + 1); 
  cnt = unique(d + 1, d + cR + 1) - d - 1; 
  FT :: reset(cnt); 
  for (int i = 1, j = 1, pos; i <= cL; ++i) {
    for ( ; j <= cR && A[i].y + B[j].y <= A[i].z + B[j].z; ++j) {
      pos = lower_bound(d + 1, d + cnt + 1, B[j].y - B[j].x) - d;
      FT :: add(pos, ((B[j].y - B[j].x) % P + P) % P);  
    }
    pos = upper_bound(d + 1, d + cnt + 1, A[i].x - A[i].y) - d - 1;
    ans = inc(ans, mul(FT :: qry1(pos), ((A[i].y - A[i].x) % P + P)) % P); 
    ans = inc(ans, FT :: qry2(pos)); 
  }

  rep(i, 1, cR) d[i] = B[i].z - B[i].x; 
  sort(d + 1, d + cR + 1); 
  cnt = unique(d + 1, d + cR + 1) - d - 1; 
  FT :: reset(cnt); 
  for (int i = cL, j = cR, pos; i; --i) {
    for ( ; j && A[i].y + B[j].y > A[i].z + B[j].z; --j) {
      pos = lower_bound(d + 1, d + cnt + 1, B[j].z - B[j].x) - d;
      FT :: add(pos, ((B[j].z - B[j].x) % P + P) % P);  
    }
    pos = upper_bound(d + 1, d + cnt + 1, A[i].x - A[i].z) - d - 1;
    ans = inc(ans, mul(FT :: qry1(pos), ((A[i].z - A[i].x) % P + P)) % P); 
    ans = inc(ans, FT :: qry2(pos)); 
  }
}
#define mid ((L + R) >> 1)
void solve (int L, int R) {
  if (L == R) {
    ans = inc(ans, min(ld[L], rd[R]) % P);
    ans = inc(ans, inc(a[1][L], a[2][L]));
    ans = inc(ans, inc(a[2][L], a[3][L])); 
    return ;   
  }

  rep(p, 1, 3) dis[p][mid][p] = a[p][mid]; 
  rep(p, 1, 3) if (p != 2) 
    dis[p][mid][2] = dis[2][mid][p] = a[p][mid] + a[2][mid];
  dis[1][mid][3] = dis[3][mid][1] = min(ld[mid], rd[mid]); 
  dep(i, L, mid - 1) {
    rep(p, 1, 3) rep(q, 1, 3) dis[p][i][q] = dis[p][i + 1][q] + a[p][i]; 
    rep(q, 1, 3) {
      dis[2][i][q] = min(dis[2][i][q], dis[1][i][q] + a[2][i]);
      dis[2][i][q] = min(dis[2][i][q], dis[3][i][q] + a[2][i]);  
    }
    int x = 1, y = 3;
    rep(q, 1, 3) {
      dis[x][i][q] = min(dis[x][i][q], dis[2][i][q] + a[x][i]);
      dis[x][i][q] = min(dis[x][i][q], ld[i] + dis[y][i][q] - a[y][i]);  
    }
    swap(x, y); 
    rep(q, 1, 3) {
      dis[x][i][q] = min(dis[x][i][q], dis[2][i][q] + a[x][i]);
      dis[x][i][q] = min(dis[x][i][q], ld[i] + dis[y][i][q] - a[y][i]);  
    }
  }
  rep(i, mid + 1, R) {
    rep(p, 1, 3) rep(q, 1, 3) dis[p][i][q] = dis[p][i - 1][q] + a[p][i]; 
    rep(q, 1, 3) {
      dis[2][i][q] = min(dis[2][i][q], dis[1][i][q] + a[2][i]);
      dis[2][i][q] = min(dis[2][i][q], dis[3][i][q] + a[2][i]);  
    }
    int x = 1, y = 3;
    rep(q, 1, 3) {
      dis[x][i][q] = min(dis[x][i][q], dis[2][i][q] + a[x][i]);
      dis[x][i][q] = min(dis[x][i][q], rd[i] + dis[y][i][q] - a[y][i]);  
    }
    swap(x, y); 
    rep(q, 1, 3) {
      dis[x][i][q] = min(dis[x][i][q], dis[2][i][q] + a[x][i]);
      dis[x][i][q] = min(dis[x][i][q], rd[i] + dis[y][i][q] - a[y][i]);  
    }
  }
  
  
  cL = cR = 0; 
  rep(p, 1, 3) rep(i, L, mid) 
    A[++cL] = (node){dis[p][i][1], dis[p][i][2], dis[p][i][3]};
  rep(p, 1, 3) rep(i, mid + 1, R)
    B[++cR] = (node){dis[p][i][1] - a[1][mid], dis[p][i][2] - a[2][mid], dis[p][i][3] - a[3][mid]}; 
  calc(); 

  solve(L, mid), solve(mid + 1, R); 
}

int main () {
  ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0); 
  cin >> n >> m; 
  rep(i, 1, n) rep(j, 1, m) cin >> a[i][j]; 
  ld[0] = rd[m + 1] = inf; 
  rep(i, 1, m) ld[i] = min(ld[i - 1], (ll)a[2][i]) + a[1][i] + a[3][i]; 
  dep(i, 1, m) rd[i] = min(rd[i + 1], (ll)a[2][i]) + a[1][i] + a[3][i]; 
  solve(1, m); 
  cout << mul(ans, 2) << '\n'; 
  return 0; 
}