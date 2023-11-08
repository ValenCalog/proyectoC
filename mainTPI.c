#include <stdio.h>
#include <string.h>
#include <time.h>

//otras estructuras
struct Fecha{
	int dia, mes, anio;
};

struct Hora{
	int seg, min, hora;
};

//estructuras principales
struct Usuario{
	int id, tipo;
	long int DNI, telefono;
	char NomApe[40], direccion[40];
	struct Fecha FechaNac;
}us;

struct Cuenta{
	long int DNI, id;
	float saldo;
};

struct Recarga{
	long int DNI, NroCtrl;
	float monto;
	float BocaPago;
	struct Hora hora;
};

struct Unidad{
	int NroUnidad, DNIC, turno, asientos, adaptado;
	char marca[30], modelo[30];
	float km;
	struct Fecha FechaAlta;
};

struct Chofer{
	int id;
	long int DNI, telefono;
	char NomApe[40], direccion[40], email[40];
}chofer;

struct Movimiento{
	long int DNI, NroTarjeta;
	char origen[25], destino [25];
	float SaldoUso;
	int nroUnidad;
	struct Fecha fecha;
	struct Hora hora;
};

//archivos miedo
FILE *USUARIOS, *CUENTAS, *RECARGAS, *MOVIMIENTOS, *CHOFERES, *UNIDADES;

/* Nombres de los archivos(anotar si faltan mas):
   Usuarios.dat
   choferes.dat
   movimientos.dat
   unidades.dat
*/

//prototipos
int GenerarUsuario();
void agregarChofer();
int generarIdChofer();
int ObtenerAnioActual();


int main() {
	int opc,confirmar;
	printf("---------------------SUBE---------------\n");
	printf("\nQue desea hacer?");
	printf("\n1. Modificar o registrar en los archivos (USUARIOS-UNIDADES-CHOFERES).");
	printf("\n2. Realizar consultas o ver listados.");
	printf("\n3. Cargar saldo.");
	printf("\n4. Pagar boleto con tarjeta.");
	printf("\n5. Pagar boleto con numero de telefono.");
	printf("\n6. Salir del programa");
	printf("\nIngrese su opcion: ");
	scanf("%d", &opc);
	system("cls");
	switch(opc){
		case 1:
				printf("\n1. Choferes");
				printf("\n2. Unidades");
				printf("\n3. Usuarios");
				printf("\n4. Volver al menu principal");
				printf("\nIngrese su opcion: ");
				scanf("%d", &opc);
				system("cls");
				switch (opc){
				case 1:
					//choferes
					printf("\n1. Agregar choferes");
					printf("\n2. Modificar choferes");
					printf("\n3. Volver atras");
					printf("\nIngrese su opcion: ");
					scanf("%d", &opc);
					system("cls");
					switch (opc){
					case 1:
						
							do{
								agregarChofer();
								printf("\nDesea agregar otro chofer? Ingrese 1 si la respuesta es si, cualquier otro numero si es no: ");
								scanf("%d", &confirmar);
							}while(confirmar==1); 
						break;
					case 2:
							//modificarUsuarios
						break;
					case 3:
						break;
					default:
						printf("\nNo se ingreso una opcion valida.");
						break;
					}
					break;
				case 2:
					//UNIDADES
					printf("\n1. Agregar unidades");
					printf("\n2. Modificar unidades");
					printf("\n3. Volver atras");
					printf("\nIngrese su opcion: ");
					scanf("%d", &opc);
					system("cls");
					switch (opc){
						case 1:
						//agregar unidades
							break;
						case 2:
						//modificar unidades
							break;
						case 3:
							break; //vuelve atras
						default:
							break;
					}
					break;
				case 3:
					//USUARIOS
					printf("\n1. Agregar usuarios");
					printf("\n2. Modificar usuarios");
					printf("\n3. Volver atras");
					printf("\nIngrese su opcion: ");
					scanf("%d", &opc);
					system("cls");
					switch (opc){
						case 1:
							//agregar usuarios
							break;
						case 2:
							//modificar usuarios
							break;
						default:
							break;
						}
					break;
				case 4:
					break;
				default:
					printf("\nNo se ingreso una opcion valida.");
					break;
				}
				break;
		case 2:
				//2. Realizar consultas o ver listados
				printf("\n1.Consultar saldo");
				printf("\n2.Listar usuarios");
				printf("\n3.Mostrar movimientos efectuados entre dos fechas");
				printf("\n4.Listar las recargas efectuadas por un usuario indicando su DNI");
				printf("\n5.Cantidad de usuarios con beneficios.");
				printf("\n6.Buscar movimientos de un usario particular ingresando su nombre.");
				printf("\n7.Buscar chofer o choferes con mas pasajeros en un mes en especifico");
				printf("\n8.Ver porcentaje de pasajeros que viajan en el primer turno del año");
				break;
		case 3:
				//3.Cargar saldo
				break;
		case 4:
			//4. Pagar boleto con tarjeta
				break;
		case 5:
			//5. Pagar boleto con numero de telefono
				break;
		case 6:
			//6. Salir del programa
	}

	return 0;
}

//funciones
int ObtenerAnioActual() {
    time_t tiempo;
    struct tm *tiempoinfo;

    time(&tiempo); // Obtiene la hora actual
    tiempoinfo = localtime(&tiempo); // Convierte la hora actual a una estructura tm

    return tiempoinfo->tm_year + 1900; // Devuelve el año actual
}
int GenerarUsuario(){
	int BandId = 0, anio = ObtenerAnioActual();
	long int compDNI;
	
	if((USUARIOS = fopen("Usuarios.dat","a+b")) != NULL){
		
		//generar una id\\
		
		fread(&us,sizeof(us),1,USUARIOS);
		
		//existe un registro
		if(!feof(USUARIOS)){
			fseek(USUARIOS,sizeof(us) * (-1), SEEK_END);
			fread(&us,sizeof(us),1,USUARIOS);
			us.id++;
			fwrite(&us,sizeof(us),1,USUARIOS);
			rewind(USUARIOS);
		}
		
		//no existe un registro aun
		else{
			us.id = 1;
			fwrite(&us,sizeof(us),1,USUARIOS);
			rewind(USUARIOS);
		}
		
		//pedir y verificar DNI
		printf("ingrese el DNI del usuario\n");
		fscanf("%ld",&us.DNI);
		
		compDNI = us.DNI;
		fread(&us,sizeof(us),1,USUARIOS);
		while(!feof(USUARIOS)){
			while(compDNI == us.DNI){
				printf("los usuarios no pueden tener el mismo DNI\n ingreselo nuevamente: ");
				fscanf("%ld",&us.DNI);
			}
			fread(&us,sizeof(us),1,USUARIOS);
		}
		rewind(USUARIOS);
		//ingresar nombre y apellido
		printf("ingrese el nombre y apellido del usuario\n");
		gets(us.NomApe);
		fflush(stdin);
		
		//pedir y controlar fecha de nacimiento
		printf("ingrese la fecha de nacimiento del usuario:\n dia: ");
		scanf("%d",&us.FechaNac.dia);
		printf("\nmes: ");
		scanf("%d",&us.FechaNac.mes);
		printf("\nanio: ");
		scanf("%d",&us.FechaNac.anio);
		
		while(us.FechaNac.dia <= 0 || us.FechaNac.dia >= 32){
			printf("\nel dia ingresado es invalido, ingreselo nuevamente: ");
			scanf("%d",&us.FechaNac.dia);
		}
		while(us.FechaNac.mes <= 0 || us.FechaNac.mes >= 13){
			printf("\nel mes ingresado es invalido, ingreselo nuevamente: ");
			scanf("%d",&us.FechaNac.mes);
		}
		while((anio - us.FechaNac.anio) >= 110){
			printf("\nel mes ingresado es invalido, ingreselo nuevamente: ");
			scanf("%d",&us.FechaNac.anio);
		}
		
		//ingresar direccion
		printf("\ningrese la direccion del ususario: ");
		gets(us.direccion);
		fflush;
		
		//ingresar telefono
		printf("\ningrese el numero de su telefono: ");
		scanf("%ld",&us.telefono);
		
			//ingresar el tipo
		printf("\ningrese el tipo de beneficios:\n 0- sin beneficios\n 1- estudiante\n 2- persona con discapacidad\n 3- persona mayor de edad\n respuesta: ");
		scanf("%d",&us.tipo);
		while(us.tipo != 0 || us.tipo != 1 || us.tipo != 2 || us.tipo != 3){
			printf("\ningrese un dato valido: ");
			scanf("%d",&us.tipo);
		}
		fwrite(&us,sizeof(us),1,USUARIOS);
	}
	else
		printf("error al abrir el archivo de usuarios\n");
	fclose(USUARIOS);
}

void agregarChofer(){
	int ultimoId;
	if((CHOFERES = fopen("choferes.dat", "a+b")) != NULL){
		

		ultimoId = generarIdChofer();
		if(ultimoId==(-1)){
			printf("Hubo un error al intentar abrir el archivo chofer");
		}else{
			chofer.id = ultimoId+1;
			printf("Ingrese nombre del chofer");
			fflush(stdin);
			fgets(chofer.NomApe, sizeof(chofer.NomApe), stdin);
			printf("\nIngrese su DNI: ");
			scanf("%ld", &chofer.DNI);
			printf("\nIngrese direccion: ");
			fflush(stdin);
			fgets(chofer.direccion, sizeof(chofer.direccion), stdin);
			printf("\nIngrese email: ");
			fflush(stdin);
			fgets(chofer.email, sizeof(chofer.email), stdin);
			printf("\nIngrese su telefono: ");
			scanf("%ld", &chofer.telefono);
			fwrite(&chofer, sizeof(chofer), 1, CHOFERES);
			fclose(CHOFERES);
		}

	}else{
		printf("No se pudo abrir el archivo choferes");
	}

}

int generarIdChofer(){
	CHOFERES  = fopen("choferes.dat","rb");
	if(CHOFERES!=NULL){
		fseek(CHOFERES,sizeof(chofer)*-1,SEEK_END);
		fread(&chofer,sizeof(chofer),1,CHOFERES);
		fclose(CHOFERES);
		return(chofer.id);
	}else{
		return -1;
    }
}
