// Problem: P9151 计数题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9151
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-12-18 22:24:44
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=5000010;
const int inf=1e9;
bool mbe;

int n,ans;
char s[maxn];
int f[maxn];
int to[maxn][2],nxt[maxn][2];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
	scanf("%s",s+1);n=strlen(s+1);ans=0;s[n+1]=' ';
	to[n+1][0]=to[n+1][1]=to[n+2][0]=to[n+2][1]=n+1;
	nxt[n+1][0]=nxt[n+1][1]=nxt[n+2][0]=nxt[n+2][1]=n+1;
	for(int i=n;i;i--){
		to[i][0]=to[i+2][0];
		to[i][1]=to[i+2][1];
		to[i][s[i]-'0']=i;
		nxt[i][0]=nxt[i+2][0];
		nxt[i][1]=nxt[i+2][1];
		if(s[i]==s[i+1])nxt[i][s[i]-'0']=i+1;
	}
	for(int i=1;i<=n;i++)f[i]=0;
	f[1]=1;
	for(int i=3;i<=n;i+=2)if(s[i]!=s[1]&&s[i]==s[i-1]){f[i]=1;break;}
	for(int i=1;i<=n;i++){
		// cout<<i<<" "<<f[i]<<" "<<nxt[i][s[i]-'0']<<" "<<to[i+1][(s[i]-'0')^1]<<"\n";
		inc(f[nxt[i][s[i]-'0']],f[i]);
		inc(f[to[i+1][(s[i]-'0')^1]],f[i]);
		if(!((n-i)&1)&&(s[i]==s[n]||nxt[i][s[i]-'0']<=n))inc(ans,f[i]);
	}
	printf("%lld\n",ans);
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