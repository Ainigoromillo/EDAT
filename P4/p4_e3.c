#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "search_queue.h"
#include "file_utils.h"

#define TOP 3

#define MAX_LINE_LENGTH 1000
#define EXTENSION_LENGTH 4
#define INPUT_EXTENSION ".txt"

int main(int argc, const char *argv[])
{
    FILE *f_in = NULL;
    float *grade = NULL, sum = 0, media, mediana;
    SearchQueue *queue = NULL, *queue_aux = NULL;
    int n_data, i;
    char line[MAX_LINE_LENGTH];

    if (argc != 2)
    {
        printf("Usage: %s input_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((strcmp(argv[1] + (strlen(argv[1]) - EXTENSION_LENGTH), INPUT_EXTENSION)))
    {
        printf("Input file format must be: "
               "file%s"
               "",
               INPUT_EXTENSION);
        return 1;
    }

    f_in = fopen(argv[1], "r");
    if (!f_in)
    {
        printf("ERROR EN OPEN DEL FICHERO DE ENTRADA");
        return 1;
    }

    queue = search_queue_new(float_print, float_cmp);
    if (!queue)
    {
        printf("ERROR EN LA CREACION DE LA COLA");
        fclose(f_in);
        return 1;
    }
    queue_aux = search_queue_new(float_print, float_cmp);
    if (!queue_aux)
    {
        printf("ERROR EN LA CREACION DE LA COLA AUXILIAR");
        search_queue_free(queue);
        fclose(f_in);
        return 1;
    }

    if (!fgets(line, MAX_LINE_LENGTH, f_in))
    {
        printf("ERROR EN EL FGETS");
        search_queue_free(queue);
        search_queue_free(queue_aux);
        fclose(f_in);
        return 1;
    }

    n_data = atoi(line);
    if(n_data < 0){
        printf("ERROR EN EL FORMATO DEL ARCHIVO");
        search_queue_free(queue_aux);
        search_queue_free(queue);
        fclose(f_in);
        return 1;
    }
    
    /*insertamos todas las notas en la cola*/
    for (i = 0; i < n_data; i++)
    {
        /*reserva de memoria para la nota*/
        grade = (float *)malloc(sizeof(float));
        if (!grade)
        {
            printf("ERROR EN LA RESERVA DE MEMORIA PARA NOTA");
            search_queue_free(queue_aux);
            search_queue_free(queue);
            fclose(f_in);
            return 1;
        }
        /*Lectura de la nota en el archivo*/
        if (fscanf(f_in, "%f", grade) != 1)
        {
            printf("ERROR EN EL FSCANF");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            fclose(f_in);
            return 1;
        }

        sum += (*grade);

        /*insercion de la nota en la cola*/
        if (search_queue_push(queue, (void *)grade) == ERROR)
        {
            printf("ERROR EN EL PUSH");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            fclose(f_in);
            return 1;
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
        for (i = 0; i < n_data / 2; i++)
        {
            grade = search_queue_pop(queue);
            if (!grade)
            {
                printf("ERROR EN EL POP PARA LA MEDIANA");
                search_queue_free(queue_aux);
                search_queue_free(queue);
                return 1;
            }
            if (search_queue_push(queue_aux, grade) == ERROR)
            {
                printf("ERROR EN EL PUSH PARA LA MEDIANA");
                free(grade);
                search_queue_free(queue_aux);
                search_queue_free(queue);
                return 1;
            }
        }

        grade = search_queue_pop(queue);
        if (!grade)
        {
            printf("ERROR EN EL POP PARA LA MEDIANA");
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return 1;
        }

        mediana = *(float *)grade;

        if (!search_queue_push(queue, grade))
        {
            printf("ERROR EN EL POP y PUSH PARA LA MEDIANA");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return 1;
        }
    }
    else
    {
        for (i = 0; i < n_data / 2 - 1; i++)
        {
            grade = search_queue_pop(queue);
            if (!grade)
            {
                printf("ERROR EN EL POP PARA LA MEDIANA");
                search_queue_free(queue_aux);
                search_queue_free(queue);
                return 1;
            }
            if (search_queue_push(queue_aux, grade) == ERROR)
            {
                printf("ERROR EN EL PUSH PARA LA MEDIANA");
                free(grade);
                search_queue_free(queue_aux);
                search_queue_free(queue);
                return 1;
            }
        }

        grade = search_queue_pop(queue);
        if (!grade)
        {
            printf("ERROR EN EL POP PARA LA MEDIANA");
            search_queue_free(queue);
            search_queue_free(queue_aux);
            return 1;
        }
        mediana = *(float *)grade;

        if (search_queue_push(queue_aux, grade) == ERROR)
        {
            printf("ERROR EN EL PUSH PARA LA MEDIANA");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return 1;
        }

        grade = search_queue_pop(queue);
        if (!grade)
        {
            printf("ERROR EN EL POP PARA LA MEDIANA");
            search_queue_free(queue);
            search_queue_free(queue_aux);
            return 1;
        }

        mediana += *(float *)grade;

        if (search_queue_push(queue_aux, grade) == ERROR)
        {
            printf("ERROR EN EL PUSH PARA LA MEDIANA");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return 1;
        }

        mediana = mediana / 2;
    }

    /*Ahora devolvemos los elementos extraidos a la cola inicial*/
    while (search_queue_isEmpty(queue_aux) == FALSE)
    {
        grade = search_queue_pop(queue_aux);
        if (!grade)
        {
            printf("ERROR EN EL POP PARA VACIAR LA COLA AUXILIAR");
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return 1;
        }
        if (search_queue_push(queue, grade) == ERROR)
        {
            printf("ERROR EN EL PUSH PARA LA COLA PRINCIPAL");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return 1;
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
            printf("ERROR EN POP DE COLA");
            search_queue_free(queue);
            search_queue_free(queue_aux);
            return 1;
        }
        if (search_queue_push(queue_aux, grade) == ERROR)
        {
            printf("ERROR EN EL PUSH A COLA AUXILIAR");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return 1;
        }

        printf("%.2f ", *(float *)grade);
    }

    /*Ahora devolvemos los elementos extraidos a la cola inicial*/
    while (search_queue_isEmpty(queue_aux) == FALSE)
    {
        grade = search_queue_pop(queue_aux);
        if (!grade)
        {
            printf("ERROR EN EL POP PARA VACIAR LA COLA AUXILIAR");
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return 1;
        }
        if (search_queue_push(queue, grade) == ERROR)
        {
            printf("ERROR EN EL PUSH PARA LA COLA PRINCIPAL");
            free(grade);
            search_queue_free(queue_aux);
            search_queue_free(queue);
            return 1;
        }
    }

    /*e)imprimimos los tres mas grandes*/
    printf("\nLos tres mas grandes son: ");

    for (i = 0; i < TOP && search_queue_isEmpty(queue) == FALSE; i++)
    {
        grade = search_queue_popBack(queue);
        if (!grade)
        {
            printf("ERROR EN POP DE COLA");
            search_queue_free(queue);
            search_queue_free(queue_aux);
            return 1;
        }
        
        printf("%.2f ", *(float *)grade);
        free(grade);
    }

    /*liberamos memoria*/
    search_queue_free(queue);
    search_queue_free(queue_aux);

    return 0;
}