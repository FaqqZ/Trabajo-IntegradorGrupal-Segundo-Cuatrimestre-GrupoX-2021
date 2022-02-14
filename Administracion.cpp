#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "Consultorio.h"
#include <windows.h>

typedef char cadena[20];
typedef char nombreArchi[20];


void RegPro(FILE *arch1, nombreArchi archiPros)
{
	profesional reg;
	cadena auxApeNom;
	bool contrasenaValida, matriculaValida;
	int situacionContrasena[7], datos = 0;
	int situacionMatricula[2];

	InfoProActual(reg, datos);

	printf("\nApellido: ");
	_flushall();
	gets(reg.nomyApe);

	printf("Nombre: ");
	_flushall();
	gets(auxApeNom);

	strcat(reg.nomyApe, ", ");
	strcat(reg.nomyApe, auxApeNom);

	datos = 1;
	system("cls");
	InfoProActual(reg, datos);

	do
	{
		matriculaValida = false;

		printf("\nNro de id profesional: ");
		scanf("%d", &reg.matricula);

		if (!CheckMatricula(reg.matricula, situacionMatricula))
		{
			printf("Error:");

			if (situacionMatricula[0] == 1)
			{
				printf("El id profesional ya esta en uso\n");
			}

			getch();
		}
		else
		{
			datos = 2;
			matriculaValida = true;
		}

		system("cls");
		InfoProActual(reg, datos);
	} while (!matriculaValida);

	do
	{
		contrasenaValida = false;

		printf("\nContrasena: ");
		_flushall();
		gets(reg.contrasenia);
		
		if (!CheckPass(reg.contrasenia, situacionContrasena))
		{
			printf("Error: ");
			if (situacionContrasena[0] == 1)
			{
				printf("La contraseña debe tener al menos una mayuscula\n");
			}
			if (situacionContrasena[1] == 1)
			{
				printf("La contraseña debe tener al menos una minuscula\n");
			}
			if (situacionContrasena[2] == 1)
			{
				printf("La contraseña debe tener al menos un digito\n");
			}
			if (situacionContrasena[3] == 1)
			{
				printf("\tContiene caracteres con tilde\n");
			}
			if (situacionContrasena[4] == 1)
			{
				printf("La contraseña debe de tener 6 caracteres como minimo\n");
			}
			if (situacionContrasena[5] == 1)
			{
				printf("La contraseña no debe tener mas de 3 numeros consecutivos\n");
			}
			if (situacionContrasena[6] == 1)
			{
				printf("La contraseña no puede tener 2 caracteres consecutivos alfabeticamente\n");
			}

			getch();
		}
		else
		{
			contrasenaValida = true;
			datos = 3;
		}

		system("cls");
		InfoProActual(reg, datos);

	} while (!contrasenaValida);

	printf("\nDNI: ");
	scanf("%d", &reg.DNI);

	datos = 4;
	system("cls");
	InfoProActual(reg, datos);

	printf("\nTelefono: ");
	_flushall();
	gets(reg.telefono);

	datos = 5;
	system("cls");
	InfoProActual(reg, datos);

	reg.modulo = 2;

	arch1 = fopen(archiPros, "r+b");

	fseek(arch1, 0, SEEK_END);

	fwrite(&reg, sizeof(reg), 1, arch1);

	fclose(arch1);

	printf("\nProfesional a%cadido",164);
	getch();
}

void RegUser(FILE *arch1, int tipoUsuario, nombreArchi archiUsuarios)
{
	user reg;
	int situacionUsuario[5], situacionContrasena[8];
	bool usuarioValido, contrasenaValida;
	cadena auxApeNom;
	char auxUsuario[20];
	char auxClave[20];	
	int datos = 0;		 
	system("cls");
	InfoUserActual(reg, datos, tipoUsuario);

	do
	{
		usuarioValido = false;

		printf("\nUsuario: ");
		_flushall();
		gets(auxUsuario);

		if (!CheckUser(auxUsuario, situacionUsuario))
		{
			printf("Error:");
			if (situacionUsuario[0] == 1)
			{
				printf("El nombre de usuario ya esta en uso\n");
			}
			if (situacionUsuario[1] == 1)
			{
				printf("El primer caracter debe de estar en minuscula\n");
			}
			if (situacionUsuario[2] == 1)
			{
				printf("Debe de tener al menos 2 mayusculas\n");
			}
			if (situacionUsuario[3] == 1)
			{
				printf("No puede tener mas de 3 numeros\n");
			}
			if (situacionUsuario[4] == 1)
			{
				printf("Es demasiado largo (Maximo de 32 caracteres)\n");
			}

			getch();
		}
		else
		{
			usuarioValido = true;
			_flushall();
			strcpy(reg.usuario, auxUsuario);
			datos = 1;
		}

		system("cls");
		InfoUserActual(reg, datos, tipoUsuario);

	} while (!usuarioValido);

	do
	{
		contrasenaValida = false;

		printf("\nContrasena: ");
		_flushall();
		gets(auxClave);

		if (!CheckPass(auxClave, situacionContrasena))
		{
			printf("Error: ");
			if (situacionContrasena[0] == 1)
			{
				printf("Debe de tener al menos una mayuscula\n");
			}
			if (situacionContrasena[1] == 1)
			{
				printf("Debe de tener al menos una minuscula\n");
			}
			if (situacionContrasena[2] == 1)
			{
				printf("Debe de tener al menos un digito\n");
			}
			if (situacionContrasena[3] == 1)
			{
				printf("Contiene caracteres con tilde\n");
			}
			if (situacionContrasena[4] == 1)
			{
				printf("Debe de tener 6 caracteres como minimo\n");
			}
			if (situacionContrasena[5] == 1)
			{
				printf("No puede tener mas de 3 numeros consecutivos\n");
			}
			if (situacionContrasena[6] == 1)
			{
				printf("No puede tener 2 caracteres consecutivos alfabeticamente\n");
			}
			if (situacionContrasena[7] == 1)
			{
				printf("Es demasiado larga (32 caracteres maximo)\n");
			}

			getch();
		}
		else
		{
			contrasenaValida = true;
			_flushall();
			strcpy(reg.contrasenia, auxClave);
			datos = 2;
		}

		system("cls");
		InfoUserActual(reg, datos, tipoUsuario);
	} while (!contrasenaValida);

	printf("\nApellido: ");
	_flushall();
	gets(reg.ApeNom);

	printf("Nombre: ");
	_flushall();
	gets(auxApeNom);

	strcat(reg.ApeNom, ", ");
	strcat(reg.ApeNom, auxApeNom);

	datos = 3;
	system("cls");
	InfoUserActual(reg, datos, tipoUsuario);

	if (tipoUsuario == 1)
	{
		reg.modulo = 1;
	}
	else if (tipoUsuario == 3)
	{
		reg.modulo = 3;
	}

	arch1 = fopen(archiUsuarios, "r+b");

	fseek(arch1, 0, SEEK_END);

	fwrite(&reg, sizeof(user), 1, arch1);

	fclose(arch1);

	printf("\nUsuario a%cadido",164);
	getch();
}

void BuscarTurnosAtendidos(FILE *arch1, FILE *arch2, nombreArchi archiProfesional, nombreArchi archiTurnos)
{
	bool matriculaExistente;
	int matricula;
	int situacionMatricula[2];

	do
	{
		matriculaExistente = false;

		system("cls");
		printf("Atenciones por Profesional\n==========================\n\n0.-Volver al menu principal\n\nMatricula: ");
		scanf("%d", &matricula);
		if (matricula == 0)
		{
			break;
		}

		CheckMatricula(matricula, situacionMatricula);

		if (situacionMatricula[0] == 0)
		{
			printf("ERROR: Matricula inexistente\n");

			getch();
		}
		else
		{
			matriculaExistente = true;
		}

	} while (!matriculaExistente);

	if (matricula != 0)
	{
		arch1 = fopen(archiProfesional, "r+b");

		profesional infoPro;

		fread(&infoPro, sizeof(infoPro), 1, arch1);

		while (!feof(arch1))
		{
			if (matricula == infoPro.matricula)
			{
				break;
			}

			fread(&infoPro, sizeof(infoPro), 1, arch1);
		}

		printf("\nProfesional:\n");
		printf("Nombre: %s\n", infoPro.nomyApe);
		printf("DNI: %d\n", infoPro.DNI);

		fclose(arch1);

		printf("\n\n\tTurnos atendidos:\n\n");

		arch2 = fopen(archiTurnos, "r+b");

		turnos infoTurno;
		int contadorTurnosAtendidos = 0;

		fread(&infoTurno, sizeof(turnos), 1, arch2);

		while (!feof(arch2))
		{
			if (infoTurno.matriculaPro == matricula and infoTurno.borrado == true)
			{
				contadorTurnosAtendidos++;
				printf("\n%d)", contadorTurnosAtendidos);
				printf(" Fecha: %d/%d/%d\n", infoTurno.fec.dia, infoTurno.fec.mes, infoTurno.fec.anio);
				printf("DNI: %d\n", infoTurno.DNIcliente);
				printf("Observaciones: %s\n", infoTurno.atencion);
			}

			fread(&infoTurno, sizeof(turnos), 1, arch2);
		}

		if (contadorTurnosAtendidos == 0)
		{
			printf("\nEste profesional no tiene turnos atendidos");
		}

		fclose(arch2);

		getch();
	}
}

void RankingProfesionales(FILE *arch1, FILE *arch2, nombreArchi archiProfesionales, nombreArchi archiTurnos)
{
	profesional infoPro;
	turnos infoTurno;
	int atendidos;
	rank rankingPro;

	arch1 = fopen(archiProfesionales, "r+b");

	arch2 = fopen(archiTurnos, "r+b");

	nodo *lista;

	lista = NULL;

	fread(&infoPro, sizeof(profesional), 1, arch1);

	while (!feof(arch1))
	{
		fread(&infoTurno, sizeof(turnos), 1, arch2);
		atendidos = 0;

		while (!feof(arch2))
		{
			if (infoPro.matricula == infoTurno.matriculaPro and infoTurno.borrado == true)
			{
				atendidos++;
			}

			fread(&infoTurno, sizeof(turnos), 1, arch2);
		}

		rankingPro.matricula = infoPro.matricula;
		strcpy(rankingPro.ApeNomPro, infoPro.nomyApe);
		rankingPro.turnosAtendidos = atendidos;

		FuncNodo(lista, rankingPro);

		fread(&infoPro, sizeof(profesional), 1, arch1);
	}

	fclose(arch1);
	fclose(arch2);

	system("cls");

	printf("Ranking de Profesionales\n");
	printf("=======================\n");

	if (lista == NULL)
	{
		printf("\nNo hay profesionales registrados...");
	}

	Listar(lista);

	getch();
}

main()
{
	FILE *arch1, *arch2, *arch3;
	nombreArchi ArchivoUsuarios = "Usuarios.dat", ArchivoProfesionales = "Profesionales.dat", ArchivoTurnos = "Turnos.dat";

	CrearArch(arch1, ArchivoProfesionales);
	CrearArch(arch2, ArchivoUsuarios);
	CrearArch(arch3, ArchivoTurnos);

	int caso = 0;
	int registrarPro;
	int registrarAsistente;
	int registrarAdmin;
	int salirPrograma;

	do
	{
		system("cls");
		printf("Modulo Administraci%cn\n======================\n\n1.-Registrar Profesional\n2.-Registrar Usuario Recepcionista\n3.-Atenciones por Profesional\n4.-Ranking de Profesionales por Atenciones\n\n5.-CERRAR APLICACION\n\nIngrese una opci%cn --> ",162,162);

		scanf("%d", &caso);

		switch (caso)
		{
		case 1:
			system("cls");
			RegPro(arch1, ArchivoProfesionales);
			break;
		case 2:
			system("cls");
			RegUser(arch2, 3, ArchivoUsuarios);
			break;
		case 3:
			BuscarTurnosAtendidos(arch1, arch3, ArchivoProfesionales, ArchivoTurnos);
			break;
		case 4:
			RankingProfesionales(arch1, arch3, ArchivoProfesionales, ArchivoTurnos);
			break;
		case 5:break;
		}

	} while (caso != 5);
}








