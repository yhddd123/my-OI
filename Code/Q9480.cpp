#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int q,len,n;
vector<int> val[maxn];
void work(){
	q=read();val[++n].pb(1);len=1;
	while(q--){
		int opt=read();
		if(opt==1){
			int u=read();
			val[n].pb(u),len=min(inf,len+1);
		}
		else if(opt==2){
			int u=read();
			val[++n].pb(u),len=min(inf,len<<1);
		}
		else{
			int x=read();
			if(x>len)puts("-1");
			else{
				for(int i=n;i;i--){
					if(x<=val[i].size()){
						printf("%lld\n",val[i][val[i].size()-x]);
						break;
					}
					x-=val[i].size()-1;
					if(x&1){
						printf("%lld\n",val[i][0]);
						break;
					}
					x>>=1;
				}
			}
		}
	}
	
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
