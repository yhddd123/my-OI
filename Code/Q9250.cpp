#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=150010;
const int maxm=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q,B;
vector<int> a[maxm];
vector<pii> upd[maxn];
int id[maxn],pl[maxn],pr[maxn];
struct ask{
	int l,r,id;
}que[maxn];
int ans[maxn],mx[maxn],mx1[maxn];
void work(){
	n=read();q=read();B=500;
	for(int i=1;i<=n;i++){
		int x=read();
		for(int j=1;j*j<=x;j++)if(x%j==0){
			a[j].pb(i);
			if(j*j!=x)a[x/j].pb(i);
		}
	}

	for(int i=1;i<=maxm-10;i++)if(a[i].size()>2){
		// cout<<i<<" "<<a[i].size()<<endl;
		for(int j=(int)a[i].size()-2,k=a[i].size();j;j--){
			while(k>j&&a[i][k-1]-a[i][j]>=a[i][j]-a[i][j-1])k--;
			// cout<<i<<" "<<j<<" "<<k<<endl;
			if(k<a[i].size())upd[a[i][j-1]].pb({a[i][k],i});
		}
	}
	for(int l=1,r,num=0;l<=n;l=r+1){
		r=min(n,l+B-1);++num;
		pl[num]=l,pr[num]=r;
		for(int j=l;j<=r;j++)id[j]=num;
	}
	for(int i=1;i<=q;i++)que[i]={read(),read(),i};
	sort(que+1,que+q+1,[&](ask u,ask v){return u.l>v.l;});
	for(int i=1,p=n;i<=q;i++){
		while(p>=que[i].l){
			for(auto[r,v]:upd[p])mx[r]=max(mx[r],v),mx1[id[r]]=max(mx1[id[r]],v);
			p--;
		}
		for(int j=id[que[i].l];j<=id[que[i].r]-1;j++)ans[que[i].id]=max(ans[que[i].id],mx1[j]);
		for(int j=pl[id[que[i].r]];j<=que[i].r;j++)ans[que[i].id]=max(ans[que[i].id],mx[j]);
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
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
