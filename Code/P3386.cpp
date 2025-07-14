#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;
int m,n,ans,bk[maxn],match[maxn],f[maxn],x;
int head[maxn],tot;
struct nd{
	int to,nxt;
}e[50010];
void add(int x,int y){
	e[++tot].nxt=head[x];
	e[tot].to=y;
	head[x]=tot;
}
bool dfs(int x){
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(!bk[y]){
			bk[y]=1;
			if(!match[y] || dfs(match[y])){
				match[y]=x;
//				cout<<x<<" "<<y<<endl;
				return true;
			}
		}
	}
	return false;
}
int main(){
	scanf("%d%d%d",&m,&n,&x);
	n+=m;
	int u,v;
	for(int i=1;i<=x;i++){
		scanf("%d%d",&u,&v);
		v+=m;
		add(u,v);
//		cout<<u<<" "<<v<<endl;
	}
	for(int i=1;i<=m;i++){
		memset(bk,0,sizeof(bk));
		if(dfs(i)==true){
			ans++;
		}
	}
	printf("%d\n",ans);
} 
