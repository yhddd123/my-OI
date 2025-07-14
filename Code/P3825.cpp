// Problem: P3825 [NOI2017] 游戏
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3825
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-07-20 16:16:39
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline","-funroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=100010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
inline char getc(){
	char ch=getchar();
	while(!isupper(ch))ch=getchar();
	return ch;
}
bool Mbe;

int n,d,p[8],m;
char s[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<3];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int que[maxn][4];
int id(int u,int c,int fl=0){
	if(s[u]=='a'){
		if(fl)c=3-c;
		if(c==1)return u;
		else return u+n;
	}
	if(s[u]=='b'){
		if(fl)c=2-c;
		if(c==0)return u;
		return u+n;
	}
	if(s[u]=='c'){
		if(fl)c=1-c;
		if(c==0)return u;
		return u+n;
	}
}
int dfn[maxn],lw[maxn],idx;
int st[maxn],tp;
int scc[maxn],scct;
void tar(int u){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else if(!scc[v])lw[u]=min(lw[u],dfn[v]);
	}
	if(dfn[u]==lw[u]){
		scc[st[tp]]=++scct;
		while(st[tp--]!=u){
			scc[st[tp]]=scct;
		}
	}
}
void work(){
	n=read();d=read();scanf("%s",s+1);
	d=0;for(int i=1;i<=n;i++)if(s[i]=='x')p[d++]=i;
	m=read();
	for(int i=1;i<=m;i++){
		que[i][0]=read();que[i][1]=getc()-'A';
		que[i][2]=read();que[i][3]=getc()-'A';
	}
	for(int ss=0;ss<(1<<d);ss++){
		for(int i=1;i<=2*n;i++)head[i]=0,dfn[i]=scc[i]=0;scct=idx=tp=tot=0;
		for(int i=0;i<d;i++){
			if((ss>>i)&1)s[p[i]]='b';
			else s[p[i]]='a';
		}
		for(int i=1;i<=m;i++){
			if(s[que[i][0]]-'a'==que[i][1])continue;
			if(s[que[i][2]]-'a'==que[i][3]){
				add(id(que[i][0],que[i][1]),id(que[i][0],que[i][1],1));
			}
			else{
				add(id(que[i][0],que[i][1]),id(que[i][2],que[i][3]));
				add(id(que[i][2],que[i][3],1),id(que[i][0],que[i][1],1));
			}
		}
		for(int i=1;i<=2*n;i++)if(!dfn[i])tar(i);
		bool fl=0;for(int i=1;i<=n;i++)if(scc[i]==scc[i+n])fl=1;
		if(fl)continue;
		for(int i=1;i<=n;i++){
			if(scc[i]>scc[i+n]){
				if(s[i]=='a')putchar('C');
				if(s[i]=='b')putchar('C');
				if(s[i]=='c')putchar('B');
			}
			else{
				if(s[i]=='a')putchar('B');
				if(s[i]=='b')putchar('A');
				if(s[i]=='c')putchar('A');				
			}
		}
		return ;
	}
	puts("-1");
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
