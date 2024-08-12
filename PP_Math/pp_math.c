#include "stdlib.h"
#include "pp_math.h"

const unsigned int mulTab[9]={1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

int deg2sec(double angle){

	int data=angle*10000;
	
	
	return (data%100)+(((data%10000)/100)*60)+((data/10000)*3600);		

}

double sec2deg(int angle){

	int sec=angle%60;
	int min=(angle/60)%60;
	int h=(angle/3600);
	
	double angInDeg=(double)h+((double)min)/100+((double)sec)/10000;
	
	return angInDeg;

}

int pow_pp(int base, unsigned int exponent){
	int data=1;
	
	for(int i=0; i<exponent; i++){
		data*=base;
	}
		
	return data;		

}

double fpow_pp(double base, int exponent){
	int exp=abs(exponent);
	double data=1;
	
	for(int i=0; i<exp; i++){
		data*=base;
	}
		
	if(exponent<0)data=1/data;
	
	return data;		

}


int abs_pp(int data){
		
	if(data<0)data*=(-1);
	
	return data;		

}


double fabs_pp(double data){
		
	if(data<0)data*=(-1);
	
	return data;		

}


int mulBy10_pp(int value, int exponent){
	unsigned int exp=abs_pp(exponent);
	int mul=pow_pp(10, exp);
	
	if(exponent>0){
		value*=mul;
	}else{
		value/=mul;
	}
	
	return value;			

}

int fs_mulBy10_pp(int value, int exponent){
	int exp=abs_pp(exponent);

	if(exponent>0){
		value*=mulTab[exp];
	}else{
		value/=mulTab[exp];
	}
	
	return value;			

}

int trim_pp(int data, int upperLimit, int lowerLimit){

	  if(data>=upperLimit)data=upperLimit;
    else if(data<=lowerLimit)data=lowerLimit;

    return data;
	
};


int round_pp(int data, int precision){
	
		int rest=data%precision;
		data-=rest;
		
		if(abs(rest)>precision/2){
			if(rest>0)data+=precision;
			else data-=precision;
		}
	
		return data;
}

int trimAcc_pp(int data, int upperLimit, int lowerLimit, int precision){
	
    data=trim_pp(data, upperLimit, lowerLimit);
		data=round_pp(data, precision);
	
		return data;
}
