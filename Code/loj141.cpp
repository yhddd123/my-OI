#include<bits/stdc++.h>
#define int long long
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
const int maxn=800010;
const int inf=1e9;
bool mbe;

int q,n,ans;
deque<char> s;
char c[maxn];
int fa[maxn],to[maxn][26],len[maxn],dep[maxn],lst[2],fl,idx;
int getf(int nd,int id){
    while(id-(len[nd]+1)*(fl?-1:1)<0||id-(len[nd]+1)*(fl?-1:1)>=s.size()||s[id-(len[nd]+1)*(fl?-1:1)]!=s[id])nd=fa[nd];
    return nd;
}
void insert(int id){
    int c=s[id]-'a';
    int &p=lst[fl];p=getf(p,id);
    if(!to[p][c]){
        int nd=++idx;
        fa[nd]=to[getf(fa[p],id)][c];
        to[p][c]=nd;
        len[nd]=len[p]+2;
        dep[nd]=dep[fa[nd]]+1;
    }
    p=to[p][c];
    if(len[p]==s.size())lst[fl^1]=p;
    ans+=dep[p];
}
void work(){
    scanf("%s",c+1);n=strlen(c+1);
    fa[0]=1;len[1]=-1;idx=1;
    for(int i=1;i<=n;i++)s.pb(c[i]),insert(s.size()-1);
    q=read();
    while(q--){
        int op=read();
        if(op==1){
            scanf("%s",c+1);n=strlen(c+1);
    		for(int i=1;i<=n;i++)s.pb(c[i]),insert(s.size()-1);
        }
        if(op==2){
        	fl=1;
            scanf("%s",c+1);n=strlen(c+1);
    		for(int i=1;i<=n;i++)s.push_front(c[i]),insert(0);
        	fl=0;
        }
        if(op==3){
            printf("%lld\n",ans);
        }
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