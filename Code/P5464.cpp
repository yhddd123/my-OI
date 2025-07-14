#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int maxn=4010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,l[maxn],ans;
int dp[maxn][maxn],sum[maxn][maxn];
struct nd{
	int x,y;
}a[maxn];
bool cmp(nd u,nd v){
	if(u.y==v.y)return u.x<v.x;
	return u.y<v.y;
}
void solve(){
	n=read();
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	sort(a+1,a+n+1,cmp);
	for(int i=2;i<=n;i++){
		int L=1,R=i,mid;l[i]=i;
		while(L<=R){
			mid=L+R>>1;
			if(a[mid].y<a[i].x)L=mid+1;
			else R=mid-1,l[i]=mid;
		}
	}
	for(int i=1;i<=4000;i++)dp[i][0]=1,sum[i][0]=1,sum[1][i]=1;
	for(int i=2,lst=0;i<=n;i++){
		for(lst=1;lst<=a[l[i]].x;lst++)sum[i][lst]=sum[i][lst-1];
		for(int j=l[i],k;j<i;j++){
			if(a[i].x<=a[j].x){
				dp[i][j]=sum[i][a[j].x-1];
			}
			else{
				dp[i][j]=sum[j][a[i].x-1];
			}
			for(k=lst;k<=a[j].y;k++)sum[i][k]=sum[i][k-1];
			sum[i][k-1]+=dp[i][j];sum[i][k-1]%=mod;
			for(;k<a[j+1].x;k++)sum[i][k]=sum[i][k-1];
			lst=k;
		}
		for(;lst<=4000;lst++)sum[i][lst]=sum[i][lst-1];
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++)ans+=dp[i][j],ans%=mod;
	}
	printf("%d\n",ans);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)solve();
}
