#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db long double
using namespace std;
const int maxn=200010;
const int inf=1e18;
const db eps=1e-6;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

db ppmx,a,b,c,d,e,f;
void work(){
	cin>>ppmx>>a>>b>>c>>d>>e>>f;
	db acc=(300*a+300*b+200*c+100*d+50*e)/(300*(a+b+c+d+e+f))*100;
	db pp=max((db)0,(320*a+300*b+200*c+100*d+50*e)/(320*(a+b+c+d+e+f))-0.8)*5*ppmx;
	pp+=0.5+eps;
	// cout<<pp<<"\n";
	printf("%.2Lf%% %lld\n",acc,(int)pp);
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
	
	cin>>T;
	while(T--)work();
}