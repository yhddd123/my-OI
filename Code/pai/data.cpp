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

int n;
mt19937 rnd(time(0));
int st[maxn],tp;
vector<int> e[maxn];
void work(){
	n=200000;
	st[tp=1]=1;
	vector<int> id;
	for(int i=2;i<=n;i++){
		while(tp>1&&(rnd()%3))tp--;
		id.pb(st[tp]),e[st[tp]].pb(i);
		st[++tp]=i;
	}
	shuffle(id.begin(),id.end(),rnd);
	for(int i=1;i<=n;i++)reverse(e[i].begin(),e[i].end());
	cout<<n<<"\n";
	for(int u:id){
		cout<<u<<" "<<e[u].back()<<"\n";
		e[u].pop_back();
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}