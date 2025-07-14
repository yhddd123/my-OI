#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=2000010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,f[maxn][21],ans=inf;
pair<int,int> a[maxn];
void sovle(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		a[i].first=read();a[i].second=read();
		if(a[i].first>a[i].second)a[i].second+=n;
	}
	sort(a+1,a+m+1);
	for(int i=1,j=1,mx=0;i<=2*n;i++){
		while(j<=m&&a[j].first<=i){
			mx=max(mx,a[j].second+1);
			j++;
		}
		if(mx)f[i][0]=mx;
	}
	for(int j=1;j<=20;j++){
		for(int i=1;i<=2*n;i++)f[i][j]=f[f[i][j-1]][j-1];
	}
	for(int i=1;i<=n;i++){
		int x=i,res=0;
		for(int j=20;j>=0;j--){
			if(f[x][j]-i<n){
				res+=(1<<j);
				x=f[x][j];
			}
		}
		x=f[x][0];res++;
		if(x-i>=n)ans=min(ans,res);
	}
	if(ans==inf)printf("impossible\n");
	else printf("%lld\n",ans);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)sovle();
}
