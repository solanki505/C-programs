#include<stdio.h>
#include<stdlib.h>
typedef struct{
    int x;
    int y;
}pair;
pair mid;

int quad(pair p){
    if(p.x>0 && p.y>0) return 1;
    else if(p.x<0 && p.y>0) return 2;
    else if(p.x<0 && p.y<0) return 3;
    return 4;
}

int orientation(pair a, pair b, pair c){
    int res = (b.y-a.y)*(c.x-b.x)-(c.y-b.y)*(b.x-a.x);
    if (res == 0) return 0;
    if (res > 0)return 1;
    return -1;
}

int compare(const void *p1,const void *q1){
    pair *p=(pair*)p1;
    pair *q=(pair*)q1;
    pair pdiff={p->x-mid.x,p->y-mid.y};
    pair qdiff={q->x-mid.x,q->y-mid.y};
    int one=quad(pdiff);
    int two=quad(qdiff);
    if(one!=two) return (one>two)?1:-1;
    return (pdiff.y*qdiff.x < qdiff.y* pdiff.x) ? -1 : 1;
}

pair * merge(pair *a,int n1,pair* b,int n2,int *ans){
    int i=0,j=0;
    for(int ai=0;ai<n1;ai++){
        if(a[ai].x>a[i].x)i=ai;
    }
    for(int bi=0;bi<n2;bi++){
        if(b[bi].x<b[i].x)i=bi;
    }
    int idxa=i,idxb=j;
    int flag=0;
    while(!flag){
        flag=1;
        while(orientation(b[idxb],a[idxa],a[(idxa+1)%n1])>=0)
        idxa=(idxa+1)%n1;
        while(orientation(a[idxa],b[idxb],b[(n2+idxb -1)%n2])<=0){
            idxb=(n2+idxb -1)%n2;
            flag=0;
        }
    }
int uppera = idxa, upperb = idxb; 
idxa=i;idxb=j;flag=0;
while(!flag){
        flag=1;
        while(orientation(a[idxa],b[idxb],b[(idxb+1)%n2])>=0)
        idxb=(idxb+1)%n2;
        while(orientation(b[idxb],a[idxa],a[(n1+idxa -1)%n1])<=0){
            idxa=(n1+idxa -1)%n1;
            flag=0;
        }
    }
    int lowera=idxa,lowerb=idxb;
    pair *ret=(pair*)malloc((n1+n2)*sizeof(pair));
    int ind=uppera;
    int k=0;
    ret[k++]=a[uppera];
    while(ind!=lowera)
    {
        ind = (ind + 1) % n1;
        ret[k++] = a[ind];
    }

    ind = lowerb;
    ret[k++] = b[lowerb];
    while (ind != upperb)
    {
        ind = (ind + 1) % n2;
        ret[k++] = b[ind];
    }

    *ans= k;
    return ret;
}
pair* bruteHull(pair *a, int n, int *ret_size) {
    pair *ret = (pair *)malloc(n * sizeof(pair));
    int k = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int x1 = a[i].x, x2 = a[j].x;
            int y1 = a[i].y, y2 = a[j].y;

            int a1 = y1 - y2;
            int b1 = x2 - x1;
            int c1 = x1 * y2 - y1 * x2;
            int pos = 0, neg = 0;

            for (int m = 0; m < n; m++) {
                if (a1 * a[m].x + b1 * a[m].y + c1 <= 0) neg++;
                if (a1 * a[m].x + b1 * a[m].y + c1 >= 0) pos++;
            }

            if (pos == n || neg == n) {
                int already_added = 0;
                for (int l = 0; l < k; l++) {
                    if (ret[l].x == a[i].x && ret[l].y == a[i].y) already_added = 1;
                }
                if (!already_added) ret[k++] = a[i];

                already_added = 0;
                for (int l = 0; l < k; l++) {
                    if (ret[l].x == a[j].x && ret[l].y == a[j].y) already_added = 1;
                }
                if (!already_added) ret[k++] = a[j];
            }
        }
    }

    *ret_size = k;
    ret = (pair *)realloc(ret, k * sizeof(pair));

    mid.x = 0;
    mid.y = 0;
    for (int i = 0; i < k; i++) {
        mid.x += ret[i].x;
        mid.y += ret[i].y;
        ret[i].x *= k;
        ret[i].y *= k;
    }

    qsort(ret, k, sizeof(pair), compare);

    for (int i = 0; i < k; i++) {
        ret[i].x /= k;
        ret[i].y /= k;
    }

    return ret;
}
pair *divide(pair *a, int n, int *ret_size)
{
    if (n <= 5)
        return bruteHull(a, n, ret_size);

    int mid=n/2;
    pair *left_hull;
    pair *right_hull;
    int left_size,right_size;
    left_hull=divide(a, mid, &left_size);
    right_hull= divide(a+mid, n-mid,&right_size);
    return merge(left_hull, left_size, right_hull, right_size, ret_size);
}
int main()
{
    pair arr[]={{1,0},{0,1},{-1,0},{0,-1},{0,0}};
    int n=sizeof(arr)/sizeof(arr[0]);
    qsort(arr,n,sizeof(pair),compare);
    int ret_size;
    pair *ans=divide(arr,n,&ret_size);
    printf("Convex hull:\n");
    for (int i = 0; i < ret_size; i++)
    {
        printf("%d %d\n", ans[i].x,ans[i].y);
    }
    free(ans);
    return 0;
}