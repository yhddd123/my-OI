#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=2000010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define vi vector<int>
#define pb push_back

int n,a[maxn],ans;
struct bit{
	int tree[maxn];
	void clear(){memset(tree,0,sizeof(tree));}
	int lowbit(int x){return x&(-x);}
	void updata(int x){
		x++;
		while(x<maxn){
			tree[x]^=1;
			x+=lowbit(x);
		}
	}
	int query(int x){
		x++;
		int res=0;
		while(x){
			res^=tree[x];
			x-=lowbit(x);
		}
		return res;
	}
}t;
int pw[21];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)a[i]=read()+a[i-1];
	pw[0]=1;for(int i=1;i<=20;i++)pw[i]=pw[i-1]<<1;
	for(int j=0;j<=19;j++){
		if(pw[j]>a[n])break;
		t.clear();
		int res=0;
		t.updata(0);
		for(int i=1;i<=n;i++){
			int x=a[i]%(pw[j+1]);
			if(x<pw[j])res^=t.query(x+pw[j])^t.query(x);
			else res^=t.query(x-pw[j])^t.query(x)^(i&1);
			t.updata(x);
		}
		ans+=res*pw[j];
//		cout<<res<<" "<<ans<<"\n";
	}
	printf("%lld\n",ans);
}
