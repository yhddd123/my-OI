#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,k,ans;
int a[maxn],b[maxn];
char s[maxn];
vector<int> pos[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
	int pre,suf,mx,len;
}tree[maxn<<2];
node merge(node u,node v){
	if(!u.len)return v;
	if(!v.len)return u;
	node res;res.len=u.len+v.len;
	res.mx=max({u.mx,v.mx,u.suf+v.pre});
	res.pre=(u.mx==u.len?u.len+v.pre:u.pre);
	res.suf=(v.mx==v.len?v.len+u.suf:v.suf);
	return res;
}
void updata(int nd,int l,int r,int p,bool fl){
	if(l==r){
		if(fl)tree[nd].mx=tree[nd].pre=tree[nd].suf=1;
		tree[nd].len=1;
		return ;
	}
	if(p<=mid)updata(ls,l,mid,p,fl);
	else updata(rs,mid+1,r,p,fl);
	tree[nd]=merge(tree[ls],tree[rs]);
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read(),pos[a[i]].pb(i);
	scanf("%s",s+1);
	for(int i=maxn-10;~i;i--){
		for(int j:pos[i])updata(1,1,n,j,s[j]=='1');
		if(tree[1].mx>=k){
			printf("%lld\n",i);
			return ;
		}
	}
	puts("0");
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
