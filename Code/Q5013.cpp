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
const int maxn=300010;
const int inf=1e9;
bool mbe;

inline vector<int> mul(const vector<int> &u,const vector<int> &v,int fl=0){
	if(!u.size())return v;
	if(!v.size())return u;
	int n=u.size()-1,m=v.size()-1;
	int p=0,q=0;
	while(p<=n&&u[p]==-inf)p++;
	while(q<=m&&v[q]==-inf)q++;
	if(p>n||q>m)return {-inf};
	vector<int> res;
	res.reserve(n+m+1+fl);
	for(int i=1;i<=p+q+fl;i++)res.pb(-inf);
	res.pb(u[p]+v[q]),p++,q++;
	while(p<=n&&q<=m){
		if(u[p]-u[p-1]>v[q]-v[q-1])res.pb(res.back()+u[p]-u[p-1]),p++;
		else res.pb(res.back()+v[q]-v[q-1]),q++;
	}
	while(p<=n)res.pb(res.back()+u[p]-u[p-1]),p++;
	while(q<=m)res.pb(res.back()+v[q]-v[q-1]),q++;
	return res;
}
inline void add(vector<int> &u,vector<int> v){
	int n=u.size()-1,m=v.size()-1;
	u.resize(max(n,m)+1,-inf);
	for(int i=0;i<=m;i++)u[i]=max(u[i],v[i]);
}

int n,a[maxn];
char s[maxn];
struct node{
	vector<int> f[2][2];
};
node cdq(int l,int r){
	if(l==r){
		node res;
		res.f[0][1]=res.f[1][0]={-inf};
		for(int o=0;o<2;o++)res.f[o][o]={a[l]==o};
		return res;
	}
	int mid=l+r>>1;
	node rl=cdq(l,mid),rr=cdq(mid+1,r);
	node res;
	for(int j=0;j<2;j++){
		for(int k=0;k<2;k++){
			for(int jj=0;jj<2;jj++){
				for(int kk=0;kk<2;kk++){
					add(res.f[j][kk],mul(rl.f[j][k],rr.f[jj][kk],(k==1&&jj==0)));
				}
			}
		}
	}
	// cout<<l<<" "<<r<<" s\n";
	// for(int j=0;j<2;j++){
		// for(int k=0;k<2;k++){
			// for(int v:res.f[j][k])cout<<v<<" ";cout<<"\n";
		// }
	// }
	return res;
}

inline void chkmx(int &u,int v){(u<v)&&(u=v);}
int ans[maxn];
int f[maxn][2];
void work(){
	n=read();scanf("%s",s+1);
	for(int i=1;i<=n;i++)a[i]=s[i]-'0';
	for(int i=1;i<=n;i++){
		f[i][0]=f[i-1][0];
		f[i][1]=max(f[i-1][1],f[i-1][0]);
		f[i][a[i]]++;
	}
	node res=cdq(1,n);
	for(int j=0;j<2;j++){
		for(int k=0;k<2;k++){
			for(int p=0;p<res.f[j][k].size();p++){
				int pp=p*2;
				if(j==1&&k==0)pp--;
				if(j==0&&k==1)pp++;
				ans[pp]=max(ans[pp],res.f[j][k][p]);
			}
		}
	}
	ans[2]=max(ans[2],ans[1]);
	ans[1]=max(f[n][0],f[n][1]);
	for(int i=1;i<=n;i++){
		chkmx(ans[i],ans[i-1]);
		printf("%lld ",ans[i]);
	}
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