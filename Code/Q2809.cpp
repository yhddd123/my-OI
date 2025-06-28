#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}

int n;
unordered_map<int,int> mp[38];
void reid(int lim,int &s){
	for(int i=lim+1;i<=37;i++)if(s&(1ll<<i)){
		bool fl=1;
		for(int j=1;j<=lim;j++)if(i%j==0){
			if(!(s&(1ll<<j)))fl=0;
		}
		if(fl)s^=1ll<<i;
	}
}
int calc(int lim,int s){
	// cout<<lim<<" "<<s<<"\n";
	if(lim==0)return 1;
	reid(lim,s);
	if(mp[lim].find(s)!=mp[lim].end())return mp[lim][s];
	int ans=0,t=s;
	if(!(s&(1ll<<lim)))ans+=calc(lim-1,s);
	t|=1ll<<lim;for(int i=lim+1;i<=37;i++)if(t&(1ll<<i))t|=1ll<<__gcd(lim,i);
	ans+=calc(lim-1,t);
	return mp[lim][s]=ans;
}
void work(){
	n=read()+1;int s=0;
	for(int lim=37;lim;lim--){
		if(s&(1ll<<lim)){
			s|=1ll<<lim;for(int i=lim+1;i<=37;i++)if(s&(1ll<<i))s|=1ll<<__gcd(lim,i);
		}
		else{
			if(n>calc(lim-1,s)){
				n-=calc(lim-1,s);
				s|=1ll<<lim;for(int i=lim+1;i<=37;i++)if(s&(1ll<<i))s|=1ll<<__gcd(lim,i);
			}
		}
	}
	printf("%lld ",__builtin_popcountll(s));
	for(int i=1;i<=37;i++)if(s&(1ll<<i))printf("%d ",i);puts("");
}

int T;
signed main(){
	// freopen("ihatemath.in","r",stdin);
	// freopen("ihatemath.out","w",stdout);

	T=read();
	while(T--)work();
}