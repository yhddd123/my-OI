#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=2010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,m;
char c[maxn];
int a[maxn][maxn];
bool vis[26];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);
		for(int j=1;j<=m;j++)a[i][j]=c[j]-'a';
	}
	for(int len=2;len<=n+m;len++){
		for(int i=0;i<26;i++)vis[i]=0;int cnt=0;
		for(int i=1;i<=min(n,len);i++){
			int j=len+1-i;
//			cout<<len<<" "<<i<<" "<<j<<"\n";
			if(j<=0||j>m)continue;
			if(!vis[a[i][j]])++cnt;
			vis[a[i][j]]=1;
		}
		if(cnt>1){printf("%lld\n",len-1);return ;}
	}
	printf("%lld\n",n+m-1);
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	T=1;
	while(T--)work();
}


