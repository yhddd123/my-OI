#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=400010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
int x[maxn],y[maxn],k[maxn];
bool vis[maxn],bk[maxn];
int sum[maxn];
queue<int> q;int ans,B;
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
vector<int> tree[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,int id){
	if(l>=ql&&r<=qr){tree[nd].push_back(id);return ;}
	if(ql<=mid)updata(ls,l,mid,ql,qr,id);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,id);
}
void modif(int nd,int l,int r,int p){
	vector<int> nw;
	for(int i:tree[nd])if(k[i]){
		k[i]--;
		if(k[i])nw.push_back(i);
		else q.push(i);
	}
	tree[nd]=nw;
	if(l==r)return ;
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
}
void work(){
	n=read();B=sqrt(n);
	for(int i=1;i<=n;i++)x[i]=read(),y[i]=read(),k[i]=read();
	for(int i=1;i<=n;i++)if(!k[i])q.push(i),bk[i]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		// cout<<u<<" "<<ans<<"\n";
		if(ans%B==0){
			for(int i=1;i<=n;i++)sum[i]=sum[i-1]+vis[i];
			for(int i=1;i<=n;i++)if(!bk[i]){
				if(sum[y[i]]-sum[x[i]-1]+B>=k[i]){
					k[i]-=sum[y[i]]-sum[x[i]-1];
					updata(1,1,n,x[i],y[i],i);
					bk[i]=1;
				}
			}
		}
		++ans;
		modif(1,1,n,u);vis[u]=1;
	}
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("Q8035_3.in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
