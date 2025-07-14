#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,a[maxn],st[maxn][25];
int lg[maxn],pw[25];
int gcd(int a,int b){
	if(a%b==0)return b;
	return gcd(b,a%b);
}
int query(int l,int r){
	int k=lg[r-l+1];
	return gcd(st[l][k],st[r-pw[k]+1][k]);
}
int l,r,mid,ans;
bool check(int x){
	for(int i=1;i+x-1<=n;i++){
		int j=i+x-1;
		if(query(i,j)==1)return true;
	}
	return false;
}
int cnt;
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),st[i][0]=a[i],cnt+=(a[i]==1);
	if(cnt==n){
		printf("0\n");
		return 0;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==1){
			printf("%d\n",n-cnt);
			return 0;
		}
	}
	pw[0]=1;lg[1]=0;
	for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=20;i++)pw[i]=pw[i-1]<<1;
	for(int j=1;j<=lg[n];j++){
		for(int i=1;i+pw[j]-1<=n;i++){
			st[i][j]=gcd(st[i][j-1],st[i+pw[j-1]][j-1]);
		}
	}
	if(query(1,n)!=1){
		printf("-1\n");
		return 0;
	}
	l=1,r=n;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d\n",ans-1+n-1);
}

