#include <stdlib.h>
#include <string.h>
#include "codgen.h"

float CODE[TAM_PROG];
int libre = 0;
int desplazamiento[TAM_DISP] = {0};

char CTES[TAM_CTES];

int libre_ctes = 0;

int construccion_no_soportada = 0;

int emitir(float valor) {
    CODE[libre] = valor;
    return libre++;
}

int codigo_tipo_mac(enum tipo tipo) {
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

static void emitir_con_tipo(int instruccion, enum tipo tipo) {
    emitir(instruccion);
    emitir(codigo_tipo_mac(tipo));
}

void emitir_inpp() { emitir(INPP); }
void emitir_parar() { emitir(PARAR); }

void emitir_crct(enum tipo tipo, float valor) {
    if (tipo != ERROR) {
        desplazamiento[get_nivel()] += ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
        emitir_con_tipo(CRCT, tipo);
        emitir(valor);
    }
}

void emitir_crcts(int posicion_en_ctes) {
    desplazamiento[get_nivel()] += ts[resolver_tipo_en_TS(INT)].ets->cant_byte;

    emitir(CRCTS);
    emitir(posicion_en_ctes);
}

void emitir_crvl(int nivel, int despl, enum tipo tipo) {
    desplazamiento[get_nivel()] += ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
    emitir(CRVL);
    emitir(nivel);
    emitir(despl);
    emitir(codigo_tipo_mac(tipo));
}

void emitir_alm(int nivel, int despl, enum tipo tipo) {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;

    emitir(ALM);
    emitir(nivel);
    emitir(despl);
    emitir(codigo_tipo_mac(tipo));
}

void emitir_cast(enum tipo origen, enum tipo destino) {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(origen)].ets->cant_byte;
    desplazamiento[get_nivel()] += ts[resolver_tipo_en_TS(destino)].ets->cant_byte;

    emitir_con_tipo(CAST, origen);
    emitir(codigo_tipo_mac(destino));
}

void emitir_sum(enum tipo tipo) {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
    emitir_con_tipo(SUM, tipo);
}

void emitir_sub(enum tipo tipo) {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
    emitir_con_tipo(SUB, tipo);
}

void emitir_mul(enum tipo tipo) {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
    emitir_con_tipo(MUL, tipo);
}

void emitir_div(enum tipo tipo) {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
    emitir_con_tipo(DIV, tipo);
}

void emitir_inv(enum tipo tipo) {
    emitir_con_tipo(INV, tipo);
}

void emitir_and(enum tipo tipo) {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
    emitir_con_tipo(AND, tipo);
}

void emitir_or(enum tipo tipo) {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
    emitir_con_tipo(OR, tipo);
}

void emitir_neg(enum tipo tipo) {
    emitir_con_tipo(NEG, tipo);
}

void emitir_cmma(enum tipo tipo) {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
    emitir_con_tipo(CMMA, tipo);
}

void emitir_cmme(enum tipo tipo) {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
    emitir_con_tipo(CMME, tipo);
}

void emitir_cmig(enum tipo tipo) {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
    emitir_con_tipo(CMIG, tipo);
}

void emitir_cmai(enum tipo tipo) {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
    emitir_con_tipo(CMAI, tipo);
}

void emitir_cmei(enum tipo tipo) {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
    emitir_con_tipo(CMEI, tipo);
}

void emitir_cmni(enum tipo tipo) {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
    emitir_con_tipo(CMNI, tipo);
}

void emitir_leer(enum tipo tipo) {
    desplazamiento[get_nivel()] += ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
    emitir_con_tipo(LEER, tipo);
}

void emitir_impr(enum tipo tipo) {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(tipo)].ets->cant_byte;
    emitir_con_tipo(IMPR, tipo);
}

void emitir_imprcs() {
    desplazamiento[get_nivel()] -= ts[resolver_tipo_en_TS(INT)].ets->cant_byte;
    emitir(IMPRCS);
}

int emitir_bifs(int salto) {
    // TODO
    emitir(BIFS);
    return emitir(salto);
}

int emitir_biff(enum tipo tipo, int salto) {
    // TODO
    emitir_con_tipo(BIFF, tipo);
    return emitir(salto);
}

void emitir_aloc(int bytes) {
    desplazamiento[get_nivel()] += bytes;
    emitir(ALOC);
    emitir(bytes);
}

void emitir_dmem(int bytes) {
    emitir(DMEM);
    emitir(bytes);
}

void emitir_enbl(int nivel) {
    desplazamiento[nivel] = 0;
    emitir(ENBL);
    emitir(nivel);
}

void emitir_finb(int nivel) {
    emitir(FINB);
    emitir(nivel);
}

int generar_objeto(char *fuente) {
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

int reservar_buffer_casteo() {
    int posicion = libre;
    libre += 3;
    return posicion;
}

void coercionar_operandos(int posicion_buffer, enum tipo tipo_izquierdo, enum tipo tipo_derecho) {
    if (tipo_izquierdo < tipo_derecho) {
        desplazamiento[get_nivel()] += ts[resolver_tipo_en_TS(tipo_derecho)].ets->cant_byte
                - ts[resolver_tipo_en_TS(tipo_izquierdo)].ets->cant_byte;

        CODE[posicion_buffer] = CAST;
        CODE[posicion_buffer + 1] = codigo_tipo_mac(tipo_izquierdo);
        CODE[posicion_buffer + 2] = codigo_tipo_mac(tipo_derecho);
    } else {
        if (tipo_izquierdo > tipo_derecho)
            emitir_cast(tipo_derecho, tipo_izquierdo);

        borrar_buffer_casteo(posicion_buffer);
    }
}

void registrar_promocion_char(enum tipo tipo_operandos) {
    if (tipo_operandos == CHAR)
        desplazamiento[get_nivel()] += ts[resolver_tipo_en_TS(INT)].ets->cant_byte
                - ts[resolver_tipo_en_TS(CHAR)].ets->cant_byte;
}

void borrar_buffer_casteo(int posicion_inicio) {
    for (int i = posicion_inicio + 3; i > posicion_inicio; i--) {
        for (int j = i; j <= libre; j++) {
            CODE[j - 1] = CODE[j];
        }
    }

    libre -= 3;
}

void resolver_asignaciones(Datos_asignacion *cabecera) {
    Datos_asignacion *asignacion = cabecera;

    while (asignacion != NULL) {
        emitir_alm(asignacion->nivel, asignacion->desplazamiento, asignacion->tipo);

        emitir_crvl(asignacion->nivel, asignacion->desplazamiento, asignacion->tipo);

        if (asignacion->proximo != NULL) {
            enum tipo tipo_lado_derecho = asignacion->tipo;
            enum tipo tipo_lado_izquierdo = asignacion->proximo->tipo;

            if (tipo_lado_izquierdo > tipo_lado_derecho)
                emitir_cast(tipo_lado_derecho, tipo_lado_izquierdo);
        }

        Datos_asignacion *asignacion_previa = asignacion;
        asignacion = asignacion_previa->proximo;
        free(asignacion_previa);
    }
}
