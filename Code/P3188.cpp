#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,tp;
int f[31][maxn],g[31][maxn];
vector<int> a[31],v[31];

signed main(){
	while(1){
		memset(f,0,sizeof(f));memset(g,0,sizeof(g));
		for(int i=0;i<=tp;i++)a[i].clear(),v[i].clear();
		n=read();m=read();
		if(n+m==-2){return 0;}
		for(int i=1;i<=n;i++){
			int u=read();
			tp=0;while(u%2==0){
				u>>=1;
				tp++;
			}
			a[tp].push_back(u);v[tp].push_back(read());
		}
		tp=0;while(m>(1<<tp+1))tp++;
		for(int t=0;t<=tp;t++){
			for(int i=0;i<a[t].size();i++){
				for(int j=10*a[t].size();j>=a[t][i];j--){
					f[t][j]=max(f[t][j],f[t][j-a[t][i]]+v[t][i]);
				}
			}
		}
		for(int i=0;i<=10*a[0].size();i++)g[0][i]=f[0][i];
		for(int t=1;t<=tp;t++){
			for(int i=0;i<=10*n;i++){
				for(int j=0;j<=i;j++){
					g[t][i]=max(g[t][i],f[t][i-j]+g[t-1][min(10*n,j*2+((m>>t-1)&1))]);
				}
			}
		}
		printf("%d\n",g[tp][1]);
	}
}
