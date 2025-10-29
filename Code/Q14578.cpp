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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n;
string s[maxn];
int to[maxn][26],idx;
int sum[maxn];
void work(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];int l=s[i].size();
		int nd=0;for(int j=0;j<l;j++){
			int c=s[j]-'a';
			if(!to[nd][c])to[nd][c]=++idx;
			nd=to[nd][c];
		}
		sum[nd]++;
	}
	queue<int> q;
	for(int i=0;i<26;i++)if(to[0][i])q.push(to[0][i]);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<26;i++){
			if(to[u][i])
		}
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	
	T=1;
	while(T--)work();
}