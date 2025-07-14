#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,ans=1;
char c[maxn];
int nxt[maxn],num[maxn];
void work(){
	scanf("%s",c+1);n=strlen(c+1);ans=1;
	num[1]=1;
	for(int i=2,j=0;i<=n;i++){
		while(j&&c[i]!=c[j+1])j=nxt[j];
		if(c[i]==c[j+1])j++;
		nxt[i]=j;
		num[i]=num[j]+1,num[i]-=num[i]>=mod?mod:0;
	}
	for(int i=2,j=0;i<=n;i++){
		while(j&&c[i]!=c[j+1])j=nxt[j];
		if(c[i]==c[j+1])j++;
		while(j>i/2)j=nxt[j];
		ans*=num[j]+1,ans%=mod;
//		cout<<j<<" "<<i<<" "<<ans<<"\n";
	}
	printf("%lld\n",ans);
}

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}
