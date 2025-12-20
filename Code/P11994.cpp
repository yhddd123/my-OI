// Problem: P11994 [JOIST 2025] 外郎糕 / Uiro
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11994
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-12-18 12:42:12
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn],b[maxn];
vector<int> pos[110];
int l[maxn],r[maxn],p[maxn],w[maxn],ans[maxn];
int mn[18][maxn],pre[maxn];
int quemn(int l,int r){
	if(l>r)return inf;
	int k=__lg(r-l+1);
	return min(mn[k][l],mn[k][r-(1<<k)+1]);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)pos[a[i]].pb(i);
	q=read();
	for(int i=1;i<=q;i++)l[i]=read(),r[i]=read(),p[i]=l[i]-1;
	for(int v=1;v<=100;v++)if(pos[v].size()){
		for(int i=1;i<=n;i++)b[i]=a[i]+b[i-1];
		for(int i=1,mn=inf;i<=n;i++){
			if(a[i]==v)mn=inf;
			mn=min(mn,b[i]);
			pre[i]=mn;
		}
		int sz=pos[v].size();
		for(int i=0;i<sz;i++)mn[0][i]=pre[i+1==sz?n:pos[v][i+1]-1]-2*i*v;
		for(int j=1;(1<<j)<=sz;j++){
			for(int i=0;i+(1<<j)-1<sz;i++)mn[j][i]=min(mn[j-1][i],mn[j-1][i+(1<<j-1)]);
		}
		for(int i=1;i<=q;i++){
			int pl=upper_bound(pos[v].begin(),pos[v].end(),p[i])-pos[v].begin(),pr=upper_bound(pos[v].begin(),pos[v].end(),r[i])-pos[v].begin()-1;
			// cout<<v<<" "<<i<<" "<<p[i]<<" "<<w[i]<<"\n";
			if(pl>pr)continue;
			int ll=pl,rr=pr,res=pr+1;
			auto check=[&](int x){
				// cout<<x<<" "<<quemn(x,pr)-b[p[i]]<<"\n";
				return -b[p[i]]+w[i]+quemn(x,pr-1)-2*(-x+1)*v>=0&&pre[r[i]]-b[p[i]]+w[i]-2*(pr-x+1)*v>=0;
			};
			while(ll<=rr){
				int mid=ll+rr>>1;
				if(check(mid))rr=mid-1,res=mid;
				else ll=mid+1;
			}
			ans[i]+=pr-res+1;
			// cout<<v<<" "<<i<<" "<<res<<" "<<p[i]<<" "<<w[i]<<" "<<ans[i]<<"\n";
			if(res==pl)continue;
			w[i]+=b[pos[v][res-1]]-b[p[i]];p[i]=pos[v][res-1];
		}
		for(int i:pos[v])a[i]=-a[i];
	}
	for(int i=1;i<=n;i++)b[i]=a[i]+b[i-1];
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
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