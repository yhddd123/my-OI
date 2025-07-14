//p3808
#include<bits/stdc++.h>
#define str string
using namespace std;
const int maxn=1000010;
int n;
int fail[maxn],trie[maxn][30],cntword[maxn],cnt;
str s;

void inword(str s){
	int root=0;
	for(int i=0;i<s.size();i++){
		int nxt=s[i]-'a';
		if(!trie[root][nxt])	trie[root][nxt]=++cnt;
		root=trie[root][nxt];
	}
	++cntword[root];
}

void getfail(){
	queue<int> q;
	for(int i=0;i<26;i++){
		if(trie[0][i]){
			fail[trie[0][i]]=0;
			q.push(trie[0][i]);
		}
	}
	while(!q.empty()){
		int now=q.front();	q.pop();
		for(int i=0;i<26;i++){
			if(trie[now][i]){
				fail[trie[now][i]]=trie[fail[now]][i];
				q.push(trie[now][i]);
			}	
			else	trie[now][i]=trie[fail[now]][i];
		}
	}
}

int query(str s){
	int now=0,ans=0;
	for(int i=0;i<s.size();i++){
		now=trie[now][s[i]-'a'];
		for(int j=now;j && cntword[j]!=-1;j=fail[j]){
			ans+=cntword[j];
			cntword[j]=-1;
		}
	}
	return ans;
}

signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>s;
		inword(s);
	}
	fail[0]=0;
	getfail();
	cin>>s;
	printf("%d",query(s));
}
