#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int maxn=5010;

extern int guess_palindromicity(int);
int count_pair(int, int, int);
int find_character(int, std::vector<int>);
std::vector<std::vector<int>> shuffle(std::vector<std::vector<int>>) ;

int ask(int u,int v,int w){return count_pair(u-1,v-1,w-1);}
int n,a[maxn];
int guess_palindromicity(int N){
	n=N;
	int p=(n+1)/2;
	vector<int> pos;
	for(int i=1;i<p;i++){
		int v=ask(i,n-i+1,p);
		if(!v)return 0;
		if(v==1)pos.pb(i-1),pos.pb(n-i+1-1);
		a[i]=v;
	}
	if(pos.size()){
		if(find_character(p-1,pos))return 0;
	}
	if(n&1)return 1;
	else{
		int v=ask(1,p,p+1);
		if(!v)return 0;
		if(v==3)return 1;
		return ask(1,p+1,n)==a[1];
	}
}

// static int N, cnt1, cnt2;
// static int S[5002];
// 
// void assertion(bool x, std::string msg) {
    // if (x) return;
    // printf("Wrong : %s", msg.c_str());
    // exit(0);
// }
// 
// int count_pair(int x, int y, int z) {
    // ++cnt1;
    // assertion(x != y && y != z && x != z, "Invalid Query");
    // assertion(0 <= x && 0 <= y && 0 <= z &&
            // x < N && y < N && z < N, "Invalid Query");
//             
    // int ret = 0;
    // if(S[x] == S[y]) ++ret;
    // if(S[y] == S[z]) ++ret;
    // if(S[z] == S[x]) ++ret;
//     
    // return ret;
// }
// 
// int find_character(int x, std::vector<int> Y) {
    // ++cnt2;
    // assertion(0 <= x && x < N, "Invalid Query");
    // for(int y : Y) {
        // assertion(0 <= y && y < N, "Invalid Query");
    // }
    // for(int y : Y) {
        // if(S[x] == S[y]) return 1;
    // }
    // return 0;
// }
// 
// int main() {
    // assertion(scanf("%d", &N) == 1, "Wrong Input");
    // for(int i=0;i<N;i++) assertion(scanf("%d", &S[i]) == 1, "Wrong Input");
    // for(int i=0;i<N;i++) assertion(1 <= S[i] && S[i] <= 5000, "Wrong Input");
// 
    // cnt1 = 0, cnt2 = 0;
//     
    // int res = guess_palindromicity(N);
    // int ans = 1;
    // for(int i=0;i<N/2;i++) if(S[i] != S[N-1-i]) ans = 0;
//     
    // assertion(res == ans, "Wrong Guess");
    // printf("Correct: %d %d", cnt1, cnt2);
// }