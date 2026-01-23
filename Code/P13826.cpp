// Problem: P13826 [Ynoi Easy Round 2026] 寒蝉鸣泣之时
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P13826
// Memory Limit: 512 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2026-01-23 11:17:40
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define ll long long
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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,m;
ll ans[maxn];
vector<tuple<int,int,int>> upd[maxn];
const int B=500;
const int maxm=maxn/B+1;
int pl[maxm],pr[maxm],num,bel[maxn];
int val[maxn];
short t[maxm][maxn];
int mn[maxm],mx[maxm],tag[maxm];
void down(int id){
	int l=pl[id],r=pr[id];
	for(int i=l;i<=r;i++)t[id][val[i]]=0;
	if(tag[id]){
		mn[id]+=tag[id],mx[id]+=tag[id];
		for(int i=l;i<=r;i++)val[i]+=tag[id];tag[id]=0;
	}
}
void init(int id){
	int l=pl[id],r=pr[id];
	for(int i=l;i<=r;i++)t[id][val[i]]++;
	mn[id]=val[l],mx[id]=val[l];
	for(int i=l+1;i<=r;i++)mn[id]=min(mn[id],val[i]),mx[id]=max(mx[id],val[i]);
}
void mdf(int l,int r,int w){
	if(bel[l]==bel[r]){
		down(bel[l]);
		for(int i=l;i<=r;i++)val[i]+=w;
		init(bel[l]);
	}
	else{
		down(bel[l]);
		for(int i=l;i<=pr[bel[l]];i++)val[i]+=w;
		init(bel[l]);
		for(int i=bel[l]+1;i<bel[r];i++)tag[i]+=w;
		down(bel[r]);
		for(int i=pl[bel[r]];i<=r;i++)val[i]+=w;
		init(bel[r]);
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		int l1=read(),r1=read()-1,l2=read(),r2=read()-1;
		upd[l1].pb({l2,r2,1}),upd[r1+1].pb({l2,r2,-1});
	}
	for(int l=1,r;l<=n;l=r+1){
		r=min(l+B-1,n);pl[++num]=l,pr[num]=r;
		for(int i=l;i<=r;i++)bel[i]=num;
		mn[num]=mx[num]=0;t[num][0]=r-l+1;
	}
	for(int i=1;i<=n;i++){
		for(auto[l,r,w]:upd[i])mdf(l,r,w);
		for(int i=1;i<=num;i++){
			int vl=(mn[i]+tag[i]+m-1)/m*m,vr=(mx[i]+tag[i])/m*m;
			// cout<<mn[i]<<" "<<mx[i]<<" "<<tag[i]<<" "<<vl<<" "<<vr<<"\n";
			for(int j=vl;j<=vr;j+=m)ans[j/m]+=t[i][j-tag[i]];
		}
		// for(int i=1;i<=n;i++)cout<<val[i]+tag[i]<<" ";cout<<"\n";
	}
	for(int i=1;i<=n/m;i++)printf("%lld\n",ans[i]);
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