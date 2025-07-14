#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=110;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,c[maxn][maxn],t[12],ans;
char s[maxn];
void sovle(){
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=0;i<=n;i++)c[i][0]=1;
	for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)c[i][j]=c[i-1][j-1]+c[i-1][j];
	for(int i=1;i<=n;i++)t[s[i]-'0']++;
	for(int i=1;i<=n;i++){
		for(int j=0;j<s[i]-'0';j++){
			if(!t[j])continue;
			--t[j];
			int res=1,sum=n-i;
			for(int k=0;k<10;k++)res*=c[sum][t[k]],sum-=t[k];
			ans+=res;
			++t[j];
		}
		t[s[i]-'0']--;
	}
	printf("%lld\n",ans);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)sovle();
}
