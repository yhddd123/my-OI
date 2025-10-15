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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
int id[maxn];
mt19937 rnd(time(0));
int tim;
int ask(int i,int j,int k){
	cout<<"? "<<i<<" "<<k<<" "<<j<<endl;
	return read();
	++tim;
	return (a[i]<=a[j]&&a[j]<=a[k])||(a[k]<=a[j]&&a[j]<=a[i]);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=i;
	shuffle(a+1,a+n+1,rnd);
	for(int i=1;i<=n;i++)id[i]=i;
	shuffle(id+1,id+n+1,rnd);
	int x=id[1],y=id[2];
	for(int i=3;i<=n;i++){
		if(ask(x,id[i],y)){}
		else if(ask(x,y,id[i]))y=id[i];
		else x=id[i];
	}
	cout<<"! "<<x<<" "<<y<<endl;
	// cout<<a[x]<<" "<<a[y]<<"\n";
	// cout<<tim<<"\n";
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