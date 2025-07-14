#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=1000010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn];
struct ask{
	int l,r,id;
	bool operator <(const ask&tmp)const{return r<tmp.r;}
}p[maxn];
int ans[maxn];
int pre[maxn],lst[maxn];
int tree[maxn];
int lowbit(int x){return x&(-x);}
void updata(int x,int w){
	while(x<=maxn-10){
		tree[x]+=w;
		x+=lowbit(x);
	}
}
int query(int x){
	int res=0;
	while(x){
		res+=tree[x];
		x-=lowbit(x);
	}
	return res;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	m=read();
	for(int i=1;i<=m;i++){
		p[i].l=read()-1;
		p[i].r=read();
		p[i].id=i;
	}
	sort(p+1,p+m+1);
	for(int i=1,j=1;i<=n;i++){
		lst[i]=pre[a[i]];
		pre[a[i]]=i;
		if(lst[i])updata(lst[i],-1);
		updata(i,1);
		while(j<=m&&p[j].r==i){
			ans[p[j].id]=query(i)-query(p[j].l);
			j++;
		}
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
}
