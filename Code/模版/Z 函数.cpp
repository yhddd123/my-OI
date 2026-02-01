#include<bits/stdc++.h>
#define int long long
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
const int maxn=2000010;
const int inf=1e9;
bool mbe;

int n;
char s[maxn];
int z[maxn];
void work(){
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=2,l=1;i<=n;i++){
		if(l+z[l]>i)z[i]=min(z[i-l+1],l+z[l]-i);
		while(i+z[i]<=n&&s[z[i]+1]==s[i+z[i]])z[i]++;
		if(i+z[i]>l+z[l])l=i;
	}
	for(int i=1;i<=n;i++)printf("%lld ",z[i]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}