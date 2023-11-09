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
	char BocaPago[30];
	struct Hora hora;
}rec;

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
	struct Fecha fechaNac;
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
   cuentas.dat
*/

//prototipos
void GenerarUsuario();
void ModificarUsuario();
void ListarUsuarios();
void CantBeneficios();
void agregarChofer();
int generarIdChofer();
void ModificarChofer();
long generarNroDeControl();
int ObtenerAnioActual();
void cargaDeSaldo();
void menuModificaciones();
void menuConsultas();
void seEncuentraDniUsuario(long dni);
int main() {
	int opc,confirmar;
	do{
		printf("---------------------SUBE---------------\n");
	printf("\nQue desea hacer?");
	printf("\n1. Modificar o registrar en los archivos (USUARIOS-UNIDADES-CHOFERES).");
	printf("\n2. Realizar consultas o ver listados.");
	printf("\n3. Cargar saldo.");
	printf("\n4. Pagar boleto con tarjeta.");
	printf("\n5. Pagar boleto con numero de telefono.");
	printf("\n0. Salir del programa");
	printf("\nIngrese su opcion: ");
	scanf("%d", &opc);
	system("cls");
	switch(opc){
		case 1:
				menuModificaciones();
				break;
		case 2:
				menuConsultas();
				break;
		case 3:
				cargaDeSaldo();
				break;
		case 4:
			//4. Pagar boleto con tarjeta
				break;
		case 5:
			//5. Pagar boleto con numero de telefono
				break;
		case 0:
			//0. Salir del programa
				break;
		default:
				break;
	}
	}while(opc!=0);
	

	
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

void GenerarUsuario(){
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

void ModificarUsuario(){
	int buscarid;
	
	if((USUARIO = fopen("Usuarios.dat","a+b")) != NULL){
		printf("ingrese el id del usuario a buscar: \n");
		scanf("%d",&buscarid);
		fread(&us,sizeof(us),1,USUARIOS);
		while(!feof(USUARIOS)){
			if(buscarid == us.id){
				//ingresar los datos nuevamente (menos el id)
				printf("ingrese el Nombre y Apellido nuenvamente: \n");
				gets(us.NomApe);
				fflush(stdin);
				printf("ingresar el DNI nuevamente\n");
				scanf("%d",&us.DNI);
				printf("ingrese la nueva Fecha de nacimiento\n Dia:\n");
				scanf("%d",&us.FechaNac.dia);
				printf("mes:\n");
				scanf("%d",&us.FechaNac.mes);
				printf("anio:\n");
				scanf("%d",&us.FechaNac.anio);
				printf("ingrese la nueva direccion:\n");
				gets(us.direccion);
				fflush(stdin);
				printf("ingrese el telefono nuevamente:\n");
				scanf("%ld",&us.telefono);
				printf("\ningrese el nuevo tipo de beneficios:\n 0- sin beneficios\n 1- estudiante\n 2- persona con discapacidad\n 3- persona mayor de edad\n respuesta: ");
				scanf("%d",&us.tipo);
				while(us.tipo != 0 || us.tipo != 1 || us.tipo != 2 || us.tipo != 3){
					printf("\ningrese un dato valido: ");
					scanf("%d",&us.tipo);
				}
			}
		}
	}
	else
		printf("error al abrir el archivo Usuarios\n");
	fclose(USUARIOS)
}

void ListarUsuarios(){
	
	if((USUARIOS = fopen("Usuarios.dat","rb")) != NULL){
		
		fread(&us,sizeof(us),1,USUARIOS);
		while(!feof(USUARIOS)){
			printf("----------------\n +Id: %d\n +Nombre y apellido: %s\n +fecha de nacimiento: %d/%d/%d\n +DNI: %ld\n +Telefono: %ld\n +Direccion: %s\n----------------\n",us.id,us.NomApe,us.FechaNac.dia,us.FechaNac.mes,us.FechaNac.anio,us.DNI,us.telefono,us.direccion);
			fread(&us,sizeof(us),1,USUARIOS);
		}
	}
	else
		printf("error al abrir el archivo usuarios\n");
	fclose(USUARIOS);
}

void CantBeneficios(){
	int cant = 0, contEst = 0, contDisc = 0, contMay = 0;
	if((USUARIOS = fopen("Usuarios.dat","rb")) != NULL){
		
		fread(&us,sizeof(us),1,USUARIOS);
		while(!feof(USUARIOS)){
			if(us.tipo != 0){
				cont++;
				switch(us.tipo){
					case 1: contEst++;break;
					case 2: contDisc++;break;
					default: contMay++;break;
				}
			}
			fread(&us,sizeof(us),1,USUARIOS);
		}
		if(cont != 0){
			printf("La cantidad de usuarios con beneficios son: %d\n",cant);
			printf("Cantidad de usuarios con beneficio estudiantil: %d\n Cantidad de usuarios con beneficio por discapacidad: %d\n Cantidad de usuarios con beneficio por ser mayor de edad: %d\n",contEst,contDisc,ContMay);
		}
		else
			printf("No hay usuarios con beneficios\n");
	}
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
			printf("\nIngrese fecha de nacimiento ");
			printf("\nDia: ");
			scanf("%d", &chofer.fechaNac.dia);
			printf("\nMes: ");
			scanf("%d", &chofer.fechaNac.mes);
			printf("\nAnio: ");
			scanf("%d",&chofer.fechaNac.anio);
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

void ModificarChofer(){
	int buscarId, band = 0;
	
	if((CHOFERES = fopen("choferes.dat","a+b")) != NULL){
		printf("ingrese el ID del chofer para modificar sus datos\n");
		scanf("%d",&buscarId);
		
		fread(&chofer,sizeof(chofer),1,CHOFERES);
		while(!feof(CHOFERES)){
			
			if(buscarId == choferes.id){
				fseek(CHOFERES,sizeof(chofer) * (-1),SEEK_CUR);
				band++;
				
				printf("-----------\n|ingrese los nuevos datos|\n-----------\n Nombre y apellido: ");
				gets(chofer.NomApe);
				printf("\n|Fecha de nacimiento|\n");
				printf("Dia: ");
				scnaf("%d",&chofer.dia);
				printf("\nmes: ");
				scnaf("%d",&chofer.mes);
				printf("\nanio: ");
				scnaf("%d",&chofer.anio);
				printf("\nIngrese la direccion nueva: ");
				gets(chofer.direccion);
				printf("\ningrese el nuevo numero telefonico: ");
				scnaf("%ld",&chofer.telefono);
				printf("\nIngrese el nuevo correo electronico: ");
				gets(chofer.email);
				printf("\nIngrese el nuevo DNI: ");
				scnaf("%ld",&chofer.DNI);

				fwrite(&chofer,sizeof(chofer),1,CHOFERES);
			}
			fread(&chofer,sizeof(chofer),1,CHOFERES);
		}
		if(band == 0)
			prinf("\nNo se pudo encontrar el ID del chofer\n");
	}
	else
		printf("error al abrir el archivo choferes\n");
	fclose(CHOFERES);
}

void menuModificaciones(){
	int opc, confirmar;

	do{
		
	printf("\n1. Agregar usuarios");
	printf("\n2. Modificar usuarios");
	printf("\n3. Agregar choferes");
	printf("\n4. Modificar choferes");
	printf("\n5. Agregar unidades");
	printf("\n6. Modificar unidades");
	printf("\n7. Volver al menu principal");
	printf("\nIngrese su opcion: ");
	scanf("%d", &opc);
	confirmar = 0;
	system("cls");
	switch(opc){
	case 1:
		do{
			GenerarUsuario();
			printf("\nDesea agregar otro Usuario? Ingrese 1 si la respuesta es si, cualquier otro numero si es no: ");
			scanf("%d", &confirmar);
		}while(confirmar==1); 
		break;
	case 2:
		ModificarUsuario();
		break;
	case 3:
		do{
			agregarChofer();
			printf("\nDesea agregar otro chofer? Ingrese 1 si la respuesta es si, cualquier otro numero si es no: ");
			scanf("%d", &confirmar);
		}while(confirmar==1); 
		break;
	case 4:
		ModificarChofer();
		break;
	case 5:
		//Agregar unidad
		break;
	case 6:
		//modificar unidad
		break;
	case 7:
		//salir
		break;
	default:
		break;
	}
	
	}while(opc!=7);

}

void menuConsultas(){

	int opc, confirmar;

	do{
		printf("\n1.Consultar saldo");
		printf("\n2.Listar usuarios");
		printf("\n3.Mostrar movimientos efectuados entre dos fechas");
		printf("\n4.Listar las recargas efectuadas por un usuario indicando su DNI");
		printf("\n5.Cantidad de usuarios con beneficios.");
		printf("\n6.Buscar movimientos de un usario particular ingresando su nombre.");
		printf("\n7.Buscar chofer o choferes con mas pasajeros en un mes en especifico");
		printf("\n8.Ver porcentaje de pasajeros que viajan en el primer turno del año");
		printf("\n9.Volver atras");
				printf("\nIngrese su opcion:");
				scanf("%d", &opc);
				system("cls");
				switch (opc){
				case 1:
					//1.Consultar saldo"
					break;
				case 2:
					ListarUsuarios();
					break;
				case 3:
					//3.Mostrar movimientos efectuados entre dos fechas");
					break;
				case 4:
					//4.Listar las recargas efectuadas por un usuario indicando su DNI");
					break;
				case 5:
					CantBeneficios();
					break;
				case 6:
					//6.Buscar movimientos de un usario particular ingresando su nombre.")
					break;
					
				case 7:
					//7.Buscar chofer o choferes con mas pasajeros en un mes en especifico");
					break;	
				case 8:
					//8.Ver porcentaje de pasajeros que viajan en el primer turno del año");
					break;
				case 9:
					break;
				default:
					printf("No se ingreso una opcion valida");
					break;
				}
	}while(opc!=9);

				
}

long generarNroDeControl(){
	long numControl, tamanio;
	FILE *nrosDeControl;
	if((nrosDeControl = fopen("nrosControlAux.dat", "a+b")) != NULL){
		fseek(nrosDeControl, 0, SEEK_END);
		
		if(ftell(nrosDeControl) > 0){
			fseek(nrosDeControl, sizeof(numControl) *-1,SEEK_END);
			fread(&numControl, sizeof(numControl), 1, nrosDeControl);
			return(numControl);
		}else{
			return 10000;
		}
		
	}else{
		return -1;
	}

}

void cargaDeSaldo(){
		FILE *archivo;
		long dniBuscar, aux;
		char nombre[30];
		int opc;
		printf("Ingrese un numero de dni");
		scanf("%ld", &dniBuscar);
		if(seEncuentraDniUsuario(dniBuscar)){
			rec.DNI = dniBuscar;
			aux= buscarNroDeControl();
			if(aux !=-1){
				rec.NroCtrl = aux+1;
				FILE *auxNroCtrl;
				if((auxNroCtrl = fopen("nrosControlAux.dat", "a+b"))!= NULL){
					sprintf(nombre, "%ld%ld", rec.DNI, rec.NroCtrl);
				    strcat(nombre, ".txt");
				   	if((archivo = fopen(nombre, "wb"))!= NULL){
						printf("\nIngrese el monto a cargar: ");
						scanf("%f", rec.monto);
						do{
							printf("\nBoca de pago: ");
						printf("\n1. Rapipago");
						printf("\n2. Terminal de omnibus");
						printf("\n3. Mini Super Ayacucho");
						printf("\n4. Agencia IPLyC");
						printf("\n5. Quiosco");
						printf("\nIngrese su opcion: ");
						scanf("%d", &opc);
						switch (opc){
						case 1:
							strcpy(rec.BocaPago, "Rapipago");
							break;
						case 2:
							strcpy(rec.BocaPago, "Terminal de omnibus");
							break;
						case 3:
							strcpy(rec.BocaPago, "Mini Super Ayacucho");
							break;
						case 4:
							strcpy(rec.BocaPago, "Agencia IPLyC");
							break;
						case 5:
							strcpy(rec.BocaPago, "Quiosco");
							break;
						default:
							printf("\nNo es numero valido.");
							break;
						}
						}while((opc <1) || (opc >5));
						rec.Hora.hora = ;/*enseguida sigo*/

					/*charBocaPago;
	                struct Hora hora;*/
					}else{
						printf("\nHubo un error al generar el ticket de la recarga.");
					}
				}else{
					printf("\nNo se pudo guardar el nroDeControl en el archivo auxiliar");
				}
				
			}else{
				printf("Hubo un error al intentar general el numero de control");
			}

		}else{
			printf("No se encontro el dni del usario (o no se pudo abrir el archivo para buscar.)");
		}

}

void seEncuentraDniUsuario(long dni){
	int encontro = 0;
	if((USUARIOS = fopen("Usuarios.dat", "rb")) != NULL){
		fread(&us, sizeof(us), 1, USUARIOS);

		while((!eof(USUARIOS)) && (!encontro)){
			if(us.DNI == dni){
				encontro = 1;
			}else{
				fread(&us, sizeof(us), 1, USUARIOS);
			}
		}
		return encontro;
	}else{
		return 0;
	}
}
