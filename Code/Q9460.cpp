#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<__int128,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn];
__int128 s1,s2;
pii ans;
vector<int> res;
void calc(int p){
	__int128 val=s2*(__int128)m-s1*s1;
	// int v=val;
	// cout<<p<<" "<<v<<"\n";
	if(ans.fi<val){
		ans={val,p};
		res.clear();res.pb(p);
	}
	else if(ans.fi==val){
		res.pb(p);
	}
}
int st[maxn],tp;
int mn[2][20][maxn];
int que(int l,int r,int op){
	if(l>r)return inf;
	int k=log2(r-l+1);
	return min(mn[op][k][l],mn[op][k][r-(1<<k)+1]);
}
int id1[maxn],id2[maxn];
int pl[maxn],pr[maxn];
void work(){
	n=read();m=n-read();
	for(int i=1;i<=n;i++)a[i]=read(),id1[i]=id2[i]=i;
	if(m==1){puts("1");return ;}
	sort(id1+1,id1+n+1,[&](int u,int v){return (a[u]<a[v])||(a[u]==a[v]&&u<v);});
	sort(id2+1,id2+n+1,[&](int u,int v){return (a[u]<a[v])||(a[u]==a[v]&&u>v);});
	// for(int i=1;i<=n;i++)cout<<id1[i]<<" ";cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<id2[i]<<" ";cout<<"\n";
	for(int i=n;i;i--)pl[a[id1[i]]]=i;
	for(int i=1;i<=n;i++)pr[a[id2[i]]]=i;
	// cout<<pl[0]<<" "<<pl[1]<<" "<<pl[2]<<" "<<pl[3]<<"\n";
	// cout<<pr[0]<<" "<<pr[1]<<" "<<pr[2]<<" "<<pr[3]<<"\n";
	s1=0,s2=0;ans={0,0};res.clear();
	for(int i=n-m+1;i<=n;i++)s1+=a[id2[i]],s2+=a[id2[i]]*a[id2[i]];
	calc(0);
	for(int i=1;i<=m;i++){
		s1-=a[id2[n-m+i]];s2-=a[id2[n-m+i]]*a[id2[n-m+i]];
		s1+=a[id1[i]],s2+=a[id1[i]]*a[id1[i]];
		if(a[id1[i]]!=a[id2[n-m+i+1]]){
			// cout<<i<<" "<<id1[i]<<" "<<a[id1[i]]<<" "<<n-m+i+1<<" "<<id2[n-m+i+1]<<" "<<a[id2[n-m+i+1]]<<"\n";
			calc(i);
		}
	}
	int pos=res.front();
	// cout<<(int)ans.fi<<" "<<res.size()<<"\n";
	// for(int i:res)cout<<i<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)mn[0][0][i]=id1[i];
	for(int j=1;j<20;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)mn[0][j][i]=min(mn[0][j-1][i],mn[0][j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=n;i++)mn[1][0][i]=id2[i];
	for(int j=1;j<20;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)mn[1][j][i]=min(mn[1][j-1][i],mn[1][j-1][i+(1<<j-1)]);
	}
	a[0]=-1;
	for(int i=1;i<res.size();i++){
		// cout<<i<<" "<<res[i]<<" "<<pos<<"\n";
		int vl=inf,vr=inf;
		int ll=pos+1,lr=res[i],rl=n-m+pos+1,rr=n-m+res[i];
		// cout<<ll<<" "<<lr<<" "<<a[id1[lr]]<<" "<<vl<<"\n";
		// cout<<rl<<" "<<rr<<" "<<a[id2[rl]]<<" "<<vr<<"\n";
		if(a[id1[lr]]==a[id2[rl]]){
			vl=que(ll,pl[a[id1[lr]]]-1,0),vr=que(pr[a[id2[rl]]]+1,rr,1);
			int len=min(lr-pl[a[id1[lr]]],pr[a[id2[rl]]]-rl)+1;
			vl=min(vl,que(pl[a[id1[lr]]]+len,lr,0));
			vr=min(vr,que(rl,pr[a[id2[rl]]]-len,1));
		}
		else vl=que(ll,lr,0),vr=que(rl,rr,1);
		if(vl<vr)pos=res[i];
	}
	// cout<<pos<<"\n";
	tp=0;
	for(int i=1;i<=pos;i++)st[++tp]=id1[i];
	for(int i=n-m+pos+1;i<=n;i++)st[++tp]=id2[i];
	sort(st+1,st+tp+1);
	for(int i=1;i<tp;i++)printf("%lld ",st[i]);printf("%lld\n",st[tp]);
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
	
	T=read();
	while(T--)work();
}