#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>

int main(){
int gd=DETECT,gm;
initgraph(&gd,&gm,NULL);
int h= getmaxy();
int w = getmaxx();

line(0,h/2,w,h/2);
line(w/2,0,w/2,h);
setcolor(RED);
int cx = w/2;
int cy = h/2;

line(0+cx,cy-100,80+cx,cy-100); 
line(80+cx,cy-100,80+cx,cy-0); 
line(80+cx,cy-100,40+cx,cy-150);
line(40+cx,cy-150,0+cx,cy-100);
line(0+cx,cy-0,0+cx,cy-100);
line(0+cx,cy-0,80+cx, cy-0);

int p1[6][3];

p1[0][0]=0;
p1[0][1]=0;
p1[1][0]=0;
p1[1][1]=100;
p1[2][0]=40;
p1[2][1]=150;
p1[3][0]=80;
p1[3][1]=100;
p1[4][0]=80;
p1[4][1]=0;
p1[5][0]=0;
p1[5][1]=0;


for(int i=0;i<6;i++){
p1[i][2]=1;
}

////////////////////////

int s[3][3];
for(int i=0; i<3; i++){
for(int j=0; j<3; j++){
	s[i][j]=0;
}
}
//scaling values
s[0][0] = 2;
s[1][1] = 2;
s[2][2]= 1;

///////////////////////////////
int t[3][3];
for(int i=0; i<3; i++){
for(int j=0; j<3; j++){
	t[i][j]=0;
}
}
//translation values
t[2][0] = -200;
t[2][1] = 0;
t[2][2] = 1;
t[0][0] =1;
t[1][1] = 1;

/////////////////////////////////

int rx[3][3];
for(int i=0; i<3; i++){
for(int j=0; j<3; j++){
	rx[i][j]=0;
}
}
//reflection along x-axis values
rx[2][2] = 1;
rx[0][0] = 1;
rx[1][1] = -1;

/////////////////////////////////


int shx[3][3];
for(int i=0; i<3; i++){
for(int j=0; j<3; j++){
	shx[i][j]=0;
}
}
//shear-X values
shx[2][2] = 1;
shx[0][0] = 1;
shx[1][1] = 1;
shx[1][0] = -2;

/////////////////////////////////



int p2[6][3];
int p2t[6][3];
int p2rx[6][3];
int p2shx[6][3];
for(int i=0;i<6;i++)    
{    
for(int j=0;j<3;j++)    
{    
p2[i][j]=0; 
p2t[i][j]=0;   
p2rx[i][j]=0;
p2shx[i][j]=0;
for(int k=0;k<3;k++)    
{    
p2[i][j]+=p1[i][k]*s[k][j];   
p2t[i][j]+=p1[i][k]*t[k][j];  
p2rx[i][j]+=p1[i][k]*rx[k][j];  
p2shx[i][j]+=p1[i][k]*shx[k][j]; 
}    
}    
} 

setcolor(BLUE);
line(p2[1][0]+cx,cy-p2[1][1],p2[3][0]+cx,cy-p2[3][1]);
line(p2[3][0]+cx,cy-p2[3][1],p2[4][0]+cx,cy-p2[4][1]);
line(p2[3][0]+cx,cy-p2[3][1],p2[2][0]+cx,cy-p2[2][1]);
line(p2[2][0]+cx,cy-p2[2][1],p2[1][0]+cx,cy-p2[1][1]);
line(p2[0][0]+cx,cy-p2[0][1],p2[1][0]+cx,cy-p2[1][1]);
line(p2[5][0]+cx,cy-p2[5][1],p2[4][0]+cx,cy-p2[4][1]);

setcolor(GREEN);
line(p2t[1][0]+cx,cy-p2t[1][1],p2t[3][0]+cx,cy-p2t[3][1]);
line(p2t[3][0]+cx,cy-p2t[3][1],p2t[4][0]+cx,cy-p2t[4][1]);
line(p2t[3][0]+cx,cy-p2t[3][1],p2t[2][0]+cx,cy-p2t[2][1]);
line(p2t[2][0]+cx,cy-p2t[2][1],p2t[1][0]+cx,cy-p2t[1][1]);
line(p2t[0][0]+cx,cy-p2t[0][1],p2t[1][0]+cx,cy-p2t[1][1]);
line(p2t[5][0]+cx,cy-p2t[5][1],p2t[4][0]+cx,cy-p2t[4][1]);

setcolor(YELLOW);
line(p2rx[1][0]+cx,cy-p2rx[1][1],p2rx[3][0]+cx,cy-p2rx[3][1]);
line(p2rx[3][0]+cx,cy-p2rx[3][1],p2rx[4][0]+cx,cy-p2rx[4][1]);
line(p2rx[3][0]+cx,cy-p2rx[3][1],p2rx[2][0]+cx,cy-p2rx[2][1]);
line(p2rx[2][0]+cx,cy-p2rx[2][1],p2rx[1][0]+cx,cy-p2rx[1][1]);
line(p2rx[0][0]+cx,cy-p2rx[0][1],p2rx[1][0]+cx,cy-p2rx[1][1]);
line(p2rx[5][0]+cx,cy-p2rx[5][1],p2rx[4][0]+cx,cy-p2rx[4][1]);

setcolor(WHITE);
line(p2shx[1][0]+cx,cy-p2shx[1][1],p2shx[3][0]+cx,cy-p2shx[3][1]);
line(p2shx[3][0]+cx,cy-p2shx[3][1],p2shx[4][0]+cx,cy-p2shx[4][1]);
line(p2shx[3][0]+cx,cy-p2shx[3][1],p2shx[2][0]+cx,cy-p2shx[2][1]);
line(p2shx[2][0]+cx,cy-p2shx[2][1],p2shx[1][0]+cx,cy-p2shx[1][1]);
line(p2shx[0][0]+cx,cy-p2shx[0][1],p2shx[1][0]+cx,cy-p2shx[1][1]);
line(p2shx[5][0]+cx,cy-p2shx[5][1],p2shx[4][0]+cx,cy-p2shx[4][1]);

delay(5000000);
closegraph();
return 0;
}
