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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,k,a[maxn],p[maxn];
bool vis[maxn];
vector<int> cyc[maxn];
vector<int> pos[maxn];
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)if(!vis[i]){
		for(int x=i;!vis[x];x=a[x])vis[x]=1,cyc[i].pb(x);
		if(__gcd((int)cyc[i].size(),k)==1){
			vector<int> id(cyc[i].size());
			for(int j=0,p=0;j<cyc[i].size();j++,p=(p+k)%id.size())id[p]=cyc[i][j];
			for(int j=0;j<id.size();j++)p[id[j]]=id[(j+1)%id.size()];
		}
		else pos[cyc[i].size()].pb(i);
	}
	for(int i=1;i<=n;i++)if(__gcd(i,k)!=1&&pos[i].size()){
		for(int j=1;i*j<=n;j++)if(__gcd(i*j,k)==j){
			for(int t=0;t<pos[i].size();t+=j){
				vector<int> id(i*j);
				for(int ii=t;ii<t+j;ii++){
					for(int jj=0,p=ii-t;jj<cyc[pos[i][ii]].size();jj++,p=(p+k)%id.size())id[p]=cyc[pos[i][ii]][jj];
				}
				for(int jj=0;jj<id.size();jj++)p[id[jj]]=id[(jj+1)%id.size()];
			}
			break;
		}
	}
	for(int i=1;i<=n;i++)printf("%d ",p[i]);
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