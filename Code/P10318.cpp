// Problem: P10318 [SHUPC 2024] 彭罗斯水槽
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10318
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-08-13 14:18:39
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
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn];
int st[21][maxn];
bool cmp(int u,int v){return a[u]<a[v];}
int que(int l,int r){
	int k=log2(r-l+1);
	return min(st[k][l],st[k][r-(1<<k)+1],cmp);
}
int ans[maxn];
void sovle(int l,int r){
	if(l>r||l>n)return ;
	int mid=que(l,r);
	int pr=min(mid,n),rr=min(r,pr+n);
	// cout<<l<<" "<<pr<<" "<<mid<<" "<<rr<<" "<<r<<"\n";
	if(pr-l<rr-mid){
		for(int i=l;i<=pr;i++){
			ans[mid-i]+=a[mid],ans[rr-i+1]-=a[mid];
			// cout<<mid-i<<" "<<rr-i<<" "<<a[mid]<<" a\n";
		}
	}
	else{
		for(int i=mid;i<=rr;i++){
			ans[i-pr]+=a[mid],ans[i-l+1]-=a[mid];
			// cout<<i-pr<<" "<<i-l<<" "<<a[mid]<<" b\n";
		}
	}
	sovle(l,mid-1),sovle(mid+1,r);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i+n]=a[i]=read();
	for(int i=1;i<=2*n;i++)st[0][i]=i;
	for(int j=1;j<=20;j++){
		for(int i=1;i+(1<<j)-1<=2*n;i++)st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)],cmp);
	}
	sovle(1,2*n);
	for(int i=1;i<=n;i++)ans[i]+=ans[i-1];
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("sink.in","r",stdin);
	// freopen("sink.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
