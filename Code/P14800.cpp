// Problem: P14800 [JOI 2026 二次预选] 船 / Ship
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14800
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2026-01-23 21:11:46
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
struct ST{
	int mn[12][maxn];
	void init(){
		for(int j=1;j<12;j++){
			for(int i=1;i+(1<<j)-1<=n;i++)mn[j][i]=min(mn[j-1][i],mn[j-1][i+(1<<j-1)]);
		}
	}
	int que(int l,int r){
		if(l>r)return inf;
		int k=__lg(r-l+1);
		return min(mn[k][l],mn[k][r-(1<<k)+1]);
	}
}st[4];
int pl[4],pr[4];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	if(n&1){
		for(int i=1;i<=n/2+2;i++){
			for(int j=0;j<4;j++)st[j].mn[0][i]=a[i+(n-3)/2+j]-a[i];
		}
		for(int i=0;i<4;i++)st[i].init();
		map<int,bool> vis;for(int i=1;i<=n;i++)vis[a[i]]=1;
		int ans=-1;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				int k=0;
				if(vis.find(2*a[i]-a[j])!=vis.end()){
					k=lower_bound(a+1,a+n+1,2*a[i]-a[j])-a;
					pl[0]=1,pr[0]=k-1;
					pl[1]=k+1,pr[1]=i-1;
					pl[2]=i+1,pr[2]=j-1;
					pl[3]=j+1,pr[3]=n;
				}
				if(vis.find(2*a[j]-a[i])!=vis.end()){
					k=lower_bound(a+1,a+n+1,2*a[j]-a[i])-a;
					pl[0]=1,pr[0]=i-1;
					pl[1]=i+1,pr[1]=j-1;
					pl[2]=j+1,pr[2]=k-1;
					pl[3]=k+1,pr[3]=n;
				}
				if(!k)continue;
				int res=a[j]-a[i];
				for(int i=0;i<4;i++){
					for(int j=i;j<4;j++){
						int l=max(pl[i]-i,pl[j]-j-(n-3)/2)+i,r=min(pr[i]-i,pr[j]-j-(n-3)/2)+i;
						if(l>r)continue;
						// cout<<i<<" "<<j<<" "<<l<<" "<<r<<" "<<st[j-i].que(l,r)<<"\n";
						res=min(res,st[j-i].que(l,r));
					}
				}
				// cout<<i<<" "<<j<<" "<<k<<" "<<res<<"\n";
				ans=max(ans,res);
			}
		}
		printf("%lld\n",ans);
	}
	else{
		int ans=inf;
		for(int i=1;i<=n/2;i++)ans=min(ans,a[i+n/2]-a[i]);
		printf("%lld\n",ans);
	}
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