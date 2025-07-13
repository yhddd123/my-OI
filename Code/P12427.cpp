#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=1000010;

bool mbe;

int n,m;
int head[maxn*41],tot;
struct nd{
    int nxt,to;
}e[maxn*40];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int ans[maxn],num;
bool vis[maxn*41],bk[maxn*41];
int st[maxn*41],tp;
// void dfs(int u){
    // vis[u]=bk[u]=1;st[++tp]=u;
    // for(int i=head[u];i;i=e[i].nxt){
        // int v=e[i].to;
        // if(!vis[v])dfs(v);
        // else if(bk[v]){
            // if(num)continue;
            // for(int i=tp;i;i--){    
                // if(st[i]<=m)ans[++num]=st[i];
                // if(st[i]==v)break;
            // }
        // }
        // if(num)break;
    // }
    // bk[u]=0;tp--;
// }
void work(){
    n=read();m=read();
    for(int i=1;i<=m+40*n;i++)head[i]=vis[i]=0;tot=0;
    for(int i=1;i<=m;i++){
        int x=read(),y=read(),c=read();
        for(int j=0;j<20;j++){
            int v=(c>>j)&1;
            add(((v^1)*20+j)*n+x+m,i);
            add(i,(v*20+j)*n+y+m);
        }
    }
    num=0;for(int i=1;i<=m+40*n;i++)if(!vis[i]){
    	vis[i]=bk[i]=1,st[++tp]=i;
    	while(tp){
    		int u=st[tp];
		    for(int &i=head[u];i;i=e[i].nxt){
		        int v=e[i].to;
		        if(!vis[v]){vis[v]=bk[v]=1,st[++tp]=v;break;}
		        else if(bk[v]&&!num){
		            for(int i=tp;i;i--){    
		                if(st[i]<=m)ans[++num]=st[i];
		                if(st[i]==v)break;
		            }
		        }
		    }
    		if(!head[u])bk[u]=0,tp--;
    	}
    	if(num)break;
    }
    if(!num){puts("NO");return ;}
    puts("YES");write(num),putchar(' ');for(int i=num;i;i--)write(ans[i]),putchar(' ');puts("");
}

bool med;

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}