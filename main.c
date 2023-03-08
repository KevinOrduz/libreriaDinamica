#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX_PRODUCTOS 100
#include "fecha.h"

struct producto{
	char nombre[20];
	float precio;
	int cantidad;
	struct producto *siguiente;
};
struct producto *lista_productos = NULL;

struct factura{
	char fecha[11];
	char nomPersona[20];
	struct producto lproductos[MAX_PRODUCTOS];
	float total;
	struct factura *siguiente;
};

struct factura *lista_facturas = NULL;

void continuar(){
    printf("\n\nPresiona una tecla para continuar");
    getch();
}

void registrar_venta(){
    int i = 1;
    if(lista_productos != NULL){
	system("cls");
	i = 0;
	char fechaH[11];
	char nombre[22];
	int cantidad;
	char opc;
	int cont = 0;
	int existe = 0;
	struct factura *nueva_factura = malloc(sizeof(struct factura));
	fecha(fechaH);
	strcpy(nueva_factura->fecha,fechaH);
	printf("Ingresa tu nombre: ");
	scanf("%s",nueva_factura->nomPersona);
	nueva_factura->total = 0;
	do{
            do{
        if(existe == 3){
            printf("\nel nombre del producto no existe...\n");
            continuar();
            system("cls");
        }
		int operacion = 0;
		lista_producto();
		printf("\nescoge el nombre del producto que desees comprar: ");
		scanf("%s",&nombre);
		fflush(stdin);
		struct producto *actual = lista_productos;
		while(actual != NULL){
			if(strcmp(actual->nombre,nombre)==0){
				printf("%s - $%.f - %d unidades\n", actual->nombre, actual->precio, actual->cantidad);
				printf("Ingresa la cantidad: ");
				scanf("%d",&cantidad);
				while(cantidad > actual->cantidad){
					printf("no hay suficientes unidades, solo hay %d unidades de %s.\n\n",actual->cantidad,actual->nombre);
					printf("Ingresa la cantidad que quieres comprar: ");
					scanf("%d",cantidad);
				}
				actual->cantidad = actual->cantidad - cantidad;

				strcpy(nueva_factura->lproductos[cont].nombre,actual->nombre);
				nueva_factura->lproductos[cont].precio = actual->precio;
				nueva_factura->lproductos[cont].cantidad = cantidad;
				operacion = actual->precio * cantidad;
				nueva_factura->total = nueva_factura->total + operacion;
			}
			actual = actual->siguiente;
			existe = 1;
		}
		existe = 3;
		}while(nueva_factura->total == 0);
		fflush(stdin);
		printf("quieres comprar otro producto? [s/n]: ");
		cont++;
		scanf("%c",&opc);
	}while(opc == 'S' || opc == 's');
	nueva_factura->siguiente = lista_facturas;
	lista_facturas = nueva_factura;
    }
    if(i==1){
        system("cls");
        printf("No hay Productos a la venta...");
    }
    continuar();
	system("cls");
	return;
}

void lista_ventas(){
    int i = 1;
    if(lista_facturas != NULL){
    i = 0;
    system("cls");
	int cont = 0;
	struct factura *actual = lista_facturas;
	while(actual != NULL){
		int x = 0;
		cont++;
		printf("===========#%d===========\n",cont);
		printf("fecha: %s\n",actual->fecha);
		printf("nombre: %s\n",actual->nomPersona);
		do{
			printf("%s - $%.f - %d unidades\n",actual->lproductos[x].nombre,actual->lproductos[x].precio,actual->lproductos[x].cantidad);
		x++;
		}while(strlen(actual->lproductos[x].nombre)!=0);
		printf("\nTotal a pagar: %.f\n========================\n\n",actual->total);
		actual = actual->siguiente;
	}
	getch();
    }
    if(i == 1){
        system("cls");
        printf("No hay ninguna venta...");
        continuar();
    }
	system("cls");
	return;
}

void crear_producto(){
	system("cls");
	char nombre[20];
	float precio;
	struct producto *nuevo_producto = malloc(sizeof(struct producto));
	printf("Ingrese el nombre del producto: ");
	scanf("%s",nombre);
	struct producto *actual = lista_productos;
	while(actual != NULL){
		if (strcmp(actual->nombre,nombre)==0){
			printf("el producto ya existe");
			getch();
			system("cls");
			return;
		}
		actual = actual->siguiente;
	}
	strcpy(nuevo_producto->nombre,nombre);
	printf("ingresa el precio del producto: ");
	scanf("%f",&precio);
	if(precio < 0){
        printf("Ingresastes un valor negativo, vuelve a intentarlo");
        continuar();
        system("cls");
        return;
	}
	nuevo_producto->precio = precio;
	printf("ingresa la cantidad del producto: ");
	scanf("%d",&nuevo_producto->cantidad);
	nuevo_producto->siguiente = lista_productos;
	lista_productos = nuevo_producto;
	system("cls");
	return;
}

void eliminar_producto(){
    struct producto *actual = lista_productos;
    struct producto *anterior = NULL;

    while (actual != NULL && actual->cantidad != 0 && actual->cantidad > 0) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != NULL) {
        if (anterior == NULL) {
            lista_productos = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }
            free(actual);
        }

}

void lista_producto(){
    int i = 1;
    if(lista_productos != NULL){
    i = 0;
    eliminar_producto();
	struct producto *actual = lista_productos;
	printf("\n===========PRODUCTOS===========\n");
	while(actual != NULL){
		printf("%s - $%.f - %d unidades\n", actual->nombre, actual->precio, actual->cantidad);
		actual = actual->siguiente;
	}
    }
    if (i == 1){
        system("cls");
        printf("No hay productos en el inventario...");
    }
	return;
}

void inventario(){
    system("cls");
	int opcion;
	do{
		printf("1- Crear Producto\n");
		printf("2- Lista de Productos\n");
		printf("3- Regresar\n");
		printf("Ingresa su opcion: ");
		scanf("%d",&opcion);
		switch(opcion){
			case 1:crear_producto();
		break;
			case 2:lista_producto();
			continuar();
			system("cls");
		break;
            case 3:
        system("cls");
        return;
            default:
        system("cls");
		}
	}while(1);
}

int main (){
	int opcion;
	do{

		printf("1- Registrar Venta\n");
		printf("2- Inventario\n");
		printf("3- Lista de ventas\n");
		printf("4- salir\n");
		printf("Ingresa su opcion: ");
		scanf("%d",&opcion);
		switch(opcion){
			case 1:registrar_venta();
		break;
			case 2:inventario();
		break;
			case 3:lista_ventas();
		break;
		}
	}while(opcion != 4);
return 0;
}
