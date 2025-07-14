#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
const double eps=1e-12;
const double pi=acos(-1);

int n,cnt;
double a,b,r;
double u,v,ang;
int tp1,tp2;
double ans;

struct poi{
	double x,y;
	poi operator +(poi &tmp){
		poi ans;
		ans.x=x+tmp.x;ans.y=y+tmp.y;
		return ans;
	} 
	bool operator <(poi &tmp){
		if(x==tmp.x)return y<tmp.y;
		return x<tmp.x;
	}
}p[maxn],c,st1[maxn],st2[maxn];
poi rerotate(poi u,double a){
	// ÏòÁ¿ u ÄæÊ±Õë a rad 
	return poi{u.x*cos(a)-u.y*sin(a),u.x*sin(a)+u.y*cos(a)};
}

bool check(poi u,poi v,poi w){
	return (u.y-v.y)*(v.x-w.x)<=(u.x-v.x)*(v.y-w.y);
}
double dis(poi u,poi v){
	return sqrt((u.x-v.x)*(u.x-v.x)+(u.y-v.y)*(u.y-v.y));
}

signed main(){
	scanf("%d%lf%lf%lf",&n,&b,&a,&r);
	a/=2.0;b/=2.0;
	for(int i=1;i<=n;i++){
		scanf("%lf%lf%lf",&u,&v,&ang);
		u+=eps;v+=eps;ang+=eps;
		c={u,v};
		p[++cnt]=rerotate((poi){a-r,b-r},ang)+c;
		p[++cnt]=rerotate((poi){r-a,b-r},ang)+c;
		p[++cnt]=rerotate((poi){r-a,r-b},ang)+c;
		p[++cnt]=rerotate((poi){a-r,r-b},ang)+c;
	}
	sort(p+1,p+cnt+1);
	for(int i=1;i<=cnt;i++){
		st1[++tp1]=p[i];
		while(tp1>=3){
			if(check(st1[tp1],st1[tp1-2],st1[tp1-1])){
				st1[tp1-1]=st1[tp1];
				--tp1;
			}
			else break;
		}
	}
	for(int i=1;i<tp1;i++)ans+=dis(st1[i],st1[i+1]);
	for(int i=cnt;i>=1;i--){
		st2[++tp2]=p[i];
		while(tp2>=3){
			if(check(st2[tp2],st2[tp2-2],st2[tp2-1])){
				st2[tp2-1]=st2[tp2];
				--tp2;
			}
			else break;
		}
	}
	for(int i=1;i<tp2;i++)ans+=dis(st2[i],st2[i+1]);
	ans+=2.0*r*pi;
	printf("%.2lf\n",ans);
}
