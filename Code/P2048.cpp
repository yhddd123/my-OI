#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=500010;
const int inf=1e18;
const db eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,k,l,r;
int a[maxn];
struct nd{
	int id,l,r,pos,val;
	bool operator <(const nd&tmp)const{return val<tmp.val;}
};
priority_queue<nd> q;
int ans;
namespace ST{
	int st[20][maxn];
	bool cmpmx(int u,int v){return a[u]<a[v];}
	void init(){
		for(int j=1;j<=19;j++){
			for(int i=1;i+(1<<j)-1<=n;i++){
				st[j][i]=max(st[j-1][i],st[j-1][i+(1<<j-1)],cmpmx);
			}
		}
	}
	int query(int l,int r){
		int k=log2(r-l+1);
		return max(st[k][l],st[k][r-(1<<k)+1],cmpmx);
	}
}
void work(){
	n=read();k=read();l=read();r=read();
	for(int i=1;i<=n;i++)a[i]=a[i-1]+read();
	for(int i=1;i<=n;i++)ST::st[0][i]=i;
	ST::init();
	for(int i=1;i<=n-l+1;i++){
		int pl=i+l-1,pr=min(n,i+r-1);
		int p=ST::query(pl,pr);
		q.push({i,pl,pr,p,a[p]-a[i-1]});
//		cout<<i<<" "<<a[p]-a[i-1]<<" "<<p<<"\n";
	}
	while(k--){
		nd u=q.top();q.pop();ans+=u.val;
		if(u.pos!=u.l){
			int pl=u.l,pr=u.pos-1;
			int p=ST::query(pl,pr);
			q.push({u.id,pl,pr,p,a[p]-a[u.id-1]});
			
		}
		if(u.pos!=u.r){
			int pl=u.pos+1,pr=u.r;
			int p=ST::query(pl,pr);
			q.push({u.id,pl,pr,p,a[p]-a[u.id-1]});
		}
	}
	printf("%lld\n",ans);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)work();
}
