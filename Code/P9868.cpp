#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-'0');ch=getchar();}
	return x*fl; 
}
const int maxn=3010;

int n,m;
char c[maxn][maxn];
int nw[maxn],s[maxn];
int t[maxn][26];
int mn[maxn],se[maxn],pos;
signed main(){
	scanf("%d%d",&n,&m);
	if(n==1){
		printf("1\n");
		return 0;
	}
	for(int i=1;i<=n;i++){
		scanf("%s",c[i]+1);
		for(int j=1;j<=m;j++)t[i][c[i][j]-'a']++;
		int p=0;
		for(int j=25;j>=0;j--){
			for(int k=1;k<=t[i][j];k++)s[++p]=j;
		}
		if(i==1){
			for(int j=1;j<=m;j++)mn[j]=s[j];
			pos=i;
		}
		else if(i==2){
			bool fl=0;
			for(int j=1;j<=m;j++){
				if(s[j]<mn[j]){
					fl=1;
					break;
				}
				if(s[j]>mn[j])break;
			}
			if(fl){
				for(int j=1;j<=m;j++)se[j]=mn[j],mn[j]=s[j];
				pos=i;
			}
			else{
				for(int j=1;j<=m;j++)se[j]=s[j];
			}
		}
		else{			
			bool fl=0;
			for(int j=1;j<=m;j++){
				if(s[j]<mn[j]){
					fl=1;
					break;
				}
				if(s[j]>mn[j])break;
			}
			if(fl){
				for(int j=1;j<=m;j++)se[j]=mn[j],mn[j]=s[j];
				pos=i;
			}
			else{
				bool fl=0;
				for(int j=1;j<=m;j++){
					if(s[j]<se[j]){
						fl=1;
						break;
					}
					if(s[j]>se[j])break;
				}
				if(fl){
					for(int j=1;j<=m;j++)se[j]==s[j];
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		int p=0;
		for(int j=0;j<26;j++){
			for(int k=1;k<=t[i][j];k++)nw[++p]=j;
		}
		if(pos==i){
			bool fl=0;
			for(int j=1;j<=m;j++){
				if(nw[j]<se[j]){
					fl=1;
					break;
				}
				if(nw[j]>se[j])break;
			}
			if(fl)printf("1");
			else printf("0");
		}
		else{
			bool fl=0;
			for(int j=1;j<=m;j++){
				if(nw[j]<mn[j]){
					fl=1;
					break;
				}
				if(nw[j]>mn[j])break;
			}
			if(fl)printf("1");
			else printf("0");
		}
	}
}
