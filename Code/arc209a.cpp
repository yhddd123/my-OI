// Problem: A - Bracket Game
// Contest: AtCoder - AtCoder Regular Contest 209 (Div. 1)
// URL: https://atcoder.jp/contests/arc209/tasks/arc209_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-09 20:01:01
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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,m;
char s[maxn];
int to[maxn];
int st[maxn],tp;
int sum[maxn];
void work(){
	scanf("%s",s+1);n=strlen(s+1);m=read();
	if((n&1)||(m&1)){puts("First");return ;}
	int fl=0;
	tp=0;for(int i=1;i<=n;i++){
		if(s[i]=='(')st[++tp]=i;
		else if(tp){
			to[i]=st[tp],to[st[tp]]=i;
			tp--;
		}
		else fl=1;
	}
	if(tp)fl=1;
	if(to[1]!=2&&to[1]!=n)fl=1;
	if(to[n]!=1&&to[n]!=n-1)fl=1;
	if(fl){puts("First");return ;}
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+(s[i]=='(')*2-1;
	for(int i=2;i<=n;i++)if(s[i]=='('){
		if(i+1<to[i]&&n-to[i]!=sum[i-1]&&i-1+sum[i-1]<n-m){puts("First");return ;}
	}
	sum[n+1]=0;for(int i=n;i;i--)sum[i]=sum[i+1]+(s[i]==')')*2-1;
	for(int i=1;i<n;i++)if(s[i]==')'){
		if(to[i]+1<i&&to[i]-1!=sum[i+1]&&n-i+sum[i+1]<n-m){puts("First");return ;}
	}
	puts("Second");
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