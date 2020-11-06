#include <cstdio>
#include <cstring>
int main(){
    char buf[100];
    memset(buf, 0, sizeof(buf));
    const char* buf1 = "test";
    int offset = 2;
    buf + offset;
    memcpy(buf, buf1, sizeof(buf1));
    printf ("strlen: %d | sizeof: %d", strlen(buf), sizeof(buf));

}