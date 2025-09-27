#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
#define mkp make_pair
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m,w,h;
pii a[maxn],b[maxn];
pii operator-(pii u,pii v){return {u.fi-v.fi,u.se-v.se};}
inline int cross(pii u,pii v){return u.fi*v.se-u.se*v.fi;}
int l[maxn],r[maxn];
void work(){
	n=read();m=read();w=read();h=read();
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	for(int i=1;i<=m;i++)b[i]={read(),read()};
	for(int i=1;i<=w;i++)l[i]=0,r[i]=maxn-1;
	for(int i=2;i<=n;i++){
		for(int j=a[i-1].fi+1;j<a[i].fi;j++){
			int p=a[i-1].se+(a[i].se-a[i-1].se)/(a[i].fi-a[i-1].fi)*(j-a[i-1].fi);
			while(cross(mkp(j,p)-a[i-1],a[i]-a[i-1])<=0)p--;
			while(cross(mkp(j,p+1)-a[i-1],a[i]-a[i-1])>0)p++;
			p=min(j,p);
			if((j+p)&1)p--;
			p=(j-p)/2;
			l[j]=p;
		}
		int j=a[i].fi,p=a[i].se-1;
		p=min(j,p);
		if((j+p)&1)p--;
		p=(j-p)/2;
		l[j]=max(l[j],p);
	}
	for(int i=2;i<=m;i++){
		for(int j=b[i-1].fi+1;j<b[i].fi;j++){
			int p=b[i-1].se+(b[i].se-b[i-1].se)/(b[i].fi-b[i-1].fi)*(j-b[i-1].fi);
			while(cross(b[i]-b[i-1],mkp(j,p)-b[i-1])<=0)p++;
			while(cross(b[i]-b[i-1],mkp(j,p-1)-b[i-1])>0)p--;
			p=max(-j,p);
			if((j+p)&1)p++;
			p=(j-p)/2;
			r[j]=p;
		}
		int j=b[i].fi,p=b[i].se+1;
		p=max(-j,p);
		if((j+p)&1)p++;
		p=(j-p)/2;
		r[j]=min(r[j],p);
	}
	for(int i=1;i<=w;i++)if(l[i]>r[i]){puts("impossible");return ;}
	int pl=0,pr=0;
	for(int i=1;i<=w;i++){
		pr++;
		pl=max(pl,l[i]),pr=min(pr,r[i]);
		if(pl>pr){puts("impossible");return ;}
	}
	printf("%d %d\n",w-2*pr,w-2*pl);
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