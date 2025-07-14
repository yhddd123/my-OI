#include "testlib.h"

using namespace std;

int l, r;
vector<pair<int, int>> e;

int readAns(InStream& stream) {
  int k = stream.readInt(1, 1 << 17);
  vector<vector<int>> adj(l + r);
  for (const pair<int, int>& pr : e) {
    int u, v;
    tie(u, v) = pr;
    int c = stream.readInt(1, k);
    adj[u - 1].push_back(c);
    adj[l + v - 1].push_back(c);
  }
  for (vector<int>& a : adj) {
    sort(a.begin(), a.end());
    if (unique(a.begin(), a.end()) != a.end())
      stream.quitf(_wa, "found two adjacent edge have same color");
  }
  int l = 0;
  while (1 << l < k)
    ++l;
  return l;
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  l = inf.readInt(1, 100000);
  inf.readSpace();
  r = inf.readInt(1, 100000);
  inf.readSpace();
  int m = inf.readInt(1, 500000);
  inf.readEoln();
  e.reserve(m);
  while (m--) {
    int u, v;
    u = inf.readInt(1, l);
    inf.readSpace();
    v = inf.readInt(1, r);
    inf.readEoln();
    e.emplace_back(u, v);
  }

  int pa = readAns(ouf), ja = readAns(ans);
  if (pa < ja)
    quitf(_fail, "participant found better X: px = %d < jx = %d", 1 << pa, 1 << ja);
  else if (pa == ja)
    quitf(_ok, "OK, same X = %d", 1 << pa);
  else
    quitf(_wa, "jury found better X: jx = %d < px = %d", 1 << ja, 1 << pa);

  return 0;
}
