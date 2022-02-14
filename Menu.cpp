#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Consultorio.h"
#include <windows.h>


main()
{
    char Usuario[10], Clave[10];
    int opcion, matricula;
    bool admin, profesional, asistente;

    do
    {
        system("cls");
        printf("Bienvenido al sistema\n=====================\n\n1.-Inicio de sesion: Profesional\n2.-Inicio de sesion: Recepcionista\n\n3.-Salir del programa\n\nIngrese una opcion -->  ");
		scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            system("cls");
            printf("Inicio de sesion: Profesional \n=============================\n\n0.-Volver al menu principal\n\nMatricula: ");
            scanf("%d", &matricula);

            if (matricula == 0)
            {
                break;
            }
            printf("\nContrase%ca: ",164);
            _flushall();
            gets(Clave);

            if (LogPro(matricula, Clave))
            {
                printf("\nSesion iniciada correctamente.\n\n Redireccionando al programa.");
                profesional = true;
                getch();
                system("Consultorio.exe");
            }
            else
            {
                printf("\nERROR: matricula o contrase%ca incorrecto/s o inexistente/s.",164);
            }

            getch();

            break;
        case 2:
            system("cls");
            printf("Inicio de sesion: Recepcionista\n============================\n\n0.-Volver al menu principal\n\nUsuario: ");
            _flushall();
            gets(Usuario);

            if (strcmp(Usuario, "0") == 0)
            {
                break;
            }

            printf("\nContrase%ca: ",164);
            _flushall();
            gets(Clave);

            if (LogUser(Usuario, Clave, 3))
            {
                printf("\nSesion iniciada correctamente.\n\n Redireccionando al programa.");
                asistente = true;

                getch();
                system("Recepcion.exe");
            }
            else
            {
                printf("\nERROR: usuario o contrase%ca incorrecto/s o inexistente/s.",164);
            }

            getch();

            break;
        case 3:break;
        }

    } while (opcion != 3);
}
