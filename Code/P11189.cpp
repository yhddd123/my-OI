// Problem: P11189 「KDOI-10」水杯降温
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11189
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-10-13 19:57:00
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],fa[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int l[maxn],r[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=2;i<=n;i++){
		fa[i]=read();
		add(fa[i],i);
	}
	for(int i=1;i<=n;i++)a[i]=read(),l[i]=r[i]=0;
	for(int u=n;u;u--){
		int sum=0,ss=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			l[u]+=l[v],ss+=l[v];
			sum=min(sum+r[v],inf);
		}
		l[u]=max(l[u],a[u]);
		int L=ss,R=inf,res=-1;
		while(L<=R){
			int mid=L+R>>1,fl=0;
			int vv=a[u]-mid,num=0;
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				if(a[v]-r[v]>vv){fl=1;break;}
				else num+=max(l[v],a[v]-vv);
				if(num>mid){fl=1;break;}
			}
			// if(u==1)cout<<mid<<" "<<vv<<" "<<num<<"\n";
			if(fl)R=mid-1;
			else L=mid+1,res=mid;
		}
		r[u]=res;
		// cout<<u<<" "<<l[u]<<" "<<r[u]<<" "<<sum<<"\n";
		if(l[u]>r[u]){puts("Shuiniao");return ;}
		if(head[u]&&l[u]>sum){puts("Shuiniao");return ;}
	}
	puts("Huoyu");
}

// \
444

bool Med;
int op,T;
signed main(){
// 	freopen("water.in","r",stdin);
// 	freopen("water.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	op=read();T=read();
	while(T--)work();
}