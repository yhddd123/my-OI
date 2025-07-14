#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn],s;
int b[maxn],len;
struct ask{
	int l,r,id;
}p[maxn];
bool cmp(ask u,ask v){
	if(u.l/s==v.l/s){
		if((u.l/s)&1)return u.r<v.r;
		return u.r>v.r;
	}
	return u.l<v.l;
}
int ans[maxn];
int t[maxn],cnt[maxn],l=1,r=0,res;
void add(int x){
	cnt[t[x]]--;t[x]++;cnt[t[x]]++;
	if(res<t[x])res=t[x];
}
void del(int x){
	cnt[t[x]]--;t[x]--;cnt[t[x]]++;
	if(cnt[res]==0)res--;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();s=sqrt(n);
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=a[i];
	sort(b+1,b+n+1);len=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+len+1,a[i])-b;
	for(int i=1;i<=m;i++)p[i]={read(),read(),i};
	sort(p+1,p+m+1,cmp);
	cnt[0]=n;
	for(int i=1;i<=m;i++){
		while(l>p[i].l)add(a[--l]);
		while(r<p[i].r)add(a[++r]);
		while(l<p[i].l)del(a[l++]);
		while(r>p[i].r)del(a[r--]);
		ans[p[i].id]=res;
	}
	for(int i=1;i<=n;i++)printf("%lld\n",-ans[i]);
}
