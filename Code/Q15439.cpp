#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,ans;
char s[maxn];
void work(){
	scanf("%s",s+1);n=strlen(s+1);ans=0;
	ans=n-2;
	for(int i=1;i<n;i++)if(s[i]==s[i+1])ans=n-1;
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen("string.in","r",stdin);
	// freopen("string.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}