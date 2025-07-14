#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

string c,t;
int tree[maxn][27],cnt;
int fail[maxn],e[maxn];
void insert(string c){
	int len=c.size(),nd=0;
	for(int i=0;i<len;i++){
		if(!tree[nd][c[i]-'a'+1])tree[nd][c[i]-'a'+1]=++cnt;
		nd=tree[nd][c[i]-'a'+1];
	}
	e[nd]=len;
}
queue<int> q;
void build(){
	for(int i=1;i<=26;i++)if(tree[0][i])q.push(tree[0][i]);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=1;i<=26;i++){
			if(tree[u][i]){
				fail[tree[u][i]]=tree[fail[u]][i];
				q.push(tree[u][i]);
			}
			else tree[u][i]=tree[fail[u]][i];
		}
	}
}
int st[maxn],tp,ans[maxn];
void sovle(string c){
	int len=c.size(),nd=0;
	for(int i=0;i<len;i++){
		nd=tree[nd][c[i]-'a'+1];
		st[++tp]=nd;
		ans[tp]=i;
		if(e[nd]){
			tp-=e[nd];
			if(!tp)nd=0;
			else nd=st[tp];
		}
	}
}

signed main(){
	cin>>t;cin>>c;
	insert(c);build();
	sovle(t);
	for(int i=1;i<=tp;i++)cout<<t[ans[i]];
}
