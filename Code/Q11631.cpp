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

int n,m,a[maxn],ans;
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
int d[maxn],id[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		int u=read()+1,v=read()+1;
		f[fd(u)]=fd(v);
	}
	int num=0;for(int i=1;i<=n;i++)num+=f[i]==i;
	if(num==1){puts("0");return ;}
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return a[u]<a[v];});
	int cnt=num,sum=2*(num-1);
	for(int ii=1;ii<=n;ii++){
		int i=id[ii],u=fd(i);
		if(d[u]+1<num&&cnt-(!d[u])<sum)cnt-=(!d[u]),sum--,d[u]++,ans+=a[i];
		// cout<<i<<" "<<d[u]<<" "<<cnt<<"\n";
	}
	if(cnt||sum){puts("Impossible");return ;}
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