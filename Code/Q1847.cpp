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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,m;
vector<int> a[maxn];
bool ans[maxn];
int vis[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int k=read();a[i].resize(k);
		for(int j=0;j<k;j++)a[i][j]=read();
	}
	sort(a+1,a+m+1,[&](vector<int> u,vector<int> v){return u.size()<v.size();});
	for(int i=1;i<=m;i++){
		map<int,int> mp;
		int s=0;
		for(int j:a[i])if(vis[j])mp[vis[j]]+=(ans[j])-(!ans[j]),s+=(ans[j])-(!ans[j]);
		for(auto[id,v]:mp)if(abs(s)>1&&v*s>0){
			s-=2*v;
			for(int j:a[id])ans[j]=!ans[j];
		}
		s=(s<0);
		for(int j:a[i])if(!vis[j])ans[j]=s,s^=1;
		for(int j:a[i])vis[j]=i;
	}
	for(int i=1;i<=n;i++)if(!vis[i])ans[i]=0;
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
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