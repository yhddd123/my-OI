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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m,k,ans;
pii edge[maxn];
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
void sovle(int a,int b){
	if(!b){ans=-1;return ;}
	if(b<=k+1){
		for(int i=0;i<b;i++)f[i]=i;
		for(int i=1;i<=k;i++)f[fd(edge[i].fi%b)]=fd(edge[i].se%b);
		int num=0;for(int i=0;i<b;i++)num+=f[i]==i;
		if(num==1){
			auto check=[&](int x){
				if(a-x+min(b,x)>k+1)return 0;
				for(int i=0;i<a-x+min(b,x);i++)f[i]=i;
				// cout<<x<<" "<<a-x+min(b,x)<<" chk\n";
				for(int i=1;i<=k;i++){
					auto[u,v]=edge[i];
					if(u<x)u=u%b;
					else u=u-x+min(b,x);
					if(v<x)v=v%b;
					else v=v-x+min(b,x);
					f[fd(u)]=fd(v);
				}
				int num=0;for(int i=0;i<a-x+min(b,x);i++)num+=f[i]==i;
				if(num==1)return 1;
				return 0;
			};
			int l=1,r=a-b-1,res=a-b;
			while(l<=r){
				int mid=l+r>>1;
				if(check(mid+b))res=mid,r=mid-1;
				else l=mid+1;
			}
			ans+=res;
			// cout<<a<<" "<<b<<" "<<res<<"\n";
			return ;
		}
	}
	ans+=a-b;
	// cout<<a<<" "<<b<<" "<<ans<<"\n";
	for(int i=1;i<=k;i++)edge[i].fi%=b,edge[i].se%=b;
	sovle(b,a%b);
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=k;i++)edge[i]={read(),read()+n};
	sovle(n+m,n);
	printf("%lld\n",ans);
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