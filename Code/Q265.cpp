#include<bits/stdc++.h>
// #define int long long
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
const int maxn=2000010;
const int inf=1e9;
bool mbe;

int n,d;
mt19937 rnd(1);
int id[maxn];
int st[maxn],tp;
int to[maxn<<1];
bool vis[maxn<<1];
int que[maxn],tl;
vector<vector<int>> color(vector<vector<int>> e){
    vector<vector<int>> ans;
    int n=e.size()-1,d=e[1].size();
    for(int i=1;i<=n;i++)id[i]=i;
    for(int i=1;i<=n;i++){
        for(int j=0;j<d;j++)e[i][j]+=n;
    }
    vector<int> res;
    shuffle(id+1,id+n+1,rnd);
    for(int i=1;i<=2*n;i++)to[i]=0;
    for(int i=1;i<=n;i++){
        int x=id[i],y=0;st[++tp]=x;
        while(!y||to[y]){
            while(!y||y==to[x])y=e[x][rnd()%d];
            st[++tp]=y,x=to[y],st[++tp]=x;
        }
        tp--;
        while(tp){
            if(vis[st[tp]]){
                while(tl&&que[tl]!=st[tp])vis[que[tl]]=0,tl--;
                vis[que[tl]]=0,tl--;
            }
            vis[st[tp]]=1,que[++tl]=st[tp];
            tp--;
        }
        for(int j=1;j<=tl;j++)vis[que[j]]=0;
        // for(int j=1;j<=t;j++)cout<<q[j]<<" ";cout<<"\n";
        while(tl){
            to[que[tl-1]]=que[tl],to[que[tl]]=que[tl-1];
            tl-=2;
        }
    }
    for(int i=1;i<=n;i++){
    	res.pb(to[i]-n);
    	for(int j=0;j<d;j++)if(e[i][j]==to[i]){swap(e[i][j],e[i][d-1]);break;}
    }
	ans.pb(res);
    return ans;
}
vector<vector<int>> e;
void work(){
	n=read();d=read();e.resize(n+1);
	for(int i=1;i<=n;i++){
		e[i].resize(d);
		for(int j=0;j<d;j++)e[i][j]=read();
	}
	vector<vector<int>> ans=color(e);
	for(int i=0;i<n;i++)printf("%d ",ans[0][i]);
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