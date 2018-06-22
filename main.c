#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "ArrayList.h"
#include "producto.h"


int cargarDesdeArchivo(FILE *datosTemporal,ArrayList* listaDeArchivos);


int main()
{
    FILE* datosTemporal;

    eProducto* nuevoProducto;
    eProducto* aux;

    ArrayList* listaDeArchivos= al_newArrayList();//de los archivos que levanta
    int opcion=0;
    char seguir='s';
    char confirm;
    int i;
    int auxCod,index;
    int flag=0;
    int cargados=0;
    int len;

    if((datosTemporal=fopen("datosTemporal.bin","rb+"))==NULL)
    {
        if ((datosTemporal=fopen("datosTemporal.bin","wb+"))==NULL)
        {
            printf("No se pudo abrir el archivo datos temporarios");
            exit(1);
        }
    }


    len= cargarDesdeArchivo(datosTemporal,listaDeArchivos);


    if(len==1)
    {
        // printf("%d--%s--%f\n",aux->codigo, aux->descripcion, aux->importe);
        cargados=1;
    }

    do
    {
        printf("\n------------------------\n");
        printf("-ALMACEN - LO DE CACHO -\n");
        printf("------------------------\n");
        printf("\n1)Alta de producto\n2)Modificar producto\n3)Baja logica\n4)Baja fisica\n5)Lista de productos\n6)Salir\n");
        printf("\nIngrese numero de opcion: ");
        scanf("%d",&opcion);

        switch(opcion)
        {
        case 1:
            printf("----------------\n");
            printf("Alta de producto\n");
            printf("----------------\n");
            nuevoProducto=(eProducto*)producto_newProducto();
            flag=0;

            if(nuevoProducto!=NULL)
            {
                for(i=0; i<al_len(listaDeArchivos); i++)
                {
                    aux=(eProducto*)al_get(listaDeArchivos,i);
                    if(aux->codigo==nuevoProducto->codigo|| ((strcmpi(aux->descripcion,nuevoProducto->descripcion))==0))
                    {
                        printf("Ese producto ya existe.\n");
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    al_add(listaDeArchivos,nuevoProducto);
                    cargados=1;
                    printf("\nDatos cargados en memoria...OK!\n");
                }

            }
            else
            {
                printf("No se pudo agregar el producto.");
            }
            getche();
            system("cls");
            break;
        case 2:
            if(cargados==1)
            {
                flag=0;
                printf("------------------\n");
                printf("Modificar producto\n");
                printf("------------------\n");
                auxCod=getInt("Ingrese el codigo del producto: ");

                for(i=0; i<al_len(listaDeArchivos); i++)
                {
                    aux=(eProducto*) al_get(listaDeArchivos,i);
                    if(auxCod== aux->codigo)
                    {
                        printf("Datos encontrados: \n");
                        printf("Codigo del producto: %d\nDescripcion: %s\nCantidad: %d\nPrecio: %.2f\nEstado: %d\n",aux->codigo,aux->descripcion,aux->cantidad,aux->importe,aux->estado);

                        aux->codigo= getInt("\nIngrese el nuevo codigo: ");
                        aux->importe=getFloat("\nIngrese el nuevo importe: ");
                        aux->cantidad=getInt("\nIngrese la nueva cantidad: ");
                        index=al_indexOf(listaDeArchivos,aux);
                       // al_set(listaDeArchivos,index,aux);
                        al_remove(listaDeArchivos,index);
                        al_push(listaDeArchivos,index,aux);
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    printf("No se encontro el producto.\n");
                }
            }
            else
            {
                printf("No se puede realizar esta opcion porque no hay archivos cargados.\n");
            }
            getche();
            system("cls");
            break;
        case 3:
            printf("-----------\n");
            printf("Baja logica\n ");
            printf("-----------\n");
            auxCod=getInt("Ingrese el codigo del producto: ");

            for(i=0; i<al_len(listaDeArchivos); i++)
            {
                aux=(eProducto*)al_get(listaDeArchivos,i);
                if(auxCod== aux->codigo)
                {
                    printf("Producto encontrado:\n ");
                    printf("Codigo: %d-Name: %s\nCantidad: %d\n Importe: %.2f\nEstado: %d\n",aux->codigo,aux->descripcion,aux->cantidad,aux->importe,aux->estado);
                    index=al_indexOf(listaDeArchivos,aux);
                    aux->estado=1;
                    al_set(listaDeArchivos,index,aux);
                    flag=1;
                    printf("El estado del producto ha sido cambiado a 1.\n");
                }
            }
            if(flag==0)
            {
                printf("No se encontro el producto.\n");
            }
            getche();
            system("cls");
            break;
        case 4:
            printf("------------\n");
            printf("Baja fisica:\n");
            printf("------------\n");
            auxCod=getInt("Ingrese el codigo del producto: ");

            for(i=0; i<al_len(listaDeArchivos); i++)
            {
                aux=(eProducto*)al_get(listaDeArchivos,i);
                if(auxCod==aux->codigo)
                {
                    printf("Dato encontrado:\n");
                    printf("Codigo: %d\nNombre: %s\nCantidad: %d\nImporte: %.2f\nEstado: %d\n",aux->codigo,aux->descripcion,aux->cantidad,aux->importe,aux->estado);
                    printf("Seguro de eliminar?s/n \n");
                    fflush(stdin);
                    scanf("%c",&confirm);
                    if(confirm=='s')
                    {
                        index=al_indexOf(listaDeArchivos,aux);
                        al_remove(listaDeArchivos,index);
                        printf("Accion realizada.\n");
                    }
                    else
                    {
                        printf("Accion cancelada.\n");
                    }
                }
            }
            getche();
            system("cls");
            break;
        case 5:
            printf("flag: %d",cargados);
            if(cargados==1)
            {
                printf("\n---------------------------\n");
                printf("Lista de productos cargados\n");
                printf("---------------------------\n");
                for(i=0; i<al_len(listaDeArchivos); i++)
                {
                    aux=(eProducto*)al_get(listaDeArchivos,i);
                    printf("%d) Descripcion: %s\tCodigo: %d\nImporte: %.2f\nCantidad: %d\nEstado: %d\n",i,aux->descripcion,aux->codigo,aux->importe,aux->cantidad,aux->estado);
                }
            }
            else
            {
                printf("\n1)flag: %d",cargados);
                printf("\nNo hay datos cargados.\n");
            }
            getche();
            system("cls");
            break;
        case 6:
            seguir='n';
            al_sort(listaDeArchivos,producto_ordenar,0);

            fclose(datosTemporal);

            if((datosTemporal=fopen("datosTemporal.bin","wb"))==NULL)
            {
                printf("No se pudo abrir el archivo datos temporarios \n");
                exit(1);
            }
            else
            {
                printf("Cargando los datos al archivo.\n");
                rewind(datosTemporal);
                for(i=0; i<al_len(listaDeArchivos); i++)
                {
                    aux=(eProducto*)al_get(listaDeArchivos,i);

//                fseek(datosTemporal,0L,SEEK_SET); como esta en modo wb va a pisar todos los datos que existen
// no es necesario el fseek

                    fflush(stdin);
                    if((fwrite(aux,sizeof(eProducto),1,datosTemporal))!=1)
                    {
                        printf("No se pudieron cargar los datos\n");
                    }
                    else
                    {
                        printf("Dato cargado.\n id: %d\nDescripcion: %s\n",aux->codigo,aux->descripcion);
                    }
                }

                if((fclose(datosTemporal))==-1)
                {
                    printf("ATENCION: No se pudo cerrar el archivo.\n");
                }
                else
                {
                    printf("Se cerro el archivo exitosamente.\n");
                }
            }
            /////
//            rewind(datosTemporal);
//
//            while(!feof(datosTemporal))
//            {
//                fread(aux,sizeof(eProducto),1,datosTemporal);
//
//                if(feof(datosTemporal))
//                {
//
//                    break;
//                }
//                else
//                {
//                    printf("No se pudo leer de archivo.\n");
//
//                    break;
//                }
//
//            }
            //////
            getche();
            system("cls");
            break;
        default:
            printf("Ese numero de opcion no existe.\n");
            break;


        }

    }
    while(seguir=='s');


    return 0;

}



int cargarDesdeArchivo(FILE *datosTemporal,ArrayList* listaDeArchivos)
{
    int cant;
    eProducto* auxiliar;
    int retornoAux=0;
    rewind(datosTemporal);

    while(!feof(datosTemporal))
    {
        auxiliar=(eProducto*)malloc(sizeof(eProducto));
        cant=fread(auxiliar,sizeof(eProducto),1,datosTemporal);
        if(cant==1)
        {
            printf("%d--%s--%f\n",auxiliar->codigo, auxiliar->descripcion, auxiliar->importe);
            al_add(listaDeArchivos,auxiliar);
            retornoAux=1;
        }
        else
        {
            if(feof(datosTemporal))
            {
                printf("Iniciando...\n");
                printf("Archivo binario leido 100%.\n");
                break;
            }
            else
            {
                printf("No se pudo leer de archivo binario.\n");

                break;
            }
        }
    }
    return retornoAux;

}
