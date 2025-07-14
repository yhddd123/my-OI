#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=410;
const int maxm=3010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],ans;
struct data{
	int dp[3][3];
	data(){mems(dp,-1);}
	void clear(){mems(dp,-1);}
	bool check(){
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++)if(dp[i][j]>=4)return true;
		}
		return false;
	}
	bool operator <(const data&tmp)const{
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++)if(dp[i][j]!=tmp.dp[i][j])return dp[i][j]<tmp.dp[i][j];
		}
		return 0;
	}
	bool operator !=(const data&tmp)const{
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++)if(dp[i][j]!=tmp.dp[i][j])return true;
		}
		return false;
	}
	void go(data &res,int x){
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++)if(~dp[i][j]){
				for(int k=0;k<3;k++)if(x>=i+j+k)res.dp[j][k]=max(res.dp[j][k],min(4ll,dp[i][j]+(x-i-j-k)/3+i));
			}
		}
	}
};
struct am{
	data p[2];int cnt;
	void clear(){
		p[0].clear();p[1].clear();cnt=-1;
	}
	bool check(){
		if(cnt>=7||p[1].check()){
			clear();
			return true;
		}
		return false;
	}
	bool operator<(const am&tmp)const{
		if(cnt!=tmp.cnt)return cnt<tmp.cnt;
		if(p[0]!=tmp.p[0])return p[0]<tmp.p[0];
		if(p[1]!=tmp.p[1])return p[1]<tmp.p[1];
		return 0;
	}
}st,ed;
am trans(am u,int x){
	if(u.cnt==-1)return u;
	am res;
	if(x>=2)u.p[0].go(res.p[1],x-2);
	u.p[0].go(res.p[0],x);
	u.p[1].go(res.p[1],x);
	res.cnt=u.cnt+(x>=2);
	res.check();
	return res;
}
queue<am> q;
map<am,int> id;
int idx,nxt[maxm][5];
void bfs(){
	st.p[0].dp[0][0]=0;
	id[st]=++idx;q.push(st);
	while(!q.empty()){
		am u=q.front();q.pop();
		for(int i=0;i<=4;i++){
			am nw=trans(u,i);
			if(id.find(nw)==id.end()){
				id[nw]=++idx;
				q.push(nw);
			}
			nxt[id[u]][i]=id[nw];
		}
	}
	ed=st;ed.clear();
}
inline int ksm(int a,int b=mod-2,int p=mod){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
int fac[maxn],inv[maxn];
int C(int m,int n){
	if(m<n)return 0;
	return fac[m]*inv[n]%mod*inv[m-n]%mod;
}
int dp[2][maxn][maxm],cur;
void work(){
	n=read();bfs();
	for(int i=1;i<=13;i++){
		int u=read(),v=read();
		a[u]++;
	}
	fac[0]=1;for(int i=1;i<=(n<<2);i++)fac[i]=fac[i-1]*i%mod;
	inv[n<<2]=ksm(fac[n<<2]);
	for(int i=(n<<2)-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	dp[0][0][id[st]]=1;cur=0;int s=4*n-13;
	for(int i=1;i<=n;i++){
		mems(dp[i&1],0);
		for(int j=s;j>=0;j--){
			for(int k=1;k<=idx;k++)if(dp[cur][j][k]){
				for(int l=0;l<=4-a[i]&&l+j<=s;l++){
					dp[i&1][j+l][nxt[k][l+a[i]]]+=dp[cur][j][k]*C(4-a[i],l)%mod;
					dp[i&1][j+l][nxt[k][l+a[i]]]%=mod;
				}
			}
		}
		cur^=1;
	}
	for(int i=1;i<=s;i++){
		for(int k=1;k<=idx;k++){
			if(k==id[ed])continue;
			ans+=dp[n&1][i][k]*fac[i]%mod*fac[s-i]%mod,ans%=mod;
		}
	}
	printf("%lld\n",ans*inv[s]%mod+1);
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
