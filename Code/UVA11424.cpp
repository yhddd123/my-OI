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

int n,ans;
bool vis[maxn];
int pre[maxn],cnt;
int ph[maxn];
int f[maxn];
void s(int n){
	ph[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			pre[++cnt]=i;
			ph[i]=i-1;
		}
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			vis[i*pre[j]]=1;
			if(i%pre[j]==0){
				ph[i*pre[j]]=ph[i]*pre[j];
				break;
			}
			else ph[i*pre[j]]=ph[i]*ph[pre[j]];
		}
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	s(maxn-10);
	for(int i=1;i<=maxn-10;i++){
		for(int j=i*2;j<=maxn-10;j+=i)f[j]+=i*ph[j/i];
	}
	for(int i=2;i<=maxn-10;i++)f[i]+=f[i-1];
	while(n=read()){
		if(!n)return 0;
		printf("%lld\n",f[n]);
	}
}
