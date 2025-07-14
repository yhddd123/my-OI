#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
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

int n,m;
int a[maxn],b[maxn];
int id[maxn],num,tmp[maxn];
int f[maxn][210];
struct ask{
	int l,r,t;
}p[maxn];
int ans[maxn];
void sovle(int l,int r,int ql,int qr){
	if(ql>qr)return ;
	int mid=l+r>>1,qmid=ql-1;
	for(int j=0;j<=200;j++)f[mid][j]=0;
	for(int i=mid+1;i<=r;i++){
		for(int j=0;j<a[i];j++)f[i][j]=f[i-1][j];
		for(int j=a[i];j<=200;j++)f[i][j]=max(f[i-1][j],f[i-1][j-a[i]]+b[i]);
	}
	for(int j=a[mid];j<=200;j++)f[mid][j]=b[mid];
	for(int i=mid-1;i>=l;i--){
		for(int j=0;j<a[i];j++)f[i][j]=f[i+1][j];
		for(int j=a[i];j<=200;j++)f[i][j]=max(f[i+1][j],f[i+1][j-a[i]]+b[i]);
	}
	int tr=0;
	for(int i=ql;i<=qr;i++){
		if(p[id[i]].r<=mid)id[++qmid]=id[i];
		else if(p[id[i]].l>mid)tmp[++tr]=id[i];
		else{
			for(int j=0;j<=p[id[i]].t;j++)ans[id[i]]=max(ans[id[i]],f[p[id[i]].l][j]+f[p[id[i]].r][p[id[i]].t-j]);
//			cout<<id[i]<<" "<<ans[id[i]]<<"\n";
		}
	}
	for(int i=1;i<=tr;i++)id[qmid+i]=tmp[i];
	qr=tr+qmid;
	sovle(l,mid,ql,qmid);sovle(mid+1,r,qmid+1,qr);
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=m;i++){
		p[i]={read(),read(),read()};
		if(p[i].l==p[i].r)ans[i]=(p[i].t>=a[p[i].l])?b[p[i].l]:0;
		else id[++num]=i;
	}
	sovle(1,n,1,num);
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
