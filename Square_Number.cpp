#include <stdio.h>
#include <math.h>
void Input_Array(int a[100],int n)
{
    printf("nhap cac phan tu cua mang: ");
    for (int i=0;i<n;i++)
    {
        printf("\n a[%d] = ",i);
        scanf("%d",&a[i]);
    }
}
void Output_Array(int a[100],int n)
{
    printf("Mang da duoc nhap la: ");
    for (int i=0;i<n;i++)
    {
        printf ("\na[%d] = %d",i,a[i]);
    }
}
bool Square_Number(int k)
{
    for (int i=2;i<=sqrt(k);i++)
    {
        if (pow(i,2)==k)
        {
            return true;
        }
    }
    return false;
}
int main()
{
    bool test=false;
    int n,k;
    int a[100];
    printf ("nhap n = ");
    scanf("%d",&n);
    Input_Array(a,n);
    Output_Array(a,n);
    printf ("\nnhap so k: ");
    scanf("%d",&k);
    for (int i=0;i<n;i++)
    {
        if (Square_Number(a[i])&&(a[i]>k))
        {
            printf ("\nso chinh phuong a[i]>k la: %d",a[i]);
            test=true;
            break;
        }
    }
    if (test==false)
        printf("khong co so chinh phuong a[i]>k trong mang a");
    return 0;
}
