#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=1010;
const int inf=1e9;
bool mbe;

int n,m,q;
int a[maxn][maxn];
pii dw[maxn][maxn],rt[maxn][maxn];

void work(){
	n=read(),m=read(),q=read();
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			dw[i][j]={i+1,j};
			rt[i][j]={i,j+1};
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)a[i][j]=read();
	}
	
	while(q--){
		int A=read(),B=read(),C=read(),D=read(),H=read(),W=read();
		pii a={0,0},b={0,0};
        for(int i=1;i<=A;i++)a=dw[a.fi][a.se];
		for(int i=1;i<B;i++)a=rt[a.fi][a.se];
        for(int i=1;i<=C;i++)b=dw[b.fi][b.se];
		for(int i=1;i<D;i++)b=rt[b.fi][b.se];
        pii c={0,0},d={0,0};
        for(int i=1;i<A;i++)c=dw[c.fi][c.se];
        for(int i=1;i<=B;i++)c=rt[c.fi][c.se];
        for(int i=1;i<C;i++)d=dw[d.fi][d.se];
        for(int i=1;i<=D;i++)d=rt[d.fi][d.se];
        pii e={0,0},f={0,0};
        for(int i=1;i<=A;i++)e=dw[e.fi][e.se];
        for(int i=1;i<=B+W-1;i++)e=rt[e.fi][e.se];
        for(int i=1;i<=C;i++)f=dw[f.fi][f.se];
        for(int i=1;i<=D+W-1;i++)f=rt[f.fi][f.se];
        pii g={0,0},h={0,0};
        for(int i=1;i<=A+H-1;i++)g=dw[g.fi][g.se];
        for(int i=1;i<=B;i++)g=rt[g.fi][g.se];
        for(int i=1;i<=C+H-1;i++)h=dw[h.fi][h.se];
        for(int i=1;i<=D;i++)h=rt[h.fi][h.se];

        for(int i=1;i<=H;i++)swap(rt[a.fi][a.se],rt[b.fi][b.se]),a=dw[a.fi][a.se],b=dw[b.fi][b.se];
        for(int i=1;i<=W;i++)swap(dw[c.fi][c.se],dw[d.fi][d.se]),c=rt[c.fi][c.se],d=rt[d.fi][d.se];
        for(int i=1;i<=H;i++)swap(rt[e.fi][e.se],rt[f.fi][f.se]),e=dw[e.fi][e.se],f=dw[f.fi][f.se];
        for(int i=1;i<=W;i++)swap(dw[g.fi][g.se],dw[h.fi][h.se]),g=rt[g.fi][g.se],h=rt[h.fi][h.se];
	}
	
	for(int i=1;i<=n;i++){
		pii p={0,0};
		for(int j=1;j<=i;j++)p=dw[p.fi][p.se];
		for(int j=1;j<=m;j++){
			p=rt[p.fi][p.se];
			printf("%lld ",a[p.fi][p.se]);
		}
        puts("");
	}
}

bool med;
int T;
signed main(){
	freopen("CF706E.in","r",stdin);
	
	T=1;
	while(T--)work();
}
