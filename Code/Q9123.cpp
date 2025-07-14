#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=50010;
const int inf=3e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,k,B;
int a[maxn],b[maxn],c[maxn];
priority_queue<pii> q;
int pos[maxn];
int d[maxn*200],tp;
int f(int x){
	int res=0;
	for(int i=1,j=n;b[i]+c[1]<=x&&i<=n;i++){
		while(b[i]+c[j]>x)j--;
		res+=j;
	}
	return res;
}
bool check(int x){
	int sum=f(x-a[B]);
	if(sum*B>=k)return 1;
	for(int i=1;i<B;i++){
		sum+=f(x-a[i]);
		if(sum>=k)return 1;
	}
	for(int i=1,j=n;i<=tp&&j>B;i++){
		while(j>B&&a[j]+d[i]>x)j--;
		sum+=j-B;
		if(sum>=k)return 1;
	}
	return 0;
}
void work(){
	n=read();k=read();B=min(n,(int)sqrt(k/n)+1);
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();
	sort(a+1,a+n+1),sort(b+1,b+n+1),sort(c+1,c+n+1);
	for(int i=1;i<=n;i++)q.push({-(b[i]+c[pos[i]=1]),i});
	while(!q.empty()&&tp<k/B){
		d[++tp]=-q.top().fi;
		int u=q.top().se;q.pop();
		if(pos[u]<n)q.push({-(b[u]+c[++pos[u]]),u});
	}
	// for(int i=1;i<=tp;i++)cout<<d[i]<<" ";cout<<"\n";
	int l=0,r=inf,res=inf;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))res=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",res);
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
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
