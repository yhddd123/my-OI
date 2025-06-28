// Problem: CF452E Three strings
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF452E
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-05-26 20:50:28
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=600010;
const int inf=1e9;
bool mbe;

int n,lim,f[maxn];
char s[maxn];
int p=1,cur=1;
int a[maxn][28],len[maxn],lnk[maxn];
int siz[maxn][3];
void insert(int c,int op){
	int u=++cur;
	if(op<3)siz[u][op]++;
	len[u]=len[p]+1;
	while(p&&!a[p][c])a[p][c]=u,p=lnk[p];
	if(!p){lnk[p=u]=1;return ;}
	int q=a[p][c];
	if(len[p]+1==len[q])lnk[u]=q;
	else{
		int cl=++cur;
		lnk[cl]=lnk[q],len[cl]=len[p]+1;
		memcpy(a[cl],a[q],sizeof(a[q]));
		lnk[u]=lnk[q]=cl;
		while(p&&a[p][c]==q)a[p][c]=cl,p=lnk[p];
	}
	p=u;
}
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
void dfs(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs(v);
		siz[u][0]+=siz[v][0],siz[u][1]+=siz[v][1],siz[u][2]+=siz[v][2];
	}
}
void work(){
	scanf("%s",s+1);n=strlen(s+1);lim=n;
	for(int i=1;i<=n;i++)insert(s[i]-'a',0);
	insert(26,3);
	scanf("%s",s+1);n=strlen(s+1);lim=min(lim,n);
	for(int i=1;i<=n;i++)insert(s[i]-'a',1);
	insert(27,3);
	scanf("%s",s+1);n=strlen(s+1);lim=min(lim,n);
	for(int i=1;i<=n;i++)insert(s[i]-'a',2);
	for(int i=2;i<=cur;i++)add(lnk[i],i);
	dfs(1);
	for(int i=2;i<=cur;i++){
		int w=siz[i][0]*siz[i][1]*siz[i][2]%mod;
		f[len[lnk[i]]+1]+=w,f[len[i]+1]+=mod-w;
	}
	for(int i=1;i<=lim;i++)(f[i]+=f[i-1])%=mod;
	for(int i=1;i<=lim;i++)printf("%lld ",f[i]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}