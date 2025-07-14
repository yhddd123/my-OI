#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n;
char c[maxn];
int a[maxn],b[maxn],val[26],bas,pw[maxn];
map<int,bool> vis;
int calc1(int l,int r){
	return (a[r]-a[l-1]*pw[r-l+1]%mod+mod)%mod;
}
int calc2(int l,int r){
	return (b[l]-b[r+1]*pw[r-l+1]%mod+mod)%mod;
}
bool check(int x){
	vis.clear();
//	cout<<x<<"\n";
	for(int i=x;i+x-1<=n;i++){
//		cout<<i<<" "<<calc2(i-x+1,i)<<" "<<calc1(i,i+x-1)<<"\n";
		if(calc2(i-x+1,i)==calc1(i,i+x-1)){
			if(vis[calc1(i,i+x-1)])return true;
			vis[calc1(i,i+x-1)]=1;
		}
	}
	return false;
}
void work(){
	n=read();scanf("%s",c+1);
//	srand(time(0));bas=rand()*rand()%mod;
//	for(int i=0;i<26;i++)val[i]=rand()*rand()%bas;
	bas=10;for(int i=0;i<26;i++)val[i]=i;
	for(int i=1;i<=n;i++)a[i]=(a[i-1]*bas+val[c[i]-'a'])%mod;
	for(int i=n;i;i--)b[i]=(b[i+1]*bas+val[c[i]-'a'])%mod;
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*bas%mod;
	int l=0,r=n,res=0;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))l=mid+1,res=mid;
		else r=mid-1;
	}
	printf("%lld\n",res);
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	T=1;
	while(T--)work();
}

