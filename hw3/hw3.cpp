#include <iostream>
#include <cmath>


long mod_exp(long a, long e, long n){
		long c=a;
		long e2=e;
		while(e2>1){
			// std::cout<<e2<<std::endl;
			if(e2%2==0){
				c=(c*c)% n;
				e2=e2/2;
			}
			else{
				return (c*mod_exp(c,e2-1,n))%n;
			}
		}
		return c;
	}

int main(int argc, char const *argv[]){
	
	long a=-57;
	long b=52;
	long x0=159201;
	long p=499;
	long q=547;
	long n=p*q;
	long m=639244;//639244
	long m2=m;
	std::cout<<"ORIGINAL MESSAGE:  "<<m<<std::endl;
	long k=log2(n);
	long h=log2(k);

	long x=x0;
	long temp=0;

	long encrypt=0;
	long t=0;
	//Encryption
	while(m>0){
		long Mnibble=0;
		long Xnibble=0;
		long bit=0;
		for (long i = 0; i < h; ++i){
			bit=m%2;
			Mnibble+=bit*pow(2,i);
			m/=2;
		}
		x=(x*x) % n;
		temp=x;
		for (long i = 0; i < h; ++i){
			bit=temp%2;
			Xnibble+=bit*pow(2,i);
			temp/=2;
		}
		
		encrypt+= (Mnibble^Xnibble)*pow(2,h*t);
		t++;
	}
	x=(x*x) % n;
	t++;
	std::cout<<"ENCRYPTED MESSAGE: "<<encrypt<<std::endl;
	std::cout<<"X(t+1):            "<<x<<std::endl;
	std::cout<<"t+1:               "<<t+1<<std::endl;
	//Decryption
	
	long d1=mod_exp((p+1)/4,t,p-1);
	long d2=mod_exp((q+1)/4,t,q-1);

	long u=mod_exp(x,d1,p);
	long v=mod_exp(x,d2,q);

	x0=(v*a*p+u*b*q)%n;	//original x0
	if(x0<0){x0+=n;}
	x=x0;
	long m3=0;
	for (int i = 0; i < t; ++i)
	{
		long Enibble=0;
		long Xnibble=0;
		long bit=0;
		for (long i = 0; i < h; ++i){
			bit=encrypt%2;
			Enibble+=bit*pow(2,i);
			encrypt/=2;
		}
		x=(x*x) % n;
		temp=x;
		for (long i = 0; i < h; ++i){
			bit=temp%2;
			Xnibble+=bit*pow(2,i);
			temp/=2;
		}
		
		m3+= (Enibble^Xnibble)*pow(2,h*i);
	}
	std::cout<<"DECRYPTED MESSAGE: "<<m3<<std::endl;
	return 0;
}