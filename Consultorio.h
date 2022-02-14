#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

struct user
{
    char usuario[10];
    char contrasenia[33];
    char ApeNom[60];
    int modulo;
};

struct profesional
{
    char nomyApe[60];
    int matricula;
    int DNI;
    char telefono[25];
    int modulo;
    char contrasenia[33];
};

struct fecha
{
    int dia;
    int mes;
    int anio;
};

struct turnos
{
    fecha fec;
    int DNIcliente;
    char atencion[380];
    int matriculaPro;
    bool borrado;
};

struct cliente
{
    char nombre[60];
    char direcc[60];
    int DNI_CLIENTE;
    char localidad[60];
    fecha fec;
    float peso;
    char numeroTel[25];
    float edad;
};

struct rank
{
    char ApeNomPro[60];
    int turnosAtendidos;
    int matricula;
};

struct nodo
{
    rank info;
    nodo *sig;
};

bool CheckUser(char Usuario[30], int situacion[5])
{


    for (int i = 0; i < 5; i++)
    {
        situacion[i] = 0;
    }

    FILE *archi = fopen("Usuarios.dat", "rb");
    user usuarioRegistrado;
    int contadorMayusculas = 0, contadorDigitos = 0;

    fread(&usuarioRegistrado, sizeof(user), 1, archi);

    while (!feof(archi))
    {
        if (strcmp(usuarioRegistrado.usuario, Usuario) == 0)
        {
            situacion[0] = 1;
        }

        fread(&usuarioRegistrado.usuario, sizeof(user), 1, archi);
    }

    if (isalpha(Usuario[0]))
    {
        if (!islower(Usuario[0]))
        {
            situacion[1] = 1;
        }
    }

    for (int i = 0; i < strlen(Usuario); i++)
    {
        if (isupper(Usuario[i]))
        {
            contadorMayusculas++;
        }
        else if (isdigit(Usuario[i]))
        {
            contadorDigitos++;
        }
    }

    if (contadorMayusculas < 2)
    {
        situacion[2] = 1;
    }

    if (contadorDigitos > 3)
    {
        situacion[3] = 1;
    }

    if (strlen(Usuario) > 32)
    {
        situacion[4] = 1;
    }

    if (situacion[0] == 1 or situacion[1] == 1 or situacion[2] == 1 or situacion[3] == 1 or situacion[4] == 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool CheckPass(char Clave[30], int situacion[8])
{
    for (int i = 0; i < 8; i++)
    {
        situacion[i] = 0;
    }

    int contadorMayusculas = 0, contadorMinusculas = 0, contadorDigitos = 0, contadorTildes = 0;

    for (int i = 0; i < strlen(Clave); i++)
    {
        if (isupper(Clave[i]))
        {
            contadorMayusculas++;
        }
        else if (islower(Clave[i]))
        {
            contadorMinusculas++;
        }
        else if (isdigit(Clave[i]))
        {
            contadorDigitos++;
        }
        else if (!isprint(Clave[i]))
        {
            contadorTildes++;
        }
    }

    if (contadorMayusculas < 1)
    {
        situacion[0] = 1;
    }

    if (contadorMinusculas < 1)
    {
        situacion[1] = 1;
    }

    if (contadorDigitos < 1)
    {
        situacion[2] = 1;
    }

    if (contadorTildes > 0)
    {
        situacion[3] = 1;
    }

    if (strlen(Clave) < 6)
    {
        situacion[4] = 1;
    }
    else
    {
        for (int i = 0; i < strlen(Clave) - 3; i++)
        {
            if (Clave[i] == (Clave[i + 1] - 1) and Clave[i + 1] == (Clave[i + 2] - 1) and Clave[i + 2] == (Clave[i + 3] - 1) and Clave[i + 3] == (Clave[i + 4] - 1))
            {
                situacion[5] = 1;
            }
        }
    }

    char ch1, ch2; 

    if (strlen(Clave) >= 2)
    {
        for (int i = 0; i < strlen(Clave) - 1; i++)
        {
            if (isalpha(Clave[i]) and isalpha(Clave[i + 1]))
            {
                ch1 = Clave[i];
                ch2 = Clave[i + 1];

                strlwr(&ch1);
                strlwr(&ch2);

                if (ch1 == (ch2 - 1))
                {
                    situacion[6] = 1;
                }
            }
        }
    }

    if (strlen(Clave) > 32)
    {
        situacion[7] = 1;
    }

    bool error = false;

    for (int i = 0; i < 8; i++) 
    {
        if (situacion[i] == 1)
        {
            error = true;
        }
    }

    return (error) ? false : true;
}

bool LogUser(char Usuario[10], char Clave[10], int modulo)
{
    FILE *archi = fopen("Usuarios.dat", "rb");

    user datosUsuario;

    fread(&datosUsuario, sizeof(user), 1, archi);

    while (!feof(archi))
    {
        if ((strcmp(Usuario, datosUsuario.usuario) == 0) and (strcmp(Clave, datosUsuario.contrasenia) == 0) and (datosUsuario.modulo == modulo))
        {
            return true;
        }

        fread(&datosUsuario, sizeof(user), 1, archi);
    }

    return false;
}

bool LogPro(int matricula, char Clave[10])
{
    FILE *archi = fopen("Profesionales.dat", "rb");

    profesional pro;

    fread(&pro, sizeof(pro), 1, archi);

    while (!feof(archi))
    {
        if (matricula == pro.matricula and strcmp(Clave, pro.contrasenia) == 0)
        {
            return true;
        }
        fread(&pro, sizeof(pro), 1, archi);
    }

    return false;
}

bool CheckMatricula(int matricula, int situacion[2])
{
    for (int i = 0; i < 2; i++)
    {
        situacion[i] = 0;
    }

    FILE *archi = fopen("Profesionales.dat", "rb");

    profesional pro;

    fread(&pro, sizeof(pro), 1, archi);

    while (!feof(archi))
    {
        if (matricula == pro.matricula)
        {
            situacion[0] = 1;
        }
        fread(&pro, sizeof(pro), 1, archi);
    }

    if (situacion[0] == 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void CrearArch(FILE *archi, char NombreArchivo[20])
{
    archi = fopen(NombreArchivo, "r+b");

    if (archi == NULL)
    {
        archi = fopen(NombreArchivo, "w+b");

        if (archi == NULL)
        {
            printf("ERROR: el archivo %s no se pudo crear", NombreArchivo);
            getch();
            exit(1);
        }
    }
}

void FuncNodo(nodo *&puntero, rank valor)
{
    nodo *nuevo = new nodo();
    nuevo->info = valor;

    nodo *aux1 = puntero;
    nodo *aux2;

    while ((aux1 != NULL) and (aux1->info.turnosAtendidos > valor.turnosAtendidos))
    {
        aux2 = aux1;
        aux1 = aux1->sig;
    }

    if (puntero == aux1)
    {
        puntero = nuevo;
    }
    else
    {
        aux2->sig = nuevo;
    }

    nuevo->sig = aux1;
}

void Listar(nodo *puntero)
{
    nodo *p = puntero;

    int posicion = 1;

    while (p != NULL)
    {
        printf("\n#%d _ \tProfesional: %s", posicion, p->info.ApeNomPro);
        printf("\nMatricula: %d", p->info.matricula);
        printf("\nTurnos atendidos: %d\n", p->info.turnosAtendidos);
        p = p->sig;
        posicion++;
    }
}

void InfoClienteActual(cliente InfoClien, int datos)
{
    printf("\t\tRegistrar Cliente");

    printf("\n\t\t=================\n");

    if (datos >= 1)
    {
        printf("\nNombre cliente: %s\n",InfoClien.nombre);

        if (datos >= 2)
        {
            printf("Direccion: %s\n",InfoClien.direcc);

            if (datos >= 3)
            {
                printf("DNI: %d\n",InfoClien.DNI_CLIENTE);

                if (datos >= 4)
                {
                    printf("Localidad: %s\n",InfoClien.localidad);

                    if (datos >= 5)
                    {
                        int auxiliar = InfoClien.edad;
                        float auxiliar2 = (InfoClien.edad - auxiliar) * 12;

                        printf("Fecha: %d/%d/%d\n",InfoClien.fec.dia, InfoClien.fec.mes, InfoClien.fec.anio);
                        printf("Edad: %d a%cos y %d meses\n",(int)InfoClien.edad,164,(int)auxiliar2);

                        if (datos >= 6)
                        {
                            printf("Peso:%.2f kg\n",InfoClien.peso);

                            if (datos >= 7)
                            {
                                printf("Telefono: %s\n",InfoClien.numeroTel);
                            }
                        }
                    }
                }
            }
        }
    }
}

void InfoTurnoActual(turnos InfoTurno, int datos)
{
    printf("Registrar Turno");

    printf("\n================\n");

    if (datos >= 1)
    {
        printf("\nMatricula: %d\n", InfoTurno.matriculaPro);

        if (datos >= 2)
        {
            printf("Fecha: %d/%d/%d\n", InfoTurno.fec.dia, InfoTurno.fec.mes, InfoTurno.fec.anio);

            if (datos >= 3)
            {
                printf("DNI - %d\n", InfoTurno.DNIcliente);
            }
        }
    }
}

void InfoEvolucionActual(turnos InfoTurno, cliente InfoCliente, int datos)
{
    printf("Registrar Evolucion de clientes");

    printf("\n==============================\n");

    if (datos >= 1)
    {
        printf("\nNombre cliente: %s\n", InfoCliente.nombre);

        if (datos >= 2)
        {
            printf("Detalles: %s\n", InfoTurno.atencion);
        }
    }
}

void InfoProActual(profesional infoPro, int datos)
{
    printf("Registrar Profesional");

    printf("\n=====================\n");

    if (datos >= 1)
    {
        printf("\nNombre: %s\n", infoPro.nomyApe);

        if (datos >= 2)
        {
            printf("Matricula: %d\n", infoPro.matricula);

            if (datos >= 3)
            {
                printf("Contrase%ca: %s\n",164, infoPro.contrasenia);

                if (datos >= 4)
                {
                    printf("DNI: %d\n", infoPro.DNI);

                    if (datos >= 5)
                    {
                        printf("Telefono: %s\n", infoPro.telefono);
                    }
                }
            }
        }
    }
}

void InfoUserActual(user infoUser, int datos, int modulo)
{
    printf("Registrar ");
    if (modulo == 1)
    {
        printf("Administrador\n=================\n");
    }
    else
    {
        printf("Asistente\n===============\n");
    }

    if (datos >= 1)
    {
        printf("\nUsuario: %s\n",infoUser.usuario);

        if (datos >= 2)
        {
            printf("Contrase%ca: %s\n",164,infoUser.contrasenia);

            if (datos >= 3)
            {
                printf("Nombre: %s\n",infoUser.ApeNom);
            }
        }
    }
}

