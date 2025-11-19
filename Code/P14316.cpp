// Problem: P14316 [Aboi Round 2] 礎の花冠
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14316
// Memory Limit: 128 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-11-18 15:03:08
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
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=400010;
const int B=640;
const int maxm=maxn/B+5;
const int inf=1e9;
bool mbe;

int n,m=400001,q,a[maxn];
vector<pii> ask[maxn];
int ans[maxn];
int lst[maxn],pos[maxn];
int addv[maxn],addb[maxm];
inline void upd(int p,int w){addv[p]+=w,addb[p/B]+=w;}
inline int que(int p){
	int id=p/B,ans=0;
	int pr=min(m,(id+1)*B);
	for(int i=p;i<pr;i++)ans+=addv[i];
	pr=m/B;
	for(int i=id+1;i<=pr;i++)ans+=addb[i];
	return ans;
}
inline void chk(int p,int w){
	if(lst[p]<w){
		upd(lst[p],-1),lst[p]=w,upd(lst[p],1);
	}
}
int stv[maxm][10][B+5],stb[10][maxm];
inline int quev(int id,int l,int r){
	int k=__lg(r-l+1);
	return max(stv[id][k][l],stv[id][k][r-(1<<k)+1]);
}
inline int queb(int l,int r){
	int k=__lg(r-l+1);
	return max(stb[k][l],stb[k][r-(1<<k)+1]);
}
inline int que(int l,int r){
	int idl=l/B,idr=r/B;
	if(idl==idr)return quev(idl,l-idl*B,r-idl*B);
	int res=0;
	res=max(res,quev(idl,l-idl*B,B-1));
	if(idl+1<=idr-1)res=max(res,queb(idl+1,idr-1));
	res=max(res,quev(idr,0,r-idr*B));
	return res;
}
void mdf(int p,int w){
	int id=p/B;p-=id*B;
	stv[id][0][p]=w;
	for(int i=1;i<10;i++){
		int pl=max(0,p-(1<<i)+1),pr=min(B-1-(1<<i)+1,p);
		for(int j=pl;j<=pr;j++)stv[id][i][j]=max(stv[id][i-1][j],stv[id][i-1][j+(1<<i-1)]);
	}
	stb[0][id]=quev(id,0,B-1);
	for(int i=1;i<10;i++){
		int pl=max(0,id-(1<<i)+1),pr=min(m/B-(1<<i)+1,id);
		for(int j=pl;j<=pr;j++)stb[i][j]=max(stb[i-1][j],stb[i-1][j+(1<<i-1)]);
	}
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		ask[r].pb({l,i});
	}
	for(int i=1;i<=n;i++){
		mdf(a[i],i);
		for(int l=1;l*l<=a[i];l++){
			int x=a[i]/l;
			chk(x,pos[l]);
		}
		for(int x=1,r=a[i],l;x*x<=a[i];x++,r=l-1){
			l=a[i]/(x+1)+1;
			chk(x,que(l,r));
		}
		if(a[i]<=B){
			for(int j=pos[a[i]]+1;j<i;j++)chk(a[j]/a[i],j);
		}
		else{
			for(int k=0;k*a[i]<=m;k++)chk(k,que(k*a[i],min(m,(k+1)*a[i]-1)));
		}
		pos[a[i]]=i;
		chk(0,que(a[i]+1,m));
		for(auto[l,id]:ask[i])ans[id]=que(l);
	}
	for(int i=1;i<=q;i++)write(ans[i]),puts("");
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