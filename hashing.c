#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define size 10000

int primenumber(int n)
{
    int prime = 1;
    for (int i = 2; i <= (int)sqrt(n); i++)
    {
        if (n % i == 0)
        {
            prime = 0;
            break;
        }
    }
    if (prime && n != 1)
        return 1;
    else
        return 0;
}
int nearest_prime(int n)
{
    for (int i = n; i < (n + 100); i++)
    {
        if (primenumber(i))
            return i;
    }
    return n;
}
typedef struct node
{
    int data;
    int status;
} hash;

typedef struct link
{
    int data;
    struct link *next;
} Chain;

Chain *create(int data)
{
    Chain *ptr = (Chain *)malloc(sizeof(Chain));
    ptr->data = data;
    ptr->next = NULL;
}

int hash_function(int hash_size, int key)
{
    return key % hash_size;
}
int double_hash_function(int hash_size, int key)
{
    int double_hashing = nearest_prime(hash_size - 50);
    return double_hashing - (key % double_hashing);
}
Chain **chaining_insertion(Chain **Hashtable_chain, int hash_size, int key, FILE *fptr, float *load_factor, int i)
{
    int index = hash_function(hash_size, key);
    Chain *temp = Hashtable_chain[index];
    int searchcount = 1;
    Chain *ptr = create(key);
    if (temp == NULL)
    {
        Hashtable_chain[index] = ptr;
        fprintf(fptr, "%0.2f,%s,%d\n", load_factor[i], "chaining", searchcount);
        return Hashtable_chain;
    }
    Chain *prev = temp;
    while (temp != NULL)
    {
        if (temp->data == key)
        {
            fprintf(fptr, "%0.2f,%s,%d\n", load_factor[i], "chaining", searchcount);
            return Hashtable_chain;
        }
        prev = temp;
        temp = temp->next;
        searchcount++;
    }
    prev->next = ptr;
    fprintf(fptr, "%0.2f,%s,%d\n", load_factor[i], "chaining", searchcount);
    return Hashtable_chain;
}
hash *linear_probing_insertion(hash *Hashtable, int hash_size, int key, FILE *fptr, float *load_factor, int i)
{
    int index = hash_function(hash_size, key);
    int searchcount = 1;
    while ((Hashtable[index].data != key) && (Hashtable[index].status != 0))
    {
        index = (hash_function(hash_size, key) + searchcount) % hash_size;
        searchcount++;
    }
    if (Hashtable[index].data == key)
    {
        fprintf(fptr, "%0.2f,%s,%d\n", load_factor[i], "linear-probing", searchcount);
        return Hashtable;
    }
    else
    {
        Hashtable[index].data = key;
        Hashtable[index].status = 1;
        fprintf(fptr, "%0.2f,%s,%d\n", load_factor[i], "linear-probing", searchcount);
        return Hashtable;
    }
}
hash *double_hashing_insertion(hash *Hashtable, int hash_size, int key, FILE *fptr, float *load_factor, int i)
{
    int index = hash_function(hash_size, key);
    int searchcount = 1;
    while ((Hashtable[index].data != key) && (Hashtable[index].status != 0))
    {
        index = (hash_function(hash_size, key) + searchcount * double_hash_function(hash_size, key)) % hash_size;
        searchcount++;
    }
    if (Hashtable[index].data == key)
    {
        fprintf(fptr, "%0.2f,%s,%d\n", load_factor[i], "double-hashing", searchcount);
        return Hashtable;
    }
    else
    {
        Hashtable[index].data = key;
        Hashtable[index].status = 1;
        fprintf(fptr, "%0.2f,%s,%d\n", load_factor[i], "double-hashing", searchcount);
        return Hashtable;
    }
}
void display_linearprob(hash *Hashtable, int hash_size)
{
    for (int i = 0; i < hash_size; i++)
    {
        if (Hashtable[i].status == 1)
            printf("Hashtable_linear_probing[%d] : %d\n", i, Hashtable[i].data);
        else
            printf("Hashtable_linear_probing[%d] : --\n", i);
    }
}
void display_doublehash(hash *Hashtable, int hash_size)
{
    for (int i = 0; i < hash_size; i++)
    {
        if (Hashtable[i].status == 1)
            printf("Hashtable_double_hashing[%d] : %d\n", i, Hashtable[i].data);
        else
            printf("Hashtable_double_hashing[%d] : --\n", i);
    }
}
void display_hashtable_chain(Chain **Hashtable_chain, int hash_size)
{
    Chain *ptr = NULL;
    for (int i = 0; i < hash_size; i++)
    {
        ptr = Hashtable_chain[i];
        printf("Hashtable_chain[%d]: ", i);
        if (ptr == NULL)
        {
            printf("->NULL");
        }
        while (ptr != NULL)
        {
            printf("->%d", ptr->data);
            ptr = ptr->next;
        }
        printf("\n");
    }
}
hash *Hashtable_linearprob, *Hashtable_doublehash;
Chain **Hashtable_chain;

int main()
{
    FILE *fptr = fopen("Hashing.csv", "w");
    if (fptr == NULL)
    {
        fprintf(stderr, "%s\n", "File is not found");
    }
    fprintf(fptr, "%s,%s,%s\n", "Load-Factor", "Hashing-type", "Search-count");
    float load_factor[4] = {0.25, 0.5, 0.75, 1};
    srand(time(0));
    int *random_arr = (int *)calloc(size, sizeof(int));
    int hash_size = nearest_prime(size);
    for (int i = 0; i < size; i++)
    {
        random_arr[i] = rand();
    }
    for (int i = 0; i < 4; i++)
    {
        Hashtable_linearprob = (hash *)calloc(hash_size, sizeof(hash));
        Hashtable_doublehash = (hash *)calloc(hash_size, sizeof(hash));
        Hashtable_chain = (Chain *)calloc(hash_size, sizeof(Chain));
        int num = size * load_factor[i];
        printf("%d\n", hash_size);
        for (int j = 0; j < num; j++)
        {
            Hashtable_chain = chaining_insertion(Hashtable_chain, hash_size, random_arr[j], fptr, load_factor, i);
            Hashtable_linearprob = linear_probing_insertion(Hashtable_linearprob, hash_size, random_arr[j], fptr, load_factor, i);
            Hashtable_doublehash = double_hashing_insertion(Hashtable_doublehash, hash_size, random_arr[j], fptr, load_factor, i);
        }
        printf("\n\n** The Hashtable with load_factor %f for chaining**\n\n", load_factor[i]);
        display_hashtable_chain(Hashtable_chain, hash_size);
        printf("\n\n*** End of Hashtable with load factor %f for chaining ***\n\n", load_factor[i]);
        printf("\n\n** The Hashtable with load_factor %f for linear probing**\n\n", load_factor[i]);
        display_linearprob(Hashtable_linearprob, hash_size);
        printf("\n\n*** End of Hashtable with load factor %f for linear probing ***\n\n", load_factor[i]);
        printf("\n\n** The Hashtable with load_factor %f for double hashing**\n\n", load_factor[i]);
        display_doublehash(Hashtable_doublehash, hash_size);
        printf("\n\n*** End of Hashtable with load factor %f for double hashing ***\n\n", load_factor[i]);
        free(Hashtable_linearprob);
        free(Hashtable_doublehash);
    }
    printf("*** End of all the Hashtables **\n");
    return 0;
}