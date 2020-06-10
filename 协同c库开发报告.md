# 协同c库开发报告

## 代码解析

### get_id()函数：获取CDS信息中的protein_id

```c
include "libgenbank.h"

char** get_id(char* gb_filename, int* count) {  //字符串gb_filename是等待被转化为FASTA格式的genbank文件的文件名                                                   
    int maxnum_id = 500;  //从文件中提取到的id的最大数量，数值上应该和CDS_info结构体数量一致                                                                         
    FILE* genbank = fopen(gb_filename, "r");
    char** protein_id = (char**)malloc(maxnum_id * sizeof(char*));  //protein_id是存储提取出的指向id的指针的存储空间的首地址                             
    char temp[50];  //temp是暂时存储protein_id的字符串                                                                    
    char eachline[500];  //eachline存储fgets()函数得到的文件的一行                                                                                  
    int i = 0;
    int j = 0;
    int id_num = 0;  //id_num用于计算protein_id中已经有的id数量                   
    while (fgets(eachline, 1000, genbank) != NULL) { //最外层while循环，作用是遍历genebank文件中的每一行，fgets函数取得的行被存放在字符串eachline中
        i = 0;  //用于遍历一行中的每一个字符的循环变量
        j = 0;  //用于为暂存字符串temp赋值的循环变量
        if (eachline[0] == 'O' && eachline[1] == 'R' && eachline[2] == 'I' && eachline[3] == 'G') {  //这个if语句的主要作用是在遍历到ORIGIN行时，跳出行遍历循环，因为文件后面将不会再有protein_id存在
            break;
        }
        while (eachline[i] == '\t' || eachline[i] == ' ') {  //这个while循环的作用是跳过一行开头可能存在的空格和\t
            i++;
        }
        if (eachline[i] == '/' && eachline[i + 1] == 'p' && eachline[i + 2] == 'r' && eachline[i + 3] == 'o' && eachline[i + 4] == 't' && eachline[i + 5] == 'e') {   //if语句的作用是判断一行在跳过开头空格之后是否是/protein_id，
            i = i + 13;
            while (eachline[i] != '\"') {  //如果是/protein_id的话，开始将第一个双引号后的protein_id内容存进temp，一直到第二个双引号出现为止
                temp[j] = eachline[i];
                i++;
                j++;
            }
            temp[j] = '\0';  //protein_id全部被读取进temp之后，在最后添加\0表示结束
            if (id_num <= maxnum_id) {  //判断存储protein_id的数组空间是否还足够
                *(protein_id + id_num) = (char*)malloc(50 * sizeof(char));
                strcpy(*(protein_id + id_num), temp);
                id_num += 1;
            } //如果空间还足够，开辟存储刚得到的protein_id的空间，将首地址存入字符指针数组，同时计数变量id_num加一
            else {
                protein_id = (char**)realloc(protein_id, (maxnum_id + 500) * sizeof(char*));
                protein_id += 500;
                *(protein_id + id_num) = (char*)malloc(50 * sizeof(char));
                strcpy(*(protein_id + id_num), temp);
                id_num += 1;
            } //如果空间不足，使用realloc扩大空间，将protein_id同理存入，同时计数变量id_num加一
            continue;
        }
        else {
            continue;  //如果一行开头没有/protein_id，说明这一行不含需要的信息，跳出，处理下一行
        }
    }
    *count = id_num;  //将传入参数地址指向的内容更改为id_num
    return protein_id; //返回存有protein_id的数组
}
```

get_id()函数的主要作用是在genebank格式的文件中提取到每个CDS对应的protein_id，由于这一id具有特异性，所以可以作为fasta格式文件中“>”后的序列名字。

查看genebank格式文件的内容即可发现，包含有protein_id的行的格式为

​				/protein_id="XXXXXXXXX"

即一行开头为若干空格或者\t，然后是/后跟protein_id=“XXXXXXX”，双引号之间的部分为函数要提取的protein_id内容。genebank文件中的CDS板块在文件前半部分出现，当文件出现以ORIGIN为开始标志的origin序列部分后，CDS模块将不会再出现，包含在CDS模块中的protein_id也就不会再出现。所以函数的核心思路是：逐一读取文件中的行，跳过行开头可能存在的空格，对空格后的字符逐一进行判断，如果符合“/protein_id”的格式，说明该行包含所需信息，在识别到双引号时，开始存储双引号之后的内容，直到识别到第二个双引号，存储结束，将得到的protein_id复制进一个字符指针数组，当读取到的行内容为“ORIGIN”时，说明全部的CDS已经被读取完，跳出行读取循环。最后返回存储有多个protein_id的数组

函数的具体解析请看上面代码块的注释

### get_cdsSeq.c()函数：根据核苷酸序号区间和ORIGIN序列获取CDS的核苷酸序列

```c
#include "libgenbank.h"

/*get_cdsSeq函数：用CDS的左右值去完整的基因组序列中提取其sequence  */

char** get_cdsSeq(int CDS_num, int** intervals, char* origin_sequence){   //id_num是genebank文件中含有的CDS的数量，intervals是存放CDS区间的二维数组             
    char** CDS_sequence = (char**)malloc(CDS_num * sizeof(char*));
    int length;  //length是存储一个CDS核苷酸序列需要的存储空间的长度                                     
    int pointer;  //用于为CDS序列赋值的循环变量
    int i, j, k, m;  //一系列循环计数变量
    for (i = 0;i <= CDS_num - 1;i++) {  //for循环的目的是逐一遍历get_interval()函数返回的存储有CDS序列起始和结束端点数组
        length = 0;
        pointer = 0;
        if (*(*(intervals + i)) <= 0) {  //判断数组的第一个数(即说明是否为互补链和期间个数的数)，是否为负数，负数的话说明是complement，需要进行核苷酸互补翻译
            for (j = 0;j <= (-1) - (*(*(intervals + i)));j++) {  //这个for循环的作用是遍历整个包含左右端点的数组，用它们相减得到存储该序列所需要的空间长度
                length += *(*(intervals + i) + 2 * j + 2) - *(*(intervals + i) + 2 * j + 1) + 2;
            }
            *(CDS_sequence + i) = (char*)malloc(length * sizeof(char));//根据得到的区间长度申请存储空间
            for (j = 0;j <= (-1) - (*(*(intervals + i)));j++) {  //这个for循环的作用是遍历一个CDS对应的每一个区间
                for (k = *(*(intervals + i) + 2 * j + 1);k <= *(*(intervals + i) + 2 * j + 2);k++) {  //这个for循环的作用是根据左右端点将序列存进分配好的空间
                    *(*(CDS_sequence + i) + pointer) = *(origin_sequence + k - 1);
                    pointer++;
                }
                *(*(CDS_sequence + i) + pointer) = ';';  //每一个区间结束之后加上分号；作为分隔
                pointer++;
            }
            *(*(CDS_sequence + i) + length) = '\0';   //当一个CDS的全部序列区间都被提取出后，在最后加上'\0'作为结束
            for (m = 0;m <= length - 1;i++) {  //由于是complement，所以对一个CDS的全部序列进行互补翻译
                switch (*(*(CDS_sequence + i) + m))
                {
                case 'a': *(*(CDS_sequence + i) + m) = 't';break;
                case 't': *(*(CDS_sequence + i) + m) = 'a';break;
                case 'c': *(*(CDS_sequence + i) + m) = 'g';break;
                case 'g': *(*(CDS_sequence + i) + m) = 'c';break;
                }
            }
        }
        else {  //对应if(){...}中complement的情况，else{}处理的是不用互补翻译的情况，从基因组序列当中提取出的就是CDS序列，这一部分代码遇上一部分基本相同，只在最后去掉了用于互补翻译的switch语句
            for (j = 0;j <= (-1) + (*(*(intervals + i)));j++) {
                length += *(*(intervals + i) + 2 * j + 2) - *(*(intervals + i) + 2 * j + 1) + 2;
            }
            *(CDS_sequence + i) = (char*)malloc(length * sizeof(char));
            for (j = 0;j <= (-1) + (*(*(intervals + i)));j++) {
                for (k = *(*(intervals + i) + 2 * j + 1);k <= *(*(intervals + i) + 2 * j + 2);k++) {
                    *(*(CDS_sequence + i) + pointer) = *(origin_sequence + k - 1);
                    pointer++;
                }
                *(*(CDS_sequence + i) + pointer) = ';';
            }
            *(*(CDS_sequence + i) + length) = '\0';
        }
    }
    return CDS_sequence;  //最后返回存有序列的字符指针数组
}
```

区间提取函数get_interval()会返回一系列数组，里面是从CDS当中提取到的CDS核苷酸序号区间，比如，第一个数组形式为(-2,2,5,7,9),第一个-2是负数表示反向互补链是编码部分（即对应complement），第一个数的绝对值2表示的是第一个CDS包含两部分核苷酸序列，分别是第2位核苷酸到第5位核苷酸，第7位核苷酸到第9位核苷酸（即对应join(2..5,7..9)）。

而get_cdsSeq()函数的作用就是根据get_interval()返回的数组，从ORIGIN基因组序列中提取出每个CDS对应的序列，并存放在一个字符串指针数组中输出，如果存在多个区间的情况，区间之间用分号；隔开。

主要思路是遍历get_interval()返回的数组，根据每个数组的包含的区间范围确定CDS序列存储空间的长度并分配空间，然后根据区间的左右端点去ORIGIN基因组序列（由函数get_genSeq()返回为一个字符串）中提取核苷酸区间存入数组，最后返回存有CDS序列的数组

函数的具体解析请看上面注释

