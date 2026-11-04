#ifndef CODGEN_H
#define CODGEN_H

#include "sistejec.h"
#include "util.h"

extern float CODE[TAM_PROG];
extern int libre;

extern char CTES[TAM_CTES];
extern int libre_ctes;

extern int construccion_no_soportada;

int emitir(float valor);

int codigo_tipo_mac(enum tipo tipo);

void emitir_inpp();
void emitir_parar();

void emitir_crct(enum tipo tipo, float valor);
void emitir_crcts(int posicion_en_ctes);
void emitir_crvl(int nivel, int desplazamiento, enum tipo tipo);
void emitir_alm(int nivel, int desplazamiento, enum tipo tipo);
void emitir_cast(enum tipo origen, enum tipo destino);

void emitir_sum(enum tipo tipo);
void emitir_sub(enum tipo tipo);
void emitir_mul(enum tipo tipo);
void emitir_div(enum tipo tipo);
void emitir_inv(enum tipo tipo);

void emitir_and(enum tipo tipo);
void emitir_or(enum tipo tipo);
void emitir_neg(enum tipo tipo);

void emitir_cmma(enum tipo tipo);
void emitir_cmme(enum tipo tipo);
void emitir_cmig(enum tipo tipo);
void emitir_cmai(enum tipo tipo);
void emitir_cmei(enum tipo tipo);
void emitir_cmni(enum tipo tipo);

void emitir_leer(enum tipo tipo);
void emitir_impr(enum tipo tipo);
void emitir_imprcs();

/* Devuelven la posición en CODE del operando desplazamiento, para completarlo después. */
int emitir_bifs(int desplazamiento);
int emitir_biff(enum tipo tipo, int desplazamiento);

void emitir_aloc(int bytes);
void emitir_dmem(int bytes);
void emitir_enbl(int nivel);
void emitir_finb(int nivel);

int generar_objeto(char *fuente);

#endif
