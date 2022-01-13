#include <stdio.h>
int main(){
	FILE *fp;
	fp = fopen( "output.txt" , "w" );
	char str[] = "0,1,3,5\n-1\n";
	fwrite(str , 1 , sizeof(str) , fp );
	fclose(fp);
	return 0;
}
