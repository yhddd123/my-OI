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
const int maxn=1000010;
const int maxk=1010;
const int inf=1e9;
bool mbe;

int n,m,k;
char s[maxn],t[maxn];
int f[maxk][maxk<<1],pre[maxk][maxk<<1];
mt19937 rnd(time(0));
int bas,val[26],pw[maxn];
struct hsh{
	int h[maxn];
	int que(int l,int r){return (h[r]+mod-1ll*h[l-1]*pw[r-l+1]%mod)%mod;}
}h1,h2;
void work(){
	n=read();m=read();k=read();scanf("%s%s",s+1,t+1);
	if(abs(n-m)>k){puts("NO");return ;}
	bas=rnd()%mod;for(int i=0;i<26;i++)val[i]=rnd()%mod;
	pw[0]=1;for(int i=1;i<=max(n,m);i++)pw[i]=1ll*pw[i-1]*bas%mod;
	for(int i=1;i<=n;i++)h1.h[i]=(1ll*h1.h[i-1]*bas+val[s[i]-'a'])%mod;
	for(int i=1;i<=m;i++)h2.h[i]=(1ll*h2.h[i-1]*bas+val[t[i]-'a'])%mod;
	memset(f,-1,sizeof(f));
	f[0][k]=0;
	// cout<<h1.que(2,3)<<" "<<h2.que(3,4)<<"\n";
	for(int i=0;i<=k;i++){
		for(int j=-k;j<=k;j++){
			int &p=f[i][j+k];
			if(p<0)continue;
			int l=1,r=min(n-p,m-(p+j)),res=0;
			while(l<=r){
				int mid=l+r>>1;
				if(h1.que(p+1,p+mid)==h2.que(p+j+1,p+j+mid))res=mid,l=mid+1;
				else r=mid-1;
			}
			p+=res;
			// cout<<i<<" "<<j<<" "<<p<<" "<<res<<" "<<min(n-p,m-(p+j))<<"\n";
			if(p+1<=n&&p+1+j<=m&&f[i+1][j+k]<p+1){
				f[i+1][j+k]=p+1;
				pre[i+1][j+k]=j;
			}
			if(-k<j&&p+1<=n&&f[i+1][j-1+k]<p+1){
				f[i+1][j-1+k]=p+1;
				pre[i+1][j-1+k]=j;
			}
			if(j<k&&p+j+1<=m&&f[i+1][j+1+k]<p){
				f[i+1][j+1+k]=p;
				pre[i+1][j+1+k]=j;
			}
		}
	}
	int kk=-1;for(int i=0;i<=k;i++)if(f[i][m-n+k]==n){kk=i;break;}
	if(kk==-1){puts("NO");return ;}
	puts("YES");
	printf("%d\n",kk);
	for(int i=kk,j=m-n;i;i--){
		int nw=pre[i][j+k];
		int p=f[i-1][nw+k];
		if(j==nw){
			printf("REPLACE %d %c\n",p+1,t[p+1+j]);
		}
		else if(j==nw-1){
			printf("DELETE %d\n",p+1);
		}
		else if(j==nw+1){
			printf("INSERT %d %c\n",p+1,t[p+j]);
		}
		// else{
			// cerr<<kk<<" "<<i<<" "<<j<<" "<<f[i][j+k]<<" "<<nw<<" "<<p<<endl;
			// exit(0);
		// }
		j=nw;
	}
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