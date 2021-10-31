#include "ADT Linked List/list_linked.h"
#include <stdio.h>
#include "ADT Queue/queue.h"
#include "ADT Mesin Kata/wordmachine.h"
#include <string.h>

Daftar createDaftar(List td, int time)
{
    Daftar daftar;
    IDX_HEAD(daftar) = IDX_UNDEF;
    IDX_TAIL(daftar) = IDX_UNDEF;
    for (int i=1;i<=time;i++)
    {
        Address current = FIRST(td);
        while(current!=NULL)
        {
            if (TimeIn(INFO(current))==i)
            {
                enqueueDaftar(&daftar, INFO(current));
            }
            current = NEXT(current);
        }
    }
    return daftar;
}

void enqueueDaftar(Daftar *q, Order val) {
/* Proses: Menambahkan val pada q dengan aturan FIFO */
/* I.S. q mungkin kosong, tabel penampung elemen q TIDAK penuh */
/* F.S. val menjadi TAIL yang baru, IDX_TAIL "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen q
        menjadi rata kiri untuk membuat ruang kosong bagi TAIL baru  */
    /* Kamus Lokal */
    int i;
    /* Algoritma */
    if(IDX_TAIL(*q)==CAPACITY-1) {
        for(i=IDX_HEAD(*q);i<=IDX_TAIL(*q);i++) {
            (*q).buffer[i-IDX_HEAD(*q)] = (*q).buffer[i];
        }
        IDX_TAIL(*q) = IDX_TAIL(*q) - IDX_HEAD(*q);
        IDX_HEAD(*q) = 0;
    }
    if(IDX_TAIL(*q)==IDX_UNDEF) {
        IDX_HEAD(*q) = 0;
        IDX_TAIL(*q) = 0;
        TAIL(*q) = val;
    } else {
        IDX_TAIL(*q)++;
        TAIL(*q) = val;
    }
};

void dequeueDaftar(Daftar *q, Order *val) {
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. q tidak mungkin kosong */
/* F.S. val = nilai elemen HEAD pd I.S., HEAD dan IDX_HEAD "mundur";
        q mungkin kosong */
    /* Kamus Lokal */
    /* Algoritma */
    *val = HEAD(*q);
    if(IDX_HEAD(*q)==IDX_TAIL(*q)) {
        IDX_HEAD(*q) = IDX_UNDEF;
        IDX_TAIL(*q) = IDX_UNDEF;
    } else {
        IDX_HEAD(*q) +=1;
    }
};

void displayDaftar(Daftar q)
{
    if(!isDEmpty(q)) {
        Order val;
        int i = 1;
        while(!isDEmpty(q))
        {
            dequeueDaftar(&q,&val);
            if(TYPE(val)=='N') {
                printf("%d. %c -> %c (Normal Item)\n", i, PickUp(val), DropOff(val));
                i++;
            } else if(TYPE(val)=='H') {
                printf("%d. %c -> %c (Heavy Item)\n", i, PickUp(val), DropOff(val));
                i++;
            } else if(TYPE(val)=='P') {
                printf("%d. %c -> %c (Perishable Item, sisa waktu %d)\n", i, PickUp(val), DropOff(val), TimePerish(val));
                i++;
            }
        }
    }
}

List readOrder(int val)
// Mesin kata membaca file konfigurasi
// masih belom yakin cara membaca kata diubah menjadi integer
{
    List TempList;
    CreateList(&TempList);
    ignoreBlank();
    for (int i=0;i<val;i++)
    {
        Order newOrder;
        copyWord();
        char *tes = currentWord.contents;
        TimeIn(newOrder) = tes;
        advWord();
        PickUp(newOrder) = currentChar;
        advWord();
        DropOff(newOrder) = currentChar;
        advWord();
        TYPE(newOrder) = currentChar;
        if (currentChar == 'P')
        {
            advWord();
            tes = currentWord.contents;
            TimePerish(newOrder) = tes;
        } else {
            TimePerish(newOrder) = 0;
        }
        insertLast(&TempList,newOrder);
        advWord();
    }
}

int main() {
    /* KAMUS */
    List toDo;
    Order ord1 = (Order){1,'G','N','N',0};
    Order ord2 = (Order){3,'G','N','H',0};
    Order ord3 = (Order){2,'B','M','N',0};
    Order ord4 = (Order){1,'M','B','H',0};
    Order ord5 = (Order){5,'C','D','N',0};
    Order ord6 = (Order){3,'F','E','N',0};
    Order ord7 = (Order){10,'P','Q','P',20};
    Order ord8 = (Order){5,'G','N','P',10};
    // Nanti bakal implementasi jadi pake mesin kata
    /* ALGORITMA */
    List TempList;
    CreateList(&TempList);
    insertLast(&TempList,ord1);
    insertLast(&TempList,ord2);
    insertLast(&TempList,ord3);
    insertLast(&TempList,ord4);
    insertLast(&TempList,ord5);
    insertLast(&TempList,ord6);
    insertLast(&TempList,ord7);
    insertLast(&TempList,ord8);
    // Buat list sementara untuk semua pesanan (tidak berurut berdasarkan Time-in gapapa)

    Daftar daftar = createDaftar(TempList,10);
    // Mengubah dan Mengurutkan list sebelumnya menjadi queue
    displayDaftar(daftar);

    return 0;
}
