#ifndef UTIL_H
#define UTIL_H
int parseInt(char* str,int* pos){
    int result=0,flg=0,sign=1;
    for (;str[*pos];(*pos)++){
        if (str[*pos]>='0'&&str[*pos]<='9'){
            result=10*result+str[*pos]-'0';
            if (!flg)
                flg=1;
            }
        else{
            if (str[*pos]=='^')
                return -1;
            if (flg)
                break;
        }
    }
    return result*sign; 
}

char* toString(char* result,int num){
    int i=0;
    if (num<0){
        result[i++]='-';
        num=-num;
    }
    while (num){
        result[i++]=num%10+'0';
        num/=10;
    }
    result[i]=0;
    return result;
}

int strlen(char* str){
    int i=0;
    while (str[i])
        i++;
    return i;
}
#endif