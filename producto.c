#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrayList.h"
#include "producto.h"


eProducto* producto_newProducto()
{

    eProducto* returnAux=NULL;
    eProducto* producto=(eProducto*)malloc(sizeof(eProducto));

    if(producto != NULL)
    {

        producto->codigo= getInt("Ingrese codigo:");
        descipcion(producto);
        producto->importe= getFloat("Ingrese valor: ");
        producto->cantidad=getInt("Ingrese cantidad: ");
        producto->estado=0;


        printf("Estado del producto:%d.\n",producto->estado);
        returnAux= producto;
}

return returnAux ;
}

void descipcion(eProducto* p)
{

    char auxName[256];
    int retorno,retorno2;

    do
    {
        retorno = getStringLetras("\nIngrese el nombre: ",auxName);
        retorno2=cantidadMaxima(auxName, 20);

    }
    while(retorno==0 || retorno2 ==0);


    strcpy(p->descripcion,auxName);

}

int getInt(char msj[])
{
    char numAux[25];
    int returnAux;

    getString(msj, numAux);
    while(!esNumerico(numAux))
    {
        getString("Reingrese:", numAux);
    }
    returnAux= atoi(numAux);
    return returnAux;
}

float getFloat(char msj[])
{
    char numAux[25];
    float returnAux;

    getString(msj, numAux);
    while(!esFloat(numAux))
    {
        getString("Reingrese:", numAux);
    }
    returnAux= atof(numAux);
    return returnAux;
}

int esFloat(char str[])
{
    int i=0;
    int auxReturn;
    while(str[i] != '\0')
    {
        if(str[i] ==','|| str[i]=='.')
        {
            auxReturn=1;
        }
        else if(str[i] < '0' || str[i] > '9' )
        {
            return 0;
        }
        i++;
    }
    return auxReturn;
}

int esNumerico(char str[])
{
    int i=0;
    while(str[i] != '\0')
    {
        if(str[i] < '0' || str[i] > '9' )
            return 0;
        i++;
    }
    return 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int esSoloLetras(char str[])
{
    int i=0;
    while(str[i] != '\0')
    {
        if((str[i] != ' ') && (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z'))
            return 0;
        i++;
    }
    return 1;
}



void getString(char mensaje[],char input[])
{
    printf("%s",mensaje);
    fflush(stdin);
    scanf("%49s", input);
    strlwr(input);
}

int getStringLetras(char mensaje[],char input[])
{
    char aux[256];
    getString(mensaje,aux);
    if(esSoloLetras(aux))
    {
        strcpy(input,aux);
        return 1;
    }
    return 0;
}

int cantidadMaxima(char input[], int max)
{
    int cantCaracteres;
    cantCaracteres=strlen(input);
    if(cantCaracteres>max)
    {
        return 0;
    }

    return 1;
}

int producto_ordenar(void* producto1, void* producto2)
{
    int returnAux;
    eProducto* productoUno = (eProducto*) producto1;
    eProducto* productoDos = (eProducto*) producto2;
    if(productoUno->codigo > productoDos->codigo)
    {
        returnAux =1;
    }
    else if( productoUno->codigo < productoDos->codigo)
    {
        returnAux =-1;
    }
    else
    {
        returnAux = 0;
    }
    return returnAux;
}
