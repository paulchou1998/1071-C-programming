#include<stdio.h>
#include<math.h>
int main(){
	int a,b,c; double x1,x2;
	printf("��J a b c");
	scanf("%d %d %d",&a,&b,&c);
	printf("�� ax^2+bx+c=0 ��ڬ�:\n");
	if(b*b-4*a*c>=0){
		x1=(-b+sqrt(b*b-4*a*c))/(2*a);
		x2=(-b-sqrt(b*b-4*a*c))/(2*a);
		printf("x1=%.1f\n",x1);
		printf("x2=%.1f",x2);
	}
	else{
		printf("�L��"); 
	}
}
