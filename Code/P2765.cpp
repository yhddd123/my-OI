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

int n,res;
vector<int> ans[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n*n;i++){
		bool fl=0;
		for(int j=1;j<=n;j++){
			if(!ans[j].size()||(int)sqrt(ans[j].back()+i)*(int)sqrt(ans[j].back()+i)==ans[j].back()+i){
				ans[j].push_back(i);
				fl=1;++res;
				break;
			}
		}
		if(!fl)break;
	}
	printf("%lld\n",res);
	for(int i=1;i<=n;i++){
		for(int j:ans[i])printf("%lld ",j);
		printf("\n");
	}
}
