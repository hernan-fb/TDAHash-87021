#include "pa2m.h"
#include "src/hash.h"
#include "src/lista.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void test_A_crea_y_destruye_estructura_vacia()
{
	/* PRUEBAS CON LA ESTRUCTURA DE DATOS VACIA */
	pa2m_nuevo_grupo(
		"\nPRUEBA A: CREAR Y DESTRUIR LA ESTRUCTURA DE DATOS EN ESTUDIO\n");
	hash_t *hashecito = hash_crear(10);
	char elemento_inexistente = 'a';
	pa2m_afirmar(
		hashecito != NULL,
		"\tLa estructura de datos pudo ser creada.\t\t\t\t\t\thashecito != NULL");
	pa2m_afirmar(hash_cantidad(hashecito) == 0,
		     "\tLa estructura de datos está inicialmente "
		     "vacía.\t\t\t\t\thash_cantidad(hashecito) == 0");
	pa2m_afirmar(
		hash_quitar(hashecito, &elemento_inexistente) == NULL,
		"\tQuitar un elemento del t.a.d. vacio devuelve "
		"NULL.\t\t\t\thash_quitar(hashecito, &elemento_inexistente) == NULL");
	pa2m_afirmar(
		hash_obtener(hashecito, &elemento_inexistente) == NULL,
		"\tIntento obtener un elemento inexistente en el t.a.d. vacio y devuelve "
		"NULL.\thash_obtener(hashecito, &elemento_inexistente) == NULL");
	pa2m_afirmar(
		hash_contiene(hashecito, &elemento_inexistente) == false,
		"\tConsulto por un elemento inexistente en el t.a.d. vacio devuelve "
		"false.\t\thash_contiene(hashecito, &elemento_inexistente) == false");
	pa2m_afirmar(true, "\tpuedo destruir la estructura de datos recién "
			   "creada:\t\t\t\thash_destruir(hashecito)");
	hash_destruir(hashecito);
}

void test_B_agrega_y_quita_un_elemento()
{
	pa2m_nuevo_grupo(
		"\nPRUEBA B: AGREGA Y QUITA UN ELEMENTO EN LA ESTRUCTURA DE "
		"DATOS EN ESTUDIO\n");
	hash_t *hashecito = hash_crear(2);
	char elemento_a_insertar = '3';
	char mismo_elemento = '3';
	char otro_elemento = '4';
	char clave[] = "clave_identificatoria";
	char misma_clave[] = "clave_identificatoria";
	char otra_clave[] = "otra_clave_identificatoria";
	char **anterior = malloc(sizeof(char *));
	pa2m_afirmar(
		anterior != NULL,
		"\tSe pidió memoria exitosamente para el char** 'anterior'.\t\t\t\t\tanterior != NULL");
	pa2m_afirmar(
		hash_insertar(hashecito, clave, &elemento_a_insertar,
			      (void **)anterior) != NULL,
		"\tPuede ser agregado un 'unico_elemento' en el tda antes "
		"vacío.\t\t\t\t\thash_insertar(hashecito, clave, &elemento_a_insertar, anterior) != NULL");
	pa2m_afirmar(
		*anterior == NULL,
		"\tComo la clave no existía, y anterior no era nulo, se almacena NULL en *anterior'.\t\t*anterior == NULL");
	pa2m_afirmar(
		hash_cantidad(hashecito) == 1,
		"\t'unico_elemento' es el único elemento en el 't.d.a.' analizado, "
		"entonces:\t\t\thash_cantidad(hashecito) == 1");
	pa2m_afirmar(
		hash_contiene(hashecito, clave) == true,
		"\t'unico_elemento' es el único elemento  en el 't.d.a.' analizado, "
		"entonces:\t\t\thash_contiene(hashecito, clave) == true");
	pa2m_afirmar(
		hash_obtener(hashecito, clave) == &elemento_a_insertar,
		"\t'unico_elemento' es el único elemento  en el 't.d.a.' analizado, "
		"entonces:\t\t\thash_obtener(hashecito, clave) == elemento_a_insertar");
	pa2m_afirmar(
		hash_insertar(hashecito, clave, &otro_elemento,
			      (void **)anterior) == hashecito,
		"\tEl único elemento puede ser actualizado por un 'elemento_nuevo' en el tda, entonces.\t\thash_insertar(hashecito, clave, &elemento_a_insertar, anterior) != NULL");
	pa2m_afirmar(
		*anterior == &elemento_a_insertar,
		"\tComo la clave ya existía, y anterior no era nulo, guardo 'unico_elemento' en *anterior'.\t*anterior == elemento_a_insertar");
	pa2m_afirmar(
		hash_cantidad(hashecito) == 1,
		"\t'elemento_nuevo' es el único elemento en el 't.d.a.' analizado, "
		"entonces:\t\t\thash_cantidad(hashecito) == 1");
	pa2m_afirmar(
		hash_contiene(hashecito, clave) == true,
		"\t'elemento_nuevo' es el único elemento  en el 't.d.a.' analizado, "
		"entonces:\t\t\thash_contiene(hashecito, clave) == true");
	pa2m_afirmar(
		hash_obtener(hashecito, clave) == &otro_elemento,
		"\t'elemento_nuevo' es el único elemento  en el 't.d.a.' analizado, "
		"entonces:\t\t\thash_obtener(hashecito, clave) == otro_elemento");
	pa2m_afirmar(
		hash_obtener(hashecito, clave) != &mismo_elemento,
		"\tno se almacenan copias del valor, "
		"entonces:\t\t\t\t\t\t\thash_obtener(hashecito, clave) != mismo_elemento");
	pa2m_afirmar(
		hash_obtener(hashecito, misma_clave) == &otro_elemento,
		"\tse almacenan copias de la clave, por lo que buscando el mismo texto desde otra variable, "
		"obtengo: hash_obtener(hashecito, misma_clave) == otro_elemento");
	pa2m_afirmar(
		hash_obtener(hashecito, otra_clave) == NULL,
		"\t'elemento_nuevo' es el único elemento  en el 't.d.a.' analizado, "
		"entonces:\t\t\thash_obtener(hashecito, otra_clave) == NULL");
	pa2m_afirmar(
		hash_quitar(hashecito, clave) == &otro_elemento,
		"\t'hash_quitar' devuelve el mismo elemento que el insertado previamente, "
		"entonces:\t\thash_quitar(hashecito, clave) == otro_elemento");
	pa2m_afirmar(
		hash_cantidad(hashecito) == 0,
		"\t'elemento_nuevo' era el único elemento en el 't.d.a.' analizado, "
		"entonces:\t\t\thash_cantidad(hashecito) == 0");
	pa2m_afirmar(
		hash_quitar(hashecito, clave) == NULL,
		"\t'hash_quitar' ya no tiene el elemento insertado previamente, "
		"entonces:\t\t\t\thash_quitar(hashecito, clave) == NULL");
	hash_destruir(hashecito);
	free(anterior);
}

void test_C_agrega_y_quita_pocos_elementos_distintos()
{
	pa2m_nuevo_grupo(
		"\nPRUEBA C: AGREGA Y QUITA POCOS ELEMENTOS DEL MISMO TIPO "
		"EN LA ESTRUCTURA DE DATOS EN ESTUDIO\n");

	/* Crear el hash, prueba inicial*/
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~ Crea el hash, prueba inicial ~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	size_t capacidad_inicial = 10;
	hash_t *hashecito = hash_crear(capacidad_inicial);

	char *vector_patentes[] = { "AC123BD", "OPQ976",  "A421ACB", "AA442CD",
				    "AC152AD", "DZE443",  "AA436BA", "QDM443",
				    "BD123AC", "CD442AA", "PQO697" };

	char *vector_descripciones[] = { "Auto de Mariano",  "Auto de Lucas",
					 "Moto de Manu",     "Auto de Guido",
					 "Auto de Agustina", "Auto de Jonathan",
					 "Auto de Gonzalo",  "Auto de Daniela",
					 "Auto de Pablo",    "Auto de Micaela",
					 "Auto de Juan" };

	char *vector_patentes_que_cambian_duenio[] = { "AC152AD", "DZE443" };

	char *vector_nuevas_descripciones[] = { "Auto de Agustina otra vez",
						"Auto de Jonathan otra vez" };

	pa2m_afirmar(hash_cantidad(hashecito) == 0,
		     "\tLa estructura de datos está "
		     "vacía.\t\t\t\t\t\thash_cantidad(hashecito) == 0");

	char buffer[300];
	bool validacion = true;
	char **anterior = malloc(sizeof(char *));
	/* Prueba Insertar elementos */
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~ Prueba Insertar varios elementos ~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	for (size_t i = 0; i < capacidad_inicial; i++) {
		sprintf(buffer,
			"\tinserto elemento nro: %zu, clave: %s, descripción: %s\n",
			i + 1, vector_patentes[i], vector_descripciones[i]);
		validacion = hash_insertar(hashecito, vector_patentes[i],
					   vector_descripciones[i],
					   (void **)anterior) == hashecito;
		pa2m_afirmar(validacion, buffer);
		sprintf(buffer,
			"\tcomo la clave: %s no se repite y anterior != NULL, entonces *anterior == NULL\n",
			vector_patentes[i]);
		pa2m_afirmar(*anterior == NULL, buffer);
	}

	/* Pruebas pos-inserción de varios clave-valor*/
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~ Pruebas pos-inserción de varios clave-valor ~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	pa2m_afirmar(
		hash_cantidad(hashecito) == 10,
		"\tla cantidad de elementos en el 't.d.a.' corresponde a la cantidad insertada, "
		"entonces:\t\t\thash_cantidad(hashecito) == 10");

	validacion = true;
	char *auxiliar = NULL;
	for (size_t i = 0; i < capacidad_inicial; i++) {
		auxiliar = hash_obtener(hashecito, vector_patentes[i]);

		validacion = auxiliar == vector_descripciones[i];

		sprintf(buffer,
			"\tBuscar el elemento nro: %zu, me brinda la descripción esperada y de hecho comparo los punteros y son iguales.\n",
			i + 1);

		pa2m_afirmar(validacion, buffer);
	}

	/* Prueba redimensión interna del hash*/
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~ Prueba redimensión interna del hash ~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	pa2m_afirmar(
		hash_insertar(hashecito, vector_patentes[capacidad_inicial],
			      vector_descripciones[capacidad_inicial],
			      (void **)anterior) == hashecito,
		"\tHaber insertado un par clave-valor produce internamente la redimensión del hash. Esto se realiza satisfactoriamente");

	validacion = true;
	for (size_t i = 0; i < capacidad_inicial + 1; i++) {
		sprintf(buffer,
			"\tHaber redimensionado no afecta los pares guardados previamente. El elemento nro: %zu, sigue estando presente en el hash.\n",
			i + 1);

		validacion = hash_contiene(hashecito, vector_patentes[i]) ==
			     true;

		pa2m_afirmar(validacion, buffer);
	}

	/* Prueba actualizacion de clave-valor*/
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~ Prueba actualizacion de clave-valor ~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	for (size_t i = 0; i < 2; i++) {
		sprintf(buffer,
			"\tInsertar un par clave-valor con una clave existente en el hash, actualiza el par de esa clave. Actualizo la clave: %s, con la nueva descripción: %s.\n",
			vector_patentes_que_cambian_duenio[i],
			vector_nuevas_descripciones[i]);
		validacion =
			(hash_insertar(hashecito,
				       vector_patentes_que_cambian_duenio[i],
				       vector_nuevas_descripciones[i],
				       (void **)anterior) == hashecito);
		pa2m_afirmar(validacion, buffer);

		sprintf(buffer,
			"\ty como anterior != NULL, *anterior ahora apunta a la descripción inicial.\n");
		validacion = (*anterior == vector_descripciones[i + 4]);
		pa2m_afirmar(validacion, buffer);

		sprintf(buffer,
			"\ty también se verifica que hash_obtener de la clave %s devuelve el nuevo texto: %s\n",
			vector_patentes_que_cambian_duenio[i],
			vector_nuevas_descripciones[i]);
		validacion =
			(hash_obtener(hashecito,
				      vector_patentes_que_cambian_duenio[i]) ==
			 vector_nuevas_descripciones[i]);
		pa2m_afirmar(validacion, buffer);
	}

	/* Prueba eliminar elementos */
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~ Prueba eliminar elementos ~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	for (size_t i = 0; i < capacidad_inicial + 1; i++) {
		sprintf(buffer,
			"\tAhora quito el par clave-valor que le corresponde a la clave %s, y obtengo la descripcion correspondiente %s\n",
			vector_patentes[i],
			(i == 4 || i == 5) ?
				vector_nuevas_descripciones[i - 4] :
				vector_descripciones[i]);
		validacion = (hash_quitar(hashecito, vector_patentes[i]) ==
			      ((i == 4 || i == 5) ?
				       vector_nuevas_descripciones[i - 4] :
				       vector_descripciones[i]));
		pa2m_afirmar(validacion, buffer);

		sprintf(buffer,
			"\ty ahora el tamaño del hash se redujo en una unidad\t\t\thash_cantidad(hashecito) == %zu\n",
			capacidad_inicial - i);
		validacion =
			(hash_cantidad(hashecito) == capacidad_inicial - i);
		pa2m_afirmar(validacion, buffer);

		sprintf(buffer,
			"\ty también se verifica que hash_obtener de la clave %s devuelve NULL\n",
			vector_patentes[i]);
		validacion =
			(hash_obtener(hashecito, vector_patentes[i]) == NULL);
		pa2m_afirmar(validacion, buffer);
	}

	/* Finalización*/
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~ Prueba Destruccion t.d.a. ~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	free(anterior);
	hash_destruir(hashecito);
	pa2m_afirmar(
		true,
		"\tpara finalizar, teniendo el hash 0 elementos, destruyo la estructura\n");
}

int main()
{
	test_A_crea_y_destruye_estructura_vacia();
	test_B_agrega_y_quita_un_elemento();
	test_C_agrega_y_quita_pocos_elementos_distintos();
	return pa2m_mostrar_reporte();
}
