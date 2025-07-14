#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n;
string c;
unordered_map<string,int> mp;
int pos[maxn],idx;
int tree[maxn][30],cnt;
int ed[maxn],fail[maxn],in[maxn],s[maxn];
void insert(string c,int id){
	int len=c.size(),nd=0;
	for(int i=0;i<len;i++){
		if(!tree[nd][c[i]-'a'+1])tree[nd][c[i]-'a'+1]=++cnt;
		nd=tree[nd][c[i]-'a'+1];
	}
	ed[nd]=id;
}
queue<int> q;
void build(){
	for(int i=1;i<=26;i++){
		if(tree[0][i])q.push(tree[0][i]);
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=1;i<=26;i++){
			if(tree[u][i]){
				fail[tree[u][i]]=tree[fail[u]][i];
				in[fail[tree[u][i]]]++;
				q.push(tree[u][i]);
			}
			else tree[u][i]=tree[fail[u]][i];
		}
	}
}
int ans[maxn];
void query(string c){
	int len=c.size(),nd=0;
	for(int i=0;i<len;i++){
		nd=tree[nd][c[i]-'a'+1];
		s[nd]++;
	}
}
void topu(){
	for(int i=1;i<=cnt;i++)if(!in[i])q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		ans[ed[u]]=s[u];
		in[fail[u]]--;
		s[fail[u]]+=s[u];
		if(!in[fail[u]])q.push(fail[u]);
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++){
		cin>>c;
		if(!mp[c]){
			mp[c]=++idx;
			insert(c,idx);
		}
		pos[i]=mp[c];
	}
	build();
//	for(int i=1;i<=cnt;i++)cout<<fail[i]<<" ";
//	cout<<"\n";
	cin>>c;query(c);
//	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
//	cout<<"\n";
	topu();
	for(int i=1;i<=n;i++)printf("%lld\n",ans[pos[i]]);
}
