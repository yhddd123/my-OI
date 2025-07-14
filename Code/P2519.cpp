#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
struct nd{
	int a,b,t;
}e[maxn];
bool cmp(nd u,nd v){
	if(u.a==v.a)return u.b<v.b;
	return u.a<v.a;
}
bool cmp1(nd u,nd v){return u.b<v.b;}
int dp[maxn],ans;
void sovle(){
	n=read();
	for(int i=1;i<=n;i++)e[i]={read()+1,n-read(),1};
	sort(e+1,e+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(e[i].a>e[i].b)continue;
		if(m&&e[i].a==e[m].a&&e[i].b==e[m].b)e[m].t++;
		else{
			if(m&&e[m].t>e[m].b-e[m].a+1)e[m].t=e[m].b-e[m].a+1;
			e[++m]=e[i];
		}
	}
	if(m&&e[m].t>e[m].b-e[m].a+1)e[m].t=e[m].b-e[m].a+1;
	sort(e+1,e+m+1,cmp1);
	for(int i=1;i<=m;i++){
//		cerr<<e[i].a<<" "<<e[i].b<<" "<<e[i].t<<"\n";
		int l=1,r=i-1,mid,ans=0;
		while(l<=r){
			mid=l+r>>1;
			if(e[mid].b<e[i].a){
				l=mid+1;
				ans=mid;
			}
			else r=mid-1;
		}
		dp[i]=max(dp[i-1],dp[ans]+e[i].t);
//		cerr<<dp[i]<<"\n";
	}
	printf("%lld\n",n-dp[m]);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)sovle();
}
