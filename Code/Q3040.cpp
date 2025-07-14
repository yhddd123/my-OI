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
const int maxn=1010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,c;
char s[maxn],t[maxn];
vector<pii> ans;
int f[maxn][maxn];
int fr[maxn][maxn];
int sum[2][maxn];
vector<int> pos[2];
int st[maxn],tp;
int to[maxn];
vector<int> id;
void work(){
	n=read();c=read();
	scanf("%s%s",s+1,t+1);
	for(int i=1;i<=n;i++)if(t[i]=='2'){
		pos[i&1].pb(i),sum[i&1][i]++;
	}
	for(int i=1;i<=n;i++){
		sum[0][i]+=sum[0][i-1];
		sum[1][i]+=sum[1][i-1];
	}
	for(int i=1;i<=n;i++)if(s[i]=='2')st[++tp]=i;
	mems(f,0x3f);
	f[0][0]=0;
	for(int i=1;i<=tp;i++){
		for(int j=0;j<i;j++)if(f[i-1][j]<=inf){
			if(j<pos[0].size()){
				int x=pos[0][j],d=abs(st[i]-x);
				int val=f[i-1][j]+(d/2)*(c+4)+(d&1)*(c+3)+max(0ll,sum[1][x]-(i-1-j));
				if(f[i][j+1]>val){
					f[i][j+1]=val;
					fr[i][j+1]=1;
				}
			}
			if(i-1-j<pos[1].size()){
				int x=pos[1][i-1-j],d=abs(st[i]-x);
				int val=f[i-1][j]+(d/2)*(c+4)+(d&1)*(c+3)+max(0ll,sum[0][x]-j);
				if(f[i][j]>val){
					f[i][j]=val;
					fr[i][j]=2;
				}
			}
		}
	}
	// printf("%lld\n",f[tp][pos[0].size()]);
	int x=pos[0].size();
	for(int i=tp;i;i--){
		if(fr[i][x]==1){
			to[st[i]]=pos[0].back();pos[0].pop_back();
			x--;
		}
		else{
			to[st[i]]=pos[1].back();pos[1].pop_back();
		}
	}
	// for(int i=1;i<=tp;i++)cout<<st[i]<<" "<<to[st[i]]<<"\n";
	for(int i=1;i<=tp;i++)if(st[i]<to[st[i]])id.pb(st[i]);
	reverse(id.begin(),id.end());
	for(int p:id){
		int ed=to[p];
		while(p+2<=ed)ans.pb({p,p+2}),p+=2;
		if(p<ed)ans.pb({p,p+1});
	}
	id.clear();
	for(int i=1;i<=tp;i++)if(st[i]>to[st[i]])id.pb(st[i]);
	for(int p:id){
		int ed=to[p];
		while(p-2>=ed)ans.pb({p-2,p}),p-=2;
		if(p>ed)ans.pb({p-1,p});
	}
	printf("%lld\n",ans.size());
	for(pii p:ans)printf("%lld %lld\n",p.fi,p.se);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen("machine.in","r",stdin);
//	freopen("machine.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
