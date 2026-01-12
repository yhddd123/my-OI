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
const int maxn=510;
const int inf=1e9;
bool mbe;

int n,a[maxn];
int mn[maxn][maxn],mx[maxn][maxn],smn[maxn][maxn],smx[maxn][maxn];
int f[maxn][maxn][3][4];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		pii vmx={0,0},vsmx={0,0},vmn={n+1,0},vsmn={n+1,0};
		for(int j=i;j<=n;j++){
			if(a[j]>vmx.fi)vsmx=vmx,vmx={a[j],j};
			else if(a[j]>vsmx.fi)vsmx={a[j],j};
			if(a[j]<vmn.fi)vsmn=vmn,vmn={a[j],j};
			else if(a[j]<vsmn.fi)vsmn={a[j],j};
			mn[i][j]=vmn.se,mx[i][j]=vmx.se,smn[i][j]=vsmn.se,smx[i][j]=vsmx.se;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			for(int o1=0;o1<=2;o1++){
				f[i][j][o1][1]=1;
			}
		}
		for(int o1=0;o1<=2;o1++){
			for(int o2=0;o2<=3;o2++)f[i][i][o1][o2]=1;
		}
	}
	for(int len=2;len<=n;len++){
		for(int i=1,j=len;j<=n;i++,j++){
			for(int o=0;o<=2;o++){
				int pmn=mn[i][j],pmx=mx[i][j];
				if(o==1)pmx=pmn,pmn=smn[i][j];
				if(o==2)pmn=pmx,pmx=smx[i][j];
				for(int k=i;k<min(pmn,pmx);k++){
					(f[i][j][o][1]+=f[i][k][0][0]*(f[k+1][j][o][1]-(i==k)))%=mod;
					(f[i][j][o][2]+=f[i][k][0][0]*(f[k+1][j][o][2]))%=mod;
					(f[i][j][o][3]+=f[i][k][0][0]*(f[k+1][j][o][3]))%=mod;
				}
				int o1,o2;
				if(!o)o1=o2=0;
				if(o==1)o1=pmn>pmx?1:0,o2=pmn<pmx?1:0;
				if(o==2)o1=pmn<pmx?2:0,o2=pmn>pmx?2:0;
				for(int k=min(pmn,pmx);k<max(pmn,pmx);k++){
					(f[i][j][o][1]+=f[i][k][o1][0]*(f[k+1][j][o2][1]-(i==k)))%=mod;
					(f[i][j][o][pmn<pmx?3:2]+=f[i][k][o1][0]*(f[k+1][j][o2][pmn<pmx?3:2]))%=mod;
				}
				// cout<<i<<" "<<j<<" "<<o<<" "<<f[i][j][o][1]<<"\n";
				for(int k=max(pmn,pmx);k<j;k++){
					(f[i][j][o][1]+=f[i][k][o][0]*f[k+1][j][0][1])%=mod;
				}
				if(!o)o1=pmn<pmx?1:2,o2=pmn<pmx?2:1;
				if(o==1)o1=pmn<pmx?1:0,o2=pmn>pmx?1:0;
				if(o==2)o1=pmn>pmx?2:0,o2=pmn<pmx?2:0;
				int sum=0;
				for(int k=min(pmn,pmx);k<max(pmn,pmx);k++){
					(sum+=f[i][k][o1][0]*(f[k+1][j][o2][pmn<pmx?2:3]))%=mod;
				}
				for(int o1=0;o1<=3;o1++)(f[i][j][o][o1]+=sum)%=mod;
				// cout<<i<<" "<<j<<" "<<o<<" "<<f[i][j][o][1]<<" a\n";
			}
		}
	}
	printf("%lld\n",f[1][n][0][1]);
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