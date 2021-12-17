#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
//My notes: In C language there is a different between '\n' and "\n" :)
// variable and symbol tables & LineNum = current reading line
#define bufSize 1000 // buffer size
int lineNum = 1 ;
int bIdx = 0; // buffer reading index
char typeTable[4][8];
char keyboardTable[11][10];
char IDstorage[20][128];
char buffer[1][bufSize];


//File Handling
FILE * inputFile;
FILE * outputFile;

void tableCleaner(int row,int column,char arr[row][column]){
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            arr[i][j]='\0';
        }
    }
}
void bufferCleaner(int row,int column,int arr[row][column]){
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            arr[i][j]=0;
        }
    }
}
void copyFileToArray(){
    buffer[0][0]=EOF;// if file is Null we can terminate accurately
    char cr=fgetc(inputFile);
    if(cr == NULL){
        //do nothing
    }else{
        buffer[0][0]=cr;
        for(int i=1;;i++){
            cr=fgetc(inputFile);
            if(cr == EOF ){
                buffer[0][i]=cr;
                break;
            }else{
                buffer[0][i]=cr;
            }
        }
    }
    fclose(inputFile);
}
void TableInitializer(int row1,int col1,int row2,int col2,char typeTable[row1][col1],char keyboardTable[row2][col2]){
    strcpy(typeTable[0],"integer");
    strcpy(typeTable[1],"boolean");
    strcpy(typeTable[2],"char");
    strcpy(typeTable[3],"string");
    strcpy(keyboardTable[0],"array");
    strcpy(keyboardTable[1],"else");
    strcpy(keyboardTable[2],"false");
    strcpy(keyboardTable[3],"for");
    strcpy(keyboardTable[4],"function");
    strcpy(keyboardTable[5],"if");
    strcpy(keyboardTable[6],"print");
    strcpy(keyboardTable[7],"return");
    strcpy(keyboardTable[8],"true");
    strcpy(keyboardTable[9],"void");
    strcpy(keyboardTable[10],"while");
}
void ungetBuffer(){
    int idx=0;
    for(int i=0;i<bufSize;i++){
        if(buffer[0][i]=='\0'){                        // current string does not match with type[i]
            idx=(i-1);
            break;
        }
    }
    for(int i=idx;i>-1;i--){
        fputc(inputFile,buffer[0][i]);
    }
}

//---------------- subroutines
bool whiteSpaceHandler(){
    // in this function we only discard white spaces,if it is the case. Also update line number
    if( (buffer[0][bIdx] == '\n') ||( buffer[0][bIdx]==' ') ||(buffer[0][bIdx]=='\t') ){
        if(buffer[0][bIdx]=='\n'){
                lineNum++;
        }
        bIdx++; // in all subroutines we should up date bIdx before return 1
        printf("i'm in WSS func1\n");
        return 1;// one means we have already handled this character
    }else{
        printf("%d i'm in WSS func0\n",bIdx);
        return 0;
    }
}

bool typeHandler(){
    printf("%d type handler start corrsponding car: %c\n",bIdx,buffer[0][bIdx]);
    int index=bIdx;//  buffer index before manipulations
    for(int i=0;i<4;i++){
        if(buffer[0][index]==typeTable[i][0]){
            for(int j=1;j<8;j++){
                printf("buffer index : %d \tchar:%c \n",bIdx ,typeTable[i][j]);
                if(typeTable[i][j]=='\0'){ // entering to this scope means we have found a match with types
                    fprintf(outputFile,"Type\t%s\tLineNumber:%d\n",typeTable[i],lineNum); //writing result
                    printf("%d type detected corrsponding type:%s\t%d\n",bIdx,typeTable[i],lineNum);
                    bIdx=index+1;
                    return 1;
                }else{
                    index++;
                    if(buffer[0][index]==EOF){
                        return 0;//evoke calling keyboard or symbol handling functions
                    }
                    if(typeTable[i][j]==buffer[0][index]){
                        //do nothing. we just look at the next character of file
                    }else{ // current string does not match with type[i]
                        index=bIdx; // reseting index for other run of for loop
                        break;//break matching input stream with type[i]
                    }
                }
            }
        }
    }
    printf("%d type handler End \n",bIdx);
    return 0;
}
bool keyboardHandler(){
    int index=bIdx;
    for(int i=0;i<11;i++){
        if(buffer[0][index]==keyboardTable[i][0]){
            for(int j=1;j<10;j++){
                if('\0'==keyboardTable[i][j]){
                    fprintf(outputFile,"Keyword\t%s\tLineNumber:%d\n",keyboardTable[i],lineNum); //writing result
                    bIdx=index+1;
                    return 1;
                }
                index++;
                if(buffer[0][index]==EOF){
                    return 0;
                }
                if(buffer[0][index]==keyboardTable[i][j]){//do nothing
                }else{
                    index=bIdx; // reseting index for other run of for loop
                    break;//break matching input stream with type[i]
                }

            }
        }
    }
    return 0;
}
bool symbolsAndIdHandler(){
    int index=bIdx;
    switch(buffer[0][index]){
    case ':':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '\'':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case ';':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '[':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case ']':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '{':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '}':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '(':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case ')':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '^':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '%':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '+':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '-':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '>':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '<':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '&':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '|':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '!':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '*':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '=':
        fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
        bIdx++;
        break;
    case '/':// complicated case
        if(buffer[0][(index+1)]=='/'){
            int endOfComm=0;
            for(int i=(index+2);;i++){
                if(buffer[0][i]=='\n'){
                    endOfComm=i;
                    break;
                }else if(buffer[0][index]==EOF){
                    exit(0);
                }
            }
           fprintf(outputFile,"Command\tNone\t startingIndex:%d endingIndex:%d\n",bIdx,endOfComm);
           bIdx = endOfComm+1;
        }else if(buffer[0][(index+1)]=='*'){
            int endOfComm=0;
            for(int i=(index+2);;i++){
                if(buffer[0][i]=='*'&& buffer[0][i]=='/'){
                    endOfComm=i+1;
                    break;
                }else if(buffer[0][index]==EOF){
                    fprintf("you have not specified the end of your comment at %d index of input file",index);
                    exit(0);
                }
            }
           fprintf(outputFile,"Comment\tNone\t startingIndex:%d endingIndex:%d\n",bIdx,endOfComm);
           bIdx = endOfComm+1;
        }else{
            fprintf(outputFile,"%c\tNone\tLineNumber:%d\n",buffer[0][index],lineNum); //writing result
            bIdx++;
        }
        break;
    case '\"':// complicated case
        for(int i=(index+1);;i++){
            if(buffer[0][i]=='\"'){
                fprintf(outputFile,"Comment \tNone\t startingIndex:%d endingIndex:%d\n",bIdx,i);
                bIdx=i+1;
                break;

            }else if(buffer[0][i]==EOF){
                fprintf(outputFile,"you have not specified the end of your string at %d index of input file",index);
                exit(0);
            }
        }
        break;
    default:// complicated case
        if(isdigit(buffer[0][index])){
            for(int i=0;;i++){
                if(!isdigit(buffer[0][(index+i+1)])){
                    fprintf(outputFile,"Number\tNone\tstartingIndex:%d endingIndex:%d\n",index,(index+i));
                    bIdx+=(i+1);
                    return 1;
                }
            }
        }else if(isalpha(buffer[0][index])){
            for(int i=0;;i++){
                if(buffer[0][(index+i+1)]=='_'||isalpha(buffer[0][(index+i+1)])||isdigit(buffer[0][(index+i+1)])){
                    //do nothing
                }else{
                    fprintf(outputFile,"ID\tNone\t startingIndex:%d endingIndex:%d\n",index,(index+i));
                    bIdx+=(i+1);
                    return 1;
                }
            }
        }else{
            fprintf("Unexpected character at %d index of input file",index);
            bIdx++;
        }
    }
    return 0;
}
//---------------

int main()
{
    // creating a pointer to files
    inputFile = fopen("txt.txt", "r");
    outputFile = fopen("output.txt", "w");

    // cleaning arrays with '\0' or 0
    tableCleaner(4,8,typeTable);
    tableCleaner(14,10,keyboardTable);
    tableCleaner(20,128,IDstorage);

    // filling Tables with corresponding symbols
    TableInitializer(4,8,14,10,typeTable,keyboardTable);

    //copy input file into array of characters :)
    copyFileToArray();
    printf("%s\n",buffer[0]);

    // Title of output file
    fprintf(outputFile,"Token_Type  Token_Value   Line_Address\n________________________\n");

    while(buffer[0][bIdx]!= EOF){
        if(whiteSpaceHandler()){
        }else if(typeHandler()){
        }else if(keyboardHandler()){
        }else if(symbolsAndIdHandler()){
        }
        //bIdx++;
        //if(bIdx>100){break;}
    }
    printf("End of syntax analyzing\n");
    fclose(outputFile);
    return 0;
}
