
#include "stdlib.h"
#include <stdio.h>
#include <math.h>

//#include<string.h>
//#include <time.h>

//#include <unistd.h>



int Registros[32];
int Rs;
int Rd;
int Rt;
int shamt;
int address;
int immediate;
char Opcode[6];
char function[6];
int contador=0;
int pc=0;
int stack[400000000];
char BITS[32]={};


typedef struct {
	char *inst;
	int Valor_PC;
}instruction;

instruction * instruccion;

void  PC(){

	int valor_inicial=0x00400000;

	instruccion[0].Valor_PC= valor_inicial;

	for(int i =1; i<(contador-1); i++){
			instruccion[i].Valor_PC= instruccion[i-1].Valor_PC +0x04;
	}

}

void liberar2(char bits[]){
	int i;
	for (i =0; i<32; i++){
		bits[i] = '\0';
	}
}

void guardar (char bits[], int i){

	int longit= strlen(bits)+1;

	instruccion[i].inst=(char*)malloc(longit*sizeof(char));

	if(instruccion[i].inst ==NULL){
		printf("No se pudo acceder a memoria");
		return(1);
	}
	strcpy(instruccion[i].inst, bits);
}


void liberar(char bits[]){
	int i;
	for (i =0; i<34; i++){
		bits[i] = '\0';
	}
}


void copiarArreglo(char* origen, int longitud) {
    for (int i = 0; i < longitud; i++) {
        BITS[i] = origen[i];
    }
}

void abrir_archivo(){

    int i;
    FILE *archivo;

    char Archivo[] = "binario.txt";
    char linea[34]; // Tamaño máximo de una línea en el archivo

    archivo = fopen(Archivo, "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    	while(!feof(archivo)){
		fgets(linea, 34, archivo);
		contador++;
	}

	rewind(archivo);

		instruccion = (instruction*)malloc(contador*sizeof(instruction));

	if (instruccion == NULL){
		printf("No se ha podido reservar la memoria. \n");
		exit(1);

	}

	for ( i=0; !feof(archivo)  ; i++){

		liberar(linea);
		fgets(linea, 34, archivo);
        copiarArreglo(linea,32);
		guardar(BITS , i);
		liberar2(BITS);
	}

    // Leer el contenido del archivo línea por línea
   // while (fgets(linea, sizeof(linea), archivo) != NULL) {
     //   printf("%s", linea); // Imprimir cada línea leída
   // }

   // fclose(archivo);

   // return 0;
}

int Binario_decimal_sinSigno(char bits[]){  // 16 bits sin signo
	 int suma=0;

	for(int i=0; i<16; i++){

		if(bits[i]=='1'){

			if(i==15)
				suma=suma+1;
			else if(i==14)
				suma=suma+2;
			else if(i==13)
				suma=suma+4;
			else if(i==12)
				suma=suma+8;
			else if(i==11)
				suma=suma+16;
			else if(i==10)
				suma=suma+32;
			else if(i==9)
				suma=suma+64;
			else if(i==8)
				suma=suma+128;
			else if(i==7)
				suma=suma+256;
			else if(i==6)
				suma=suma+512;
			else if(i==5)
				suma=suma+1024;
			else if(i==4)
				suma=suma+2048;
			else if(i==3)
				suma=suma+4096;
			else if(i==1)
				suma=suma+8192;
			else if(i==0)
				suma=suma +16384;
		}
	}
	return(suma);
 }

int Binario_decimal_conSigno(char bits[]){        /////16 bits con signo
	 int suma=0;
	char p[16];

	if(bits[0]=='1'){

		for(int j=0; j<16; j++){
			if (bits[j]=='1'){
				p[j]='0';
			}
			else  if (bits[j]=='0'){
				p[j]='1';
			}
		}

	}
	else
		strcpy(p, bits);

	for(int i=1; i<16; i++){

		if(p[i]=='1'){

			if(i==15)
				suma=suma+1;
			else if(i==14)
				suma=suma+2;
			else if(i==13)
				suma=suma+4;
			else if(i==12)
				suma=suma+8;
			else if(i==11)
				suma=suma+16;
			else if(i==10)
				suma=suma+32;
			else if(i==9)
				suma=suma+64;
			else if(i==8)
				suma=suma+128;
			else if(i==7)
				suma=suma+256;
			else if(i==6)
				suma=suma+512;
			else if(i==5)
				suma=suma+1024;
			else if(i==4)
				suma=suma+2048;
			else if(i==3)
				suma=suma+4096;
			else if(i==2)
				suma=suma+8192;
			else if(i==1)
				suma=suma+16384;
		}
	}
	if (bits[0]=='1'){
		suma=suma+1;
		suma=-1*suma;

	}
	return(suma);
 }

int Binario_Decimal(char bits[]){    /////5 bits

	int suma=0;

	for(int i=0; i<5; i++){

		if(bits[i]=='1'){
			if(i==4)
				suma=suma+1;

			else if(i==3)
				suma=suma+2;

			else if(i==2)
				suma=suma+4;

			else if(i==1)
				suma=suma+8;

			else if(i==0)
				suma=suma+16;
		}
	}

	return(suma);
}

int Binario_decimal_32bits(char bits[]){

	int suma=0;
	int a=31;

	for(int i=0; i<32; i++ ){

		if(bits[i]=='1'){
			int b= pow(2, a);
			suma= suma +  b;
		}
		a--;
	}
	return(suma);
}


///////TIPO R/////////
void add(int rs, int rd, int rt){

	Registros[rd]= Registros[rs] + Registros[rt];
    pc++;
}

void addu(int rs, int rd, int rt){
	unsigned int rs_us=Registros[rs];
	unsigned int rt_us=Registros[rt];
	Registros[rd]= rs_us+rt_us;
    pc++;
}

void and(int rs, int rd, int rt){

	Registros[rd]= Registros[rs] & Registros[rt];
    pc++;
}
///////////////////////////////////////////////////////////////////
void jr(int rs){
	 for (int i=0; i<(contador-1); i++){
		 if(instruccion[i].Valor_PC==Registros[rs]){
			 pc++;//pc=i;
		 }

	 }
}

void nor(int rs, int rd, int rt){

	Registros[rd] = ~(Registros[rs] | Registros [rt]);
    pc++;
}

void or(int rs, int rd, int rt){

	Registros[rd] = Registros[rs] | Registros [rt];
    pc++;
}

void slt(int rs, int rd, int rt){

	Registros[rd] = (Registros[rs]<Registros[rt]) ? 1 : 0;
    pc++;
}


void sltu(int rs, int rd, int rt){

	unsigned int rs_us=Registros[rs];
	unsigned int rt_us= Registros[rt];

	Registros[rd] = (rs_us<rt_us) ? 1 : 0;
    pc++;
}

void sll( int rd, int rt, int shamt){

	Registros[rd] = Registros[rt]  << shamt;
    pc++;
}

void srl( int rd, int rt, int shamt){

	Registros[rd] = Registros[rt]  >> shamt;
    pc++;
}

void sub(int rs, int rd, int rt){

	Registros[rd]= Registros[rs] - Registros[rt];
    pc++;
}

void subu(int rs, int rd, int rt){

	unsigned int rs_us=Registros[rs];
	unsigned int rt_us= Registros[rt];

	Registros[rd]= rs_us - rt_us;
    pc++;
}

////////////  TIPO I   /////////////////

void addi (int rs, int rt, int immediate){

	Registros[rt] = Registros[rs] + immediate;
    pc++;
}

void andi (int rs, int rt, int immediate){

	Registros[rt] = Registros[rs] & immediate;
    pc++;
}

void beq(int rs, int rt, int immediate){

	if(Registros[rs]==Registros[rt]){
		pc=pc+1+immediate;
	}
	else
        pc++;
}

void bne(int rs, int rt, int immediate){

	if(Registros[rs] !=Registros[rt]){
		pc=pc+1+immediate;
	}
	else
		pc++;
}

void lui(int rt, int immediate){

	Registros[rt] = immediate<<16;
    pc++;
}

void ori(int rs, int rt, int immediate){

	Registros[rt]= Registros[rs] | immediate;
    pc++;
}

void slti (int rs, int rt, int immediate){

	Registros[rt]= (Registros[rs]<immediate) ? 1:0;
    pc++;
}

void sltiu (int rs, int rt, int immediate){

	Registros[rt]= (Registros[rs]<immediate) ? 1:0;
    pc++;
}

void lw(int rs, int rt, int immediate){

	address= immediate+Registros[rs];

	Registros[rt]=stack[address];
    pc++;
}

void sw(int rs, int rt, int immediate){

	address= immediate+Registros[rs];

	stack[address]=Registros[rt];
    pc++;
}

////////////////   TIPO J  ///////////////

void jump(int immediate){

	for(int i=0; i<(contador-1); i++){

		if(instruccion[i].Valor_PC==immediate){
			 pc++;//pc=i;
		}
	}
}

void jal (int immediate){

	Registros[31]=instruccion[pc+1].Valor_PC;

	for(int i=0; i<(contador-1); i++){

		if(instruccion[i].Valor_PC==immediate){
			 pc++;//pc=i;
		}
	}
}

static void Opcode_instruccion( char bits[]){

	for ( int i =0; i<6; i++){
		Opcode[i]=bits[i];
	}
}

static void Function_instruccion(char bits[]){
	int j=0;
	for (int i=26; i<32; i++){
		function[j]=bits[i];
		j++;
	}
}

static void registros_intruccionesR(char bits[]){
	char rs[5];
	char rd[5];
	char rt[5];

	int a=0;
	int b=0;
	int c=0;

	for ( int j =16; j<21; j++){
		rd[a]=bits[j];
		a++;
	}

    for ( int h =11; h<16; h++){
		rt[b]=bits[h];
		b++;
	}

    for ( int i =6; i<11; i++){
		rs[b]=bits[i];
		c++;
	}



	Rs= Binario_Decimal(rs);
	Rd= Binario_Decimal(rd);
	Rt= Binario_Decimal(rt);
}

static void registros_intruccionesI(char bits[]){
	char rs[5];
	char rt[5];

	int a=0;
	int b=0;

	for ( int i =6; i<11; i++){
		rs[a]=bits[i];
		a++;
	}

	for ( int j =11; j<16; j++){
		rt[b]=bits[j];
		b++;
	}

	Rs= Binario_Decimal(rs);
	Rt= Binario_Decimal(rt);

}

static void Immediate_withSigne(char bits[]){

	int a=0;
	char inmediato[16];

	for (int i=16; i<32; i++){
		inmediato[a]=bits[i];
		a++;
	}
	immediate= Binario_decimal_conSigno(inmediato);
}

static void Immediate_Unsigned(char bits[]){

	int a=0;
	char inmediato[16];
	for (int i=16; i<32; i++){
		inmediato[a]=bits[i];
		a++;
	}
	immediate= Binario_decimal_sinSigno(inmediato);
}

static void Shamt(char bits[]){

	char Shamt[5];

	int a=0;

	for ( int i =21; i<26; i++){
		Shamt[a]=bits[i];
		a++;
	}

	shamt=Binario_Decimal(Shamt);

}

static void Jump_addr(char bits[]){
	int a=0;
	char inmediato[32];
	char address[26];

	for (int i=6; i<32; i++){
		address[a]=bits[i];
		a++;
	}

	int b=0;
	for (int j=0; j<32; j++){
		if (j<4){
			inmediato[j]='0';
		}
		else if (3<j<30 ){
			inmediato[j]=address[b];
			b++;
		}
		else
			inmediato[j]='0';
	}

	immediate= Binario_decimal_32bits(inmediato);
}


int main() {
    abrir_archivo();

    PC();
    int a= 0;

    while ( pc<(contador-1)){

		char bits[32];

		strcpy( bits , instruccion[pc].inst);


		if (a==0) {

			Opcode_instruccion(bits);

    ////TIPO R ////

			if (strcmp(Opcode, "000000") ==0){

				Function_instruccion(bits);

				if (strcmp(function, "100000") == 0){        //add
					registros_intruccionesR(bits);
					printf("0x%x     add $%i, $%i, $%i \n\n", instruccion[pc].Valor_PC, Rd, Rs, Rt);
					add(Rs, Rd, Rt);
				}

				else if (strcmp(function, "100001") ==0){   // addu
					registros_intruccionesR(bits);
					printf("0x%x     addu $%i, $%i, $%i \n\n", instruccion[pc].Valor_PC, Rd, Rs, Rt);
					addu(Rs, Rd, Rt);
				}

				else if (strcmp(function, "100100") ==0){   // and
					registros_intruccionesR(bits);
					printf("0x%x     and $%i, $%i, $%i \n\n", instruccion[pc].Valor_PC, Rd, Rs, Rt);
					and(Rs, Rd, Rt);
				}

				else if (strcmp(function, "001000") ==0){   // jr
					registros_intruccionesR(bits);
					printf("0x%x     jr $%i \n\n", instruccion[pc].Valor_PC, Rs);
					jr(Rs);
				}

				else if (strcmp(function, "100111") ==0){   // nor
					registros_intruccionesR(bits);
					printf("0x%x     nor $%i, $%i, $%i \n\n", instruccion[pc].Valor_PC, Rd, Rs, Rt);
					nor(Rs, Rd, Rt);
				}

				else if (strcmp(function, "100101") ==0){   // or
					registros_intruccionesR(bits);
					printf("0x%x     or  $%i, $%i, $%i \n\n", instruccion[pc].Valor_PC, Rd, Rs, Rt);
					or(Rs, Rd, Rt);
				}

				else if (strcmp(function, "101010") ==0){   // slt
					registros_intruccionesR(bits);
					printf("0x%x     slt  $%i, $%i, $%i \n\n", instruccion[pc].Valor_PC, Rd, Rs, Rt);
					slt(Rs, Rd, Rt);
				}

				else if (strcmp(function, "101011") ==0){   // sltu
					registros_intruccionesR(bits);
					printf("0x%x     sltu  $%i, $%i, $%i \n\n", instruccion[pc].Valor_PC, Rd, Rs, Rt);
					sltu(Rs, Rd, Rt);
				}

				else if (strcmp(function, "000000") ==0){   // sll
					registros_intruccionesR(bits);
					Shamt(bits);
					printf("0x%x     sll $%i, $%i, %i \n\n", instruccion[pc].Valor_PC, Rd, Rt, shamt);
					sll(Rd, Rt, shamt);
				}

				else if (strcmp(function, "000010") ==0){   // srl
					registros_intruccionesR(bits);
					Shamt(bits);
					printf("0x%x     srl $%i, $%i, %i \n\n", instruccion[pc].Valor_PC, Rd, Rt, shamt);
					srl(Rd, Rt, shamt);

				}

				else if (strcmp(function, "100010") ==0){   // sub
					registros_intruccionesR(bits);
					printf("0x%x     sub $%i, $%i, $%i \n\n", instruccion[pc].Valor_PC, Rd, Rs, Rt);
					sub(Rs, Rd, Rt);
				}

				else if (strcmp(function, "100011") ==0){   // subu
					registros_intruccionesR(bits);
					printf("0x%x     subu, $%i, $%i, $%i \n\n", instruccion[pc].Valor_PC, Rd, Rs, Rt);
					subu(Rs, Rd, Rt);
				}

			}

    ////Tipo I ////

			else if (strcmp(Opcode, "001000") ==0){  // addi
				registros_intruccionesI(bits);
				Immediate_withSigne(bits);
				printf("0x%x     addi $%i, $%i, %i \n\n", instruccion[pc].Valor_PC, Rt, Rs, immediate);
				addi(Rs, Rt, immediate);

			}

			else if (strcmp(Opcode, "001001") ==0){  //  addiu
				registros_intruccionesI(bits);
				Immediate_Unsigned(bits);
				printf("0x%x     addiu $%i, $%i, %i \n\n", instruccion[pc].Valor_PC, Rt, Rs, immediate);
				addi(Rs, Rt, immediate);
			}

			else if (strcmp(Opcode, "001100") ==0){  // andi
				registros_intruccionesI(bits);
				Immediate_withSigne(bits);
				printf("0x%x     andi $%i, $%i, %i \n\n", instruccion[pc].Valor_PC, Rt, Rs, immediate);
				andi(Rs, Rt, immediate);

			}
			else if (strcmp(Opcode, "000100") ==0){ // beq
				registros_intruccionesI(bits);
				Immediate_withSigne(bits);
				printf("0x%x     beq $%i, $%i, %i \n\n", instruccion[pc].Valor_PC, Rs, Rt, immediate);
				beq (Rs,Rt, immediate);

			}

			else if (strcmp(Opcode, "000101") ==0){ // bne
				registros_intruccionesI(bits);
				Immediate_withSigne(bits);
				printf("0x%x     bne $%i, $%i, %i \n\n", instruccion[pc].Valor_PC, Rs, Rt, immediate);
				bne(Rs, Rt, immediate);
			}
			else if (strcmp(Opcode, "001111") ==0){ // lui
				registros_intruccionesI(bits);
				Immediate_withSigne(bits);
				printf("0x%x     lui $%i, %i \n\n", instruccion[pc].Valor_PC, Rt, immediate);
				lui( Rt, immediate);
			}
			else if (strcmp(Opcode, "001101") ==0){ // ori
				registros_intruccionesI(bits);
				Immediate_withSigne(bits);
				printf("0x%x     ori $%i, $%i, %i \n\n", instruccion[pc].Valor_PC, Rt, Rs, immediate);
				ori(Rs, Rt, immediate);
			}

			else if (strcmp(Opcode, "001010") ==0){ // slti
				registros_intruccionesI(bits);
				Immediate_withSigne(bits);
				printf("0x%x     slti $%i, $%i, %i \n\n", instruccion[pc].Valor_PC, Rt, Rs, immediate);
				slti(Rs, Rt, immediate);
			}

			else if (strcmp(Opcode, "001011") ==0){ // sltiu
				registros_intruccionesI(bits);
				Immediate_Unsigned(bits);
				printf("0x%x     sltiu $%i, $%i, %i \n\n", instruccion[pc].Valor_PC, Rt, Rs, immediate);
				sltiu(Rs, Rt, immediate);
			}

			else if (strcmp(Opcode, "100011") ==0){ // lw
				registros_intruccionesI(bits);
				Immediate_withSigne(bits);
				printf("0x%x     lw $%i, %i, ($%i), \n\n", instruccion[pc].Valor_PC, Rt, immediate , Rs);
				lw(Rs, Rt, immediate);


			}
			else if (strcmp(Opcode, "101011") ==0){ // sw
				registros_intruccionesI(bits);
				Immediate_withSigne(bits);
				printf("0x%x     sw $%i, %i, ($%i), \n\n", instruccion[pc].Valor_PC, Rt, immediate , Rs);
				sw(Rs, Rt, immediate);
			}

    ////Tipo J ////

			else if (strcmp(Opcode, "000010") ==0){ //  j
				Jump_addr(bits);
				printf("0x%x     j %x \n\n", instruccion[pc].Valor_PC, immediate);
				jump(immediate);
			}

			else if (strcmp(Opcode, "000011") ==0){ //  jal
				Jump_addr(bits);
				printf("0x%x     jal %x \n\n", instruccion[pc].Valor_PC, immediate);
				jal(immediate);
			}
		}

	}



    return 0;
}
