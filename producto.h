
typedef struct
{
    int codigo;
    char descripcion[50];
    float importe;
    int cantidad;
    int estado;

}eProducto;
eProducto* producto_newProducto();
void descipcion(eProducto* p);
int getInt(char msj[]);
float getFloat(char msj[]);
int esNumerico(char str[]);
int esFloat(char str[]);
int esSoloLetras(char str[]);
void getString(char mensaje[],char input[]);
int getStringLetras(char mensaje[],char input[]);
int cantidadMaxima(char input[], int max);
int producto_ordenar(void* producto1, void* producto2);
