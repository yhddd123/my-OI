#include<bits/stdc++.h>
// #define int long long
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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int q,n,ans[maxn];
deque<int> s[maxn];
int f[maxn];
int fd(int x){
    if(f[x]==x)return x;
    return f[x]=fd(f[x]);
}
char c[maxn];
int rt0[maxn],rt1[maxn],lst[maxn][2],fl[maxn],idx;
int fa[maxn<<5],to[maxn<<5][2],len[maxn<<5];
int getf(int u,int nd,int id){
    while(id-(len[nd]+1)*(fl[u]?-1:1)<0||id-(len[nd]+1)*(fl[u]?-1:1)>=s[u].size()||s[u][id-(len[nd]+1)*(fl[u]?-1:1)]!=s[u][id])nd=fa[nd];
    return nd;
}
void insert(int u,int id){
    int c=s[u][id]-'a';
    int &p=lst[u][fl[u]];p=getf(u,p,id);
    if(!to[p][c]){
        int nd=++idx;ans[u]++;
        fa[nd]=to[getf(u,fa[p],id)][c];
        if(!fa[nd])fa[nd]=rt0[u];
        to[p][c]=nd;
        len[nd]=len[p]+2;
    }
    p=to[p][c];
    if(len[p]==s[u].size())lst[u][fl[u]^1]=p;
}
void work(){
	n=read();scanf("%s",c+1);
    for(int i=1;i<=n;i++){
        fa[idx+1]=idx+2,len[idx+1]=0;
        fa[idx+2]=idx+1,len[idx+2]=-1;
        lst[i][0]=lst[i][1]=rt0[i]=idx+1;rt1[i]=idx+2;
        idx+=2;
    }
    for(int i=1;i<=n;i++)s[i].pb(c[i]-'0'),insert(i,0);
    for(int i=1;i<=n;i++)f[i]=i;
    for(int i=1;i<n;i++){
        int u=fd(read()),v=fd(read());
        if(s[u].size()>=s[v].size()){
            f[v]=u;
            for(int c:s[v])s[u].pb(c),insert(u,s[u].size()-1);
        }
        else{
            f[u]=v;
            fl[v]=1;
            reverse(s[u].begin(),s[u].end());
            for(int c:s[u])s[v].push_front(c),insert(v,0);
            fl[v]=0;
        }
        printf("%d\n",ans[fd(u)]);
    }
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}