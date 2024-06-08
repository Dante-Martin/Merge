#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_OK 0
#define ERR_ARG 1
#define ERR_ARCH 2

#define CANT_PROD 3
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
int mostrarProductos(const char *nomArchProd);
void procesarProductoNuevo(Movimiento *mov, FILE* archMovs, FILE* archProdTemp);
int generarArchivoMovimientos(const char *archMovs);


int main(int argc, char *argv[])
{
    int ret;
    generarArchivoProductos(argv[ARG_PRODUCTOS]);
    generarArchivoMovimientos(argv[ARG_MOVIMIENTOS]);

    if(argc - 1 != CANT_ARGS)
        return ERR_ARG;
    puts("Antes de actualizar");
    mostrarProductos(argv[ARG_PRODUCTOS]);

    ret = actualizarProductos(argv[ARG_PRODUCTOS], argv[ARG_MOVIMIENTOS]); //Retorna si fue o no exitosa la funcion

    puts("Despues de actualizar");
    mostrarProductos(argv[ARG_PRODUCTOS]);
    return 0;
}

int generarArchivoProductos(const char *nomArchProd){
    Productos prods[CANT_PROD] = {{0, "Kiwi", 20}, {1, "Higo", 9}, {2, "Banana", 39},};
    FILE*arch = fopen(nomArchProd, "wb");
    if(arch == NULL)
    {
        return ERR_ARG;
    }
    fwrite(prods, sizeof(Productos),CANT_PROD,arch);

    fclose(arch);


}
int generarArchivoMovimientos(const char *archMovs){
    Movimiento movs[CANT_PROD] = {{0, "Kiwi", 40}, {4, "Sandia", 9}, {2, "Banana", -12},};
    FILE*arch = fopen(archMovs, "wb");
    if(arch == NULL)
    {
        return ERR_ARG;
    }
    fwrite(movs, sizeof(Movimiento),CANT_PROD,arch);

    fclose(arch);
}
int mostrarProductos(const char *nomArchProd){
    FILE*arch = fopen(nomArchProd, "rb");
    if(!arch)
{
    return ERR_ARCH;
}
Productos prod;
fread(&prod, sizeof(Productos),1, arch);
while(!feof(arch))
{
    printf("%2s | %-20s | %04d \n", prod.codigo, prod.descripcion, prod.stock);
    fread(&prod, sizeof(Productos),1, arch);
}
fclose(arch);
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

    char nomArchProdTemp[101];
    strcpy(nomArchProdTemp,nomArchProds);
    char *extension = strchr(nomArchProdTemp,'.')+1;
    strcpy(extension,"tmp");//se cambio la extension de un archivo. de .dat a .tmp

    FILE* archProdsTemp=fopen(nomArchProdTemp,"wb");
     if(!archProdsTemp){
        fclose(archProds);
        fclose(archMovs);
        return ERR_ARCH;
    }

    Productos prod;
    Movimiento mov;
    int comp;

    fread(&prod, sizeof(Productos),1,archProds);
    fread(&mov, sizeof(Movimiento),1,archMovs);

    while(!feof(archMovs)&& !feof(archProds)){

        comp=strcmp(prod.codigo,mov.codigo);

        if(comp==0){//mismo codigo
            prod.stock += mov.cantidad;
            fread(&mov,sizeof(Movimiento),1,archMovs);
        }
        if(comp<0){//sin movimientos
            fwrite(&prod,sizeof(Productos),1,archProdsTemp);
            fread(&prod,sizeof(Productos),1,archProds);
        }
        if(comp>0){//Mov sin prod (nuevo producto)
            procesarProductoNuevo(&mov, archMovs, archProdsTemp);
        }
        while(!feof(archProds)) //Cuando tengo elementos de mas, por lo tnaot son productos sin movimiento
        {
            fwrite(&prod,sizeof(Productos),1,archProdsTemp);
            fread(&prod,sizeof(Productos),1,archProds);
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

}
return TODO_OK;
}

void procesarProductoNuevo(Movimiento *mov, FILE* archMovs, FILE* archProdTemp)
{
    Productos prodNuevo;
    strcpy(prodNuevo.codigo,mov->codigo);
            *(prodNuevo.descripcion) = '\0'; // para obtener el primer char del vector
            prodNuevo.stock=mov->cantidad;
            fread(mov, sizeof(Movimiento),1,archMovs);
            while(!feof(archMovs) && strcmp(mov->codigo,prodNuevo.codigo)==0){
                prodNuevo.stock+=mov->cantidad;
                fread(mov, sizeof(Movimiento),1,archMovs);

            }
            fwrite(&prodNuevo,sizeof(Productos),1,archProdTemp);
}
