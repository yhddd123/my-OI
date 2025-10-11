#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=210;
const int maxk=18;
const int inf=1e9;
bool mbe;

int n;
vector<int> e[maxn];
int d[maxn];
int f[maxn][maxn];
int g[2][1<<maxk],h[2][maxn][1<<maxk],cur;
int C[maxn][maxn],S[maxn][maxn],fac[maxn],pw[maxn][maxn];
int val[maxn][1<<maxk];
int coef[maxn][maxn];
inline void fix(int &u){u-=mod,u+=((u>>31)&mod);}
void dfs(int u,int fa){
    vector<int> son;
    for(int v:e[u]){
        if(v==fa)continue;
        dfs(v,u);d[u]++;
        son.pb(v);
    }
    if(!d[u])return ;
    sort(son.begin(),son.end(),[&](int x,int y){return d[x]>d[y];});
    int num=0;while(son.size()&&!d[son.back()])son.pop_back(),num++;
    int mn=2*son.size(),p=son.size();
    for(int i=0;i<son.size()&&i<16;i++)if(i+d[son[i]]<=mn)mn=i+d[son[i]],p=i;
    int U=1<<(mn-p+1);
    for(int i=0;i<U;i++)g[0][i]=0;
    g[cur=0][0]=1;
    for(int i=p,nw=1;i<son.size();i++,nw^=1){
        int v=son[i];
        for(int s=0;s<U;s++)g[nw][s]=0;
        for(int s=0;s<U;s++){
            for(int j=0;j<=d[v];j++){
                fix(g[nw][s|(1<<j)]+=1ll*g[cur][s]*f[v][j]%mod);
            }
        }
        cur=nw;
    }
    for(int j=0;j<p;j++)val[d[u]+1][1<<j]=0;
    for(int j=0;j<p;j++){
    	int v=son[j];
	    for(int i=d[u]+1;i<=d[v];i++)fix(val[d[u]+1][1<<j]+=f[v][i]);
    }
    val[d[u]+1][0]=1;
    for(int i=d[u];i;i--){
        for(int j=0;j<p;j++)fix(val[i][1<<j]=val[i+1][1<<j]+f[son[j]][i]);
        val[i][0]=1;for(int s=1;s<(1<<p);s++)val[i][s]=1ll*val[i][s^(s&(-s))]*val[i][s&(-s)]%mod;
    }
	for(int j=0;j<=num;j++){
		for(int v=0;v<=n-j;v++){
			coef[j][v]=0;
    		for(int k=j;k<=num;k++)fix(coef[j][v]+=1ll*C[num][k]*S[k][j]%mod*fac[j]%mod*pw[v][num-k]%mod);
		}
	}
    int tmp=cur;
    for(int ss=0;ss<U;ss++)if(g[tmp][ss]){
    	// if(u==1)cout<<ss<<" "<<g[tmp][ss]<<"\n";
        for(int i=0;i<=num;i++){
            for(int s=0;s<(1<<p);s++)h[0][i][s]=h[1][i][s]=0;
        }
        h[0][0][(1<<p)-1]=g[tmp][ss];
        cur=0;
        int pp=p;
        for(int t=0,nw=1;t<=d[u];t++,nw^=1){
        	while(pp&&d[son[pp-1]]<t)pp--;
            if(t<=20&&(ss&(1<<t))){
                for(int i=0;i<=min(num,t);i++){
                    for(int s=0;s<(1<<pp);s++)h[nw][i][s]=h[cur][i][s],h[cur][i][s]=0;
                }
            }
            else{
                for(int i=0;i<=min(num,t+1);i++){
                    for(int s=0;s<(1<<pp);s++)h[nw][i][s]=0;
                }
                for(int i=0;i<=min(num,t);i++){
                    for(int s=0;s<(1<<pp);s++)if(h[cur][i][s]){
                    	// cout<<u<<" "<<t<<" "<i<<" "<<s<<" "<<h[cur][i][s]<<" "<<coef[i][n-t]<<"\n";
                        fix(f[u][t]+=1ll*h[cur][i][s]*val[t+1][s]%mod*coef[i][n-t]%mod);
                    }
                }
            }
            for(int i=0;i<=min(num,t);i++){
                for(int j=0;j<p;j++){
                    int v=son[j];
                    for(int s=0;s<(1<<pp);s++)if(s&(1<<j)){
                        fix(h[nw][i][s^(1<<j)]+=1ll*h[cur][i][s]*f[v][t]%mod);
                        fix(h[nw][i][s^(1<<j)]+=1ll*h[nw][i][s]*f[v][t]%mod);
                    }
                }
            }
            for(int i=min(num,t+1);i;i--){
                for(int s=0;s<(1<<pp);s++){
                    fix(h[nw][i][s]+=h[cur][i-1][s]);
                    fix(h[nw][i][s]+=h[nw][i-1][s]);
                }
            }
            cur=nw;
        }
    }
    // for(int v:son)cout<<d[v]<<" ";cout<<"\n";
    // cout<<u<<" "<<p<<" "<<mn<<" "<<num<<" "<<d[u]<<"\n";
	// for(int i=0;i<=n;i++)cout<<f[u][i]<<" ";cout<<"\n";
}
void work(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        e[u].pb(v),e[v].pb(u);
    }
    for(int i=0;i<=n;i++){
        C[i][0]=1;for(int j=1;j<=i;j++)fix(C[i][j]=C[i-1][j]+C[i-1][j-1]);
        pw[i][0]=1;for(int j=1;j<=n;j++)pw[i][j]=1ll*pw[i][j-1]*i%mod;
    }
    S[0][0]=1;for(int i=1;i<=n;i++){
    	for(int j=1;j<=i;j++)fix(S[i][j]=S[i-1][j-1]+1ll*j*S[i-1][j]%mod);
    }
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    dfs(1,0);
    for(int i=0;i<=n;i++)printf("%d\n",f[1][i]);
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}