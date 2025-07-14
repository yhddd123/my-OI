#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,res;
int p[maxn],e[maxn];
int cnt,x;
bool ans[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	while(cin>>n>>m){
		for(int i=1;i<=n;i++)ans[i]=0;
		x=m;res=0;cnt=0;
		for(int i=2;i*i<=m;i++){
			if(x%i==0){
				p[++cnt]=i;e[cnt]=0;
				while(x%i==0){
					e[cnt]++;
					x/=i;
				}
			}
		}
		if(x!=1)p[++cnt]=x,e[cnt]=1;
		n--;
		for(int i=1;i<=cnt;i++){
			int num=0;
			for(int j=1;j<n;j++){
				x=n-j+1;
				while(x%p[i]==0){
					x/=p[i];
					++num;
				}
				x=j;
				while(x%p[i]==0){
					x/=p[i];
					--num;
				}
				if(num<e[i])ans[j]=1;
			}
		}
		for(int i=1;i<n;i++)if(!ans[i])++res;
		printf("%d\n",res);
		for(int i=1;i<n;i++)if(!ans[i]){
			--res;
			if(!res)printf("%d",i+1);
			else printf("%d ",i+1);
		}
		printf("\n");
	}
}
