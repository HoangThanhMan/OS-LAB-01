#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

#define READ_END 0
#define WRITE_END 1

void CSP_Filter(int fd[]){

    int fd_tmp[2];

    pipe(fd_tmp);

    char buf[1];
    int primes[50];
    int cnt=0;

    while((read(fd[READ_END], buf, sizeof(buf)))!=0){
        primes[cnt++] = buf[0];
    }

    close(fd[READ_END]);

    if(cnt==0) return;

    for(int i=1;i<cnt;i++){
        if(primes[i]%primes[0]!=0){
            char num = primes[i];
            write(fd_tmp[WRITE_END], &num, 1);
        }
    }

    close(fd_tmp[WRITE_END]);

    int pid = fork();

    if(pid==0){
        printf("prime %d\n",primes[0]);
        CSP_Filter(fd_tmp);
    }
}

int main(){

    int fd[2];

    pipe(fd);

    for(int i=2;i<=35;i++){
        char p = i;
        write(fd[WRITE_END], &p, 1);
    }
    close(fd[WRITE_END]);

    CSP_Filter(fd);

    wait((int *) 0);

    exit(0);
}


