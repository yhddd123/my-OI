#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
using namespace std;
const int maxn=500010;
const int inf=3e4;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,s,k,res;
struct nd{
	int x,y,w,col;
}e[maxn];
bool cmp(nd u,nd v){
	if(u.w==v.w)return u.col>v.col;
	return u.w<v.w;
}
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
int cnt;
int check(int x){
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++)if(e[i].col)e[i].w+=x;
	sort(e+1,e+m+1,cmp);
	int num1=0,num2=0;res=0;
	for(int i=1;i<=m;i++){
		int u=fd(e[i].x),v=fd(e[i].y);
		if(u!=v){
			f[v]=u;num1++;
			res+=e[i].w;
			if(e[i].col)num2++;
		}
	}
	for(int i=1;i<=m;i++)if(e[i].col)e[i].w-=x;
	if(num1!=n-1){
		printf("Impossible\n");
		exit(0);
	}
	return num2>=k;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();s=read();k=read();
	for(int i=1;i<=m;i++){
		e[i].x=read(),e[i].y=read(),e[i].w=read();
		if(e[i].x==s||e[i].y==s)e[i].col=1,++cnt;
	}
	if(cnt<k){
		printf("Impossible\n");
		return 0;
	}
	if(cnt==m&&cnt!=k){
		printf("Impossible\n");
		return 0;
	}
	int l=-inf,r=inf,ans=-1;
	while(l<=r){
		if(check(mid)){
			ans=res-mid*k;
			l=mid+1;
		}
		else r=mid-1;
	}
	if(ans==-1)printf("Impossible\n");
	else printf("%lld\n",ans);
}
