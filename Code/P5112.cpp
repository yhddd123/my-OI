#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=3000010;
const int bas=44;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,k,s;
int h[maxn],pw[maxn];
int a[maxn];
unordered_map<int,int> mp;
int t[maxn],idx;
char c[maxn];
struct ask{
	int l,r,id;
	bool operator <(const ask&v)const{
		if(l/s!=v.l/s)return l<v.l;
		if((l/s)&1)return r<v.r;
		return r>v.r;
	}
}p[100010];
int sum,ans[maxn],l=1,r;

signed main(){
	n=read();m=read();k=read();
	scanf("%s",c+1);
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*bas;
	for(int i=1;i<=n;i++)h[i]=(h[i-1]*bas+c[i]-'a'+1);
	for(int i=1;i+k-1<=n;i++){
		a[i]=(h[i+k-1]-h[i-1]*pw[k]);
		if(!mp[a[i]])mp[a[i]]=++idx;
		a[i]=mp[a[i]];
	}
	s=n/sqrt(m);
	for(int i=1;i<=m;i++){
		p[i].l=read();p[i].r=read();
		p[i].r=min(p[i].r,n-k+1);
		if(p[i].l>p[i].r)p[i].l=1,p[i].r=0;
		p[i].id=i;
	}
	sort(p+1,p+m+1);
	for(int i=1;i<=m;i++){
		while(l>p[i].l)sum+=t[a[--l]]++;
		while(r<p[i].r)sum+=t[a[++r]]++;
		while(l<p[i].l)sum-=--t[a[l++]];
		while(r>p[i].r)sum-=--t[a[r--]];
		ans[p[i].id]=sum;
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
}
