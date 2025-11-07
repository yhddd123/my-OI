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
const int maxn=100010;
const int B=300;
const int maxm=1<<20;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
struct ask{
	int l,r,id;
}que[maxn];
int res,t[2][maxm];
void add(int p){
	res+=t[p&1][a[p]];
	t[p&1][a[p]]++;
	// cout<<p<<" "<<a[p]<<" "<<t[p&1][a[p]]<<" "<<res<<"\n";
}
void del(int p){
	t[p&1][a[p]]--;
	res-=t[p&1][a[p]];
}
int ans[maxn];
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=(read()-1)^a[i-1];
	// for(int i=0;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
	for(int i=1;i<=q;i++)que[i]={read()-1,read(),i};
	sort(que+1,que+q+1,[&](ask u,ask v){
		if(u.l/B==v.l/B){
			if((u.l/B)&1)return u.r>v.r;
			return u.r<v.r;
		}
		return u.l<v.l;
	});
	for(int i=1,l=1,r=0;i<=q;i++){
		while(r<que[i].r)add(++r);
		while(l>que[i].l)add(--l);
		while(r>que[i].r)del(r--);
		while(l<que[i].l)del(l++);
		// cout<<l<<" "<<r<<" "<<res<<"\n";
		ans[que[i].id]=(r-l)*(r-l+1)/2-res;
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
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