#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        printf("\n1)Alta\n2)Modificar\n3)Baja logica\n4)Baja fisica\n5)Lista\n6)Salir\n");
        printf("Ingrese numero de opcion: ");
        scanf("%d",&opcion);

        switch(opcion)
        {
        case 1:
            printf("Alta de producto\n");
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
                    printf("Datos cargados en memoria.\n");
                }

            }
            else
            {
                printf("No se pudo agregar el producto.");
            }
            break;
        case 2:
            if(cargados==1)
            {
                flag=0;
                printf("Modificar datos\n");
                auxCod=getInt("Ingrese el codigo del producto:");

                for(i=0; i<al_len(listaDeArchivos); i++)
                {
                    aux=(eProducto*) al_get(listaDeArchivos,i);
                    if(auxCod== aux->codigo)
                    {
                        printf("Datos encontrados: \n");
                        printf("Codigo del producto: %d\nDescripcion: %s\nCantidad: %d\tPrecio: %.2f\nEstado: %d\n",aux->codigo,aux->descripcion,aux->cantidad,aux->importe,aux->estado);

                        aux->codigo= getInt("Ingrese el nuevo codigo: ");
                        aux->importe=getFloat("Ingrese el nuevo importe: ");
                        aux->cantidad=getInt("Ingrese la nueva cantidad: ");
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
            break;
        case 3:
            printf("Baja logica\n ");
            auxCod=getInt("Ingrese el codigo del producto:");

            for(i=0; i<al_len(listaDeArchivos); i++)
            {
                aux=(eProducto*)al_get(listaDeArchivos,i);
                if(auxCod== aux->codigo)
                {
                    printf("Producto encontrado:\n ");
                    printf("Codigo: %d-Name: %s\nCantidad: %d- Importe: %.2f\nEstado: %d\n",aux->codigo,aux->descripcion,aux->cantidad,aux->importe,aux->estado);
                    index=al_indexOf(listaDeArchivos,aux);
                    aux->estado=1;
                    al_set(listaDeArchivos,index,aux);
                    flag=1;
                    printf("El estado del producto ha sido cambiado a 1");
                }
            }
            if(flag==0)
            {
                printf("No se encontro el producto.\n");
            }

            break;
        case 4:
            printf("Baja fisica:\n");
            auxCod=getInt("Ingrese el codigo del producto:");

            for(i=0; i<al_len(listaDeArchivos); i++)
            {
                aux=(eProducto*)al_get(listaDeArchivos,i);
                if(auxCod==aux->codigo)
                {
                    printf("Dato encontrado:");
                    printf("Codigo: %d-Name: %s\nCantidad: %d- Importe: %.2f\nEstado: %d\n",aux->codigo,aux->descripcion,aux->cantidad,aux->importe,aux->estado);
                    printf("Seguro de eliminar?s/n");
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
            break;
        case 5:
            printf("flag: %d",cargados);
            if(cargados==1)
            {
                printf("Lista de productos cargados\n");
                for(i=0; i<al_len(listaDeArchivos); i++)
                {
                    aux=(eProducto*)al_get(listaDeArchivos,i);
                    printf("%d) Descripcion: %s\tCodigo: %d\nImporte: %.2f\tCantidad: %d\nEstado: %d\n",i,aux->descripcion,aux->codigo,aux->importe,aux->cantidad,aux->estado);
                }
            }
            else
            {
                printf("1)flag: %d",cargados);
                printf("No hay archivos cargados.\n");
            }
            break;
        case 6:
            seguir='n';
            al_sort(listaDeArchivos,producto_ordenar,0);

            fclose(datosTemporal);

            if((datosTemporal=fopen("datosTemporal.bin","wb"))==NULL)
            {
                printf("No se pudo abrir el archivo datos temporarios");
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
                        printf("No se pudieron cargar los datos");
                    }
                    else
                    {
                        printf("Dato cargado: id: %d-Descr.: %s\n",aux->codigo,aux->descripcion);
                    }
                }

                if((fclose(datosTemporal))==-1)
                {
                    printf("No se pudo cerrar el archivo.");
                }
                else
                {
                    printf("Se cerro el archivo exitosamente.");
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
                printf("Se llego al final del archivos.\n");
                break;
            }
            else
            {
                printf("No se pudo leer de archivo.\n");

                break;
            }
        }
    }
    return retornoAux;

}
