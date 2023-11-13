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
	int id, tipo, idCuenta;
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
   UNIDADES.dat
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
void ModificarUnidad();
int generarIdCuenta();
long generarNroDeTarjeta();
void choferesConMasPasajeros();
void buscarRecargasPorDni();
int seEncuentraDniChofer(long dni);
void pagarPasajeTarjeta();
void PrimerTurno();
int compararDosFechas(struct Fecha fecha1, struct Fecha fecha2);
void movimientosEntreDosFechas();
void showaccountcredit();
void buscarMovimientosUsuario();
int nroDeTelefonoEsCorrecto(long nroDeTelefono);
void ListarChoferes();

int main() {
	int opc,confirmar;
	do{
	printf("\n---------------------SUBE---------------\n");
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
				pagarPasajeTarjeta();
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
		do{
			ModificarUsuario();
			printf("\nDesea modificar otro usuario? Ingrese 1 si la respuesta es si, cualquier otro numero si es no: ");
			scanf("%d", &confirmar);
		}while(confirmar==1); 
		break;
	case 3:
		do{
			agregarChofer();
			printf("\nDesea agregar otro chofer? Ingrese 1 si la respuesta es si, cualquier otro numero si es no: ");
			scanf("%d", &confirmar);
		}while(confirmar==1); 
		break;
	case 4:
		do{
			ModificarChofer();
			printf("\nDesea modificar otro chofer? Ingrese 1 si la respuesta es si, cualquier otro numero si es no: ");
			scanf("%d", &confirmar);
		}while(confirmar==1); 
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
		do{
			ModificarUnidad();
			printf("\nDesea modificar otra unidad? Ingrese 1 si la respuesta es si, cualquier otro numero si es no: ");
			scanf("%d", &confirmar);
		}while(confirmar==1); 
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
					showaccountcredit();
					break;
				case 2:
					ListarUsuarios();
					break;
				case 3:
					movimientosEntreDosFechas();
					break;
				case 4:
					buscarRecargasPorDni();
					break;
				case 5:
					CantBeneficios();
					break;
				case 6:
					buscarMovimientosUsuario();
					break;
					
				case 7:
					choferesConMasPasajeros();
					break;	
				case 8:
					PrimerTurno();
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
					if (generarNroDeTarjeta() != -1){
						cuenta.idCuenta = generarIdCuenta()+1;
						cuenta.idUsuario = us.id;	
						cuenta.nroDeTarjeta = generarNroDeTarjeta()+1;
						cuenta.saldo = 0;
						fwrite(&cuenta, sizeof(cuenta), 1, CUENTAS);
						us.idCuenta = cuenta.idCuenta;
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
			fseek(CUENTAS,(long int)sizeof(cuenta)*-1,SEEK_END); 
			fread(&cuenta,sizeof(cuenta),1,CUENTAS);
			fclose(CUENTAS);
			return(cuenta.idCuenta);
		}else{
			//si el archivo estuviera vacio ftell devolveria 0
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
			fseek(CUENTAS,(long int)sizeof(cuenta)*-1,SEEK_END);
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
				fgets(us.NomApe, sizeof(us.NomApe), stdin);
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
				fgets(us.direccion, sizeof(us.direccion), stdin);
				fflush(stdin);
				printf("ingrese el telefono nuevamente:\n");
				scanf("%ld",&us.telefono);
				printf("\ningrese el nuevo tipo de beneficios:\n 0- sin beneficios\n 1- estudiante\n 2- persona con discapacidad\n 3- persona mayor de edad\n 4-  Beneficio Ex-Combatiente de Malvinas\n respuesta: ");
				scanf("%d",&us.tipo);
				while(us.tipo != 0 || us.tipo != 1 || us.tipo != 2 || us.tipo != 3 || us.tipo != 4){
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
		fclose(USUARIOS);
	}
	else
		printf("error al abrir el archivo usuarios\n");
	
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
		fclose(USUARIOS);
	}else{
		printf("\nError al abrir archivo usuarios");
	}
}

int seEncuentraDniChofer(long dni){
	int encontro = 0;
	if((CHOFERES = fopen("choferes.dat", "rb")) != NULL){
		
		fread(&chofer, sizeof(chofer), 1, CHOFERES);

		while((!feof(CHOFERES)) && (!encontro)){
			if(chofer.DNI == dni){
				encontro = chofer.id;
			}else{
				fread(&us, sizeof(us), 1, USUARIOS);
			}
		}
		return encontro;
	}else{
		return -1;
	}
}

void agregarChofer(){
	int ultimoId, band, existe;
	if((CHOFERES = fopen("choferes.dat", "a+b")) != NULL){

		ultimoId = generarIdChofer();
		if(ultimoId==(-1)){
			printf("Hubo un error al intentar abrir el archivo chofer");
		}else{
			chofer.id = ultimoId+1;
			
			do{
				band = 0;
				printf("\nIngrese DNI del chofer: ");
				scanf("%ld", &chofer.DNI);
				existe = seEncuentraDniChofer(chofer.DNI);
				if(existe==0){
						printf("\nIngrese nombre del chofer: ");
						fflush(stdin);
						fgets(chofer.NomApe, sizeof(chofer.NomApe), stdin);
						printf("\nIngrese direccion: ");
						fflush(stdin);
						fgets(chofer.direccion, sizeof(chofer.direccion), stdin);
						printf("\nIngrese email: ");
						fflush(stdin);
						fgets(chofer.email, sizeof(chofer.email), stdin);
						printf("\nIngrese fecha de nacimiento ");
						printf("\nDia: ");
						scanf("%d", &chofer.fechaNac.dia);
						while((chofer.fechaNac.dia > 31) || (chofer.fechaNac.dia < 1)){
							printf("\nIngrese un dia valido: ");
							scanf("%d",&chofer.fechaNac.dia);
						}
						printf("\nMes: ");
						scanf("%d", &chofer.fechaNac.mes);
						while((chofer.fechaNac.mes > 12) || (chofer.fechaNac.mes < 1)){
							printf("\nIngrese un mes valido: ");
							scanf("%d",&chofer.fechaNac.mes);
						}
						printf("\nAnio: ");
						scanf("%d",&chofer.fechaNac.anio);
						while(chofer.fechaNac.anio < 0){
							printf("\nIngrese un anio valido: ");
							scanf("%d",&chofer.fechaNac.anio);
						}
						printf("\nIngrese su telefono: ");
						scanf("%ld", &chofer.telefono);
						fwrite(&chofer, sizeof(chofer), 1, CHOFERES);
				}else{
					if(existe==-1){
						printf("\nHubo un error al intentar verificar si existia el registro de un chofer con ese DNI.");
					}else{
						band =1;
						printf("\nUn chofer con ese DNI ya se encuentra registrado. Por favor ingrese uno nuevo.");
					}
				}
				
			}while(band==1);
			
			
		}
		fclose(CHOFERES);
	}else{
		printf("No se pudo abrir el archivo choferes");
	}

}

int generarIdChofer(){
	int aux = 0;
	if((CHOFERES = fopen("choferes.dat","rb")) != NULL){
		fseek(CHOFERES, 0, SEEK_END);
		
		if(ftell(CHOFERES) > 0){
			fseek(CHOFERES,(long int)sizeof(chofer)*-1,SEEK_END);
			fread(&chofer,sizeof(chofer),1,CHOFERES);
			aux = chofer.id;
		}
		fclose(CHOFERES);
		return aux;
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
		while(!feof(CHOFERES) && band == 0){
			
			if(buscarId == chofer.id){
				band++;
			}else{
				fread(&chofer,sizeof(chofer),1,CHOFERES);
			}
			
		}
		if(band == 0){
			printf("\nNo se pudo encontrar el ID del chofer\n");
		}else{
			printf("-----------\n|ingrese los nuevos datos|\n-----------\n Nombre y apellido: ");
				fflush(stdin);
				fgets(chofer.NomApe, sizeof(chofer.NomApe), stdin);
				printf("\n|Fecha de nacimiento|\n");
				printf("Dia: ");
				scanf("%d",&chofer.fechaNac.dia);
				while((chofer.fechaNac.dia > 31) || (chofer.fechaNac.dia < 1)){
					printf("\nIngrese un dia valido: ");
					scanf("%d",&chofer.fechaNac.dia);
				}
				printf("\nmes: ");
				scanf("%d",&chofer.fechaNac.mes);
				while((chofer.fechaNac.mes > 12) || (chofer.fechaNac.mes < 1)){
					printf("\nIngrese un mes valido: ");
					scanf("%d",&chofer.fechaNac.mes);
				}
				printf("\nanio: ");
				scanf("%d",&chofer.fechaNac.anio);
				while(chofer.fechaNac.anio < 0){
					printf("\nIngrese un anio valido: ");
					scanf("%d",&chofer.fechaNac.anio);
				}

				printf("\nIngrese la direccion nueva: ");
				fflush(stdin);
				fgets(chofer.direccion, sizeof(chofer.direccion), stdin);
				printf("\ningrese el nuevo numero telefonico: ");
				scanf("%ld",&chofer.telefono);
				printf("\nIngrese el nuevo correo electronico: ");
				fflush(stdin);
				fgets(chofer.email, sizeof(chofer.email), stdin);
				fseek(CHOFERES,(long int)sizeof(chofer) * (-1),SEEK_CUR);
				fwrite(&chofer,sizeof(chofer),1,CHOFERES);
		}
			
		fclose(CHOFERES);
	}
	else
		printf("error al abrir el archivo choferes\n");
	
}

void choferesConMasPasajeros(){
	int mesIngresado, encontroUnidad = 0, encontroAux = 0;
	do{
			
		printf("\nIngrese un mes (numero del 1 al 12): ");
		scanf("%d", &mesIngresado);
		if((mesIngresado < 1) || (mesIngresado > 12)){
			printf("\nPor favor ingrese un numero valido.");
		}
	}while((mesIngresado < 1) || (mesIngresado > 12));

	FILE *auxDniChoferes;
	FILE *auxParaContar = fopen("auxParaContar.dat", "wb");
	struct Aux{
		long DNIC;
		int cantidadPasajeros;
	}aux;
	if((CHOFERES = fopen("choferes.dat", "rb")) != NULL){

		if((MOVIMIENTOS = fopen("movimientos.dat", "rb")) != NULL){

			if((UNIDADES = fopen("UNIDADES.dat", "rb")) != NULL){

				if((auxDniChoferes = fopen("auxDniChoferes.dat", "a+b")) != NULL){

					if(auxParaContar!= NULL){
						if((auxParaContar = fopen("auxParaContar.dat", "r+b")) != NULL){
							

							fread(&mov, sizeof(mov), 1, MOVIMIENTOS);
							while(!feof(MOVIMIENTOS)){
								if(mov.fecha.mes == mesIngresado){
								
									fread(&unidad, sizeof(unidad), 1, UNIDADES);
									//busco en unidades el nro de unidad que se encuentra en el movimiento para sacar el dni del chofer:
									while((!feof(UNIDADES)) && (!encontroUnidad)){
										
										if(unidad.NroUnidad == mov.nroUnidad){
											encontroUnidad = 1;
										}else{
											fread(&unidad, sizeof(unidad), 1, UNIDADES);
										}
									}

									if(encontroUnidad){
										//al encontrar la unidad, escribo en un archivo auxiliar solo el dni
										fwrite(&unidad.DNIC, sizeof(unidad.DNIC), 1, auxDniChoferes);
									}
								}
								fread(&mov, sizeof(mov), 1, MOVIMIENTOS);
								rewind(UNIDADES);
								encontroUnidad = 0;	
									
							}

							encontroAux = 0;
							rewind(auxDniChoferes);
							fread(&unidad.DNIC, sizeof(unidad.DNIC), 1, auxDniChoferes);
							while(!feof(auxDniChoferes)){

								encontroAux = 0;
								fread(&aux, sizeof(aux), 1, auxParaContar);
								while((!feof(auxParaContar)) && (!encontroAux)){

									if(unidad.DNIC == aux.DNIC){
										encontroAux = 1;
									}else{
										fread(&aux, sizeof(aux), 1, auxParaContar);
									}
								}
								if(encontroAux){
									//si ya esta escrito el dni, le sumo uno a la cantidad de pasajeros
									aux.cantidadPasajeros = aux.cantidadPasajeros +1;
									fseek(auxParaContar, (long int)sizeof(aux) * -1, SEEK_CUR);
									fwrite(&aux, sizeof(aux), 1, auxParaContar);
								}else{
									//si no esta escrito el dni, lo escribo y seteo los pasajeros en uno
									aux.DNIC = unidad.DNIC;
									aux.cantidadPasajeros = 1;
									fwrite(&aux, sizeof(aux), 1, auxParaContar);
								}
								
								rewind(auxParaContar);

								fread(&unidad.DNIC, sizeof(unidad.DNIC), 1, auxDniChoferes);
							}

							fread(&aux, sizeof(aux), 1, auxParaContar);
							int max = aux.cantidadPasajeros;
							while(!feof(auxParaContar)){

								if(aux.cantidadPasajeros >= max){
									max = aux.cantidadPasajeros;
								}
								fread(&aux, sizeof(aux), 1, auxParaContar);
							}
							encontroAux = 0;
							rewind(auxParaContar);
							printf("\nEl chofer o los choferes con mas pasajeros son: ");
							fread(&aux, sizeof(aux), 1, auxParaContar);
							while(!feof(auxParaContar)){

								if(aux.cantidadPasajeros == max){
									fread(&chofer, sizeof(chofer), 1, CHOFERES);
									while((!feof(CHOFERES)) && (!encontroAux)){
										if(chofer.DNI == aux.DNIC){
											encontroAux = 1;
										}else{
											fread(&chofer, sizeof(chofer), 1, CHOFERES);
										}
									}
									if(encontroAux){
										printf("\nNombre: %s, DNI: %ld", chofer.NomApe, chofer.DNI);
									}
								}
								encontroAux = 0;
								rewind(CHOFERES);
								fread(&aux, sizeof(aux), 1, auxParaContar);
									
							}
							fclose(auxParaContar);
							remove("auxParaContar.dat");	
						}else{
							printf("\nHubo un error al abrir el archivo auxiliar para contar.");
						}
						
					}else{
						printf("\nHubo un error al crear el archivo auxiliar para contar");
					}

				fclose(auxDniChoferes);
				remove("auxDniChoferes.dat");
				}else{
					printf("\nHubo un crear o abrir al abrir el archivo auxDniChoferes");
				}
				


				
			fclose(UNIDADES);
			}else{
				printf("\nHubo un error al abrir el archivo unidades");
			}
		fclose(MOVIMIENTOS);
		}else{
			printf("\nHubo un error al abrir el archivo movimientos");
		}
	fclose(CHOFERES);
	}else{
		printf("\nHubo un error al intentar abrir el archivo choferes");
	}
}

void buscarRecargasPorDni(){
	long dni;
	printf("\nIngrese el dni que desea buscar: ");
	scanf("%ld", &dni);

	if((RECARGAS = fopen("recargas.dat", "rb")) != NULL){

		fread(&rec, sizeof(rec), 1, RECARGAS);
		while(!feof(RECARGAS)){
			if(rec.DNI == dni){
				printf("\nDNI: %ld , Nro. Control: %ld, Monto: %f, Boca de pago: %s, Fecha: %d/%d/%d, Hora: %d:%d:%d", rec.DNI, rec.NroCtrl, rec.monto, rec.BocaPago, rec.fecha.dia, rec.fecha.mes, rec.fecha.anio, rec.hora.hora, rec.hora.min, rec.hora.seg);
			}
			fread(&rec, sizeof(rec), 1, RECARGAS);
		}
	}

	/*Forma diferente abriendo archivo por archivo de texto: 
			char nombre[45];
			char nroDeControlTexto[45], cadena[200];
			long nroDeControl = 9000001;
			sprintf(nombre, "%ld", dni);
			sprintf(nroDeControlTexto, "%ld", nroDeControl+1);
			strcat(nombre, nroDeControlTexto);
			FILE *archivo;
			while(nroDeControl <= generarNroDeControl()){
				if((archivo = fopen(nombre, "r")) != NULL){
					fgets(cadena, sizeof(cadena), archivo);
					while (!feof(archivo)) {
						printf("%s", archivo);
						fgets(cadena, sizeof(cadena), archivo);
					}
				}
				nroDeControl++;
				sprintf(nombre, "%ld", dni);
				sprintf(nroDeControlTexto, "%ld", nroDeControl);
				strcat(nombre, nroDeControlTexto);
			}	
	*/

}

long generarNroDeControl(){
	if((RECARGAS = fopen("recargas.dat", "rb")) != NULL){
		fseek(RECARGAS, 0, SEEK_END);
		
		if(ftell(RECARGAS) > 0){
			fseek(RECARGAS, (long int)sizeof(rec) *-1,SEEK_END);
			fread(&rec, sizeof(rec), 1, RECARGAS);
			return(rec.NroCtrl);
		}else{
			return 900000;
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
		do{
			IdUsuario = seEncuentraDniUsuario(dniBuscar);
			band = 0;
			if((IdUsuario != -1)){
				rec.DNI = dniBuscar;
				aux= generarNroDeControl();
				if(aux !=-1){
					rec.NroCtrl = aux+1;
					if((RECARGAS = fopen("recargas.dat", "a+b"))!= NULL){
						sprintf(nombre, "%ld%ld", rec.DNI, rec.NroCtrl);
						strcat(nombre, ".txt");
						if((archivo = fopen(nombre, "w"))!= NULL){
								if((CUENTAS = fopen("cuentas.dat", "r+b")) != NULL){
									printf("\nIngrese el monto a cargar: ");
									scanf("%f", rec.monto);
									printf("\nBoca de pago: ");
									printf("\n1. Rapipago");
									printf("\n2. Terminal de omnibus");
									printf("\n3. Mini Super Ayacucho");
									printf("\n4. Agencia IPLyC");
									printf("\n5. Quiosco");
									do{
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
											printf("\nNo es numero valido. Por favor intentelo de nuevo");
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
										printf("\nLa recarga se realizo con exito. ");
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

int nroDeTelefonoEsCorrecto(long nroDeTelefono){
	int encontro = 0;
	if((USUARIOS = fopen("Usuarios.dat", "rb")) != NULL){
		fread(&us, sizeof(us), 1, USUARIOS);
		while((!feof(USUARIOS)) && encontro){
			if(us.telefono == nroDeTelefono){
				encontro = 1;
			}else{
				fread(&us, sizeof(us), 1, USUARIOS);
			}
		}
		return encontro;
	}else{
		return -1;
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
							while(nroDeTelefonoEsCorrecto(mov.NroTarjetaOTelefono) == 0){
								printf("\nEl numero de telefono que se ingreso no coincide con el de la cuenta. Ingrese nuevamente: ");
								scanf("%ld", mov.NroTarjetaOTelefono);
							}
							if(nroDeTelefonoEsCorrecto(mov.NroTarjetaOTelefono) == 1){
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
									if(cuenta.saldo<=mov.SaldoUso){
										cuenta.saldo = cuenta.saldo - mov.SaldoUso;
										fseek(CUENTAS, (long int)sizeof(cuenta)*-1, SEEK_CUR);
										fwrite(&cuenta, sizeof(cuenta), 1, CUENTAS);
										fwrite(&mov, sizeof(mov), 1, MOVIMIENTOS);
									}else{
										printf("\nSaldo insuficiente.");
									}
								}else{
									printf("\nSe produjo un error.");
								}
							}else{
								printf("\nHubo un error al confirmar el numero de telefono.");
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
			rewind(UNIDADES);
		}
		else {
			fseek(UNIDADES, (long int)sizeof(unidad) * (-1), SEEK_END);
			fread(&unidad, sizeof(unidad),1, UNIDADES);
			unidad.idUnidad++;
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
		fclose(UNIDADES);
		}
		
	else 
		printf("error al abrir el archivo unidades\n");
}

void ModificarUnidad(){
	int buscarID, encontro = 0;
	
	if((UNIDADES = fopen("UNIDADES.dat","r+b")) != NULL){
		printf("ingrese el ID de la unidad a buscar: ");
		scanf("%d",&buscarID);
		
		fread(&unidad,sizeof(unidad),1,UNIDADES);
		while(!feof(UNIDADES) && (encontro == 0)){
			if(buscarID == unidad.idUnidad){
				encontro = 1;
			}else{
				fread(&unidad,sizeof(unidad),1,UNIDADES);
			}
		}
		if(encontro == 0){
			printf("no se encontro a la unidad");
		}else{
			//id
				unidad.idUnidad =  buscarID;
				//pedir datos nuevos
				printf("ingrese el numero de la unidad\n");
   				scanf("%d", &unidad.NroUnidad);
   				
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
				fgets(unidad.marca, sizeof(unidad.marca), stdin);
				
				printf("ingrese el modelo de la unidad\n");
				fflush(stdin);
				fgets(unidad.modelo, sizeof(unidad.modelo), stdin);
				
				printf("Ingrese el kilometraje de la unidad\n");
				scanf("%f", &unidad.km);
				
				printf("Ingrese la fecha de alta de la unidad\n Año");
				scanf("%d", &unidad.FechaAlta.anio);
				while(unidad.FechaAlta.anio < 0){
					printf("\nIngrese un año valido: ");
					scanf("%d", &unidad.FechaAlta.anio);
				}
				printf("mes\n");
				scanf("%d", &unidad.FechaAlta.mes);
				while(unidad.FechaAlta.mes < 1 || unidad.FechaAlta.mes > 12){
					printf("\nIngrese un mes valido: ");
					scanf("%d", &unidad.FechaAlta.mes);
				}
				printf("día\n");
				scanf("%d", &unidad.FechaAlta.dia);
				while((unidad.FechaAlta.dia < 1) || (unidad.FechaAlta.dia > 31)){
					printf("\nIngrese un anio valido: ");
					scanf("%d", &unidad.FechaAlta.anio);
				}
				printf("Esta adaptada la unidad para discapacitados? presione 1 para confirmar y 0 para negar\n");
				scanf("%d", &unidad.adaptado);
				while(unidad.adaptado != 0 && unidad.adaptado !=1)
				{
					printf("El identificador de discapacitados proporcionado no es valido, por favor ingrese 0 para am y 1 para pm\n");
					scanf("%d", &unidad.adaptado);
				}
				fseek(UNIDADES,(long int) sizeof(unidad) * (-1),SEEK_CUR);
				fwrite(&unidad, sizeof(unidad),1, UNIDADES);
		}
	}
	else
		printf("error al abrir el archivo para realizar la modificacion\n");
	fclose(UNIDADES);
}

// Los objetos de valor de mi casa se encuentra en el siguiente enlace: https://www.youtube.com/watch?v=dQw4w9WgXcQ
void pagarPasajeTarjeta(){
	if ((CUENTAS = fopen("cuentas.dat","r+b"))!=NULL){
		if ((MOVIMIENTOS = fopen("movimientos.dat","ab"))!=NULL){
			long int DNI, NumTarjeta;
			int CuentaEncontro = 0;
			printf("\nIngrese numero de Tarjeta:\n");
			scanf("%ld",&NumTarjeta);
			// Busca la cuenta de la tarjeta Fisica
			while(!feof(CUENTAS) && !CuentaEncontro){
				if (NumTarjeta == cuenta.nroDeTarjeta){
					CuentaEncontro = 1;
				} else 
					fread(&cuenta, sizeof(cuenta), 1, CUENTAS);
			}
			puts("Ingrese nro de Unidad");
			scanf("%s",&mov.nroUnidad);
			puts("Ingrese origen del pasajero:");
			scanf("%s",&mov.origen);
			puts("Ingrese destino del pasajero:");
			scanf("%s",&mov.destino);
			puts("Saldo a descontar:");
			scanf("%f",&mov.SaldoUso);
			//Si no tenes plata te saca.
			if(cuenta.saldo < mov.SaldoUso){
				puts("SALDO INSUFICIENTE");
			}
			mov.hora.hora = tiempoActual(1);
			mov.hora.min = tiempoActual(2);
			mov.hora.seg = tiempoActual(3);
			mov.fecha.anio = tiempoActual(4);
			mov.fecha.mes = tiempoActual(5);
			mov.fecha.dia = tiempoActual(6);
			fwrite(&mov,sizeof(mov),1,MOVIMIENTOS);
			cuenta.saldo = cuenta.saldo - mov.SaldoUso;
			fwrite(&cuenta,sizeof(cuenta),1,CUENTAS);	
			fclose(MOVIMIENTOS);
			fclose(CUENTAS);
		} else
			puts("Error al abrir el archivo CUENTAS");	
	} else 
		puts("Error al abrir el archivo MOVIMIENTOS");
}

void PrimerTurno(){
	int cont = 0, Ctotal = 0,anio;
	float por;
	
	if((MOVIMIENTOS = fopen("Movimientos.dat","rb")) != NULL){
		
		printf("\ningrese el anio: ");
		scanf("%d",&anio);
		
		fread(&mov,sizeof(mov),1,MOVIMIENTOS);
		
		while(!feof(MOVIMIENTOS)){
			if(anio == mov.fecha.anio){
				
				if(mov.hora.hora >= 00 && (mov.hora.hora <= 11 && mov.hora.min <= 59)){
					cont++;
				}
			}
			Ctotal++;
			fread(&mov,sizeof(mov),1,MOVIMIENTOS);
		}
		por = (cont * 100) / Ctotal;
		printf("el porcentaje de pasajeros que viajaron en el anio es de: %.2f \n", por);
		fclose(MOVIMIENTOS);
	}
	else
		printf("no se abrio el archivo\n");
	
}


int compararDosFechas(struct Fecha fecha1, struct Fecha fecha2){
	int band;
	//1:la primera fecha es mayor, 2:la segunda fecha es mayor, 0:son iguales
	if(fecha1.anio > fecha2.anio){
		//la primera fecha es mayor
		band = 1;
	}else{
		if(fecha2.anio > fecha1.anio){
			//la segunda fecha es mayor
			band = 2;
		}else{
			if(fecha1.anio == fecha2.anio){
				//Si las fechas son iguales entonces me fijo el mes
				if(fecha1.mes > fecha2.mes){
					//la fecha 1 es mayor
					band = 1; 
				}else{
					if(fecha2.mes > fecha1.mes){
						//la fecha 2 es mayor
						band = 2;
					}else{
						if(fecha1.mes == fecha2.mes){
							//si los meses son iguales comparo los dias
							if (fecha1.dia > fecha2.dia){
								// la fecha 1 es mayor
								band = 1;
							}else{
								if(fecha2.dia > fecha1.dia){
									// la fecha 2 es mayor
									band = 2;
								}else{
									//las fechas son iguales
									band = 0;
								}
							}
							
						}
					}
					
				}
			}
		}
	}
}

void movimientosEntreDosFechas(){

	struct Fecha fechaInicio;
	struct Fecha fechaFinal;
	printf("\nPrimera fecha.");
	printf("\nAño: ");
	scanf("%d", &fechaInicio.anio);
	while(fechaInicio.anio < 1){
		printf("\nIngrese un anio valido: ");
		scanf("%d", &fechaInicio.anio);
	}

	printf("\nMes: ");
	scanf("%d", &fechaInicio.mes);
	while(fechaInicio.mes < 1 || fechaInicio.mes > 12){
		printf("\nIngrese un mes valido: ");
		scanf("%d", &fechaInicio.mes);
	}

	printf("\nDia: ");
	scanf("%d", &fechaInicio.dia);
	while(fechaInicio.dia < 1 || fechaInicio.dia > 31){
		printf("\nIngrese un dia valido: ");
		scanf("%d", &fechaInicio.dia);
	}

	printf("\n\nFecha final.");
	printf("\nAño: ");
	scanf("%d", &fechaFinal.anio);
	while(fechaFinal.anio < 1){
		printf("\nIngrese un anio valido: ");
		scanf("%d", &fechaFinal.anio);
	}

	printf("\nMes: ");
	scanf("%d", &fechaFinal.mes);
	while(fechaFinal.mes < 1 || fechaFinal.mes > 12){
		printf("\nIngrese un mes valido: ");
		scanf("%d", &fechaFinal.mes);
	}

	printf("\nDia: ");
	scanf("%d", &fechaFinal.dia);
	while(fechaFinal.dia < 1 || fechaFinal.dia > 31){
		printf("\nIngrese un dia valido: ");
		scanf("%d", &fechaFinal.dia);
	}
	if((MOVIMIENTOS = fopen("movimientos.dat", "rb")) != NULL){

		fread(&mov, sizeof(mov), 1, MOVIMIENTOS);
		while(!feof(MOVIMIENTOS)){

			if((compararDosFechas(mov.fecha, fechaInicio) < 2 )&& (compararDosFechas(fechaFinal, mov.fecha) < 2)){
				printf("\nDNI: %ld, NroDeTarjeta/NroDeTelefono: %ld, Origen: %s, Destino: %s, Saldo: %f, Fecha: %d/%d/%d, Hora: %d:%d:%d", mov.DNI, mov.NroTarjetaOTelefono, mov.origen, mov.destino, mov.SaldoUso, mov.fecha.anio, mov.fecha.mes, mov.fecha.dia, mov.hora.hora, mov.hora.min, mov.hora.seg);
			}
			fread(&mov, sizeof(mov), 1, MOVIMIENTOS);
		}

	}else{
		printf("No se pudo abrir el archivo movimientos.");
	}
	

}



void showaccountcredit(){
	long int accountdni = 0;
	time_t houracc = time(NULL);
	struct tm hr = *localtime(&houracc);
	if ((CUENTAS = fopen("cuentas.dat", "r+b")) != NULL && (USUARIOS = fopen("Usuarios.dat", "r+b")) != NULL)
		{
		printf("ingrese su DNI\n");
		scanf("%ld", &accountdni);
		fread(&us, sizeof(us), 1, USUARIOS);
			while (!feof(USUARIOS)){
				if (accountdni==us.DNI){
					fread(&cuenta, sizeof(cuenta),1, CUENTAS);
					while (!feof(CUENTAS)){
						if (us.id==cuenta.idUsuario){
							printf("Su saldo es de %d\n %02d %02d %02d", cuenta.saldo, hr.tm_hour, hr.tm_min, hr.tm_sec);
							break;
						}
						fread(&cuenta, sizeof(cuenta),1, CUENTAS);
					}
				}
				fread(&us, sizeof(us), 1, USUARIOS);
			}
	}
}

void buscarMovimientosUsuario() {
	char NomApebusc[40];
	int Encontro = 0;
	if ((USUARIOS = fopen("Usuarios.dat","rb"))!=NULL) {
		if ((MOVIMIENTOS = fopen("movimientos.dat","rb"))!=NULL){
			puts("Ingrese un nombre y apellido");
			fflush(stdin);
			fgets(NomApebusc, sizeof(NomApebusc), stdin);
			while (!feof(USUARIOS) && !Encontro){
				if (strcmp(NomApebusc,us.NomApe)==0){
					Encontro = 1;
				} else
					fread(&us,sizeof(us),1,USUARIOS);					
			}
			while (!feof(MOVIMIENTOS)){
				if (us.DNI == mov.DNI){
					printf("DNI:\n%ld\n\nNumero Tarjeta o Telefono:\nld\n\nOrigen:\n%s\n\nDestino:\n%s\n\nPrecio:\n%.2f\n\nNro Unidad:\n%d\n\nFecha:\n%d/%d%d\n\nHora:\n%d/%d",&mov.DNI,&mov.NroTarjetaOTelefono,&mov.origen,&mov.destino,&mov.SaldoUso,&mov.nroUnidad,&mov.fecha.dia,&mov.fecha.mes,&mov.fecha.anio,&mov.hora.hora,&mov.hora.min);
					printf("\n************************************************\n\n************************************************");
				} else
					fread(&mov,sizeof(mov),1,MOVIMIENTOS);
			}
		} else
			puts("Error al abrir el archivo movimientos");
	} else
		puts("Error al abrir el archivo Usuarios");
}

void ListarChoferes(){

	if((CHOFERES = fopen("choferes.dat","rb")) != NULL){
		
		fread(&chofer, sizeof(chofer),1,CHOFERES);
		while(!feof(CHOFERES)){
			printf("----------------\n +Id: %d\n +Nombre y apellido: %s\n +fecha de nacimiento: %d/%d/%d\n +DNI: %ld\n +Telefono: %ld\n +Direccion: %s\n +Email: %s\n----------------\n",chofer.id, chofer.NomApe, chofer.fechaNac.dia,chofer.fechaNac.mes, chofer.fechaNac.anio, chofer.DNI, chofer.telefono, chofer.direccion, chofer.email);
			fread(&chofer,sizeof(chofer),1,CHOFERES);
		}
		fclose(CHOFERES);
	}
	else
		printf("error al abrir el archivo choferes\n");
	}

void unistlist()
{
	if ((UNIDADES = fopen ("unidades.dat", "rb"))!= NULL);
	{
		fread(&unidad, sizeof(unidad),1,UNIDADES);
		while (!feof(CHOFERES))
		{
			printf ("\n Id: %d \n Numero de unidad: %d \n Tiene %d asientos \n Corresponde al modelo %s de la marca %s \n Fue dado de alta %d %d %d y cuenta con %f Km\n se encuentra conducida por el chofer con DNI %d", unidad.idUnidad, unidad.NroUnidad, unidad.asientos, unidad.marca, unidad.modelo, unidad.FechaAlta.dia, unidad.FechaAlta.mes, unidad.FechaAlta.anio, unidad.km, unidad.DNIC);
			if (unidad.turno==1)
			{
				printf("\nCircula por el turno tarde 12:00-23:59");
			}
			else 
			printf ("\nCircula por el turno mañana 00:00-11:59");
			
			if (unidad.adaptado==1)
			{
				printf("La unidad se encuentra adaptada para discapacitados");
			}
			else 
			printf ("la unidad no admite invalidos");
		}
	}
}
			
			
		
	

