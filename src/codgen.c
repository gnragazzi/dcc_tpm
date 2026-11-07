#include <stdlib.h>
#include <string.h>
#include "codgen.h"

float CODE[TAM_PROG];
int libre = 0;
int desplazamiento[TAM_DISP] = {0};

char CTES[TAM_CTES];

int libre_ctes = 0;

int construccion_no_soportada = 0;

int emitir(float valor)
{
	CODE[libre] = valor;
	return libre++;
}

int codigo_tipo_mac(enum tipo tipo)
{
	switch (tipo) {
		case CHAR:
			return 0;
		case INT:
			return 1;
		case FLOAT:
			return 2;
		default:
			return -1;
	}
}

static void emitir_con_tipo(int instruccion, enum tipo tipo)
{
	emitir(instruccion);
	emitir(codigo_tipo_mac(tipo));
}

void emitir_inpp() { emitir(INPP); }
void emitir_parar() { emitir(PARAR); }

void emitir_crct(enum tipo tipo, float valor)
{
	if (tipo != ERROR) {
		// TODO falta forma de sumar a la variable desplazamiento
		emitir_con_tipo(CRCT, tipo);
		emitir(valor);
	}
}

void emitir_crcts(int posicion_en_ctes)
{
	emitir(CRCTS);
	emitir(posicion_en_ctes);
}

void emitir_crvl(int nivel, int despl, enum tipo tipo)
{
	emitir(CRVL);
	emitir(nivel);
	emitir(despl);
	emitir(codigo_tipo_mac(tipo));
}

void emitir_alm(int nivel, int despl, enum tipo tipo)
{
	// TODO falta forma de restar el almacenamiento tomado
	emitir(ALM);
	emitir(nivel);
	emitir(despl);
	emitir(codigo_tipo_mac(tipo));
}

void emitir_cast(enum tipo origen, enum tipo destino)
{
	emitir_con_tipo(CAST, origen);
	emitir(codigo_tipo_mac(destino));
}

void emitir_sum(enum tipo tipo) { emitir_con_tipo(SUM, tipo); }
void emitir_sub(enum tipo tipo) { emitir_con_tipo(SUB, tipo); }
void emitir_mul(enum tipo tipo) { emitir_con_tipo(MUL, tipo); }
void emitir_div(enum tipo tipo) { emitir_con_tipo(DIV, tipo); }
void emitir_inv(enum tipo tipo) { emitir_con_tipo(INV, tipo); }

void emitir_and(enum tipo tipo) { emitir_con_tipo(AND, tipo); }
void emitir_or(enum tipo tipo) { emitir_con_tipo(OR, tipo); }
void emitir_neg(enum tipo tipo) { emitir_con_tipo(NEG, tipo); }

void emitir_cmma(enum tipo tipo) { emitir_con_tipo(CMMA, tipo); }
void emitir_cmme(enum tipo tipo) { emitir_con_tipo(CMME, tipo); }
void emitir_cmig(enum tipo tipo) { emitir_con_tipo(CMIG, tipo); }
void emitir_cmai(enum tipo tipo) { emitir_con_tipo(CMAI, tipo); }
void emitir_cmei(enum tipo tipo) { emitir_con_tipo(CMEI, tipo); }
void emitir_cmni(enum tipo tipo) { emitir_con_tipo(CMNI, tipo); }

void emitir_leer(enum tipo tipo) { emitir_con_tipo(LEER, tipo); }
void emitir_impr(enum tipo tipo) { emitir_con_tipo(IMPR, tipo); }
void emitir_imprcs() { emitir(IMPRCS); }

int emitir_bifs(int salto)
{
	emitir(BIFS);
	return emitir(salto);
}

int emitir_biff(enum tipo tipo, int salto)
{
	emitir_con_tipo(BIFF, tipo);
	return emitir(salto);
}

void emitir_aloc(int bytes)
{
	emitir(ALOC);
	emitir(bytes);
}

void emitir_dmem(int bytes)
{
	emitir(DMEM);
	emitir(bytes);
}

void emitir_enbl(int nivel)
{
	desplazamiento[nivel] = 0;
	emitir(ENBL);
	emitir(nivel);
}

void emitir_finb(int nivel)
{
	emitir(FINB);
	emitir(nivel);
}

int generar_objeto(char *fuente)
{
	size_t largo = strlen(fuente);
	char *objeto = (char *) malloc(largo + 3);
	int ok;

	strcpy(objeto, fuente);
	if (largo >= 2 && strcmp(fuente + largo - 2, ".c") == 0)
		objeto[largo - 1] = 'o';
	else
		strcat(objeto, ".o");

	ok = guardar_codgen(CODE, CTES, objeto);
	free(objeto);
	return ok;
}
