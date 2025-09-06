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
const int inf=1e15;
bool mbe;

int n,m,k,v;
int a[maxn],b[maxn],h[maxn];
bool check(int x){
	priority_queue<pii,vector<pii>,greater<pii>> q;
	for(int i=1;i<=n;i++)b[i]=x;
	for(int i=1;i<=n;i++) if(b[i]-a[i]*m<h[i]) q.push({b[i]/a[i]+1,i});
	for(int i=1;i<=m;i++){
		for(int j=1;j<=k;j++)if(q.size()){
			int p=q.top().se;q.pop();
			if(b[p]-a[p]*i<0)return 0;
			b[p]+=v;
			if(b[p]-a[p]*m<h[p]) q.push({b[p]/a[p]+1,p});
		}
	}
	return !q.size();
}
void work(){
	n=read();m=read();k=read();v=read();
	for(int i=1;i<=n;i++)h[i]=read(),a[i]=read();
	int l=0,r=inf,res=inf;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))res=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",res);
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