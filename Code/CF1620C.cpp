// Problem: C. BA-String
// Contest: Codeforces - Educational Codeforces Round 119 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1620/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-06 14:31:01
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

int n,m,k;
char s[maxn];
int a[maxn],b[maxn],l;
void work(){
	n=read();m=read();k=read()-1;
	scanf("%s",s+1);
	int lst=0;l=0;
	for(int i=1;i<=n;i++)if(s[i]=='a'){
		a[++l]=i-lst-1;
		lst=i;
	}
	a[++l]=n-lst;
	// for(int i=1;i<=l;i++)cout<<a[i]<<" ";cout<<"\n";
	for(int i=l;i;i--){
		b[i]=k%(a[i]*m+1);
		k/=a[i]*m+1;
	}
	for(int i=1;i<=l;i++){
		for(int j=1;j<=b[i];j++)putchar('b');
		if(i<l)putchar('a');
	}puts("");
}

bool med;
int T;
signed main(){
	// freopen("desert.in","r",stdin);
	// freopen("desert.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}