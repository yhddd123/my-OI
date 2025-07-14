// Problem: P5047 [Ynoi2019 模拟赛] Yuno loves sqrt technology II
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5047
// Memory Limit: 31 MB
// Time Limit: 250000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=101000;
const int maxm=320;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn],s;
struct ask{
	int l,r,id;
}q[maxn];
int ans[maxn];
bool cmp(ask u,ask v){
	if(u.l/s==v.l/s){
		if((u.l/s)&1)return u.r>v.r;
		return u.r<v.r;
	}
	return u.l<v.l;
}
struct nd{
	int l,r,p,id;
};
vector<nd> al[maxn],ar[maxn];
vector<int> lsh;
struct bit{
	int c[maxn];
	int lowbit(int x){return x&(-x);}
	void updata(int x,int w){while(x<=n)c[x]+=w,x+=lowbit(x);}
	int query(int x){int res=0;while(x)res+=c[x],x-=lowbit(x);return res;}
	void clr(){mems(c,0);}
}b;
int id[maxn],idl[maxm],idr[maxm];
int sum[maxm],tot[maxn],sl[maxn],sr[maxn];
// time_t st,ed;
void work(){
	n=read();m=read();s=317;
	for(int i=1;i<=n;i++)a[i]=read(),lsh.push_back(a[i]);
	sort(lsh.begin(),lsh.end());lsh.erase(unique(lsh.begin(),lsh.end()),lsh.end());
	for(int i=1;i<=n;i++)a[i]=lower_bound(lsh.begin(),lsh.end(),a[i])-lsh.begin()+1;
	for(int i=1;i<=n;i++){
		sl[i]=sl[i-1]+b.query(n)-b.query(a[i]);
		b.updata(a[i],1);
	}
	b.clr();
	for(int i=n;i>=1;i--){
		sr[i]=sr[i+1]+b.query(a[i]-1);
		b.updata(a[i],1);
	}
	for(int i=1;i<=m;i++)q[i]={read(),read(),i};
	sort(q+1,q+m+1,cmp);
	for(int i=1,l=1,r=0;i<=m;i++){
		ans[q[i].id]=sl[q[i].r]-sl[r]+sr[q[i].l]-sr[l];
		 // cout<<ans[q[i].id]<<"\n";
		if(q[i].r>r)ar[l-1].push_back({r+1,q[i].r,1,q[i].id});
		if(q[i].r<r)ar[l-1].push_back({q[i].r+1,r,-1,q[i].id});
		r=q[i].r;
		if(l>q[i].l)al[r+1].push_back({q[i].l,l-1,1,q[i].id});
		if(l<q[i].l)al[r+1].push_back({l,q[i].l-1,-1,q[i].id});
		l=q[i].l;
	}
	for(int i=1;i<=s;i++){
		idl[i]=(i-1)*s+1,idr[i]=i*s;
		for(int j=idl[i];j<=idr[i];j++)id[j]=i;
	}
	// cout<<idr[s]<<"\n";
	for(int i=1;i<=n;i++){
		for(int j=1;j<id[a[i]];j++)++sum[j];
		for(int j=idl[id[a[i]]];j<=a[i];j++)++tot[j];
		for(nd j:ar[i]){
			for(int k=j.l;k<=j.r;k++)ans[j.id]+=-j.p*(sum[id[a[k]+1]]+tot[a[k]+1]);
		}
	}
	mems(sum,0);mems(tot,0);
	for(int i=n;i>=1;i--){
		for(int j=id[a[i]]+1;j<=s;j++)++sum[j];
		for(int j=a[i];j<=idr[id[a[i]]];j++)++tot[j];
		for(nd j:al[i]){
			for(int k=j.l;k<=j.r;k++)ans[j.id]+=-j.p*(sum[id[a[k]-1]]+tot[a[k]-1]);
		}
	}
	for(int i=2;i<=m;i++)ans[q[i].id]+=ans[q[i-1].id];
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
}

// \
444

bool Med;
int T;
signed main(){
	 // freopen("P5047_2.in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
