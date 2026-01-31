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
const int maxn=55;
const int maxk=10;
const int maxl=2;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int n,m,k,lim;
vector<pii> e[maxk];
struct node{
	int a[maxl];
	inline bool val(){
		for(int i=0;i<lim;i++)if(a[i])return true;
		return false;
	}
	inline int lb(){
		for(int i=0;i<lim;i++)if(a[i])return i;
		return lim;
	}
	node(){mems(a,0);}
	inline node&operator+=(const node&v){
		for(int i=0;i<lim;i++)inc(this->a[i],v.a[i]);
		return *this;
	}
	inline node&operator-=(const node&v){
		for(int i=0;i<lim;i++)inc(this->a[i],mod-v.a[i]);
		return *this;
	}
};
inline node operator+(node &u,node &v){
	node res;
	for(int i=0;i<lim;i++)inc(res.a[i]=u.a[i],v.a[i]);
	return res;
}
inline node operator-(node &u,node &v){
	node res;
	for(int i=0;i<lim;i++)inc(res.a[i]=u.a[i],mod-v.a[i]);
	return res;
}
inline node operator*(node &u,node &v){
	node res;
	for(int i=0;i<lim;i++){
		for(int j=0;j<=i;j++)inc(res.a[i],1ll*u.a[j]*v.a[i-j]%mod);
	}
	return res;
}
inline node operator/(node &u,node &v){
	node res;
	int ni=ksm(v.a[0]);
	for(int i=0;i<lim;i++){
		res.a[i]=u.a[i];
		for(int j=0;j<i;j++)inc(res.a[i],mod-1ll*res.a[j]*v.a[i-j]%mod);
		res.a[i]=1ll*res.a[i]*ni%mod;
	}
	return res;
}
inline void shiftlow(node &u,int k){
	if(k>=lim)u=node();
	else{
		for(int i=0;i<lim-k;i++)u.a[i]=u.a[i+k];
		for(int i=lim-k;i<lim;i++)u.a[i]=0;
	}
}
inline void shifthigh(node &u,int k){
	if(k>=lim)u=node();
	else{
		for(int i=lim-1;i>=k;i--)u.a[i]=u.a[i-k];
		for(int i=0;i<k;i++)u.a[i]=0;
	}
}
node a[maxn][maxn];
node det(){
	int a0=1,pw=0;
	for(int i=1;i<=n;i++){
		pii mn={a[i][i].lb(),i};
		for(int j=i+1;j<=n;j++)mn=min(mn,{a[j][i].lb(),j});
		// cout<<mn.fi<<" "<<mn.se<<"\n";
		if(mn.fi==lim)return node();
		if(mn.se!=i){
			swap(a[i],a[mn.se]);
			a0=-a0;
		}
		pw+=mn.fi;
		if(pw>=lim)return node();
		for(int j=i;j<=n;j++)shiftlow(a[j][i],mn.fi);
		for(int j=i+1;j<=n;j++){
			if(a[j][i].val()){
				node d=a[j][i]/a[i][i];
				for(int k=i;k<=n;k++){
					node tmp=d*a[i][k];
					a[j][k]-=tmp;
				}
			}
		}
	}
	node res;
	res.a[0]=(a0==1?1:mod-1);
	for(int i=1;i<=n;i++)res=res*a[i][i];
	if(pw)shifthigh(res,pw);
	return res;
}
node ans[1<<maxk];
mt19937 rnd(0);
int rd[maxn][maxn];
void work(){
	n=read();m=read();k=read();lim=2;
	for(int i=0;i<k;i++)e[i].clear();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),c=read()-1;
		e[c].pb({u,v});
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)rd[i][j]=rnd()%mod;
	}
	for(int s=1;s<(1<<k);s++){
		for(int i=1;i<=n;i++){	
			for(int j=1;j<=n;j++)a[i][j]=node();
		}
		for(int i=0;i<k;i++){
			for(auto[u,v]:e[i]){
				if(s&(1<<i))inc(a[u][v].a[0],rd[u][v]);
				if(s&(1<<(i+1)%k))inc(a[u][v].a[1],rd[u][v]);
				if(s&(1<<(i+k-1)%k))inc(a[u][v].a[1],rd[u][v]);
			}
		}
		// cout<<s<<"\n";
		// for(int i=1;i<=n;i++){	
			// for(int j=1;j<=n;j++)cout<<i<<" "<<j<<" "<<a[i][j].a[0]<<" "<<a[i][j].a[1]<<"\n";
		// }
		ans[s]=det();
		// cout<<s<<" "<<ans[s].a[0]<<" "<<ans[s].a[1]<<"\n";
	}
	for(int i=0;i<k;i++){
		for(int s=0;s<(1<<k);s++)if(s&(1<<i))ans[s]-=ans[s^(1<<i)];
	}
	for(int s=0;s<(1<<k);s++)putchar(ans[s].val()?'1':'0');puts("");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}