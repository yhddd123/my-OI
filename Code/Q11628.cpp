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
const int maxn=2010;
const int inf=1e9;
bool mbe;

int n,a[maxn],fa[maxn];
int d[maxn];
bool vis[maxn],fl[maxn],ban[maxn];
int ed[maxn];
vector<int> ans;
void mov(int p){
	ans.pb(p);
	int tmp=a[1],pos=p;
	vector<int> id;
	while(fa[p]){
		id.pb(p);
		p=fa[p];
	}
	while(id.size()){
		a[fa[id.back()]]=a[id.back()],id.pop_back();
	}
	a[pos]=tmp;
}
void work(){
	n=read();
	for(int i=2;i<=n;i++)fa[i]=read()+1;
	for(int i=1;i<=n;i++)a[i]=read()+1;
	while(!vis[1]){
		for(int i=1;i<=n;i++)d[i]=0,fl[i]=0;
		for(int i=1;i<=n;i++)if(!vis[i])d[fa[i]]++;
		for(int i=n;i;i--)if(!vis[i]){
			if(d[i]==0)fl[i]=1,ed[i]=i;
			if(fl[i]&&d[fa[i]]==1)fl[fa[i]]=1,ed[fa[i]]=ed[i];
		}
		int p=n;
		while(!ban[a[1]]){
			if(fl[a[1]]){
				int u=ed[a[1]];
				while(ban[a[u]]&&a[u]>a[1])u=fa[u];
				mov(u);ban[a[u]]=1;
			}
			else{
				while(vis[p]||ban[a[p]])p--;
				if(p)mov(p),p--;
				else break;
			}
		}
		for(int i=1;i<=n;i++)if(fl[i])fl[i]=0,vis[i]=1;
	}
	// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
	printf("%d\n",ans.size());
	for(int u:ans)printf("%d\n",u-1);
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