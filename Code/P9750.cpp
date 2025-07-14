#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
	return x*fl;
}

int a,b,c,d,s;
int p,q,fl;
int gcd(int a,int b){
	if(a%b==0)return b;
	return gcd(b,a%b);
}
void sovle(){
	a=read();b=read();c=read();
	d=b*b-4*a*c;
	if(d<0)printf("NO\n");
	else{
		s=(int)sqrt(d);
		if(s*s==d){
			q=2*a;fl=1;
			if(q<0){
				p=-b-s;q=-q;fl=-1;
				if(p<0)p=-p,fl=1;
			}
			else{
				p=-b+s;
				if(p<0)p=-p,fl=-1;
			}
			// cout<<p<<" "<<q<<"\n";
			int gg=gcd(p,q);
			p/=gg;q/=gg;
			p*=fl;
			if(q==1)printf("%lld\n",p);
			else printf("%lld/%lld\n",p,q);
			// if(p==-5&&q==2)cout<<a<<" "<<b<<" "<<c<<"\n";
		}
		else{
			p=-b;q=2*a;fl=1;
			if(p){
				if(p<0&&q<0)p=-p,q=-q;
				if(p<0)fl=-1,p=-p;
				if(q<0)fl=-1,q=-q;
				int gg=gcd(p,q);
				p/=gg;q/=gg;
				p*=fl;
				if(q==1)printf("%lld+",p);
				else printf("%lld/%lld+",p,q);
			}
			p=1,q=2*a;
			if(q<0)q=-q;
			for(int i=2;i*i<=d;i++){
				while(d%(i*i)==0){
					d/=(i*i),p*=i;
					// cout<<d<<" "<<p<<"\n";
				}
			}
			int gg=gcd(p,q);
			p/=gg;q/=gg;
			if(p==q)printf("sqrt(%lld)\n",d);
			else if(p%q==0)printf("%lld*sqrt(%lld)\n",p/q,d);
			else if(p==1)printf("sqrt(%lld)/%lld\n",d,q);
			else printf("%lld*sqrt(%lld)/%lld\n",p,d,q);
		}
	}
}

int T,M;
signed main(){
//	freopen("uqe.in","r",stdin);
//	freopen("uqe.out","w",stdout);
	
	T=read();M=read();
	while(T--)sovle();
}
