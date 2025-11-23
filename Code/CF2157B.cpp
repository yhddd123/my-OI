// Problem: B. Expansion Plan 2
// Contest: Codeforces - Codeforces Round 1066 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2157/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-11-23 17:37:44
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,x,y;
char s[maxn];
void work(){
	n=read();x=read();y=read();scanf("%s",s+1);
	if(x<0)x=-x;
	if(y<0)y=-y;
	if(!x&&!y){puts("YES");return ;}
	for(int i=n;i;i--){
		if(s[i]=='4'){
			if(x<y)y--;
			else x--;
		}
		else{
			if(x&&y)x--,y--;
			else if(x)x--;
			else y--;
		}
		if(!x&&!y){puts("YES");return ;}
	}
	puts("NO");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}