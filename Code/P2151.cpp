#include<bits/stdc++.h>
#define int long long
#define mod 45989
using namespace std;
const int maxn=125;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,k,s,t,ans;
int len;
struct mat{
	int e[maxn][maxn];
	mat(){memset(e,0,sizeof(e));}
	mat operator *(const mat&tmp)const{
		mat ans;
		for(int i=1;i<=len;i++){
			for(int j=1;j<=len;j++){
				for(int k=1;k<=len;k++)ans.e[i][j]+=e[i][k]*tmp.e[k][j]%mod;
				ans.e[i][j]%=mod;
			}
		}
		return ans;
	}
}bas,nw;
mat ksm(mat a,int b){
	mat ans;
	for(int i=1;i<=len;i++)ans.e[i][i]=1;
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
int head[maxn],tot=1;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}

int T;
signed main(){
//		freopen("P2151_1.in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();k=read();s=read()+1;t=read()+1;
	for(int i=1;i<=m;i++){
		int u=read()+1,v=read()+1;
		add(u,v);add(v,u);
	}
	len=tot;
	for(int i=head[s];i;i=e[i].nxt)nw.e[1][i]=1;
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			for(int j=head[v];j;j=e[j].nxt){
				if(i!=(j^1))bas.e[i][j]=1;
			}
		}
	}
	nw=nw*ksm(bas,k-1);
	for(int i=head[t];i;i=e[i].nxt)ans+=nw.e[1][i^1],ans%=mod;
	printf("%lld\n",ans);
}
