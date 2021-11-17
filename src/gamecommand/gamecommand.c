#include <stdio.h>
#include <stdlib.h>
#include "gamecommand.h"

void CommandMove(){
    int tAwal, tAkhir;
    printf(" -------------------------MOVE--------------------\n\n");
    printf("Posisi yang dapat dicapai:\n");
    int array[100];
    accessiblePosition(map,locMobita,array);
    printf("Posisi yang dipilih? (ketik 0 jika ingin kembali)\n\n");
    printf("ENTER COMMAND: ");
    startCommand();
    int option = CommandToInt(currentCommand);
    printf("\n");
    tAwal = GetCurrentTime(T);
    AddTimeByMove(&T);
    tAkhir = GetCurrentTime(T);
    updToDo(&todo, &DaftarOrder, &T) ;
    if(tAkhir-tAwal>0) updPerishInProgress(&Inprogress, tAkhir-tAwal);
    ListDin l;
    l = LOC(map);
    if (option != 0) {
        locMobita = ELMTl(l,array[option]).name;
        printf("Mobita sekarang berada di titik ");
        printf("%c ", ELMTl(l,array[option]).name);
        TulisPOINT(ELMTl(l,array[option]).posisi);
        printf("\n");
        printf("Waktu: %.0f\n", CurrentTime(T));
    } 
}
void CommandPickUp(){   
    printf(" -----------------------PICK_UP-------------------\n\n");        
    if(searchPickUp(&todo,locMobita)){
        if (isStackFull(Tas)){
            printf("Tas Sudah Full, Tidak Bisa Melakukan Pick UP.");
        }
        else{
            PickUpItem(&todo,&Inprogress,&Tas,locMobita);
            if(TYPE(TOP(Tas)) == 'H'){
                Weight(T) += 1;
            }
            printf("Item Berhasil di Pick Up.\n");
        }
    }
    else{
        printf("Tidak ada Order di Bangunan Ini/Todolist kosong.\n");
    }
}

void CommandDropOff(){
    /* KAMUS LOKAL */
    Address current;
    Order ord;
    /* ALGORITMA */
    printf(" -----------------------DROP_OFF------------------\n\n");
    if (isEmptyLL(Inprogress)) {
        printf("Tidak ada pesanan yang dapat diantarkan!\n");
    }else if (isStackEmpty(Tas)) {
        printf("Tas kosong! Tidak ada baran yang bisa diantar!\n");
    }
    else {
        current = FIRST(Inprogress);
        while ((current != NULL) && (DropOff(INFO(current)) != locMobita)) {
            current = NEXT(current);
        }

        if (DropOff(INFO(current)) == locMobita) {
            if (isOrderEqual(INFO(current), TOP(Tas))) {
                if (TYPE(ord) == 'H') {
                    Weight(T)-=1;
                    AddSpeedBoost(&T);
                    money += 200;
                    printf("Uang yang didapatkan : 200 Yen\n");
                }
                else if (TYPE(ord) == 'P') {
                    IncreaseCapacity(&Tas);
                    money += 400;
                    printf("Uang yang didapatkan : 400 Yen\n");
                }
                else {
                    money += 400;
                    printf("Uang yang didapatkan : 400 Yen!\n");
                }
                popStack(&Tas,&ord);
                DeliverItem(&Inprogress,locMobita);
                printf("Jumlah uang sekarang : %d\n Yen", money);
                counter++;
            }
            else {
                printf("Item teratas pada tas tidak sesuai dengan pesanan pada lokasi.\n");
            }
        }
        else {
            printf("Tidak ada pesanan yang dapat diantarkan!\n");
        }
    }

}
void CommandMap(){
    printf(" --------------------------MAP--------------------\n\n");
    displayMap(map,locMobita,Tas,todo,Row,Column);
}
void CommandToDo(){
    printf(" ------------------------TO_DO--------------------\n\n");
    displayToDo(todo);
}
void CommandInProgress(){
    printf(" ---------------------IN_PROGRESS-----------------\n\n");
    displayInProg(Inprogress);
}
void CommandBuy(){
    printf(" -------------------------BUY---------------------\n\n");
    if(locMobita == '8'){
        printf("Uang Anda sekarang: %d Yen\n",money);
        printf("Gadget yang tersedia:\n");
        printf("1. Kain Pembungkus Waktu (800 Yen)\n");
        printf("2. Senter Pembesar (1200 Yen)\n");
        printf("3. Pintu Kemana Saja (1500 Yen)\n");
        printf("4. Mesin Waktu (3000 Yen)\n");
        printf("5. Senter Pengecil (800 Yen)\n");
        printf("Gadget mana yang ingin kau beli? (ketik 0 jika ingin kembali)\n");
        money += 3000;
        printf("ENTER COMMAND: ");
        startCommand();
        if(currentCommand.contents[0] == '1'){
            if (money >= 800)
            {
                if(!isGadgetFull(&InventoryGadget)){
                    money -= 800;
                    insertGadget(&InventoryGadget, "Kain Pembungkus Waktu");
                    printf("Gadget telah dibeli.\n");
                }
                else{
                    printf("Inventory Gadget sudah full. Cancelling...");
                }
            }
            else{
                printf("Uang tidak cukup untuk membeli gadget tersebut.\n");
            }
        }
        else if(currentCommand.contents[0] == '2'){
            if (money >= 1200)
            {
                if(!isGadgetFull(&InventoryGadget)){
                    money -= 1200;
                    insertGadget(&InventoryGadget, "Senter Pembesar");
                    printf("Gadget telah dibeli.\n");
                }
                else{
                    printf("Inventory Gadget sudah full. Cancelling...");
                }
            }
            else{
                printf("Uang tidak cukup untuk membeli gadget tersebut.\n");
            }
        }
        else if(currentCommand.contents[0] == '3'){
            if (money >= 1500)
            {
                if(!isGadgetFull(&InventoryGadget)){
                    money -= 1500;
                    insertGadget(&InventoryGadget, "Pintu Kemana Saja");
                    printf("Gadget telah dibeli.\n");
                }
                else{
                    printf("Inventory Gadget sudah full. Cancelling...");
                }
            }
            else{
                printf("Uang tidak cukup untuk membeli gadget tersebut.\n");
            }
        }
        else if(currentCommand.contents[0] == '4'){
            if (money >= 3000)
            {
                if(!isGadgetFull(&InventoryGadget)){
                    money -= 3000;
                    insertGadget(&InventoryGadget, "Mesin Waktu");
                    printf("Gadget telah dibeli.\n");
                }
                else{
                    printf("Inventory Gadget sudah full. Cancelling...");
                }
            }
            else{
                printf("Uang tidak cukup untuk membeli gadget tersebut.\n");
            }
        }
        else if(currentCommand.contents[0] == '5'){
            if (money >= 800)
            {
                if(!isGadgetFull(&InventoryGadget)){
                    money -= 800;
                    insertGadget(&InventoryGadget, "Senter Pengecil");
                    printf("Gadget telah dibeli.\n");
                }
                else{
                    printf("Inventory Gadget sudah full. Cancelling...");
                }
            }
            else{
                printf("Uang tidak cukup untuk membeli gadget tersebut.\n");
            }
        }
        else if(currentCommand.contents[0] == '0'){
            printf("Cancelling...\n");
        }
        else{
            printf("Input salah, Cancelling...\n");
        }
    }
    else{
        printf("Command Buy Hanya Bisa dilakukan di HQ.\n");
    }
}
void CommandInventory(){
    printf(" ----------------------INVENTORY------------------\n\n");
    displayInventory(InventoryGadget);

    printf("Gadget mana yang ingin digunakan? (ketik 0 jika ingin kembali)\n\n");
    printf("ENTER COMMAND: ");
    startCommand();
    int pilihan = CommandToInt(currentCommand);
    pilihan -= 1;
    if (ELMTListPos(InventoryGadget,pilihan)=="Kain Pembungkus Waktu"){
        useKainPembungkusWaktu(&TOP(Tas));
        printf("Kain Pembungkus Waktu berhasil digunakan!\n");
        removeGadget(&InventoryGadget,"Kain Pembungkus Waktu");
    } else if (ELMTListPos(InventoryGadget,pilihan)=="Senter Pembesar"){
        useSenterPembesar(&Tas);
        printf("Senter Pembesar berhasil digunakan!\n");
        removeGadget(&InventoryGadget,"Senter Pembesar");
    } else if (ELMTListPos(InventoryGadget,pilihan)=="Pintu Kemana Saja"){
        // kurang tau cara kerja lokasi sekarang gimana jadi pake POINT currentP sementara
        printf("Lokasi yang ingin dituju ada di: ");
        startCommand();
        usePintuKemanaSaja(&locMobita, currentCommand.contents[0]);
        printf("Pintu Kemana Saja berhasil digunakan!\n");
        printf("Lokasi Mobita sekarang adalah : %c\n", locMobita);
        removeGadget(&InventoryGadget,"Pintu Kemana Saja");
    } else if (ELMTListPos(InventoryGadget,pilihan)=="Mesin Waktu"){
        //kurang tau cara kerja waktu sekarang gimana jadi pake TIME T sementara
        useMesinWaktu(&T);
        printf("Mesin Waktu berhasil digunakan!\n");
        removeGadget(&InventoryGadget,"Mesin Waktu");
    } else if (ELMTListPos(InventoryGadget,pilihan)=="Senter Pengecil"){
        useSenterPengecil(&TOP(Tas),&Inprogress);
        printf("Senter Pengecil berhasil digunakan!\n");
        removeGadget(&InventoryGadget,"Senter Pengecil");
    } else {
        printf("Tidak ada Gadget yang dapat digunakan.\n");
    }
}
void CommandHelp(){
    printf(" -------------------------HELP--------------------\n");
    printf("\n");
    printf("1. MOVE : Menampilkan pilihan lokasi yang dapat dicapai dan berpindah ke tempat pilihan\n");
    printf("2. PICK_UP : Mengambil item pada lokasi dan menghapusnya dari To-Do list.\n");
    printf("3. DROP_OFF : Mengantarkan item pada lokasi.\n");
    printf("4. MAP : Menampilkan peta.\n");
    printf("5. TO_DO : Menampilkan pesanan yang masuk pada To Do list.\n");
    printf("6. IN_PROGRESS : Menampilkan barang yang sedang diantarkan.\n");
    printf("7. BUY : Digunakan untuk menampilkan gadget yang dapat dibeli. Hanya dapat dipanggil di HQ.\n");
    printf("8. INVENTORY : Menampilkan isi list inventory (gadgets) dan bisa memilih menggunakan gadget.\n");
    printf("9. HELP : Menampilkan list command dan penjelasannya.\n");
    printf("10. EXIT : Keluar dari game Mobilita Delivery Services.\n");
    printf("\n");
}
boolean CommandExit(){
    printf(" -------------------------EXIT--------------------\n\n");
    printf("ARE YOU SURE YOU WANT TO EXIT THE GAME? YOUR PROGRESS WILL NOT BE SAVED\n");
    printf("(Y/N)\n");
    printf("ENTER COMMAND: ");

    boolean correctinput = true;
    while (correctinput){
        startCommand();
        if(isEqualCommand(currentCommand,Y)){
            printf("EXITING GAME....\n");
            return true;
        }
        else if(isEqualCommand(currentCommand,N)){
            printf("EXIT Cancelled....\n");
            printf("Returning to game...\n");
            return false;
        }
        else{
            printf("Input Invalid: (Y/N)");
        }
    }
    
}
