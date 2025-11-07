struct mat{
	int e[maxk][maxk];
	mat(){memset(e,0,sizeof(e));}
}bas,pw[60];
mat operator*(mat &u,mat &v){
	mat res;
	for(int i=0;i<l;i++){
		for(int k=0;k<l;k++){
			for(int j=0;j<l;j++)(res.e[i][j]+=u.e[i][k]*v.e[k][j])%=mod;
		}
	}
	return res;
}
mat one(){
	mat res;
	for(int i=0;i<l;i++)res.e[i][i]=1;
	return res;
}
mat qpow(mat a,int b){
	mat ans=one();
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
struct vec{
	int e[maxk];
	vec(){memset(e,0,sizeof(e));}
};
vec operator*(mat &u,vec &v){
	vec res;
	for(int i=0;i<l;i++){
		for(int j=0;j<l;j++)(res.e[i]+=u.e[i][j]*v.e[j])%=mod;
	}
	return res;
}