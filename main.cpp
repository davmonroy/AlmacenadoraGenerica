#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string.h>
#include "rutinas.h"
#include "mantenimiento.h"

void mostrar_f(facturas *t) {
	detalle *d = t->abajo;
	printf("\n**************************************************************");
	printf("\n**_____________________FACTURA %s_________________________**", t->num);
	printf("\n**                Sucursal: %s                              ", t->sucursal);
	printf("\n**                 Fecha: %s                                ", t->fecha);
	printf("\n**          Nombre de cliente: %s                           ", t->cliente);
	printf("\n**        Total a pagar: Bs. %i                              ", t->total);
	printf("\n**__________________________________________________________**");
	printf("\n\n**   Detalle de factura:                                    **");
	while (d) {
		printf("\n\n**           Lote: %s                                         ", d->lote);
		printf("\n**           Unidades: %i                                        ", d->unidades);
		printf("\n**           Precio: Bs. %i (Por unidad)                         ", d->precio);
		printf("\n**           Subtotal: Bs. %i                                    ", (d->precio * d->unidades));
		printf("\n\n**                                                             ");
		d = d->abajo;
	}
	printf("\n**************************************************************\n\n");
}

void factura(facturas **f, sucursales **s, clientes **c, lotes**l, rubros **r) {
	facturas *t = new facturas;
	detalle *d = new detalle, *dt = new detalle;
	facturas *aux = *f, *aux2 = *f;
	lotes *lt = *l;
	int sale = -1, ag = -1, cantidad, repe, contfac = 0; // cantotal = 0, 
	long total = 0; // subtotal;
	char campo[20], sucursal2[20], rubro[20], subcat[20], nf[5], codigo[5], codigo_nuevo[5]; // En codigo se guardara el valor numerico de la factura nueva (antes de ser anexado a 'F') 

	while (aux2) {
		aux2 = aux2->sig;
		contfac++;
	}
	contfac++;
	if (contfac < 10) {
		strcpy(codigo, _itoa(contfac, nf, 10));
		char f[5] = { 'F', '0','0', '\0' };
		strcpy(codigo_nuevo, strcat(f, codigo));
	}
	else if (contfac >= 10) {
		strcpy(codigo, _itoa(contfac, nf, 10));
		char f[5] = { 'F', '0', '\0' };
		strcpy(codigo_nuevo, strcat(f, codigo));
	}
	strcpy(t->num, codigo_nuevo);

	printf("\n\t Cliente: ");
	fflush(stdin);
	scanf(" %[^\n]", &campo);
	if (!(busca_c(c, campo))) {
		printf("\n\tNo existe cliente %s en el sistema\n\n", campo);
		agrega_c(c);
	}
	else strcpy(t->cliente, campo);


	do {
		printf("\n\t Sucursal: ");
		fflush(stdin);
		scanf(" %[^\n]", &campo);
		if (!(busca_s(s, campo))) printf("\n\tNo existe sucursal %s en el sistema\n\n", campo);
	} while (!(busca_s(s, campo)));
	strcpy(t->sucursal, campo);

	printf("\n\t Fecha (dd/mm/aaaa): ");
	fflush(stdin);
	scanf(" %[^\n]", &campo);
	strcpy(t->fecha, campo);

	t->sig = NULL;
	t->abajo = NULL;

	t->abajo = dt;


	repe = 1;
	//////  AQUI INICIA AGREGAR DETALLE
	system("cls");
	rubros *rol;
	do {
		rol = *r;
		printf("\n\t Indique rubro de subcategoria que desea: ( ");
		while (rol) {
			printf("%s ", rol->nombre);
			rol = rol->sig;
		}
		printf(")\n");
		fflush(stdin);
		scanf(" %[^\n]", &campo);
		if (!(busca_r(r, campo))) printf("\n\tNo existe rubro %s en el sistema\n\n", campo);
	} while (!(busca_r(r, campo)));
	strcpy(rubro, campo);


	lotes *auxl;
	do {
		do {
			printf("\n\t Indique subcategoria que desea: ( ");
			rol = *r;
			sub *su;
			while (rol) {
				su = rol->abajo;
				if (strcmp(rol->nombre, rubro) == 0) {
					while (su) {
						printf("%s ", su->tipo);
						su = su->abajo;
					}
				}
				rol = rol->sig;
			}
			printf(")\n");
			fflush(stdin);
			scanf(" %[^\n]", &campo);
			if (!(busca_sub(r, campo, rubro))) printf("\n\tNo existe subcategoria %s para el rubro %s\n\n", campo, rubro);
		} while (!(busca_sub(r, campo, rubro)));
		strcpy(subcat, campo);



		printf("\n\n\t Lotes de %s\n", subcat);

		auxl = *l;
		while (auxl) {
			if (strcmp(subcat, auxl->sub) == 0) {
				printf("\n\t Lote: %s", auxl->lote);
				printf("\n\t Disponible: %i", auxl->exist);
				printf("\n\t Sucursal: %s\n", auxl->sucursal);
				sale = 1;
			}
			auxl = auxl->sig;
		}
		if (sale != 1) {
			printf("\n\t Por los momentos no hay ningun lote de %s\n", subcat);
			sale = -1;
		}
	} while (sale != 1);

	do {
		printf("\n\tIndique la sucursal en la que quiere hacer la compra: ");
		fflush(stdin);
		scanf(" %[^\n]", &campo);
		strcpy(sucursal2, campo);
		system("cls");

		sale = -1;
		auxl = *l;
		while (auxl) {
			if ((strcmp(sucursal2, auxl->sucursal) == 0) && (strcmp(subcat, auxl->sub) == 0)) {
				printf("\n\t Sucursal: %s\n", auxl->sucursal);
				printf("\n\t Lote: %s", auxl->lote);
				printf("\n\t Disponible: %i\n", auxl->exist);
				sale = 1;
				strcpy(d->lote, auxl->lote);
				d->precio = auxl->costo + ((auxl->costo) * 0.3);
				if (auxl->exist == 0) {
					printf("\n\t No tenemos disponible %s\n\n", auxl->sub);
					return;
				}
			}
			auxl = auxl->sig;
		}
		if (sale != 1) {
			printf("\n\t Seleccion invalida\n\n");
		}
	} while (sale != 1);

	do {
		sale = -1;
		printf("\n\t Indique cantidad de unidades que desea comprar: ");
		scanf("%i", &cantidad);

		auxl = *l;
		while (auxl) {
			if ((strcmp(sucursal2, auxl->sucursal) == 0) && (strcmp(subcat, auxl->sub) == 0)) {
				if (cantidad > auxl->exist) {
					printf("No tenemos esa cantidad en el almacen, puede comprar maximo %i", auxl->exist);
				}
				else {
					sale = 1;
					auxl->exist = auxl->exist - cantidad;
					break;
				}

			}
			auxl = auxl->sig;
		}
	} while (sale != 1);

	d->unidades = cantidad;

	t->abajo = d;
	d->abajo = NULL;


	system("cls");
	printf("\n\tSr. %s, ha pedido %i unidades de %s (%s)", t->cliente, cantidad, subcat, t->sucursal);

	printf("\n\n\t1. Otro pedido");
	printf("\n\n\t2. Orden completada (Ver factura)");
	printf("\n\n\t3. Cancelar (Descartar todo)\n\n");
	scanf("%i", &repe);

	//////////////////////// Los cambios que se hayan hecho hasta aqui, deben hacerse de igual forma debajo   ////////////////////////////////////////////////////

	// Este while proximo es para seguir agregando detalle a la factura
	if (repe == 1) {
		while (repe = 1) {
			d = new detalle;
			system("cls");
			rubros *rol;
			do {
				rol = *r;
				printf("\n\t Indique rubro de subcategoria que desea: ( ");
				while (rol) {
					printf("%s ", rol->nombre);
					rol = rol->sig;
				}
				printf(")\n");
				fflush(stdin);
				scanf(" %[^\n]", &campo);
				if (!(busca_r(r, campo))) printf("\n\tNo existe rubro %s en el sistema\n\n", campo);
			} while (!(busca_r(r, campo)));
			strcpy(rubro, campo);

			rol = *r;
			sub *su;
			do {
				printf("\n\t Indique subcategoria que desea: ( ");

				while (rol) {
					su = rol->abajo;
					if (strcmp(rol->nombre, rubro) == 0) {
						while (su) {
							printf("%s ", su->tipo);
							su = su->abajo;
						}
					}
					rol = rol->sig;
				}
				printf(")\n");
				fflush(stdin);
				scanf(" %[^\n]", &campo);
				if (!(busca_sub(r, campo, rubro))) printf("\n\tNo existe subcategoria %s para el rubro %s\n\n", campo, rubro);
			} while (!(busca_sub(r, campo, rubro)));
			strcpy(subcat, campo);

			lotes *auxl;
			do {
				printf("\n\n\t Lotes de %s\n", subcat);

				auxl = *l;
				while (auxl) {
					if (strcmp(subcat, auxl->sub) == 0) {
						printf("\n\t Lote: %s", auxl->lote);
						printf("\n\t Disponible: %i", auxl->exist);
						printf("\n\t Sucursal: %s\n", auxl->sucursal);
						sale = 1;
					}
					auxl = auxl->sig;
				}
				if (sale != 1) {
					printf("\n\t Por los momentos no hay ningun lote de %s\n", subcat);
					sale = 1;
				}
			} while (sale != 1);

			do {
				printf("\n\tIndique la sucursal en la que quiere hacer la compra: ");
				fflush(stdin);
				scanf(" %[^\n]", &campo);
				strcpy(sucursal2, campo);
				system("cls");

				sale = -1;
				auxl = *l;
				while (auxl) {
					if ((strcmp(sucursal2, auxl->sucursal) == 0) && (strcmp(subcat, auxl->sub) == 0)) {
						printf("\n\t Sucursal: %s\n", auxl->sucursal);
						printf("\n\t Lote: %s", auxl->lote);
						printf("\n\t Disponible: %i\n", auxl->exist);
						sale = 1;
						strcpy(d->lote, auxl->lote);
						d->precio = auxl->costo + ((auxl->costo) * 0.3);
						if (auxl->exist == 0) {
							printf("\n\t No tenemos disponible %s\n\n", auxl->sub);
							return;
						}
					}
					auxl = auxl->sig;
				}
				if (sale != 1) {
					printf("\n\t Seleccion invalida\n\n");
				}
			} while (sale != 1);

			do {
				sale = -1;
				printf("\n\t Indique cantidad de unidades que desea comprar: ");
				scanf("%i", &cantidad);

				auxl = *l;
				while (auxl) {
					if ((strcmp(sucursal2, auxl->sucursal) == 0) && (strcmp(subcat, auxl->sub) == 0)) {
						if (cantidad > auxl->exist) {
							printf("No tenemos esa cantidad en el almacen, puede comprar maximo %i", auxl->exist);
						}
						else {
							sale = 1;
							auxl->exist = auxl->exist - cantidad;
							break;
						}

					}
					auxl = auxl->sig;
				}
			} while (sale != 1);

			d->unidades = cantidad;

			dt = t->abajo;
			while ((dt) && (dt->abajo))
				dt = dt->abajo;
			dt->abajo = d;
			d->abajo = NULL;


			system("cls");
			printf("\n\tSr. %s, ha pedido %i unidades de %s (%s)", t->cliente, cantidad, subcat, t->sucursal);

			printf("\n\n\t1. Otro pedido");
			printf("\n\n\t2. Orden completada (Ver factura)");
			printf("\n\n\t3. Cancelar (Descartar todo)\n\n");
			scanf("%i", &repe);
			if (repe != 1) break;
		}
	}

	if (repe == 2) {
		aux = *f;
		while ((aux) && (aux->sig))
			aux = aux->sig;
		aux->sig = t;
		dt = t->abajo;

		while (dt) {
			total += (dt->precio) * dt->unidades;
			dt = dt->abajo;
		}
		t->total = total;
		system("cls");
		mostrar_f(t);
	}

	else if (repe == 3) {
		delete t;
		return;
	}

}

void mostrar_l(lotes *t, char x[]) {
	lotes *p = t;
	int cont = 0;
	while (p) {
		if (!(strcmp(x, p->lote))) {
			cont++;
			printf("\n**************************************************************");
			printf("\n**_____________________LOTE %s_________________________**", p->lote);
			printf("\n**                Sucursal: %s                              ", p->sucursal);
			printf("\n**                 Rubro: %s                            ", p->rubro);
			printf("\n**	      Subrubro: %s                           ", p->sub);
			printf("\n**        Total unidades inicial: %i                         ", p->total);
			printf("\n**        Unidades en existencia: %i                         ", p->exist);
			printf("\n**        Peso del producto: %f                         ", p->peso);
			printf("\n**                 Costo: %ld                         ", p->costo);
			printf("\n**************************************************************\n\n");
			break;
		}
		else p = p->sig;
	}
	if (!cont) printf("El numero de lote %s no existe\n", x);
}

void cons2(facturas *t, char x[]) {
	facturas *p = t;
	detalle *det;
	long cont = 0;

	printf("\n\t Todos los detalles de %s: \n", x);
	while (t) {
		if (strcmp(x, t->cliente) == 0) {
			detalle *d = t->abajo;
			printf("\n**************************************************************");
			printf("\n**_____________________FACTURA %s_________________________**", t->num);
			printf("\n**                Sucursal: %s                              ", t->sucursal);
			printf("\n**                 Fecha: %s                                ", t->fecha);
			printf("\n**          Nombre de cliente: %s                           ", t->cliente);
			printf("\n**        Total a pagar: Bs. %i                              ", t->total);
			printf("\n**__________________________________________________________**");
			printf("\n\n**   Detalle de factura:                                    **");
			while (d) {
				printf("\n\n**           Lote: %s                                         ", d->lote);
				printf("\n**           Unidades: %i                                        ", d->unidades);
				printf("\n**           Precio: Bs. %i (Por unidad)                         ", d->precio);
				printf("\n**           Subtotal: Bs. %i                                    ", (d->precio * d->unidades));
				printf("\n\n**                                                             ");
				d = d->abajo;
			}
			printf("\n**************************************************************\n\n");
			cont += t->total;
		}
		t = t->sig;
	}
	printf("\n\t\t TOTAL: Bs. %i\n\n", cont);
}

void cons4(lotes *t, rubros *r, char x[]) { //REVISAR SOLO LEE GRANOS (O SEA EL PRIMERO)
	lotes *p = t;
	rubros *s = r;
	int u = 0, cont = 0;
	long c = 0;
	while (s) {
		u = 0;
		c = 0;
		while (p) {
			if (!(strcmp(x, p->sucursal))) {
				cont++;
				if (!(strcmp(s->nombre, p->rubro))) {
					u += p->exist;
					c += p->costo;
				}
			}
			p = p->sig;
		}
		if (u) {
			printf("n\En la sucursal %s, hay en existencia:", x);
			printf("\n %s: %i y su total de costo es %ld\n", s->nombre, u, c);
		}
		s = s->sig;
	}
	if (!cont) printf("No existe esta sucursal %s", x);
}

void cons7(lotes *t, char x[]) {
	lotes *p = t;
	int u = 0, cont = 0;
	long c = 0;
	while (p) {
		if (!(strcmp(x, p->rubro))) {
			u += p->exist;
			c += p->costo;
			cont++;
			printf("\n\t   Lote: %s\n", p->lote);
			printf("\t   Sucursal: %s\n", p->sucursal);
			printf("\t   Subcategoria: %s\n", p->sub);
			printf("\t   Existencia: %i\n", p->exist);
			printf("\t   Costo: %ld \n", p->costo);
			printf("\n");
		}
		p = p->sig;
	}
	if (!cont)
		printf("No hay lotes de este rubro:  %s\n", x);

	if (u)
		printf("\n Del rubro %s: hay en existencia %i y su total de costo es %ld\n\n", x, u, c);
}

int main() {
	int op = -1, op2 = -1, op3 = -1, sale;
	char persona[25], campo[20], val[20], val2[20];
	char sucur[25], rubro[20], subcat[20];
	lotes *lot = NULL;
	lot = new lotes;


	sucursales *suc = NULL;
	suc = new sucursales;
	clientes *cli = NULL;
	cli = new clientes;
	facturas *fac = NULL;
	fac = new facturas;
	rubros *rub = NULL;
	rub = new rubros;


	leerLotes(&lot);
	leerClientes(&cli);
	leerSucursales(&suc);
	leerFacturas(&fac);
	leerDetalles(&fac);
	leerRubros(&rub);
	leerSubrubros(&rub);

	lotes *auxlot = lot;
	sucursales *auxsuc = suc;
	clientes *auxcli = cli;
	facturas *auxfac = fac;
	rubros *auxrub = rub;
	detalle *auxfac2;
	sub *auxrub2;

	//        AUTORES: David Monroy - Carolina Patiño				

	while (op) {
		system("cls");
		printf("\n\t	Proyecto MONROY - PATINO \n\n");
		printf("\n\t	MENU PRINCIPAL\n");
		printf("\n\t1. Mantenimiento");
		printf("\n\t2. Crear factura");
		printf("\n\t3. Consultas");
		printf("\n\n\t0. Salir");
		printf("\n\n\tIndique opcion: ");
		scanf("%i", &op);
		system("cls");

		switch (op) {
		case 1:

			printf("\n\t	MANTENIMIENTO\n");
			printf("\n\t1. Agregar lote");
			printf("\n\t2. Modificar lote");
			printf("\n\t3. Validar lote");
			printf("\n\t4. Eliminar lote\n");

			printf("\n\t5. Agregar sucursal");
			printf("\n\t6. Modificar sucursal");
			printf("\n\t7. Validar sucursal");
			printf("\n\t8. Eliminar sucursal\n");

			printf("\n\t9. Agregar cliente");
			printf("\n\t10. Modificar cliente");
			printf("\n\t11. Validar cliente");
			printf("\n\t12. Eliminar cliente\n");

			printf("\n\t13. Agregar rubro");
			printf("\n\t14. Modificar rubro");
			printf("\n\t15. Validar rubro");
			printf("\n\t16. Eliminar rubro\n");

			printf("\n\t17. Agregar subcategoria");
			printf("\n\t18. Modificar subcategoria");
			printf("\n\t19. Validar subcategoria");
			printf("\n\t20. Eliminar subcategoria\n");

			printf("\n\t21. Mostrar lotes en sistemaa");
			printf("\n\t22. Mostrar clientes en sistema");
			printf("\n\t23. Mostrar sucursales en sistema");
			printf("\n\t24. Mostrar rubros en sistema\n");

			printf("\n\n\t0. Salir");

			printf("\n\n\tIndique opcion: ");
			scanf("%i", &op2);
			system("cls");

			switch (op2) {
			case 1:	agrega_l(&lot, &suc, &rub);
				break;
			case 2:	modifica_l(&lot, &suc, &rub);
				break;
			case 3: printf("\n\t Indique lote a validar: ");
				scanf(" %[^\n]", &(campo));
				fflush(stdin);
				strcpy(val, campo);
				auxlot = lot;
				if (busca_l(&auxlot, val))
					printf("\n\t El lote %s si esta registrado\n\n", val);
				else
					printf("\n\t El lote %s no esta registrado\n\n", val);
				break;
			case 4:	eliminar_l(&lot);
				break;
			case 5: agrega_s(&suc);
				break;
			case 6: modifica_s(&suc, &lot, &fac);
				break;
			case 7: printf("\n\t Indique sucursal a validar: ");
				scanf(" %[^\n]", &(campo));
				fflush(stdin);
				strcpy(val, campo);
				auxsuc = suc;
				if (busca_s(&auxsuc, val))
					printf("\n\t La sucursal %s si esta registrads\n\n", val);
				else
					printf("\n\t La sucursal %s no esta registrada\n\n", val);
				break;
			case 8: eliminar_s(&suc, &fac, &lot);
				break;
			case 9: agrega_c(&cli);
				break;
			case 10: modifica_c(&cli, &fac);
				break;
			case 11: printf("\n\t Indique cliente a validar: ");
				scanf(" %[^\n]", &(campo));
				fflush(stdin);
				strcpy(val, campo);
				auxcli = cli;
				if (busca_c(&auxcli, val))
					printf("\n\t El cliente %s si esta registrado\n\n", val);
				else
					printf("\n\t El cliente %s no esta registrado\n\n", val);
				break;
			case 12: eliminar_c(&cli, &fac);
				break;
			case 13: agrega_r(&rub);
				break;
			case 14: modifica_r(&rub, &lot);
				break;
			case 15: printf("\n\t Indique rubro a validar: ");
				scanf(" %[^\n]", &(campo));
				fflush(stdin);
				strcpy(val, campo);
				auxrub = rub;
				if (busca_r(&auxrub, val))
					printf("\n\t El rubro %s si esta registrado\n\n", val);
				else
					printf("\n\t El rubro %s no esta registrado\n\n", val);
				break;
			case 16: eliminar_r(&rub, &fac, &lot);
				break;
			case 17: agrega_sub(&rub);
				break;
			case 18: modifica_sub(&rub, &lot);
				break;
			case 19: printf("\n\t Indique subcategoria a validar: ");
				scanf(" %[^\n]", &(campo));
				fflush(stdin);
				strcpy(val, campo);
				printf("\n\t Indique en que rubro validar %s: ", val);
				scanf(" %[^\n]", &(campo));
				fflush(stdin);
				strcpy(val2, campo);
				auxrub = rub;
				if (busca_sub(&auxrub, val, val2))
					printf("\n\t La subcategoria %s si esta registrada\n\n", val);
				else
					printf("\n\t La subcategoria %s no esta registrada\n\n", val);
				break;
			case 20: eliminar_sub(&rub, &lot);
				break;
			case 21: mostrar_l(&lot);
				break;
			case 22: mostrar_c(&cli);
				break;
			case 23: mostrar_s(&suc);
				break;
			case 24: mostrar_r(&rub);
				break;
			}
			break; // Rompe caso 1

		case 2: factura(&fac, &suc, &cli, &lot, &rub);
			break; // Rompe caso 2

		case 3:
			printf("\n\t\t\t	CONSULTAS\n");
			printf("\n\t Segun cliente:\n");
			printf("\n\t1. Mostrar datos generales de su factura");
			printf("\n\t2. Imprimir su factura");
			printf("\n\t3. Mostrar los totales de compras por rubro\n");
			printf("\n\t Segun sucursal:\n");
			printf("\n\t4. Total en existencia por rubros");
			printf("\n\t5. Total en existencia por subcategoria");
			printf("\n\t6. Total de subcategoria con existencia 0\n");
			printf("\n\t Segun rubro:\n");
			printf("\n\t7. Total en existencia");
			printf("\n\t8. Total de ingreso bruto e ingreso neto de las ventas de esos rubros\n");
			printf("\n\tDado un lote \n");
			printf("\n\t9. Imprimir lote\n");
			printf("\n\t0. Salir\n");
			scanf("%i", &op3);
			system("cls");
			switch (op3) {
			case 1:
				do {
					printf("\n\t Cliente: ");
					scanf(" %[^\n]", &(campo));
					fflush(stdin);
					if (!(busca_c(&cli, campo)))
						printf("\n\t No existe cliente %s\n", campo);
				} while (!(busca_c(&cli, campo)));
				strcpy(persona, campo);
				printf("\n\t\t Datos generales de las facturas de %s\n", persona);
				auxfac = fac;
				int totalu;
				long monto;
				totalu = 0;
				monto = 0;
				sale = -1;
				while (auxfac) {
					if (strcmp(persona, auxfac->cliente) == 0) {
						printf("\n\t    Factura: %s", auxfac->num);
						printf("\n\t    Sucursal: %s", auxfac->sucursal);
						printf("\n\t    Fecha: %s", auxfac->fecha);
						printf("\n\t    Total de factura: Bs. %i\n", auxfac->total);
						auxfac2 = auxfac->abajo;
						while (auxfac2) {
							totalu += auxfac2->unidades;
							auxfac2 = auxfac2->abajo;
						}
						monto += auxfac->total;
						sale = 1;
					}
					auxfac = auxfac->sig;
				}
				if (sale != 1) printf("\n\t %s no cuenta con facturas en el sistema\n\n", persona);
				else {
					printf("\n------------------------------------------------------\n");
					printf("\n\t    Total de unidades: %i\n", totalu);
					printf("\n\t    Monto total: Bs. %i\n", monto);
					printf("\n------------------------------------------------------\n\n");
				}
				break;
			case 2:
				do {
					printf("\n\t Cliente: ");
					scanf(" %[^\n]", &(campo));
					fflush(stdin);
					if (!(busca_c(&cli, campo)))
						printf("\n\t No existe cliente %s\n", campo);
				} while (!(busca_c(&cli, campo)));
				strcpy(persona, campo);
				cons2(fac, persona);

				break;
			case 3:
				do {
					printf("\n\t Cliente: ");
					scanf(" %[^\n]", &(campo));
					fflush(stdin);
					if (!(busca_c(&cli, campo)))
						printf("\n\t No existe cliente %s\n", campo);
				} while (!(busca_c(&cli, campo)));
				strcpy(persona, campo);

				auxrub = rub;
				int unirub;
				long totalrub;
				while (auxrub) {
					unirub = 0;
					totalrub = 0;
					auxfac = fac;
					printf("\n\t %s: ", auxrub->nombre);
					while (auxfac) {
						if (strcmp(auxfac->cliente, persona) == 0) {
							auxfac2 = auxfac->abajo;
							while (auxfac2) {
								auxlot = lot;
								while (auxlot) {
									if ((strcmp(auxlot->rubro, auxrub->nombre) == 0) && (strcmp(auxlot->lote, auxfac2->lote) == 0)) {
										totalrub += (auxfac2->precio * auxfac2->unidades);
										unirub += auxfac2->unidades;
									}
									auxlot = auxlot->sig;
								}
								auxfac2 = auxfac2->abajo;
							}
						}
						auxfac = auxfac->sig;
					}
					auxrub = auxrub->sig;
					printf("\n\t     Total de unidades compradas: %i", unirub);
					printf("\n\t     Monto total: %i", totalrub);
					printf("\n");
				}

				break;
			case 4:
				do {
					printf("\n\t Sucursal: ");
					scanf(" %[^\n]", &(campo));
					fflush(stdin);
					if (!(busca_s(&suc, campo)))
						printf("\n\t No existe sucursal %s\n", campo);
				} while (!(busca_s(&suc, campo)));
				strcpy(sucur, campo);
				auxrub = rub;
				int totale, cost;

				while (auxrub) {
					totalu = 0;
					totale = 0;
					cost = 0;
					auxlot = lot;
					printf("\n\t %s: ", auxrub->nombre);
					while (auxlot) {
						if ((strcmp(auxlot->sucursal, sucur) == 0) && (strcmp(auxlot->rubro, auxrub->nombre) == 0)) {
							totalu += auxlot->total;
							totale += auxlot->exist;
							cost = auxlot->costo;
						}
						auxlot = auxlot->sig;
					}
					printf("\n\t     Unidades en existencia: %i", totale);
					printf("\n\t     Total de unidades: %i", totalu);
					printf("\n\t     Costo: Bs. %i\n", cost);
					auxrub = auxrub->sig;
				}
				printf("\n");
				break;
			case 5:
				do {
					printf("\n\t Sucursal: ");
					scanf(" %[^\n]", &(campo));
					fflush(stdin);
					if (!(busca_s(&suc, campo)))
						printf("\n\t No existe sucursal %s\n", campo);
				} while (!(busca_s(&suc, campo)));
				strcpy(sucur, campo);

				auxrub = rub;

				while (auxrub) {

					auxlot = lot;
					auxrub2 = auxrub->abajo;
					while (auxrub2) {
						totalu = 0;
						totale = 0;
						cost = 0;
						sale = -1;
						auxlot = lot;
						while (auxlot) {
							if ((strcmp(auxlot->sucursal, sucur) == 0) && (strcmp(auxlot->sub, auxrub2->tipo) == 0)) {
								totalu += auxlot->total;
								totale += auxlot->exist;
								cost = auxlot->costo;
								sale = 1;
							}
							auxlot = auxlot->sig;
						}
						if (sale == 1) {
							printf("\n\t %s: ", auxrub->nombre);
							printf("\n\t     %s: ", auxrub2->tipo);
							printf("\n\t         Unidades en existencia: %i", totale);
							printf("\n\t         Total de unidades: %i", totalu);
							printf("\n\t         Costo: Bs. %i\n", cost);
						}
						auxrub2 = auxrub2->abajo;
					}
					auxrub = auxrub->sig;
				}
				printf("\n");
				break;

			case 6:
				do {
					printf("\n\t Sucursal: ");
					scanf(" %[^\n]", &(campo));
					fflush(stdin);
					if (!(busca_s(&suc, campo)))
						printf("\n\t No existe sucursal %s\n", campo);
				} while (!(busca_s(&suc, campo)));
				strcpy(sucur, campo);
				

				printf("\n\t Subcategorias con exitencia cero(0) de lotes en %s: \n", sucur);
				auxrub = rub;

				while (auxrub) {

					auxrub2 = auxrub->abajo;
					printf("\n\t    %s: ", auxrub->nombre);
					while (auxrub2) {
						totale = 0;
						auxlot = lot;
						while (auxlot) {
							if ((strcmp(auxlot->sucursal, sucur) == 0) && (strcmp(auxlot->sub, auxrub2->tipo) == 0))
								if ((auxlot->exist) == 0)
									printf("\n\t        %s", auxlot->sub);
							auxlot = auxlot->sig;
						}
						auxrub2 = auxrub2->abajo;
					}
					auxrub = auxrub->sig;
				}
				printf("\n");

				printf("\n\t Subcategorias cuyos lotes no hay en %s: \n", sucur);
				printf("\n--------------------------------------------------------------\n");
				auxrub = rub;
				
				while (auxrub) {
					
					auxrub2 = auxrub->abajo;
					printf("\n\t    %s: ", auxrub->nombre);
					while (auxrub2) {
						totale = 0;
						auxlot = lot;
						while (auxlot) {
							if ((strcmp(auxlot->sucursal, sucur) == 0) && (strcmp(auxlot->sub, auxrub2->tipo) == 0))
								totale += auxlot->exist;
							auxlot = auxlot->sig;
						}
						if (totale == 0) {						
							printf("\n\t       %s ", auxrub2->tipo);
						}
						auxrub2 = auxrub2->abajo;
					}
					auxrub = auxrub->sig;
				}
				printf("\n\n");
				break;

			case 7:printf("\n\t Rubro: ");
				scanf("%s", &rubro);
				cons7(lot, rubro);
				break;

			case 8:
				long bruto, neto;
				do {
					printf("\n\t Rubro: ");
					scanf(" %[^\n]", &(campo));
					fflush(stdin);
					if (!(busca_r(&rub, campo)))
						printf("\n\t No existe rubro %s\n", campo);
				} while (!(busca_r(&rub, campo)));
				strcpy(rubro, campo);
				auxfac = fac;
				bruto = 0;
				neto = 0;
				while (auxfac) {
					auxfac2 = auxfac->abajo;
					while (auxfac2) {
						auxlot = lot;
						while (auxlot) {
							if ((strcmp(auxlot->lote, auxfac2->lote) == 0) && (strcmp(auxlot->rubro, rubro) == 0)) {
								neto += ((auxlot->costo)*(auxfac2->unidades));
								bruto += ((auxfac2->unidades)*(auxfac2->precio));
								break;
							}
							auxlot = auxlot->sig;
						}
						auxfac2 = auxfac2->abajo;
					}
					auxfac = auxfac->sig;
				}
				printf("\n\tEl total bruto del rubro %s es %ld", rubro, bruto);
				printf("\n\tEl total neto del rubro %s es %ld", rubro, bruto - neto);
				printf("\n");

				break;

			case 9:
				char numlot[5];
				int cont;
				do {
					printf("\n\t Lote: ");
					scanf(" %[^\n]", &(campo));
					fflush(stdin);
					if (!(busca_l(&lot, campo)))
						printf("\n\t No existe lote %s\n", campo);
				} while (!(busca_l(&lot, campo)));
				strcpy(numlot, campo);
				printf("\n\t Datos del lote %s: \n", numlot);
				auxlot = lot;
				while ((auxlot) && (strcmp(auxlot->lote, numlot) != 0))
					auxlot = auxlot->sig;
				printf("\n\t      Sucursal: %s ", auxlot->sucursal);
				printf("\n\t      Rubro: %s ", auxlot->rubro);
				printf("\n\t      Subcategoria: %s ", auxlot->sub);
				printf("\n\t      Total de unidades: %i ", auxlot->total);
				printf("\n\t      En existencia: %i ", auxlot->exist);
				printf("\n\t      Peso: %.2f ", auxlot->peso);
				printf("\n\t      Costo: %i \n", auxlot->costo);

				printf("\n\t Facturas asociadas al lote %s\n", auxlot->lote);
				auxfac = fac;
				cont = 0;
				while (auxfac) {
					auxfac2 = auxfac->abajo;
					while (auxfac2) {
						if (strcmp(auxfac2->lote, auxlot->lote) == 0) {
							printf("\n\t      Factura: %s", auxfac->num);
							printf("\n\t      Cantidad de %s: %i\n", auxlot->sub, auxfac2->unidades);
							cont += auxfac2->unidades;
						}
						auxfac2 = auxfac2->abajo;
					}
					auxfac = auxfac->sig;
				}
				if (cont)
					printf("\n\t Total de unidades: %i\n\n", cont);
				else
					printf("\n No hay facturas asociadas al lote %s\n\n", auxlot->lote);
				printf("\n");
				break;
			};

			break; //Rompe caso 3

		}; // switch op
		if (op) system("PAUSE");
	}

	//Crea archivo para guardar actualizacion de lotes
	FILE *M;
	M = fopen("lotes.txt", "w");

	auxlot = lot;
	while (auxlot && auxlot->sig) {
		fprintf(M, "%s\n%s\n%s\n%s\n%i\n%i\n%.2f\n%i\n", auxlot->lote, auxlot->sucursal, auxlot->rubro, auxlot->sub, auxlot->total, auxlot->exist, auxlot->peso, auxlot->costo); //guarda en el archivo los datos de la lista lotes
		auxlot = auxlot->sig;
	}
	fprintf(M, "%s\n%s\n%s\n%s\n%i\n%i\n%f\n%i", auxlot->lote, auxlot->sucursal, auxlot->rubro, auxlot->sub, auxlot->total, auxlot->exist, auxlot->peso, auxlot->costo);
	fclose(M);

	//Crea archivo para guardar actualizacion de facturas
	FILE *F;
	F = fopen("facturas.txt", "w");

	auxfac = fac;
	while (auxfac && auxfac->sig) {
		fprintf(F, "%s\n%s\n%s\n%s\n%ld\n", auxfac->num, auxfac->sucursal, auxfac->fecha, auxfac->cliente, auxfac->total); //guarda en el archivo los datos de la lista facturas
		auxfac = auxfac->sig;
	}
	fprintf(F, "%s\n%s\n%s\n%s\n%ld", auxfac->num, auxfac->sucursal, auxfac->fecha, auxfac->cliente, auxfac->total);
	fclose(F);

	//Crea archivo para guardar actualizacion de sucursales
	FILE *S;
	S = fopen("sucursales.txt", "w");

	auxsuc = suc;
	while (auxsuc && auxsuc->sig) {
		fprintf(S, "%s\n", auxsuc->sede); //guarda en el archivo los datos de la lista sucursales
		auxsuc = auxsuc->sig;
	}
	fprintf(S, "%s", auxsuc->sede);
	fclose(S);

	//Crea archivo para guardar actualizacion de rubros
	FILE *R;
	R = fopen("rubros.txt", "w");

	auxrub = rub;
	while (auxrub && auxrub->sig) {
		fprintf(R, "%s\n", auxrub->nombre); //guarda en el archivo los datos de la lista rubros
		auxrub = auxrub->sig;
	}
	fprintf(R, "%s", auxrub->nombre);
	fclose(R);

	//Crea archivo para guardar actualizacion de clientes
	*R;
	R = fopen("clientes.txt", "w");

	auxcli = cli;
	while (auxcli && auxcli->sig) {
		fprintf(R, "%s\n", auxcli->nombre); //guarda en el archivo los datos de la lista rubros
		auxcli = auxcli->sig;
	}
	fprintf(R, "%s", auxcli->nombre);
	fclose(R);

	//Crea archivo para guardar actualizacion de DETALLES DE FACTURAS

	FILE *D;
	D = fopen("detalle.txt", "w");

	auxfac = fac;

	while (auxfac && auxfac->sig) {
		auxfac2 = auxfac->abajo;
		//guarda en el archivo los detalles
		while (auxfac2) {
			fprintf(D, "%s\n%s\n%i\n%ld\n", auxfac->num, auxfac2->lote, auxfac2->unidades, auxfac2->precio);
			auxfac2 = auxfac2->abajo;
		}
		auxfac = auxfac->sig;
	}
	auxfac2 = auxfac->abajo;
	while (auxfac2 && auxfac2->abajo) {
		fprintf(D, "%s\n%s\n%i\n%ld\n", auxfac->num, auxfac2->lote, auxfac2->unidades, auxfac2->precio);
		auxfac2 = auxfac2->abajo;
	}
	if (auxfac2)fprintf(D, "%s\n%s\n%i\n%ld", auxfac->num, auxfac2->lote, auxfac2->unidades, auxfac2->precio);
	fclose(D);

	//Crea archivo para guardar actualizacion de SUBCATEGORIAS DE RUBROS

	FILE *B;
	B = fopen("sub.txt", "w");

	auxrub = rub;

	while (auxrub && auxrub->sig) {
		auxrub2 = auxrub->abajo;
		//guarda en el archivo los datos de alumnos en cursos
		while (auxrub2) {
			fprintf(B, "%s\n%s\n", auxrub->nombre, auxrub2->tipo);
			auxrub2 = auxrub2->abajo;
		}
		auxrub = auxrub->sig;
	}
	auxrub2 = auxrub->abajo;
	while (auxrub2 && auxrub2->abajo) {
		fprintf(B, "%s\n%s\n", auxrub->nombre, auxrub2->tipo);
		auxrub2 = auxrub2->abajo;
	}
	if (auxrub2)fprintf(B, "%s\n%s", auxrub->nombre, auxrub2->tipo);
	fclose(B);

	return 0;

}