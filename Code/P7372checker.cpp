#include <algorithm>
#include <numeric>

#include "testlib.h"

using namespace std;

int n, m;
long long k;

int f[10005];
bool vis[10005];

pattern pop("R|T");

int getid(int x, int y) { return (x - 1) * m + y; }

void rotate(const vector<int>& pos) {
	for (int i = 1; i < pos.size(); ++i)
		swap(f[pos[i - 1]], f[pos[i]]);
}

bool readAns(InStream& stream) {
	int b = stream.readInt(-1, 500000);
	if (b == -1) return false;
	for (int i = 1; i <= n * m; ++i)
		f[i] = i;
	while (b--) {
		string op = stream.readWord(pop);
		int x = stream.readInt(1, n - 1);
		int y = stream.readInt(1, m - 1);
		if (op == "R")
			rotate({getid(x, y), getid(x, y + 1), getid(x + 1, y + 1), getid(x + 1, y)});
		else
			rotate({getid(x, y), getid(x, y + 1), getid(x + 1, y)});
	}
	long long lcm = 1;
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n * m; ++i) {
		if (vis[i]) continue;
		int cyc = 0, x = i;
		while (!vis[x]) {
			vis[x] = true;
			x = f[x];
			++cyc;
		}
		if (k % cyc)
			stream.quitf(_wa, "the expected repetition times of mega-move is not K");
		lcm *= cyc / __gcd((long long)cyc, lcm);
	}
	if (lcm != k)
		stream.quitf(_wa, "the expected repetition times of mega-move is not K");
	return true;
}

int main(int argc, char* argv[]) {
	registerTestlibCmd(argc, argv);
	
	n = inf.readInt(2, 100);
	inf.readSpace();
	m = inf.readInt(2, 100);
	inf.readSpace();
	k = inf.readLong(2LL, 1000000000000LL);
	inf.readEoln();
	inf.readEof();
	
	bool jans = readAns(ans);
	bool pans = readAns(ouf);
	
	if (jans == true && pans == false)
		quitf(_wa, "participant didn't find answer, but answer exists");
	if (jans == false && pans == true)
		quitf(_fail, "answer exists, but jury didn't find");
	
	quitf(_ok, "answer is %s", jans ? "YES" : "NO");
	
	return 0;
}

