#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>

void floodfill(int x,int y,int color){
	if(getpixel(x,y)==0){
		putpixel(x,y,color);
		delay(1);
		floodfill(x-1,y,color);
		floodfill(x+1,y,color);
		floodfill(x,y+1,color);
		floodfill(x,y-1,color);		
	}
}

void boundaryfill(int x,int y,int color){
	if(getpixel(x,y)!=15 && getpixel(x,y)!=color){
		putpixel(x,y,color);
		delay(1);
		boundaryfill(x+1,y,color);
		boundaryfill(x,y+1,color);
		boundaryfill(x-1,y,color);
		boundaryfill(x,y-1,color);		
	}
}



int main(){
int gd=DETECT,gm;
initgraph(&gd,&gm,NULL);
int h= getmaxy();
int w = getmaxx();

line(0,h/2,w,h/2);
line(w/2,0,w/2,h);

int cx = w/2;
int cy = h/2;


int p1[5][3];
/*
p1[0][0]=0;
p1[0][1]=0;
p1[1][0]=0;
p1[1][1]=100;
p1[2][0]=80;
p1[2][1]=100;
p1[3][0]=80;
p1[3][1]=0;
p1[4][0]=0;
p1[4][1]=0;
*/
printf("Enter 5 co-ordinates pair :\n");
for(int i=0; i<5; i++){
	for(int j=0; j<2; j++){
		scanf("%d", &p1[i][j]);
}	
}
line(p1[1][0]+cx,cy-p1[1][1],p1[2][0]+cx,cy-p1[2][1]); 
line(p1[2][0]+cx,cy-p1[2][1],p1[3][0]+cx,cy-p1[3][1]); 
line(p1[0][0]+cx,cy-p1[0][1],p1[1][0]+cx,cy-p1[1][1]);
line(p1[0][0]+cx,cy-p1[0][1],p1[3][0]+cx,cy-p1[3][1]);

for(int i=0;i<5;i++){
p1[i][2]=1;
}

floodfill(cx+50,cy-50,5);
boundaryfill(cx+50,cy-50,10);
delay(5000000);
closegraph();
return 0;
}
