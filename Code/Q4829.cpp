#include<bits/stdc++.h>
int main(){
	int t=time(0),s=0;
	puts(t&1?"mark\n0":"ok");
	while(t==time(0))s++;
	std::cerr<<s<<"\n";
}