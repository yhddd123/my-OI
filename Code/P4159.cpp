#include<bits/stdc++.h>
#define int long long
#define mod 2009
using namespace std;
const int maxn=110;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,t;
struct nd{
	int e[maxn][maxn];
	nd(){memset(e,0,sizeof(e));}
	nd operator *(const nd&tmp)const{
		nd ans;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++)ans.e[i][j]+=e[i][k]*tmp.e[k][j]%mod;
				ans.e[i][j]%=mod;
			}
		}
		return ans;
	}
}bas;
char c[maxn];
nd ksm(nd a,int b){
	nd ans;
	for(int i=1;i<=n;i++)ans.e[i][i]=1;
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	m=read();t=read();n=9*m;
	for(int i=1;i<=m;i++){
		scanf("%s",c+1);
		for(int j=1;j<=m;j++){
			if(c[j]>'0')bas.e[9*(i-1)+c[j]-'0'][9*(j-1)+1]=1;
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<9;j++)bas.e[9*(i-1)+j][9*(i-1)+j+1]=1;
	}
	bas=ksm(bas,t);
	printf("%lld\n",bas.e[1][(m-1)*9+1]);
}
