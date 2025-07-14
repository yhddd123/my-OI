#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=100010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn],s;
struct ask{
	int opt,l,r,w,id;
}p[maxn];
bool cmp(ask u,ask v){
	if(u.l/s==v.l/s){
		if((u.l/s)&1)return u.r<v.r;
		return u.r>v.r;
	}
	return u.l<v.l;
}
int ans[maxn];
int l=1,r,t[maxn];
bitset<maxn> f,g;
void add(int x){
	if(++t[x]==1)f.set(x),g.set(maxn-x);
}
void del(int x){
	if(--t[x]==0)f.set(x,false),g.set(maxn-x,false);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();s=sqrt(n);
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)p[i]={read(),read(),read(),read(),i};
	sort(p+1,p+m+1,cmp);
	for(int i=1;i<=m;i++){
		while(l>p[i].l)add(a[--l]);
		while(r<p[i].r)add(a[++r]);
		while(l<p[i].l)del(a[l++]);
		while(r>p[i].r)del(a[r--]);
		if(p[i].opt==1){
			if((f&(f<<p[i].w)).any())ans[p[i].id]=1;
		}
		if(p[i].opt==2){
			if((f&(g>>(maxn-p[i].w))).any())ans[p[i].id]=1;
		}
		if(p[i].opt==3){
			for(int j=1;j*j<=p[i].w;j++){
				if(p[i].w%j==0){
					if(t[j]&&t[p[i].w/j]){
						ans[p[i].id]=1;
						break;
					}
				}
			}
		}
	}
	for(int i=1;i<=m;i++){
		if(ans[i])printf("hana\n");
		else printf("bi\n");
	}
}
