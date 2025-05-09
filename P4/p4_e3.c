#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "search_queue.h"
#include "file_utils.h"

#define TOP 3

#define MAX_LINE_LENGTH 1000
#define EXTENSION_LENGTH 4
#define INPUT_EXTENSION ".txt"
#define FIRST_ARGUMENT 1
#define N_TOTAL_ARGUMENTS 2

#define halve(value) ((value) / 2)

int main(int argc, const char *argv[])
{
    FILE *f_in = NULL;
    float *grade = NULL, sum = 0, media, mediana;
    SearchQueue *queue = NULL, *queue_aux = NULL;
    int n_data, i;
    char line[MAX_LINE_LENGTH];

    if (argc != N_TOTAL_ARGUMENTS)
    {
        fprintf(stderr, "Usage: %s input_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((strcmp(argv[FIRST_ARGUMENT] + (strlen(argv[FIRST_ARGUMENT]) - EXTENSION_LENGTH), INPUT_EXTENSION)))
    {
        fprintf(stderr, "Input file format must be: "
               "file%s"
               "",
               INPUT_EXTENSION);
        return EXIT_FAILURE;
    }

    f_in = fopen(argv[FIRST_ARGUMENT], "r");
    if (!f_in)
    {
        fprintf(stderr, "ERROR EN OPEN DEL FICHERO DE ENTRADA");
        return EXIT_FAILURE;
    }

    queue = search_queue_new(float_print, float_cmp);
    if (!queue)
    {
        fprintf(stderr, "ERROR EN LA CREACION DE LA COLA");
        fclose(f_in);
        return EXIT_FAILURE;
    }
    queue_aux = search_queue_new(float_print, float_cmp);
    if (!queue_aux)
    {
        fprintf(stderr, "ERROR EN LA CREACION DE LA COLA AUXILIAR");
        search_queue_free(queue);
        fclose(f_in);
        return EXIT_FAILURE;
    }

    if (!fgets(line, MAX_LINE_LENGTH, f_in))
    {
        fprintf(stderr, "ERROR EN EL FGETS");
        search_queue_free(queue);
        search_queue_free(queue_aux);
        fclose(f_in);
        return EXIT_FAILURE;
    }

    n_data = atoi(line);
    if(n_data < 0){
        fprintf(stderr, "ERROR EN EL FORMATO DEL ARCHIVO");
        search_queue_free(queue_aux);
        search_queue_free(queue);
        fclose(f_in);
        return EXIT_FAILURE;
    }
    
    /*insertamos todas las notas en la cola*/
    for (i = 0; i < n_data; i++)
    {
        /*reserva de memoria para la nota*/
        grade = (float *)malloc(sizeof(float));
        if (!grade)
        {
            fprintf(stderr, "ERROR EN LA RESERVA DE MEMORIA PARA NOTA");
            search_queue_free(queue_aux);
            search_queue_free(queue);
            fclose(f_in);
            return EXIT_FAILURE;
        }
        /*Lectura de la nota en el archivo*/
        if (fscanf(f_in, "%f", grade) != 1)
        {
            fprintf(stderr, "ERROR EN EL FSCANF");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            fclose(f_in);
            return EXIT_FAILURE;
        }

        sum += (*grade);

        /*insercion de la nota en la cola*/
        if (search_queue_push(queue, (void *)grade) == ERROR)
        {
            fprintf(stderr, "ERROR EN EL PUSH");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            fclose(f_in);
            return EXIT_FAILURE;
        }
    }
    /*cerramos el archivo de lectura*/
    fclose(f_in);
    /*calculo de la media*/
    media = sum / n_data;

    /*a)imprimimos la cola entera*/
    printf("La cola con las notas en orden es: \n");
    search_queue_print(stdout, queue);

    /*b)imprimimos la media*/
    printf("La media es %.2f\n", media);

    /*c)imprimimos la mediana*/

    if (n_data % 2)
    {
        for (i = 0; i < halve(n_data); i++)
        {
            grade = search_queue_pop(queue);
            if (!grade)
            {
                fprintf(stderr, "ERROR EN EL POP PARA LA MEDIANA");
                search_queue_free(queue_aux);
                search_queue_free(queue);
                return EXIT_FAILURE;
            }
            if (search_queue_push(queue_aux, grade) == ERROR)
            {
                fprintf(stderr, "ERROR EN EL PUSH PARA LA MEDIANA");
                free(grade);
                search_queue_free(queue_aux);
                search_queue_free(queue);
                return EXIT_FAILURE;
            }
        }

        grade = search_queue_pop(queue);
        if (!grade)
        {
            fprintf(stderr, "ERROR EN EL POP PARA LA MEDIANA");
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return EXIT_FAILURE;
        }

        mediana = *(float *)grade;

        if (!search_queue_push(queue, grade))
        {
            fprintf(stderr, "ERROR EN EL POP y PUSH PARA LA MEDIANA");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return EXIT_FAILURE;
        }
    }
    else
    {
        for (i = 0; i < halve(n_data) - 1; i++)
        {
            grade = search_queue_pop(queue);
            if (!grade)
            {
                fprintf(stderr, "ERROR EN EL POP PARA LA MEDIANA");
                search_queue_free(queue_aux);
                search_queue_free(queue);
                return EXIT_FAILURE;
            }
            if (search_queue_push(queue_aux, grade) == ERROR)
            {
                fprintf(stderr, "ERROR EN EL PUSH PARA LA MEDIANA");
                free(grade);
                search_queue_free(queue_aux);
                search_queue_free(queue);
                return EXIT_FAILURE;
            }
        }

        grade = search_queue_pop(queue);
        if (!grade)
        {
            fprintf(stderr, "ERROR EN EL POP PARA LA MEDIANA");
            search_queue_free(queue);
            search_queue_free(queue_aux);
            return EXIT_FAILURE;
        }
        mediana = *(float *)grade;

        if (search_queue_push(queue_aux, grade) == ERROR)
        {
            fprintf(stderr, "ERROR EN EL PUSH PARA LA MEDIANA");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return EXIT_FAILURE;
        }

        grade = search_queue_pop(queue);
        if (!grade)
        {
            fprintf(stderr, "ERROR EN EL POP PARA LA MEDIANA");
            search_queue_free(queue);
            search_queue_free(queue_aux);
            return EXIT_FAILURE;
        }

        mediana += *(float *)grade;

        if (search_queue_push(queue_aux, grade) == ERROR)
        {
            fprintf(stderr, "ERROR EN EL PUSH PARA LA MEDIANA");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return EXIT_FAILURE;
        }

        mediana = halve(mediana);
    }

    /*Ahora devolvemos los elementos extraidos a la cola inicial*/
    while (search_queue_isEmpty(queue_aux) == FALSE)
    {
        grade = search_queue_pop(queue_aux);
        if (!grade)
        {
            fprintf(stderr, "ERROR EN EL POP PARA VACIAR LA COLA AUXILIAR");
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return EXIT_FAILURE;
        }
        if (search_queue_push(queue, grade) == ERROR)
        {
            fprintf(stderr, "ERROR EN EL PUSH PARA LA COLA PRINCIPAL");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return EXIT_FAILURE;
        }
    }

    printf("La mediana es: %.2f\n", mediana);

    /*d)imprimimos los tres mas pequeños*/
    printf("Los tres mas pequeños son: ");
    for (i = 0; i < TOP && search_queue_isEmpty(queue) == FALSE; i++)
    {
        grade = search_queue_pop(queue);
        if (!grade)
        {
            fprintf(stderr, "ERROR EN POP DE COLA");
            search_queue_free(queue);
            search_queue_free(queue_aux);
            return EXIT_FAILURE;
        }
        if (search_queue_push(queue_aux, grade) == ERROR)
        {
            fprintf(stderr, "ERROR EN EL PUSH A COLA AUXILIAR");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return EXIT_FAILURE;
        }

        printf("%.2f ", *(float *)grade);
    }

    /*Ahora devolvemos los elementos extraidos a la cola inicial*/
    while (search_queue_isEmpty(queue_aux) == FALSE)
    {
        grade = search_queue_pop(queue_aux);
        if (!grade)
        {
            fprintf(stderr, "ERROR EN EL POP PARA VACIAR LA COLA AUXILIAR");
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return EXIT_FAILURE;
        }
        if (search_queue_push(queue, grade) == ERROR)
        {
            fprintf(stderr, "ERROR EN EL PUSH PARA LA COLA PRINCIPAL");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return EXIT_FAILURE;
        }
    }

    /*e)imprimimos los tres mas grandes*/
    printf("\nLos tres mas grandes son: ");

    for (i = 0; i < TOP && search_queue_isEmpty(queue) == FALSE; i++)
    {
        grade = search_queue_popBack(queue);
        if (!grade)
        {
            fprintf(stderr, "ERROR EN POP DE COLA");
            search_queue_free(queue);
            search_queue_free(queue_aux);
            return EXIT_FAILURE;
        }
        
        printf("%.2f ", *(float *)grade);
        free(grade);
    }
    printf("\n");

    /*liberamos memoria*/
    search_queue_free(queue);
    search_queue_free(queue_aux);

    return EXIT_SUCCESS;
}