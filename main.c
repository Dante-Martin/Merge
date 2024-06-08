#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_OK 0
#define ERR_ARG 1
#define ERR_ARCH 2

#define CANT_ARGS 2
#define ARG_PRODUCTOS 1 // L apos de losarchivos
#define ARG_MOVIMIENTOS 2 // Las posiciones de los archivos
// Merge Productos.dat Movimientos.dat

typedef struct
{
    char codigo[7];
    char descripcion[21];
    int stock;
}Productos;

typedef struct
{
    char codigo[7];
    int cantidad;
}Movimiento;


int generarArchivoProductos(const char *nomArchProd);
int actualizarProductos(const char* nomArchProds, const char* nomArchMovs);
void procesarProductoNuevo(Movimiento *mov, FILE* archMovs, FILE* archProdTemp);


int main(int argc, char *argv[])
{
    int ret;
    generarArchivoProductos(argv[ARG_PRODUCTOS]);
    generarArchivoMOvimientos(argv[ARG_MOVIMINTOS]);

    if(argc - 1 != CANT_ARGS)
        return ERR_ARG;
    int ret;
    puts("Antes de actualizar");
    mostrarProductos(argv[ARG_PRODUCTOS], argv[ARG_MOVIMIENTOS]);

    ret = actualizarProductos(argv[ARG_PRODUCTOS], argv[ARG_MOVIMIENTOS]);

    puts("Despues de actualizar");
    mostrarProductos(argv[ARG_PRODUCTOS], argv[ARG_MOVIMIENTOS]);
    return 0;
}

int generarArchivoProductos(const char *nomArchProd){
    Movimierno movs[CANT_PROD]
}
void mostarProductos(const char*nomArchProd){


return TODO_OK;
}
int actualizarProductos(const char* nomArchProds, const char* nomArchMovs){

    FILE* archProds=fopen(nomArchProds,"rb");
    if(!archProds){
        return ERR_ARCH;

    }
    FILE* archMovs=fopen(nomArchMovs,"rb");
    if(!archMovs){
        fclose(archProds);
        return ERR_ARCH;

    }

    char nomArchProdTmp[101];
    strcpy(nomArchProdTmp,nomArchProd);
    char *extension = strchr(nomArchProdTmp,'.')+1;
    strcpy(extension,"tmp");//se cambio la extension de un archivo. de .dat a .tmp

    FILE* archProdsTemp=fopen(nomArchProdsTemp,"wb");
     if(!archProdsTemp){
        fclose(archProds);
        fclose(archMovs);
        return ERR_ARCH;
    }

    Producto prod;
    Movimiento mov;
    int comp;

    fread(&prod, sizeof(Producto),1,archProds);
    fread(&mov, sizeof(Movimineto),1,archMovs);

    while(!feof(archMovs)&& !feof(archProds)){

        comp=strcmp(prod.codigo,mov.codigo);

        if(comp==0){//mismo codigo
            prod.stock+=mov.cantidad;
            fread(&mov,sizeof(Movimieto),1,archMovs);
        }
        if(comp<0){//sin movimientos
            fwrite(&prod,sizeof(Producto),1,archProdsTemp);
            fread(&prod,sizeof(Producto),1,archProds);
        }
        if(comp>0){//Mov sin prod (nuevo producto)
            procesarProductoNuevo(&mov, archMovs, archProdsTemp);
        }
        while(!feof(archProds)) //Cuando tengo elementos de mas, por lo tnaot son productos sin movimiento
        {
            fwrite(&prod,sizeof(Producto),1,archProdsTemp);
            fread(&prod,sizeof(Producto),1,archProds);
        }
        while(!feof(archMovs)) //Todos productos nuevos, por lo tanto tambien los guardo en nueva struct
        {
            procesarProductoNuevo(&mov, archMovs, archProdsTemp);
        }
        fclose(archProdsTemp);
        fclose(archMovs);
        fclose(archProds);

        remove(nomArchProds);
        rename(nomArchProdTemp, nomArchProds);

    return TODO_OK;
}

void procesarProductoNuevo(Movimiento *mov, FILE* archMovs, FILE* archProdTemp)
{
    Producto prodNuevo;
    strcpy(prodNuevo.codigo,mov->codigo);
            *(prodNuevo.descripcion) = '\0'; // para obtener el primer char del vector
            prodNuevo.stock=mov->cantidad;
            fread(mov, sizeof(Movimineto),1,archMovs);
            while(!feof(archMovs) && strcmp(mov->codigo,prodNuevo.codigo)==0){
                prodNuevo.stock=+=mov->cantidad;
                fread(mov, sizeof(Movimineto),1,archMovs);

            }
            fwrite(&prodNuevo,sizeof(Producto),1,archProdsTemp);
}
