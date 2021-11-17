#include <stdio.h>
#include "gadget.h"

void useKainPembungkusWaktu(Stack *tas) {
  /* KAMUS LOKAL */
  Order ord;
  /* ALGORITMA */
  ord = TOP(*tas);
  TimePerish(ord) = TimePerishDefault(ord);
}

void useSenterPembesar(Stack *tas) {
  CurrentCap(*tas) = (2 * CurrentCap(*tas)) % CAPACITY;
}

//bingung ngeaddress posisi sekarang, jadi sementara pake current point
void usePintuKemanaSaja(char currentP, char nextP){
    /* KAMUS LOKAL */
  /* ALGORITMA */
  currentP = nextP;
}

void useMesinWaktu(Time *T) {
  /* KAMUS LOKAL */
  /* ALGORITMA */
  if (CurrentTime(*T) >= 50) {
    CurrentTime(*T) -= 50;
  }
  else {
    CurrentTime(*T) = 0;
  }
}


void useSenterPengecil(Stack *tas) {
  /* KAMUS LOKAL */
  Order ord = TOP(*tas);
  /* ALGORITMA */
  TYPE(ord) = 'N';

}