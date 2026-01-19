// Problem: P7564 [JOISC 2021] ボディーガード (Day3)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7564
// Memory Limit: 3901 MB
// Time Limit: 25000 ms
// Written by yhm.
// Start codeing:2026-01-19 09:22:10
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
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
const int maxn=5610;
const int inf=2e9;
bool mbe;

int n,q;
int t[maxn],a[maxn],b[maxn],c[maxn];
int lshx[maxn],lenx,lshy[maxn],leny;
int f[maxn][maxn];
int e[maxn][maxn],g[maxn][maxn];
const int maxq=3000010;
int ans[maxq];
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
struct line{
	int k,b;
	int calc(int x){return k*x+b;}
}tree[maxn<<6];
int lc[maxn<<6],rc[maxn<<6],idx,rt;
void updata(int &nd,int l,int r,line w){
	if(!nd){tree[nd=++idx]=w;return ;}
	if(tree[nd].calc(mid)<=w.calc(mid))swap(tree[nd],w);
	if(l==r)return ;
	if(tree[nd].calc(l)<=w.calc(l))updata(ls,l,mid,w);
	else updata(rs,mid+1,r,w);
}
int query(int nd,int l,int r,int p){
	if(!nd)return 0;
	if(l==r)return tree[nd].calc(p);
	if(p<=mid)return max(tree[nd].calc(p),query(ls,l,mid,p));
	else return max(tree[nd].calc(p),query(rs,mid+1,r,p));
}
void clr(){
	while(idx)tree[idx]={0,0},lc[idx]=rc[idx]=0,idx--;
	rt=0;
}
vector<tuple<int,int,int>> ask1[maxn],ask2[maxn];  
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++){
		t[i]=read(),a[i]=read(),b[i]=read(),c[i]=read()/2;
		// cout<<t[i]-a[i]<<" "<<t[i]+a[i]<<" "<<t[i]+abs(a[i]-b[i])-b[i]<<" "<<t[i]+abs(a[i]-b[i])+b[i]<<"\n";
		lshx[++lenx]=t[i]-a[i],lshy[++leny]=t[i]+a[i];
		lshx[++lenx]=t[i]+abs(a[i]-b[i])-b[i],lshy[++leny]=t[i]+abs(a[i]-b[i])+b[i];
	}
	sort(lshx+1,lshx+lenx+1),lenx=unique(lshx+1,lshx+lenx+1)-lshx-1;
	sort(lshy+1,lshy+leny+1),leny=unique(lshy+1,lshy+leny+1)-lshy-1;
	for(int i=1;i<=n;i++){
		int sx=lower_bound(lshx+1,lshx+lenx+1,t[i]-a[i])-lshx,sy=lower_bound(lshy+1,lshy+leny+1,t[i]+a[i])-lshy;
		int ex=lower_bound(lshx+1,lshx+lenx+1,t[i]+abs(a[i]-b[i])-b[i])-lshx,ey=lower_bound(lshy+1,lshy+leny+1,t[i]+abs(a[i]-b[i])+b[i])-lshy;
		// cout<<sx<<" "<<sy<<" "<<ex<<" "<<ey<<"\n";
		if(sx==ex){
			for(int j=sy+1;j<=ey;j++)e[sx][j]=max(e[sx][j],c[i]);
		}
		else{
			for(int j=sx+1;j<=ex;j++)g[j][sy]=max(g[j][sy],c[i]);
		}
	}
	for(int i=lenx;i;i--){
		for(int j=leny;j;j--){
			f[i][j-1]=max(f[i][j-1],f[i][j]+e[i][j]*(lshy[j]-lshy[j-1]));
			f[i-1][j]=max(f[i-1][j],f[i][j]+g[i][j]*(lshx[i]-lshx[i-1]));
		}
	}
	// for(int i=1;i<=lenx;i++)cout<<lshx[i]<<" ";cout<<"\n";
	// for(int i=1;i<=leny;i++)cout<<lshy[i]<<" ";cout<<"\n";
	for(int i=1;i<=q;i++){
		int t=read(),p=read(),x=t-p,y=t+p;
		int px=lower_bound(lshx+1,lshx+lenx+1,x)-lshx,py=lower_bound(lshy+1,lshy+leny+1,y)-lshy;
		// cout<<x<<" "<<y<<" "<<px<<" "<<py<<"\n";
		if(px<=lenx&&py<=leny)ask1[py].pb({px,y,i}),ask2[px].pb({py,x,i});
	}
	for(int i=1;i<=leny;i++){
		sort(ask1[i].begin(),ask1[i].end());
		clr();
		for(int j=lenx,k=ask1[i].size()-1;j&&(~k);j--){
			updata(rt,-inf,inf,{-e[j][i],f[j][i]+e[j][i]*lshy[i]});
			while(k>=0){
				auto[px,y,id]=ask1[i][k];
				if(px!=j)break;
				ans[id]=max(ans[id],query(rt,-inf,inf,y));
				k--;
			}
		}
	}
	for(int i=1;i<=lenx;i++){
		sort(ask2[i].begin(),ask2[i].end());
		clr();
		for(int j=leny,k=ask2[i].size()-1;j&&(~k);j--){
			updata(rt,-inf,inf,{-g[i][j],f[i][j]+g[i][j]*lshx[i]});
			while(k>=0){
				auto[py,x,id]=ask2[i][k];
				if(py!=j)break;
				ans[id]=max(ans[id],query(rt,-inf,inf,x));
				k--;
			}
		}
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
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