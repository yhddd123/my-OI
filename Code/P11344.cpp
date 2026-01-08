#include<bits/stdc++.h>
using namespace std;

const int maxn=100000;

void init();
int morning(int my_num, int right_num);
int afternoon(int left_num, int my_num, int right_num);
int evening(int left_num, int my_num, int right_num);

void init(){}
int calc(int u,int v){
	int k=__lg((u^v)&(-(u^v)));
	// cout<<u<<" "<<v<<" "<<k<<" "<<2*k+(((u>>k)&1)<((v>>k)&1))<<"\n";
	return 2*k+(((u>>k)&1)<((v>>k)&1));
}
int morning(int my_num, int right_num){return calc(my_num,right_num);}
int afternoon(int left_num, int my_num, int right_num){return calc(calc(left_num,my_num),calc(my_num,right_num));}
int evening(int left_num, int my_num, int right_num){return calc(calc(left_num,my_num),calc(my_num,right_num));}

// using std::array;
// using std::cin;
// using std::cout;
// using std::endl;
// using std::max;
// 
// namespace {
	// void ensure(bool p, const char *err) {
		// if (!p) {
			// cout << err << endl;
			// exit(0);
		// }
	// }
// }
// 
// mt19937 Rnd(1);
// int main() {
	// int q;
	// cin >> q;
	// init();
	// for (int i = 0; i < q; i++) {
		// int n;
		// cin >> n;
		// std::vector<int> v(n);
		// for (int j = 0; j < n; j++) v[j]=j;
		// shuffle(v.begin(),v.end(),Rnd);
// 
		// {
			// std::vector<int> p = v;
			// for (int j = 0; j < n; j++) {
				// int a = p[j];
				// int b = p[(j + 1) % n];
				// v[j] = morning(a, b);
				// ensure(v[j] >= 0 && v[j] < 1'000'000'000, "Wrong Answer [1]");
			// }
		// int mx=0;for(int val:v)mx=max(mx,val);
		// cout<<mx<<"\n";
		// }
		// {
			// std::vector<int> p = v;
			// for (int j = 0; j < n; j++) {
				// int a = p[(j + n-1) % n];
				// int b = p[j];
				// int c = p[(j + 1) % n];
				// v[j] = afternoon(a, b, c);
				// ensure(v[j] >= 0 && v[j] < 1'000'000'000, "Wrong Answer [2]");
			// }
		// int mx=0;for(int val:v)mx=max(mx,val);
		// cout<<mx<<"\n";
		// }
		// {
			// std::vector<int> p = v;
			// for (int j = 0; j < n; j++) {
				// int a = p[(j + n-1) % n];
				// int b = p[j];
				// int c = p[(j + 1) % n];
				// v[j] = evening(a, b, c);
				// ensure(v[j] >= 0 && v[j] < 40, "Wrong Answer [3]");
			// }
		// }
		// int ans = 0;
		// for (int j = 0; j < n; j++) {
			// ans = max(ans, v[j] + 1);
			// ensure(v[j] != v[(j + 1) % n], "Wrong Answer [4]");
		// }
		// cout << "Correct!" << endl;
		// cout << "m = " << ans << endl;
	// }
	// return 0;
// }