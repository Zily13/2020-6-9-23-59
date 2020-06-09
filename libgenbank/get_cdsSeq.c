#include "libgenbank.h"

/*get_cdsSeq��������CDS������ֵȥ�����Ļ�������������ȡ��sequence  */

char** get_cdsSeq(int CDS_num, int** intervals, char* origin_sequence){   //id_num��CDS�ĸ�����intervals�Ǵ��CDS����Ķ�ά����
    char** CDS_sequence = (char**)malloc(CDS_num * sizeof(char*));
    int length;  //length��һ��CDS��Ӧ���еĳ���
    int pointer;
    int i, j, k, m;
    for (i = 0;i <= CDS_num - 1;i++) {
        length = 0;
        pointer = 0;
        if (*(*(intervals + i)) <= 0) {
            for (j = 0;j <= (-1) - (*(*(intervals + i)));j++) {
                length += *(*(intervals + i) + 2 * j + 2) - *(*(intervals + i) + 2 * j + 1) + 2;
            }
            *(CDS_sequence + i) = (char*)malloc(length * sizeof(char));
            for (j = 0;j <= (-1) - (*(*(intervals + i)));j++) {
                for (k = *(*(intervals + i) + 2 * j + 1);k <= *(*(intervals + i) + 2 * j + 2);k++) {
                    *(*(CDS_sequence + i) + pointer) = *(origin_sequence + k - 1);
                    pointer++;
                }
                *(*(CDS_sequence + i) + pointer) = ';';
                pointer++;
            }
            *(*(CDS_sequence + i) + length) = '\0';
            for (m = 0;m <= length - 1;i++) {
                switch (*(*(CDS_sequence + i) + m))
                {
                case 'a': *(*(CDS_sequence + i) + m) = 't';break;
                case 't': *(*(CDS_sequence + i) + m) = 'a';break;
                case 'c': *(*(CDS_sequence + i) + m) = 'g';break;
                case 'g': *(*(CDS_sequence + i) + m) = 'c';break;
                }
            }
        }
        else {
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
    return CDS_sequence;
}
