/* NIM: 13520009 */
/* Nama: Ahmad Romy Zahran */
/* Tanggal : 8 September 2021 */
/* Topik Praktikum : ADT List */
/* File : listpos.c */
/* Berisi implementasi primitif pemrosesan list integer dengan elemen 
   positif */

#include "listpos.h"
#include <stdio.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListPos(ListPos *l) {
/* I.S. l sembarang */
/* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY */
/* Proses: Inisialisasi semua elemen List l dengan VAL_UNDEF */
   /* Kamus Lokal */
   int i;
   /* Algoritma */
   for(i=0;i<CAPACITY;i++) {
      ELMT(*l,i) = VAL_UNDEF;
   }   
};

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int length(ListPos l) {
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */
   /* Kamus Lokal */
   int last=-1;
   /* Algoritma */
   while(last <CAPACITY-1 && ELMT(l,last+1)!=VAL_UNDEF) {
      last = last+1;
   }
   return last+1;
};

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListPos l, int i) {
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
/* yaitu antara indeks yang terdefinisi utk container*/
   /* Kamus Lokal */
   /* Algoritma */
    return (i>=0 && i<CAPACITY);
};
boolean isIdxEff(ListPos l, int i) {
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
/* yaitu antara 0..length(l)-1 */
   /* Kamus Lokal */
   /* Algoritma */
   return (i>=0 && i<length(l));
};

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmpty(ListPos l) {
/* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
/* *** Test List penuh *** */
   /* Kamus Lokal */
   /* Algoritma */
   return (length(l)==0);
};
boolean isFull(ListPos l) {
/* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
   /* Kamus Lokal */
   /* Algoritma */
    return (length(l)==CAPACITY);   
};

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */
void readList(ListPos *l) {
/* I.S. l sembarang */
/* F.S. List l terdefinisi */
/* Proses: membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya n */
/*    Pembacaan diulangi sampai didapat n yang benar yaitu 0 <= n <= CAPACITY */
/*    Jika n tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < n <= CAPACITY; Lakukan n kali: 
          Baca elemen mulai dari indeks 0 satu per satu diakhiri enter */
/*    Jika n = 0; hanya terbentuk List kosong */
   /* Kamus Lokal */
   boolean nvalid=false;
   int n;
   int i=0;
   /* Algoritma */
   while(!nvalid) {
      scanf("%d", &n);
      if(n>=0 && n<=CAPACITY) {
         nvalid =true;
      }
   }
   for(i=0;i<n;i++) {
      scanf("%d", &ELMT(*l,i));
   }
   for(;i<CAPACITY;i++) {
      ELMT(*l,i) = VAL_UNDEF;
   }
};
void displayList(ListPos l) {
/* Proses : Menuliskan isi List dengan traversal, List ditulis di antara kurung 
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. l boleh kosong */
/* F.S. Jika l tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika List kosong : menulis [] */
   /* Kamus Lokal */
   int i;
   /* Algoritma */
   if(isEmpty(l)) {
      printf("[]");
   } else {
      printf("[%d", ELMT(l,0));
      for(i=1;i<length(l);i++) {
         printf(",%d", ELMT(l,i));
      }
      printf("]");
   }
};

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika List : Penjumlahan, pengurangan, perkalian, ... *** */
ListPos plusMinusTab(ListPos l1, ListPos l2, boolean plus) {
/* Prekondisi : l1 dan l2 berukuran sama dan tidak kosong */
/* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada 
       indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi 
       elemen l2 pada indeks yang sama */
   /* Kamus Lokal */
   int i;
   ListPos l3;
   /* Algoritma */
   CreateListPos(&l3);
   for(i=0;i<length(l1);i++) {
      if(plus) {
         ELMT(l3,i) = ELMT(l1,i) + ELMT(l2,i);
      } else {
         ELMT(l3,i) = ELMT(l1,i) - ELMT(l2,i);
      }
   }
   return l3;
};

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan List: *** */
boolean isListEqual(ListPos l1, ListPos l2) {
/* Mengirimkan true jika l1 sama dengan l2 yaitu jika ukuran l1 = l2 dan semua 
   elemennya sama */
   /* Kamus Lokal */
   boolean equal=true;
   int i;
   /* Algoritma */
   if(length(l1)==length(l2)) {
      for(i=0;i<length(l1) && equal;i++) {
         if(ELMT(l1,i)!=ELMT(l2,i)) equal=false;
      }
   } else {
      equal =false;
   }
   return equal;
};

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOf(ListPos l, ElType val) {
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
/* Skema Searching yang digunakan bebas */
   /* Kamus Lokal */
   boolean found=false;
   int i=0, idx=IDX_UNDEF;
   /* Algoritma */
   while(i<length(l) && !found) {
      if(ELMT(l,i)==val) {
         found=true;
         idx = i;
      } 
      i++;
   }
   return idx;
};

/* ********** NILAI EKSTREM ********** */
void extremes(ListPos l, ElType *max, ElType *min) {
/* I.S. List l tidak kosong */
/* F.S. Max berisi nilai terbesar dalam l;
        Min berisi nilai terkecil dalam l */
   /* Kamus Lokal */
   int i;
   /* Algoritma */
   *max = -1;
   *min = __INT_MAX__;
   for(i=0;i<length(l);i++) {
      if(ELMT(l,i)>*max) *max=ELMT(l,i);
      if(ELMT(l,i)<*min) *min=ELMT(l,i);
   }
};

/* ********** OPERASI LAIN ********** */
boolean isAllEven(ListPos l) {
/* Menghailkan true jika semua elemen l genap */
   /* Kamus Lokal */
   int i;
   boolean even=true;
   /* Algoritma */
   for(i=0;i<length(l) && even;i++) {
      if(ELMT(l,i)%2!=0) even=false;  
   }
   return even;
};

/* ********** SORTING ********** */
void sort(ListPos *l, boolean asc) {
/* I.S. l boleh kosong */
/* F.S. Jika asc = true, l terurut membesar */
/*      Jika asc = false, l terurut mengecil */
/* Proses : Mengurutkan l dengan salah satu algoritma sorting,
   algoritma bebas */
   /* Kamus Lokal */
   int j,i, key;
   /* Algoritma */
   if(!isEmpty(*l)) {
      for(j=1;j<length(*l);j++) {
         key = ELMT(*l,j);
         i = j-1;
         if(asc) {
            while(i>=0 && ELMT(*l,i)>key) {
               ELMT(*l,i+1) = ELMT(*l,i);
               i = i-1;
            }
         } else {
            while(i>=0 && ELMT(*l,i)<key) {
               ELMT(*l,i+1) = ELMT(*l,i);
               i = i-1;
            }
         }
         ELMT(*l,i+1) =key;
      }
   }
};

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListPos *l, ElType val) {
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
   /* Kamus Lokal */
   /* Algoritma */
   ELMT(*l,length(*l)) = val;
};

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListPos *l, ElType *val) {
/* Proses : Menghapus elemen terakhir List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
   /* Kamus Lokal */
   /* Algoritma */
   *val = ELMT(*l,length(*l)-1);
   ELMT(*l,length(*l)-1) = VAL_UNDEF;
};