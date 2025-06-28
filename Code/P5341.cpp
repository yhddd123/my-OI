// Problem: P5341 [TJOI2019] 甲苯先生和大中锋的字符串
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5341
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-05-26 20:34:22
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,k;
char s[maxn];
int p=1,cur=1;
int a[maxn][26],len[maxn],lnk[maxn];
int siz[maxn];
void insert(int c){
	int u=++cur;
	len[u]=len[p]+1,siz[u]=1;
	while(p&&!a[p][c])a[p][c]=u,p=lnk[p];
	if(!p){lnk[p=u]=1;return ;}
	int q=a[p][c];
	if(len[p]+1==len[q])lnk[u]=q;
	else{
		int cl=++cur;
		len[cl]=len[p]+1,lnk[cl]=lnk[q];
		memcpy(a[cl],a[q],sizeof(a[q]));
		lnk[q]=lnk[u]=cl;
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
		int v=e[i].to;dfs(v);
		siz[u]+=siz[v];
	}
}
int f[maxn];
void work(){
	scanf("%s",s+1);n=strlen(s+1);k=read();
	while(cur)len[cur]=lnk[cur]=siz[cur]=0,mems(a[cur],0),cur--;cur=p=1;
	for(int i=1;i<=n;i++)insert(s[i]-'a');
	for(int i=1;i<=cur;i++)head[i]=0;tot=0;
	for(int i=2;i<=cur;i++)add(lnk[i],i);
	dfs(1);
	for(int i=1;i<=n;i++)f[i]=0;
	for(int i=2;i<=cur;i++)if(siz[i]==k)f[len[lnk[i]]+1]++,f[len[i]+1]--;
	// for(int i=2;i<=cur;i++)cout<<i<<" "<<siz[i]<<" "<<len[lnk[i]]+1<<" "<<len[i]<<"\n";
	for(int i=1;i<=n;i++)f[i]+=f[i-1];
	pii mx={0,0};for(int i=1;i<=n;i++)mx=max(mx,{f[i],i});
	if(!mx.fi)mx.se=-1;
	printf("%lld\n",mx.se);
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