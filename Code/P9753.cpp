#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2000010;

int n,ans;
int lst[maxn],num[maxn];
char c[maxn];

signed main(){
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	scanf("%lld%s",&n,c+1);
	for(int i=1;i<=n;i++){
		int x=i;
		while(c[i]!=c[x-1]&&lst[x-1]!=0)x=lst[x-1];
		if(c[i]==c[x-1])lst[i]=x-1;
		if(!lst[i])continue;
		num[i]=num[lst[i]-1]+1;ans+=num[i];
	}
	printf("%lld\n",ans);
}
