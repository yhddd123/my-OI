#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=600010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],s[4][maxn],numa,numb,res;
int ans[maxn][3],pos[maxn];
priority_queue<pii> q;
void mk(int na,int nb){
	for(int i=1,j=1;i<=na;i++){
		while(a[j]!=1)j++;
		ans[i][1]=j;pos[j]=i;j++;
	}
	for(int i=1,j=1;i<=nb;i++){
		while(a[j]!=3)j++;
		ans[i+na][1]=j;pos[j]=i+na;j++;
	}
	for(int i=na,j=n;i;i--){
		while(a[j]!=3)j--;
		ans[i][3]=j;j--;
	}
	for(int i=nb,j=n;i;i--){
		while(a[j]!=1)j--;
		ans[i+na][3]=j;j--;
	}
	for(int i=1;i<=n;i++){
		if(pos[i])q.push({-ans[pos[i]][3],pos[i]});
		if(a[i]==2&&!q.empty()){
			ans[q.top().se][2]=i;q.pop();
		}
	}
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	// for(int i=1;i<=n;i++)cout<<i<<" "<<a[i]<<"\n";
	for(int j=1;j<=3;j++)for(int i=1;i<=n;i++)s[j][i]=s[j][i-1]+(a[i]==j);
	// cout<<s[1][n]<<" "<<s[2][n]<<" "<<s[3][n]<<"\n";
	numa=numb=res=n;
	// for(int na=0;na<=5;na++)for(int nb=0;nb<=5;nb++){
		// bool fl=1;
		// for(int l=1;l<=n;l++)for(int r=l;r<=n;r++){
			// if(max(na-s[1][l-1]-s[3][n]+s[3][r],0ll)+max(nb-s[3][l-1]-s[1][n]+s[1][r],0ll)>s[2][r]-s[2][l-1])fl=0;
			// // cout<<max(2-s[1][l-1]-s[3][n]+s[3][r],0ll)+max(1-s[3][l-1]-s[1][n]+s[1][r],0ll)<<" "<<s[2][r]-s[2][l-1]<<"\n";
		// }
		// if(fl)cout<<na<<" "<<nb<<"\n";
	// }
	for(int i=1,mna=0,mnb=0,mnans=0;i<=n;i++){
		numa=min(numa,s[2][i]+s[3][n]-s[3][i]+mna);
		mna=min(mna,s[1][i]-s[2][i]);
		numb=min(numb,s[2][i]+s[1][n]-s[1][i]+mnb);
		mnb=min(mnb,s[3][i]-s[2][i]);
		res=min(res,s[2][i]+s[1][n]-s[1][i]+s[3][n]-s[3][i]+mnans);
		mnans=min(mnans,s[1][i]+s[3][i]-s[2][i]);
	}
	// printf("%lld\n",res);
	// cout<<numa<<" "<<numb<<"\n";
	numb=min(res-numa,min({s[1][n],s[2][n],s[3][n]})-numa);
	res=numa+numb;printf("%lld\n",res);
	mk(numa,numb);
	for(int i=1;i<=numa+numb;i++)printf("%lld %lld %lld\n",ans[i][1]-1,ans[i][2]-1,ans[i][3]-1);
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
