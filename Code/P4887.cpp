// Problem: P4887 【模板】莫队二次离线（第十四分块(前体)）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4887
// Memory Limit: 40 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
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

int n,m,k,s;
int a[maxn];
struct ask{
	int l,r,id;
}q[maxn];
int ans[maxn];
bool cmp(ask u,ask v){
	if(u.l/s==v.l/s){
		if((u.l/s)&1)return u.r<v.r;
		return u.r>v.r;
	}
	return u.l/s<v.l/s;
}
struct nd{
	int l,r,p,id;
};
vector<int> val;
vector<nd> al[maxn],ar[maxn];
int t[maxn],num[maxn];
void work(){
	n=read();m=read();k=read();s=sqrt(n);
	for(int i=1;i<=n;i++)a[i]=read();
	if(k>14){
		for(int i=1;i<=m;i++)printf("0\n");
		return ;
	}
	for(int i=0;i<=16384;i++)if(__builtin_popcount(i)==k)val.push_back(i);
	for(int i=1;i<=m;i++)q[i]={read(),read(),i};
	sort(q+1,q+m+1,cmp);
	for(int i=1,l=1,r=0;i<=m;i++){
		if(l>q[i].l)al[r].push_back({q[i].l,l-1,1,q[i].id});
		if(l<q[i].l)al[r].push_back({l,q[i].l-1,-1,q[i].id});
		l=q[i].l;
		if(r<q[i].r)ar[l].push_back({r+1,q[i].r,1,q[i].id});
		if(r>q[i].r)ar[l].push_back({q[i].r+1,r,-1,q[i].id});
		r=q[i].r;
	}
	for(int i=1;i<=n;i++){
		num[i]=t[a[i]];
		for(int j:val)t[a[i]^j]++;
	}
	mems(t,0);
	for(int i=1;i<=n;i++){
		for(nd j:ar[i]){
			for(int k=j.l;k<=j.r;k++){
				ans[j.id]+=j.p*(num[k]-t[a[k]]);
			}
		}
		for(int j:val)t[a[i]^j]++;
	}
	mems(t,0);
	for(int i=n;i>=1;i--){
		num[i]=t[a[i]];
		for(int j:val)t[a[i]^j]++;
	}
	mems(t,0);
	for(int i=n;i>=1;i--){
		for(nd j:al[i]){
			for(int k=j.l;k<=j.r;k++){
				ans[j.id]+=j.p*(num[k]-t[a[k]]);
			}
		}
		for(int j:val)t[a[i]^j]++;
	}
	for(int i=2;i<=m;i++)ans[q[i].id]+=ans[q[i-1].id];
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
