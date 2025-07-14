#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=60010;
const int maxm=70000010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn],s;
char c[maxn];
int t[maxm];
struct ask{
	int l,r,id;
}p[maxn];
bool cmp(ask u,ask v){
	if(u.l/s==v.l/s){
		if((u.l/s)&1)return u.r<v.r;
		else return u.r>v.r;
	}
	return u.l<v.l;
}
int ans[maxn];
int l=1,r,res;
void add(int x){
	res+=t[x];t[x]++;
	for(int i=0;i<26;i++)res+=t[x^(1<<i)];
}
void del(int x){
	t[x]--;res-=t[x];
	for(int i=0;i<26;i++)res-=t[x^(1<<i)];
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();s=sqrt(n);
	scanf("%s",c+1);
	for(int i=1;i<=n;i++)a[i]=a[i-1]^(1<<(c[i]-'a'));
	for(int i=1;i<=m;i++)p[i]={read()-1,read(),i};
	sort(p+1,p+m+1,cmp);
	for(int i=1;i<=m;i++){
		while(l>p[i].l)add(a[--l]);
		while(r<p[i].r)add(a[++r]);
		while(l<p[i].l)del(a[l++]);
		while(r>p[i].r)del(a[r--]);
		ans[p[i].id]=res;
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
}
