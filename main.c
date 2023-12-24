#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>

int sudoku[9][9];/* = {{3,0,0,2,0,0,0,0,0},
                    {0,0,0,1,0,7,0,0,0},
                    {7,0,6,0,3,0,5,0,0},
                    {0,7,0,0,0,9,0,8,0},
                    {9,0,0,0,2,0,0,0,4},
                    {0,1,0,8,0,0,0,5,0},
                    {0,0,9,0,4,0,3,0,1},
                    {0,0,0,7,0,2,0,0,0},
                    {0,0,0,0,0,8,0,0,6}};

*/
int cells[82],board[9][9],solved[9][9];


int ColumnCheck(int n){
    int i,j;

    int check[10]={0,0,0,0,0,0,0,0,0,0};

    if (n == -1){
        for(j=0;j<9;j++)
            if (ColumnCheck(j)==0) return 0;

        return 1;
    }

    for(i=0;i<9;i++){
        if (sudoku[i][n]!=0)
        {
            check[sudoku[i][n]]++;
            if (check[sudoku[i][n]]>1){
                //printf("ColumnError:%d",sudoku[i][n]);
                return 0;
                }
        }
    }

    return 1;
}


int RowCheck(int n){
    int i,j;

    int check[10]={0,0,0,0,0,0,0,0,0,0};

    if (n == -1){
        for(i=0;i<9;i++)
            if (RowCheck(i)==0) return 0;

        return 1;
    }

    for(j=0;j<9;j++){
        if (sudoku[n][j]!=0)
        {
            check[sudoku[n][j]]++;
            if (check[sudoku[n][j]]>1)
                //printf("RowError:%d",sudoku[n][j]);
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
            //if (BlockCheck(3*(p/3),3*(p%3))==0) return 0;
            if (BlockCheck(topr[p],topc[p])==0) return 0;
            //return 1;
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
                //printf("BlockError:%d",sudoku[i][j]);
                return 0;
        }
    }

    return 1;
}

int Solve(int n,int c){

    if(ColumnCheck(-1)==0 || RowCheck(-1)==0 || BlockCheck(-1,-1)==0)
    {
            //printf("No Answer\n");
            return 0;
    }

    if (n==c)
        return 1;

    int i,success=0;
    for(i=1;i<10;i++){

        sudoku[cells[n]/9][cells[n]%9]=i;

        if (ColumnCheck(cells[n]%9)==1 && RowCheck(cells[n]/9)==1 && BlockCheck(cells[n]/9,cells[n]%9)==1)
        {
            success=Solve(n+1,c);
            if (success==1)
                return 1;
        }
    }

    sudoku[cells[n]/9][cells[n]%9]=0;

    return 0;

}

void my_swap(int *a, int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void swap3col(int brd[9][9], int a , int b)
{
    int k=0;
    for(k=0;k<9;k++)
    {
         my_swap(&brd[k][3*a],&brd[k][3*b]);
         my_swap(&brd[k][3*a+1],&brd[k][3*b+1]);
         my_swap(&brd[k][3*a+2],&brd[k][3*b+2]);
    }

}

void swap3row(int brd[9][9], int a, int b)
{
    int k=0;
    for(k=0;k<9;k++)
    {
         my_swap(&brd[3*a][k],&brd[3*b][k]);
         my_swap(&brd[3*a+1][k],&brd[3*b+1][k]);
         my_swap(&brd[3*a+2][k],&brd[3*b+2][k]);
    }

}


void NewGame(){
    int i,j,c=0;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            sudoku[i][j]=0;
        }
    }
    srand(time(0));
    for (j=0;j<9;j++){
        do{
           board[0][j]=(rand()%9)+1;
           sudoku[0][j]=board[0][j];
        }while(RowCheck(0)==0);
    }
    srand(time(0));
    j=rand()%9;

    for (i=1;i<9;i++){
        do{
            board[i][j]=(rand()%9)+1;
            sudoku[i][j]=board[i][j];
        }while(ColumnCheck(j)==0 || BlockCheck(-1,-1)==0);
    }



    for (i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(sudoku[i][j]==0)
                {
                    cells[c]=(9*i)+j;
                    c++;
                }
        }
    }

    printf("%d\n",Solve(0,c));

    for(i=0;i<5;i++)
    {
        int a = rand()%3;
        int b = rand()%3;

        swap3col(sudoku,a,b);

        a = rand()%3;
        b = rand()%3;

        swap3row(sudoku,a,b);


    }



        for (i=0;i<9;i++){
        for (j=0;j<9;j++){
            printf("%d ",sudoku[i][j]);
        }
        printf("\n");
    }
        /*for (i=0;i<9;i++){
        for (j=0;j<9;j++){
            printf("%d ",sudoku[i][j]);
        }
        printf("\n");
    }*/
}




void FileNewGame(int mode){
    int i,j,c=0,n,temp;
    FILE *grid,*save;
    int str[81];
    grid=fopen("sudoku5774.txt","r");
    save=fopen("save.txt","r");
    if (mode==1){
        srand(time(0));
        n=(rand()%30)+1;
        //printf("%d\n",n);

        for (j=0;j<n-1;j++){
            for (i=0;i<81;i++){
                fscanf(grid,"%1d",&temp);
            }
        }
        for (i=0;i<9;i++){
            for(j=0;j<9;j++){
                fscanf(grid,"%1d",&str[(9*i)+j]);
                sudoku[i][j]=str[(9*i)+j];
                board[i][j]=str[(9*i)+j];
            }
        }
    }
    else{
        for (i=0;i<9;i++){
            for(j=0;j<9;j++){
                fscanf(save,"%1d",&str[(9*i)+j]);
                sudoku[i][j]=str[(9*i)+j];
                board[i][j]=str[(9*i)+j];
            }
        }

    }

    for (i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(sudoku[i][j]==0)
            {
                cells[c]=(9*i)+j;
                c++;
            }
        }
    }

    Solve(0,c);

    for (i=0;i<9;i++){
        for(j=0;j<9;j++){
            solved[i][j]=sudoku[i][j];
            sudoku[i][j]=board[i][j];
        }
    }


    UserSolve(c,c);

}

void UserSolve(int n,int blank){
    int i,j,r,c,number;
    int h;
    if(blank!=0 || ColumnCheck(-1)==0 || RowCheck(-1)==0 || BlockCheck(-1,-1)==0){
        if (blank==n){
            system("cls");
            for (i=0;i<9;i++){
                for (j=0;j<9;j++){
                    if(j==2 || j==5){
                        printf("%d",board[i][j]);
                        printf("|");
                    }
                    else
                        printf("%d ",board[i][j]);
                }
                printf("\n");
                if (i==2 || i==5)
                    printf("-----------------\n");
            }
        }


    printf("\nHint?[Y/N] ");
    if (getche()=='N'){
        printf("\nEnter Row and Column:");
        scanf("%d %d",&r,&c);
        printf("\nEnter your number:");
        scanf("%d",&number);
        board[r][c]=number;
        sudoku[r][c]=number;

        system("cls");

        for (i=0;i<9;i++){
                for (j=0;j<9;j++){
                    if(j==2 || j==5){
                        printf("%d",board[i][j]);
                        printf("|");
                    }
                    else
                        printf("%d ",board[i][j]);
                }
                printf("\n");
                if (i==2 || i==5)
                    printf("-----------------\n");
            }
    }

    else if (BlockCheck(-1,-1)==1 && ColumnCheck(-1)==1 && RowCheck(-1)==1){
        srand(time(0));
        do{
            h=rand()%(n+1);
        }while(board[cells[h]/9][cells[h]%9]!=0);
        board[cells[h]/9][cells[h]%9]=solved[cells[h]/9][cells[h]%9];

        //printf("%d %d\n",cells[h]/9,cells[h]%9);

        system("cls");

        for (i=0;i<9;i++){
                for (j=0;j<9;j++){
                    if(j==2 || j==5){
                        printf("%d",board[i][j]);
                        printf("|");
                    }
                    else
                        printf("%d ",board[i][j]);
                }
                printf("\n");
                if (i==2 || i==5)
                    printf("-----------------\n");
            }
    }
    else{
        system("cls");
        printf("You Have Mistake!!\n");
        for (i=0;i<9;i++){
                for (j=0;j<9;j++){
                    if(j==2 || j==5){
                        printf("%d",board[i][j]);
                        printf("|");
                    }
                    else
                        printf("%d ",board[i][j]);
                }
                printf("\n");
                if (i==2 || i==5)
                    printf("-----------------\n");
            }
    }
    printf("Save?[Y/N]");
    if (getche()=='Y'){
        FILE *save;
        save=fopen("save.txt","w");
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                fprintf(save,"%d",board[i][j]);
            }
        }
        printf("\nYour Game Saved Successfully!\n");
        fclose(save);
    }
    printf("\nExit?[Y/N]");
    if (getche()=='Y'){

        system("cls");

        printf("\nSave?[Y/N]");
        if (getche()=='Y'){
            FILE *save;
            save=fopen("save.txt","w");
            for(i=0;i<9;i++){
                for(j=0;j<9;j++){
                    fprintf(save,"%d",board[i][j]);
                }
            }
            printf("\nYour Game Saved Successfully!\n");
            fclose(save);
        }
        return;
    }

    if (blank<=0)
        UserSolve(n,0);
    else
        UserSolve(n,blank-1);

    }

    else {
        printf("\nCongratulation!!! You Solved it Successfully\n");
    }

}


int main()
{
    int i,j,c=0,n,m;

    printf("Welcome To Our SUDOKU Game!\n");
    printf("1: New Game\n2: Solve Grid\n3: Load a Game\n4: Exit\n");
    printf("Please Enter A Number:");
    scanf("%d",&n);
    if (n==2){

    for (i=0;i<9;i++){
        for(j=0;j<9;j++){
            scanf("%d",&sudoku[i][j]);
        }
    }

    for (i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(sudoku[i][j]==0)
                {
                    cells[c]=(9*i)+j;
                    c++;
                }
        }
    }

    printf("%d\n",Solve(0,c));

        for (i=0;i<9;i++){
        for (j=0;j<9;j++){
            printf("%d ",sudoku[i][j]);
        }
        printf("\n");
    }
}

    else if (n==1){
        FileNewGame(1);
    }

    else if(n==3){
        FileNewGame(-1);
    }

    else{
        getch();
        return 0;
    }

    printf("\n");
    getch();
    return 0;
}
