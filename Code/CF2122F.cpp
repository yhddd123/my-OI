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
const int maxn=22;
const int inf=1e9;
bool mbe;

int n,a[maxn];
int b[maxn][2],m;
void sovle(int l,int r){
	if(l==r)return ;
	int mid=l+r>>1;
	int s1=0,s2=0;
	for(int i=l;i<=mid;i++)s1+=a[i];
	for(int i=mid+1;i<=r;i++)s2+=a[i];
	b[++m][0]=s1-1,b[m][1]=s2-1;
	sovle(l,mid),sovle(mid+1,r);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sovle(1,n);
	vector<pii> ans,ans2;
	for(int i=1,x=0,y=0;i<=m;i++){
		if(i%2==1){
			if(i>1)x+=2;
			ans.pb({x,y});
			for(int j=1;j<=b[i][0];j++)ans.pb({x,++y});
			ans.pb({x,y=100});
		}else{
			if(i>1){
				x+=2,y++,ans.pb({x,y});
				x+=2,y--;
			}
			ans.pb({x,y});
			for(int j=1;j<=b[i][1];j++)ans.pb({x,--y});
			ans.pb({x,y=0});
		}
	}
	reverse(ans.begin(),ans.end());
	for(int i=1,x=1,y=0;i<=m;i++){
		if(i%2==1){
			if(i>1){
				x+=2,y--,ans.pb({x,y});
				x+=2,y++;
			}
			ans.pb({x,y});
			for(int j=1;j<=b[i][1];j++)ans.pb({x,++y});
			ans.pb({x,y=100});
		}else{
			if(i>1)x+=2;
			ans.pb({x,y});
			for(int j=1;j<=b[i][0];j++)ans.pb({x,--y});
			ans.pb({x,y=0});
		}
	}
	printf("%d\n",ans.size());
	for(auto[u,v]:ans)printf("%d %d\n",u,v);
	
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