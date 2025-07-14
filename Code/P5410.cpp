#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=40000010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,ans;
char a[maxn],b[maxn];
int z[maxn];

int T;
signed main(){
//		freopen("P5410_2.in","r",stdin);
	//	freopen(".out","w",stdout);
	
	scanf("%s%s",a+1,b+1);
	n=strlen(a+1);m=strlen(b+1);
	b[m+1]='#';for(int i=m+2;i<=n+m+1;i++)b[i]=a[i-m-1];
	m+=n+1;
	for(int i=2,l=1;i<=m;i++){
		if(l+z[l]>i)z[i]=min(z[i-l+1],l+z[l]-i);
		while(i+z[i]<=n+m&&b[z[i]+1]==b[i+z[i]])z[i]++;
		if(i+z[i]>l+z[l])l=i;
	}
	z[1]=m-n-1;
	for(int i=1;i<=m-n-1;i++)ans^=(z[i]+1)*i;
	printf("%lld\n",ans);ans=0;
	for(int i=1;i<=n;i++)ans^=(z[i-n+m]+1)*i;
	printf("%lld\n",ans);
}
