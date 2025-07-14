#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=55;
const int inf=1e18;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,t,k;
int a[maxn];
int len;
struct mat{
	int e[maxn*5][maxn*5];
	mat(){memset(e,-0x3f,sizeof(e));};
	mat operator*(const mat&tmp)const{
		mat res;
		for(int i=1;i<=len;i++){
			for(int j=1;j<=len;j++){
				for(int k=1;k<=len;k++){
					res.e[i][j]=max(res.e[i][j],e[i][k]+tmp.e[k][j]);
				}
			}
		}
		return res;
	}
}pw[31],ans;
mat mul(mat a,mat b){
	mat res;
	for(int i=1;i<=len;i++){
		for(int j=1;j<=len;j++){
			res.e[1][i]=max(res.e[1][i],a.e[1][j]+b.e[j][i]);
		}
	}
	return res;
}
struct nd{
	int tim,pos,val;
}p[maxn*4];
bool cmp(nd u,nd v){return u.tim<v.tim;}
void sovle(){
	n=read();m=read();t=read();k=read();len=n*5;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=2;j<=5;j++){
			if(j==2)pw[0].e[(i-1)*5+j][(i-1)*5+j-1]=a[i];
			else pw[0].e[(i-1)*5+j][(i-1)*5+j-1]=0;
		}
	}
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		if(w==1)pw[0].e[(u-1)*5+1][(v-1)*5+w]=a[v];
		else pw[0].e[(u-1)*5+1][(v-1)*5+w]=0;
	}
	for(int i=1;i<=k;i++)p[i]={read(),read(),read()};
	sort(p+1,p+k+1,cmp);
	p[++k].tim=t;
	for(int i=1;i<=30;i++)pw[i]=pw[i-1]*pw[i-1];
	ans.e[1][1]=0;
	for(int i=1;i<=k;i++){
		int d=p[i].tim-p[i-1].tim;
		for(int j=0;j<=30;j++){
			if(d&(1<<j))ans=mul(ans,pw[j]);
		}
		for(int j=1;j<=len;j++){
			if(ans.e[j][(p[i].pos-1)*5+1]>=0){
				ans.e[j][(p[i].pos-1)*5+1]+=p[i].val;
			}
		}
	}
	if(ans.e[1][1]<0)printf("-1\n");
	else printf("%lld\n",ans.e[1][1]+a[1]);
}

int T;
signed main(){
//		freopen("P6772_9.in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)sovle();
}
