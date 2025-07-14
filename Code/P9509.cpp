#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn],s;
bitset<maxn*maxn> dp1,dp2;

void sovle(){
	n=read();s=0;
	for(int i=1;i<=n;i++)a[i]=read(),s+=a[i];
	if(s%n){
		printf("No\n");
		return ;
	}
	s/=n;
	for(int i=1;i<=n;i++){
		if(a[i]==s){
			printf("Yes\n");
			return ;
		}
	}
	for(int i=1;i<=n;i++)a[i]-=s;
	dp1.reset();dp2.reset();
	dp1[0]=1;dp2[0]=1;
	for(int i=1;i<=n;i++){
		if(a[i]>0)dp1|=(dp1<<a[i]);
		else dp2|=(dp2<<(-a[i]));
	}
	if((dp1&dp2).count()>=3)printf("Yes\n");
	else printf("No\n");
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=read();
	while(T--)sovle();
}
