#include <QtGui>
#include <QString>
#include <stdio.h>
#include "SDialog.h"

static int cells[81];
static int sudoku[9][9];

int ColumnCheck(int n){
    	int i,j;
    	int check[10]={0,0,0,0,0,0,0,0,0,0};
    	if(n==-1){
        	for(j=0;j<9;j++)
            		if (ColumnCheck(j)==0) 
				return 0;
        	return 1;
    	}
    	for(i=0;i<9;i++){
        	if(sudoku[i][n]!=0){
            		check[sudoku[i][n]]++;
            		if(check[sudoku[i][n]]>1){
                		return 0;
                	}
        	}
    	}
    	return 1;
}
int RowCheck(int n){
	int i,j;
    	int check[10]={0,0,0,0,0,0,0,0,0,0};
    	if(n==-1){
        	for(i=0;i<9;i++)
            		if(RowCheck(i)==0) 
				return 0;
        	return 1;
    	}
    	for(j=0;j<9;j++){
        	if (sudoku[n][j]!=0){
            		check[sudoku[n][j]]++;
            		if (check[sudoku[n][j]]>1)
                		return 0;
        	}
    	}
	return 1;
}
int BlockCheck(int r,int q){
    	int p,i,j=0;
    	int check[10]={0,0,0,0,0,0,0,0,0,0};
    	int topr[]={0,0,0,3,3,3,6,6,6};
    	int topc[]={0,3,6,0,3,6,0,3,6};
    	if (r==-1 && q==-1){
        	for (p=0;p<9;p++){
            		if (BlockCheck(topr[p],topc[p])==0) 
				return 0;
        	}
        	return 1;
    	}
    	r=3*(r/3);
    	q=3*(q/3);
    	for(i=r;i<=r+2;i++){
        	for(j=q;j<=q+2;j++){
            		if (sudoku[i][j]!=0){
                		check[sudoku[i][j]]++;
            		}
            		if (check[sudoku[i][j]]>1)
                		return 0;
        	}
    	}
    	return 1;
}
int Solve(int n,int c){
    	if(ColumnCheck(-1)==0 || RowCheck(-1)==0 || BlockCheck(-1,-1)==0){        
            return 0;
    	}
    	if(n==c)
        	return 1;
    	int i,success=0;
    	for(i=1;i<10;i++){
        	sudoku[cells[n]/9][cells[n]%9]=i;
        	if(ColumnCheck(cells[n]%9)==1 && RowCheck(cells[n]/9)==1 && BlockCheck(cells[n]/9,cells[n]%9)==1){
            		success=Solve(n+1,c);
            		if (success==1)
            		    return 1;
        	}
    	}
    	sudoku[cells[n]/9][cells[n]%9]=0;
    	return 0;
}
SDialog::SDialog(QWidget* parent):QDialog(parent){
	setupUi(this);
	connect(solveButton,SIGNAL(clicked()),this,SLOT(solve_button_press()));
}
void SDialog::solve_button_press(){
	int i,j;
	int c=0;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(table->item(i,j)!=0)
				sudoku[i][j]=((table->item(i,j))->text()).toInt();
			else
				sudoku[i][j]=0;
		}
	}
	for (i=0;i<9;i++){
        	for(j=0;j<9;j++){
			if(sudoku[i][j]==0){
                		    cells[c]=(9*i)+j;
                		    c++;
                	}
        	}
    	}
	Solve(0,c);
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(table->item(i,j)!=0)
				(table->item(i,j))->setText(QString::number(sudoku[i][j]));
			else
				table->setItem(i,j,new QTableWidgetItem(QString::number(sudoku[i][j])));
		}
	}
}
