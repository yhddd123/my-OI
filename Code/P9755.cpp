#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=100010;
const int inf=1e9;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
	return x*fl;
}

int n,m;
int a[maxn],b[maxn],c[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int t[maxn];
void dfs(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		dfs(v,u);
		t[u]=min(t[u],t[v]-1);
	}
}
bool check2(int d,int i,int x){
	if(!c[i])return (x-d+1)*b[i]>=a[i];
	if(c[i]>0)return ((x-d+1)*b[i]+(__int128)c[i]*(x+d)*(x-d+1)/2)>=a[i];
	if(c[i]<0){
		int p=(b[i]-1)/(-c[i])+1;
		if(p<=x){
			if(p<=d)return x-d+1>=a[i];
			return ((x-p+1)+b[i]*(p-d)+(__int128)c[i]*(p-1+d)*(p-d)/2)>=a[i];
		}
		else return ((x-d+1)*b[i]+(__int128)c[i]*(x+d)*(x-d+1)/2)>=a[i];
	}
}
bool check(int x){
	// cout<<x<<"\n";
	for(int i=1;i<=n;i++){
		int l=0,r=x,mid,ans=0;
		while(l<=r){
			mid=l+r>>1;
			if(check2(mid,i,x)){
				ans=mid;
				l=mid+1;
			}
			else r=mid-1;
		}
		t[i]=ans;
		if(t[i]<=0)return false;
	}
	dfs(1,0);
	sort(t+1,t+n+1);
	for(int i=1;i<=n;i++)if(i>t[i])return false;
	return true;
}

signed main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read(),c[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	int l=0,r=inf,mid,ans=r;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%lld\n",ans);
}
