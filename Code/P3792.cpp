// Problem: P3792 由乃与大母神原型和偶像崇拜
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3792
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn];
int ask[maxn][3];
int b[maxn<<1],len;
mt19937 rnd(1);
int num[maxn];
#define lb(x) (x&(-x))
int sum[maxn],val[maxn];
void updsum(int x,int w){
	while(x<=n)sum[x]+=w,x+=lb(x);
}
void updval(int x,int w){
	while(x<=n)val[x]^=w,x+=lb(x);
}
int quesum(int x){
	int res=0;while(x)res+=sum[x],x-=lb(x);return res;
}
int queval(int x){
	int res=0;while(x)res^=val[x],x-=lb(x);return res;
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[++len]=a[i],b[++len]=a[i]+1;
	for(int i=1;i<=m;i++){
		ask[i][0]=read(),ask[i][1]=read(),ask[i][2]=read();
		if(ask[i][0]==1)b[++len]=ask[i][2],b[++len]=ask[i][2]+1;
	}
	sort(b+1,b+len+1);len=unique(b+1,b+len+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+len+1,a[i])-b;
	for(int i=1;i<=m;i++){
		if(ask[i][0]==1)ask[i][2]=lower_bound(b+1,b+len+1,ask[i][2])-b;
	}
	for(int i=1;i<=len;i++)num[i]=rnd()^num[i-1];
	// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)updsum(i,a[i]),updval(i,num[a[i]]^num[a[i]-1]);
	for(int i=1;i<=m;i++){
		int op=ask[i][0],u=ask[i][1],v=ask[i][2];
		if(op==1){
			updsum(u,-a[u]),updval(u,num[a[u]]^num[a[u]-1]);
			a[u]=v;updsum(u,a[u]),updval(u,num[a[u]]^num[a[u]-1]);
		}
		else{
			int sum=quesum(v)-quesum(u-1);
			if(sum*2%(v-u+1)){puts("yuanxing");continue;}
			int s=sum*2/(v-u+1);
			int vl=(s+u-v)/2,vr=(s+v-u)/2;
			if((vl+vr)*(vr-vl+1)/2!=sum){puts("yuanxing");continue;}
			// cout<<vl<<" "<<vr<<" "<<sum<<" "<<(num[vr]^num[vl-1])<<" "<<(queval(v)^queval(u-1))<<"\n";
			if((num[vr]^num[vl-1])==(queval(v)^queval(u-1)))puts("damushen");
			else puts("yuanxing");
		}
		
	}
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
