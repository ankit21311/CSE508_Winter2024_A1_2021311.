#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

#define sys_kernel_2d_memcpy 448

int main(int argc, char const *argv[])
{
        float arr1[4][3];
        float c=2;
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 3; j++)
                {
                        arr1[i][j]=c++;
                }
        }
        printf("Original Array:\n  ");
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 3; j++)
                {
                        printf("%f ", arr1[i][j]);
                }
                printf("\n");
        }

        float arr2[4][3];
        
        long ans = syscall(sys_kernel_2d_memcpy, arr2, arr1, 4, 3);
        if(ans!=0)
        {
                printf("Error...\n");
                return 1;
        }
        printf("\nExpected Array\n");
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 3; j++)
                {
                        printf("%f ", arr2[i][j]);
                }
                printf("\n");
        }
}
