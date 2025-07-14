#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define ls nd<<1
#define rs nd<<1|1
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

int n,nxt[maxn];
char c[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();scanf("%s",c+1);
	for(int i=2,j=0;i<=n;i++){
		while(j&&c[i]!=c[j+1])j=nxt[j];
		if(c[i]==c[j+1])j++;
		nxt[i]=j;
	}
	printf("%lld\n",n-nxt[n]);
}
