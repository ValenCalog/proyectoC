#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
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
	int idCuenta, idUsuario;
	long nroDeTarjeta;
	float saldo;
}cuenta;

struct Recarga{
	long int DNI, NroCtrl;
	float monto;
	char BocaPago[30];
	struct Fecha fecha;
	struct Hora hora;
}rec;

struct Unidad{
	int idUnidad, NroUnidad, DNIC, turno, asientos, adaptado;
	char marca[30], modelo[30];
	float km;
	struct Fecha FechaAlta;
}unidad;

struct Chofer{
	int id;
	long int DNI, telefono;
	char NomApe[40], direccion[40], email[40];
	struct Fecha fechaNac;
}chofer;

struct Movimiento{
	long int DNI, NroTarjetaOTelefono;
	char origen[25], destino[25];
	float SaldoUso;
	int nroUnidad;
	struct Fecha fecha;
	struct Hora hora;
}mov;

//archivos miedo
FILE *USUARIOS, *CUENTAS, *RECARGAS, *MOVIMIENTOS, *CHOFERES, *UNIDADES;

/* Nombres de los archivos(anotar si faltan mas):
   Usuarios.dat
   choferes.dat
   movimientos.dat
   unidades.dat
   cuentas.dat
   recargas.dat
*/

//prototipos
int tiempoActual(int tipo);
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
int seEncuentraDniUsuario(long dni);
void usoDeBilleteraVirtual();
void addunit();
int generarIdCuenta();
long generarNroDeTarjeta();


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
				usoDeBilleteraVirtual();
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
		do
		{
			addunit();
			printf("desea añadir otra unidad? ingrese 1 para confirmar\n");
			scanf("%d", &confirmar);
		} while (confirmar==1);
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
		
		//generar una id
		
		fread(&us,sizeof(us),1,USUARIOS);
		
		//existe un registro
		if(!feof(USUARIOS)){
			fseek(USUARIOS,(long int)sizeof(us) * (-1), SEEK_END);
			fread(&us,sizeof(us),1,USUARIOS);
			us.id++;
			rewind(USUARIOS);
		}
		//no existe un registro aun
		else{
			us.id = 1;
			rewind(USUARIOS);
		}
		
		//pedir y verificar DNI
		printf("ingrese el DNI del usuario\n");
		scanf("%ld",&us.DNI);
		
		compDNI = us.DNI;
		fread(&us,sizeof(us),1,USUARIOS);
		while(!feof(USUARIOS)){
			while(compDNI == us.DNI){
				printf("los usuarios no pueden tener el mismo DNI\n ingreselo nuevamente: ");
				scanf("%ld",&us.DNI);
			}
			fread(&us,sizeof(us),1,USUARIOS);
		}
		rewind(USUARIOS);
		//ingresar nombre y apellido
		printf("ingrese el nombre y apellido del usuario\n");
		fflush(stdin);
		fgets(us.NomApe, sizeof(us.NomApe), stdin);

		
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
		fflush(stdin);
		fgets(us.direccion, sizeof(us.direccion), stdin);

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

			//genero la cuenta:
			if((CUENTAS = fopen("cuentas.dat", "a+b")) != NULL){

				if(generarIdCuenta() != -1){
					if (generarNroDeTarjeta != -1){
						cuenta.idCuenta = generarIdCuenta()+1;
						cuenta.idUsuario = us.id;	
						cuenta.nroDeTarjeta = generarNroDeTarjeta()+1;
						cuenta.saldo = 0;
						fwrite(&cuenta, sizeof(cuenta), 1, CUENTAS);
						fwrite(&us,sizeof(us),1,USUARIOS); //recien se registra el usuario cuando la cuenta tambien se registra correctamnete
					}else{
						printf("\nHubo un error al generar el id de la cuenta.");
					}
					
					
					
				}else{
					printf("\nHubo un error al generar el id de la cuenta. ");
				}
				fclose(CUENTAS);
			}else{
				printf("Hubo un error al abrir el archivo cuentas");
			}
		fclose(USUARIOS);
	}
	else
		printf("error al abrir el archivo de usuarios\n");

}

int generarIdCuenta(){
	if((CUENTAS = fopen("cuentas.dat","rb")) != NULL){
		fseek(CUENTAS, 0, SEEK_END);
		
		if(ftell(CUENTAS) > 0){
			fseek(CUENTAS,sizeof(cuenta)*-1,SEEK_END);
			fread(&cuenta,sizeof(cuenta),1,CUENTAS);
			fclose(CUENTAS);
			return(cuenta.idCuenta);
		}else{
			return 0;
		}
		
	}else{
		return -1;
	}
}

long generarNroDeTarjeta(){
	if((CUENTAS = fopen("cuentas.dat","rb")) != NULL){
		fseek(CUENTAS, 0, SEEK_END);
		
		if(ftell(CUENTAS) > 0){
			fseek(CUENTAS,sizeof(cuenta)*-1,SEEK_END);
			fread(&cuenta,sizeof(cuenta),1,CUENTAS);
			fclose(CUENTAS);
			return(cuenta.nroDeTarjeta);
		}else{
			return 100000;
		}
		
	}else{
		return -1;
	}
}

void ModificarUsuario(){
	int buscarid;
	
	if((USUARIOS = fopen("Usuarios.dat","a+b")) != NULL){
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
	fclose(USUARIOS);
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
				cant++;
				switch(us.tipo){
					case 1: contEst++;break;
					case 2: contDisc++;break;
					default: contMay++;break;
				}
			}
			fread(&us,sizeof(us),1,USUARIOS);
		}
		if(cant != 0){
			printf("La cantidad de usuarios con beneficios son: %d\n",cant);
			printf("Cantidad de usuarios con beneficio estudiantil: %d\n Cantidad de usuarios con beneficio por discapacidad: %d\n Cantidad de usuarios con beneficio por ser mayor de edad: %d\n",contEst,contDisc,contMay);
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
	if((CHOFERES = fopen("choferes.dat","rb")) != NULL){
		fseek(CHOFERES, 0, SEEK_END);
		
		if(ftell(CHOFERES) > 0){
			fseek(CHOFERES,(long int)sizeof(chofer)*-1,SEEK_END);
			fread(&chofer,sizeof(chofer),1,CHOFERES);
			fclose(CHOFERES);
			return(chofer.id);
		}else{
			return 0;
		}
		
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
			
			if(buscarId == chofer.id){
				fseek(CHOFERES,(long int)sizeof(chofer) * (-1),SEEK_CUR);
				band++;
				
				printf("-----------\n|ingrese los nuevos datos|\n-----------\n Nombre y apellido: ");
				gets(chofer.NomApe);
				printf("\n|Fecha de nacimiento|\n");
				printf("Dia: ");
				scanf("%d",&chofer.fechaNac.mes);
				printf("\nmes: ");
				scanf("%d",&chofer.fechaNac.mes);
				printf("\nanio: ");
				scanf("%d",&chofer.fechaNac.anio);
				printf("\nIngrese la direccion nueva: ");
				gets(chofer.direccion);
				printf("\ningrese el nuevo numero telefonico: ");
				scanf("%ld",&chofer.telefono);
				printf("\nIngrese el nuevo correo electronico: ");
				gets(chofer.email);
				printf("\nIngrese el nuevo DNI: ");
				scanf("%ld",&chofer.DNI);

				fwrite(&chofer,sizeof(chofer),1,CHOFERES);
			}
			fread(&chofer,sizeof(chofer),1,CHOFERES);
		}
		if(band == 0)
			printf("\nNo se pudo encontrar el ID del chofer\n");
	}
	else
		printf("error al abrir el archivo choferes\n");
	fclose(CHOFERES);
}



long generarNroDeControl(){
	if((RECARGAS = fopen("recargas.dat", "rb")) != NULL){
		fseek(RECARGAS, 0, SEEK_END);
		
		if(ftell(RECARGAS) > 0){
			fseek(RECARGAS, (long int)sizeof(rec) *-1,SEEK_END);
			fread(&rec, sizeof(rec), 1, RECARGAS);
			return(rec.NroCtrl);
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
		int opc, IdUsuario, band = 0;
		printf("Ingrese un numero de dni");
		scanf("%ld", &dniBuscar);
		IdUsuario = seEncuentraDniUsuario(dniBuscar);
		do{
			band = 0;
			if((IdUsuario != -1)){
				rec.DNI = dniBuscar;
				aux= generarNroDeControl();
				if(aux !=-1){
					rec.NroCtrl = aux+1;
					if((RECARGAS = fopen("recargas.dat", "a+b"))!= NULL){
						sprintf(nombre, "%ld%ld", rec.DNI, rec.NroCtrl);
						strcat(nombre, ".txt");
						if((archivo = fopen(nombre, "wb"))!= NULL){
								if((CUENTAS = fopen("cuentas.dat", "r+b")) != NULL){
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

									rec.hora.hora = tiempoActual(1);
									rec.hora.min = tiempoActual(2);
									rec.hora.seg = tiempoActual(3);
									rec.fecha.anio = tiempoActual(4);
									rec.fecha.mes = tiempoActual(5);
									rec.fecha.dia = tiempoActual(6);
									fprintf(archivo, "DNI: %ld , Nro. Control: %ld, Monto: %f, Boca de pago: %s, Fecha: %d/%d/%d, Hora: %d:%d:%d", rec.DNI, rec.NroCtrl, rec.monto, rec.BocaPago, rec.fecha.dia, rec.fecha.mes, rec.fecha.anio, rec.hora.hora, rec.hora.min, rec.hora.seg);
									fclose(archivo);
									fwrite(&rec, sizeof(rec), 1, RECARGAS);
				
									int encontroCuenta = 0;
									fread(&cuenta, sizeof(cuenta), 1, CUENTAS);
									while((!feof(CUENTAS)) && (!encontroCuenta)){

										if(cuenta.idUsuario == IdUsuario){
											encontroCuenta = 1;
										}else{
											fread(&cuenta, sizeof(cuenta), 1, CUENTAS);
										}
									}
									
									if(encontroCuenta){
										cuenta.saldo = cuenta.saldo + rec.monto;
										fseek(CUENTAS,(long int)sizeof(cuenta) *-1, SEEK_CUR);
										fwrite(&cuenta, sizeof(cuenta), 1, CUENTAS);
									}else{
										printf("\nNo se encontro el Id de usuario en el archivo cuentas.");
									}

									fclose(CUENTAS);

								}else{
									printf("No se puedo abrir el archivo cuentas para actualizar el saldo.");
								}
						}else{
							printf("\nHubo un error al generar el ticket de la recarga.");
						}
								fclose(RECARGAS);
					}else{
						printf("\nNo se pudo guardar el nroDeControl en el archivo auxiliar de recargas");
					}
					
				}else{
					printf("Hubo un error al intentar general el numero de control");
				}

		}else{
			if(IdUsuario == 0){
				printf("No se encontro el dni del usuario, por favor ingrese uno valido. ");
				scanf("%ld", dniBuscar);
				band = 1;
			}else{
				printf("\nNo se pudo abrir el archivo usuarios.");
			}
		}


		}while(band == 1);
		

}

int seEncuentraDniUsuario(long dni){
	int encontro = 0;
	if((USUARIOS = fopen("Usuarios.dat", "rb")) != NULL){
		fread(&us, sizeof(us), 1, USUARIOS);

		while((!feof(USUARIOS)) && (!encontro)){
			if(us.DNI == dni){
				encontro = us.id;
			}else{
				fread(&us, sizeof(us), 1, USUARIOS);
			}
		}
		return encontro;
	}else{
		return -1;
	}
}


int tiempoActual(int tipo){
	time_t segundosUnix;
    struct tm * tiempoLocal;
    segundosUnix = time(NULL);
    tiempoLocal = localtime(&segundosUnix);
	if(tipo == 1){
		return tiempoLocal->tm_hour; // horas
	}else{
		if(tipo == 2){
			return tiempoLocal->tm_min; //minutos
		}else{
			if(tipo == 3){
				return tiempoLocal->tm_sec; //Segundos
			}else{
				if(tipo == 4){
					return tiempoLocal->tm_year+1900; //anio
				}else{
					if (tipo == 5){
						return tiempoLocal->tm_mon+1; //mes
					}else{
						if(tipo == 6){
							return tiempoLocal->tm_mday; // dia
						}
					}
					
				}
			}
		}
	}
}

void usoDeBilleteraVirtual(){
	int band = 0;
	if((CUENTAS = fopen("cuentas.dat", "r+b")) != NULL){

		if((MOVIMIENTOS = fopen("movimientos.dat", "a+b")) != NULL){

			printf("\nIngrese su numero de DNI: ");
			scanf("%ld", &mov.DNI);
				int IdUsuario;
				do{
					band = 0;
					IdUsuario = seEncuentraDniUsuario(mov.DNI);
					if( (IdUsuario != -1) && (IdUsuario !=0)){
							printf("\nIngrese su numero de telefono: ");
							scanf("%ld", mov.NroTarjetaOTelefono);
							printf("\nNumero de unidad: ");
							scanf("%d", mov.nroUnidad); // se tiene que verificar si existe numero de unidad
							printf("\nOrigen: ");
							fflush(stdin);
							fgets(mov.origen, sizeof(mov.origen), stdin);
							printf("\nDestino: ");
							fflush(stdin);
							fgets(mov.destino, sizeof(mov.destino), stdin);
							printf("\nCantidad de saldo usado: ");
							scanf("%f", mov.SaldoUso);
							mov.hora.hora = tiempoActual(1);
							mov.hora.min = tiempoActual(2);
							mov.hora.seg = tiempoActual(3);
							mov.fecha.anio = tiempoActual(4);
							mov.fecha.mes = tiempoActual(5);
							mov.fecha.dia = tiempoActual(6);
							int encontroCuenta = 0;
							fread(&cuenta, sizeof(cuenta), 1, CUENTAS);

							while((!feof(CUENTAS)) && (!encontroCuenta)){

								if(cuenta.idUsuario == IdUsuario){
									encontroCuenta = 1;
								}else{
									fread(&cuenta, sizeof(cuenta), 1, CUENTAS);
								}
							}

							if(encontroCuenta){

								cuenta.saldo = cuenta.saldo - mov.SaldoUso;
								fseek(CUENTAS, (long int)sizeof(cuenta)*-1, SEEK_CUR);
								fwrite(&cuenta, sizeof(cuenta), 1, CUENTAS);
								fwrite(&mov, sizeof(mov), 1, MOVIMIENTOS);
							}else{
								printf("\nSe produjo un error.");
							}
			   		}else if(IdUsuario == -1){
						printf("\nHubo un error al abrir el archivo usuarios");
			    	}else{
						printf("\nEl dni no se encuentra registrado en el archivo de Usuarios. Ingrese uno valido");
						scanf("%ld", &mov.DNI);
						band = 1;
					}
				}while(band == 1);
			fclose(MOVIMIENTOS);
		}else{
			printf("\nNo se pudo abrir el archivo movimientos");
		}
		fclose(CUENTAS);
	}else{
		printf("\nNo se pudo abrir el archivo cuentas");
	}
}


void addunit(){
	int checkunitdoesnotexist = 0, foundunit;
	
	if ((UNIDADES = fopen("UNIDADES.dat", "a+b")) != NULL)
	{
		fread(&unidad, sizeof(unidad),1, UNIDADES);
		
		if (feof(UNIDADES))
		{
			unidad.idUnidad=1;
			fwrite (&unidad, sizeof(unidad),1,UNIDADES);
			rewind(UNIDADES);
		}
		else {
			fseek(UNIDADES, (long int)sizeof(unidad) * (-1), SEEK_END);
			fread(&unidad, sizeof(unidad),1, UNIDADES);
			unidad.idUnidad++;
			fwrite(&unidad, sizeof(unidad),1, UNIDADES);
			rewind(UNIDADES);
		}
		do {
    	printf("ingrese el numero de la unidad\n");
    	scanf("%d", &unidad.NroUnidad);
   		rewind(UNIDADES);
		checkunitdoesnotexist = unidad.NroUnidad;
		foundunit = 0; 
    	while (!feof(UNIDADES) && !foundunit)
    	{
        fread(&unidad,sizeof(unidad),1,UNIDADES);
        if (unidad.NroUnidad == checkunitdoesnotexist)
        {
            foundunit = 1;
            printf("La unidad ya existe, por favor ingrese otro numero de unidad\n");
        }
    	}
		} while (foundunit);
	
		rewind(UNIDADES);

		printf("ingrese dni del chofer\n");
		scanf("%d", &unidad.DNIC);
		printf("Ingrese 0 para asignar turno mañana o 1 para asignar turno tarde\n");	
		scanf("%d", &unidad.turno);
		while(unidad.turno != 0 && unidad.turno !=1)
		{
			printf("El identificador de turno proporcionado no es valido, por favor ingrese 0 para am y 1 para pm\n");
			scanf("%d", &unidad.turno);
		}
		printf("Ingrese el nombre de la compañia manufacturera de la unidad\n");
		fflush(stdin);
		fgets(unidad.marca,sizeof(unidad.marca),stdin);
		printf("ingrese el modelo de la unidad\n");
		fflush(stdin);
		fgets(unidad.modelo, sizeof(unidad.modelo),stdin);
		printf("Ingrese el kilometraje de la unidad\n");
		scanf("%f", &unidad.km);
		printf("Ingrese la fecha de alta de la unidad\n Año");
			scanf("%d", &unidad.FechaAlta.anio);
			printf("mes\n");
			scanf("%d", &unidad.FechaAlta.mes);
			printf("día\n");
			scanf("%d", &unidad.FechaAlta.dia);
		printf("Esta adaptada la unidad para discapacitados? presione 1 para confirmar y 0 para negar\n");
		scanf("%d", &unidad.adaptado);
		while(unidad.adaptado != 0 && unidad.adaptado !=1)
		{
			printf("El identificador de discapacitados proporcionado no es valido, por favor ingrese 0 para am y 1 para pm\n");
			scanf("%d", &unidad.adaptado);
		}
		fwrite(&unidad, sizeof(unidad),1, UNIDADES);	
		}
	else 
		printf("error al abrir el archivo unidades\n");
	fclose(UNIDADES);
}
