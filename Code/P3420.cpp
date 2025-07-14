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

int n,f[maxn],ans;
int fd(int x){
	if(f[x]==x)return f[x];
	return f[x]=fd(f[x]);
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	n=read();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=n;i++){
		int x;x=read();
		if(fd(x)==i){
			++ans;
		}
		else f[fd(i)]=x;
	}
	printf("%lld\n",ans);
}

