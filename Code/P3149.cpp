#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=300010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn];
int b[maxn],len;
int tree[maxn],sum[maxn];
int lowbit(int x){return x&(-x);}
void updata(int x){
	while(x<=len){
		tree[x]++;
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
void sovle(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
//	cerr<<"run\n";
	sort(b+1,b+n+1);len=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+len+1,a[i])-b;
	for(int i=n;i>=1;i--)updata(a[i]),sum[a[i]]+=query(a[i]-1);
	for(int i=len-1;i>=1;i--)sum[i]+=sum[i+1];
	int u=1;
	printf("%lld\n",sum[u]);
	while(m--){
		u=max(a[read()]+1,u);
		printf("%lld\n",sum[u]);
	}
}

int T;
signed main(){
//		freopen("P3149_7.in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)sovle();
}
