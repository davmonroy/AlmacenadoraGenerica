void agrega_l(lotes **p, sucursales **s, rubros **r) {
	//Agrega, en orden, lotes
	lotes *t = new lotes;
	lotes *aux = *p;
	char campo[20];
	do {
		printf("\n\t Numero de lote: ");
		fflush(stdin);
		scanf("%s", &(campo));
		if (busca_l(p, campo)) printf("\n\tYa existe un lote con ese codigo\n\n");
	} while (busca_l(p, campo));

	strcpy(t->lote, campo);

	do {
		printf("\n\t Sucursal: ");
		fflush(stdin);
		scanf(" %[^\n]", &campo);
		if (!(busca_s(s, campo))) printf("\n\tNo existe sucursal %s en el sistema\n\n", campo);
	} while (!(busca_s(s, campo)));

	strcpy(t->sucursal, campo);

	do {
		printf("\n\t Rubro: ");
		fflush(stdin);
		scanf(" %[^\n]", &campo);
		if (!(busca_r(r, campo))) printf("\n\tNo existe rubro %s en el sistema\n\n", campo);
	} while (!(busca_r(r, campo)));

	strcpy(t->rubro, campo);


	do {
		printf("\n\t Subcategoria: ");
		fflush(stdin);
		scanf(" %[^\n]", &(campo));
		if (!(busca_sub(r, campo, t->rubro))) printf("\n\tNo existe subcategoria %s  para rubro %s en el sistema\n\n", campo, t->rubro);
	} while (!(busca_sub(r, campo, t->rubro)));

	strcpy(t->sub, campo);

	printf("\n\t Cantidad de unidades inicial: ");
	fflush(stdin);
	scanf("%i", &(t->total));

	t->exist = t->total;
	printf("\n\t Se agregaron %i unidades disonibles", t->exist);

	printf("\n\t Peso unidad: ");
	fflush(stdin);
	scanf("%f", &(t->peso));
	printf("\n\t Costo: ");
	fflush(stdin);
	scanf("%i", &(t->costo));

	while ((aux) && (aux->sig)) {
		aux = aux->sig;
	}

	aux->sig = t;
	t->sig = NULL;

	printf("\n\n------------------------------------------------------\n");
	printf("\n\t Lote agregado exitosamente");
	printf("\n\n------------------------------------------------------\n");
}

void agrega_s(sucursales **p) {
	//Agrega, en orden, sucursales
	sucursales *t = new sucursales;
	sucursales *aux = *p;
	char campo[20];

	do {
		printf("\n\t Ciudad de sucursal: ");
		fflush(stdin);
		scanf(" %[^\n]", &campo);
		if (busca_s(p, campo)) printf("\n\tYa existe la sucursal %s\n\n", campo);
	} while (busca_s(p, campo));
	strcpy(t->sede, campo);


	while ((aux) && (aux->sig))
		aux = aux->sig;

	aux->sig = t;
	t->sig = NULL;

	printf("\n\n------------------------------------------------------\n");
	printf("\n\t Sucursal agregada exitosamente");
	printf("\n\n------------------------------------------------------\n");
}

void agrega_c(clientes **p) {
	//Agrega, en orden, lotes
	clientes *t = new clientes;
	clientes *aux = *p;
	char campo[20];
	do {
		printf("\n\t Nombre de cliente: ");
		fflush(stdin);
		scanf(" %[^\n]", &campo);
		if (busca_c(p, campo)) printf("\n\tEl cliente %sya esta registrado en el sistema\n\n", campo);
	} while (busca_c(p, campo));

	strcpy(t->nombre, campo);

	while ((aux) && (aux->sig))
		aux = aux->sig;

	aux->sig = t;
	t->sig = NULL;

	printf("\n\n------------------------------------------------------\n");
	printf("\n\t Cliente agregado exitosamente");
	printf("\n\n------------------------------------------------------\n");
}

void agrega_r(rubros **p) {
	//Agrega  rubros
	rubros *t = new rubros;
	rubros *aux = *p;
	char campo[20];
	do {
		printf("\n\t Nombre de rubro: ");
		fflush(stdin);
		scanf(" %[^\n]", &campo);
		if (busca_r(p, campo)) printf("\n\tYa existe el rubro %s\n\n", campo);
	} while (busca_r(p, campo));
	strcpy(t->nombre, campo);

	while ((aux) && (aux->sig))
		aux = aux->sig;

	aux->sig = t;
	t->sig = NULL;
	t->abajo = NULL;

	printf("\n\n------------------------------------------------------\n");
	printf("\n\t Rubro agregado exitosamente");
	printf("\n\n------------------------------------------------------\n");
}

void agrega_sub(rubros **p) {
	//Agrega  rubros
	sub *t = new sub;
	rubros *aux = *p;
	sub *tos;
	char r[20], campo[20], campo_s[20];

	do {
		printf("\n\t Indique categoria (rubro) a la que pertenecera: ");
		fflush(stdin);
		scanf(" %[^\n]", &(campo));

		while ((aux->sig) && (strcmp(aux->nombre, campo) != 0))
			aux = aux->sig;
		if (strcmp(aux->nombre, campo) != 0) printf("\n\t No existe el rubro %s", campo);
	} while (strcmp(aux->nombre, campo) != 0);

	do {
		printf("\n\t Nombre de subcategoria: ");
		fflush(stdin);
		scanf(" %[^\n]", &(campo_s));
		if (busca_sub(p, campo_s,campo)) printf("\n\tYa existe la subcategoria %s del rubro %s\n\n", campo_s, campo);
	} while (busca_sub(p, campo_s, campo));
	strcpy(t->tipo, campo_s);

	if (aux->abajo) {
		tos = aux->abajo;
		while ((tos) && (tos->abajo))
			tos = tos->abajo;
		tos->abajo = t;
	}
	else aux->abajo = t;

	strcpy(r, campo);


	t->abajo = NULL;

	printf("\n\n------------------------------------------------------\n");
	printf("\n\t Rubro agregado exitosamente");
	printf("\n\n------------------------------------------------------\n");
}

void modifica_l(lotes **p, sucursales **s, rubros **r) {
	lotes *t = *p;
	char campo[20];
	char ref[10];

	do {
	printf("\n\t Indique numero de lote a modificar: ");
	scanf(" %[^\n]", &(campo));
	fflush(stdin);
		if (!(busca_l(p, campo)))
			printf("\n\t No existe lote con codigo %s\n", campo);
	} while (!(busca_l(p, campo)));

	strcpy(ref, campo);
	t = *p;
	while (t) {														
		if (strcmp((t->lote), ref) == 0) {
			do {
				printf("\n\tSucursal de lote actual:  %s",t->sucursal);
				printf("\n\tNueva sucursal: ");
				fflush(stdin);
				scanf(" %[^\n]", &campo);
				if (!(busca_s(s, campo))) {
					printf("\n\tNo existe sucursal %s en el sistema\n\n", campo);
				}
			} while (!(busca_s(s, campo)));
			strcpy(t->sucursal, campo);
			do {
				printf("\n\tRubro de lote actual:  %s", t->rubro);
				printf("\n\tNuevo rubro: ");
				fflush(stdin);
				scanf(" %[^\n]", &campo);
				if (!(busca_r(r, campo))) {
					printf("\n\tNo existe rubro %s en el sistema\n\n", campo);
				}
			} while (!(busca_r(r, campo)));
			strcpy(t->rubro, campo);
			do {
				printf("\n\tSubcategoria de lote actual:  %s", t->sub);
				printf("\n\tNueva subcategoria: ");
				fflush(stdin);
				scanf(" %[^\n]", &campo);
				if (!(busca_sub(r, campo, t->rubro))) {
					printf("\n\tNo existe subcategoria %s  para rubro %s en el sistema\n\n", campo, t->rubro);
				}
			} while (!(busca_sub(r, campo, t->rubro)));
			strcpy(t->sub, campo);
			int ex, to;
			do{
				printf("\n\tNumero total de unidades actual:  %i", t->total);
				printf("\n\tNuevo numero total de unidades: ");
				scanf("%i", &(to));
					printf("\n\tNumero de unidades en existencia actual:  %i", t->exist);
					printf("\n\tNuevo numero en existencia: ");
					scanf("%i", &(ex));
					if (ex > to) {
						printf("\n\tLa cantidad de unidades en existencia (%i) no puede ser mayor al total (%i)\n\n", ex, to);
					}
			} while (ex > to);
			t->total = to; t->exist = ex;
			printf("\n\tNuevo valor Peso/Volumen: ");
			scanf("%f", &(t->peso));
			printf("\n\tNuevo costo: ");
			scanf("%i", &(t->costo));
			printf("\n\n------------------------------------------------------\n");
			printf("\n\t Lote modificado exitosamente");
			printf("\n\n------------------------------------------------------\n");
			break;
		}
		t = t->sig;
	}
};

void modifica_s(sucursales **p, lotes **l, facturas **f) {
	sucursales *t = *p;
	lotes *lt = *l;
	facturas *fc = *f;
	char campo[20];
	char ref[10];

	do {
	printf("\n\t Indique sucursal a modificar: ");
	scanf(" %[^\n]", &(campo));
	fflush(stdin);
	strcpy(ref, campo);
		if (!(busca_s(p, ref))) 
			printf("\n\tNo existe la sucursal %s\n\n", ref);
	} while (!(busca_s(p, ref)));

	while (t) {
		if (strcmp((t->sede), ref) == 0) {
			do {
				printf("\n\tSucursal a modificar: %s", ref);
				printf("\n\tNueva sucursal: ");
				fflush(stdin);
				scanf(" %[^\n]", &campo);
				if ((busca_s(p, campo))) 
					printf("\n\tYa existe la sucursal %s\n\n", campo);
			
			} while ((busca_s(p, campo)));
			strcpy(t->sede, campo);
			printf("\n\n------------------------------------------------------\n");
			printf("\n\t Sucursal modificada exitosamente");
			printf("\n\n------------------------------------------------------\n");
			break;
		}
		t = t->sig;
	}

	while (lt) {  // Cambia nueva sucursal en lotes
		if (strcmp(lt->sucursal, ref) == 0)
			strcpy(lt->sucursal, t->sede);
		lt = lt->sig;
	}
	while (fc) {    // Cambia nueva sucursal en facturas
		if (strcmp(fc->sucursal, ref) == 0)
			strcpy(fc->sucursal, t->sede);
		fc = fc->sig;
	}
}

void modifica_r(rubros **p, lotes **l) {
	rubros *t = *p;
	lotes *lt = *l;

	char campo[20];
	char ref[10];

	do {
	printf("\n\t Indique rubro a modificar: ");
		scanf(" %[^\n]", &(campo));
		fflush(stdin);
		if (!(busca_r(p, campo))) 
			printf("\n\tNo existe el rubro %s\n\n", campo);		
	} while (!(busca_r(p, campo)));
	strcpy(ref, campo);

	while (t) {
		if (strcmp((t->nombre), ref) == 0) {
			do {
				printf("\n\tRubro a modificar: %s", ref);
				printf("\n\tNuevo rubro: ");
				fflush(stdin);
				scanf(" %[^\n]", &campo);
				if (busca_r(p, campo)) {
					printf("\n\tYa existe el rubro %s\n\n", campo);
				}
			} while (busca_r(p, campo));
			strcpy(t->nombre, campo);
			printf("\n\n------------------------------------------------------\n");
			printf("\n\t Rubro modificado exitosamente");
			printf("\n\n------------------------------------------------------\n");
			break;
		}
		t = t->sig;
	}

	while (lt) {  // Cambia nuevo rubro en lotes
		if (strcmp(lt->rubro, ref) == 0)
			strcpy(lt->rubro, t->nombre);
		lt = lt->sig;
	}
}

void modifica_c(clientes **p, facturas **l) {
	clientes *t = *p;
	facturas *lt = *l;

	char campo[20];
	char ref[10];

	do {
	printf("\n\t Indique cliente a modificar: ");
		scanf(" %[^\n]", &(campo));
		fflush(stdin);
		if (!(busca_c(p, campo)))
			printf("\n\tNo existe el cliente %s\n\n", campo);
	} while (!(busca_c(p, campo)));
	strcpy(ref, campo);
	while (t) {
		if (strcmp((t->nombre), ref) == 0) {
			do {
				printf("\n\tCliente a modificar: %s ", ref);
				printf("\n\tNuevo nombre de cliente: ");
				fflush(stdin);
				scanf(" %[^\n]", &campo);
				if (busca_c(p, campo)) 
					printf("\n\tYa existe el cliente %s\n\n", campo);
			} while (busca_c(p, campo));
			strcpy(t->nombre, campo);
			printf("\n\n------------------------------------------------------\n");
			printf("\n\t Cliente modificado exitosamente");
			printf("\n\n------------------------------------------------------\n");
			break;
		}
		t = t->sig;
	}

	while (lt) {  // Cambia nuevo cliente en facturas
		if (strcmp(lt->cliente, ref) == 0)
			strcpy(lt->cliente, t->nombre);
		lt = lt->sig;
	}
}

void modifica_sub(rubros **p, lotes **l) {
	rubros *t = *p;
	sub *s;
	lotes *lt = *l;

	char campo[20];
	char ref[20], refo[20];

	do {
	printf("\n\t Indique rubro de subcategoria a modificar: ");
		scanf(" %[^\n]", &(campo));
		fflush(stdin);
		if (!(busca_r(p, campo)))
			printf("\n\tNo existe el rubro %s\n\n", campo);
	} while (!(busca_r(p, campo)));
	strcpy(refo, campo);

	do {
	printf("\n\t Indique subcategoria a modificar: ");
		scanf(" %[^\n]", &(campo));
		fflush(stdin);
		if (!(busca_sub(p, campo, refo)))
			printf("\n\tNo existe subcategoria %s para rubro %s", campo, refo);
	} while (!(busca_sub(p, campo, refo)));
	strcpy(ref, campo);

	while (t) {
		if (strcmp((t->nombre), refo) == 0) {
			s = t->abajo;
			while (s) {
				if (strcmp((s->tipo), ref) == 0) {
					do {
						printf("\n\tSubcategoria actual: %s", s->tipo);
						printf("\n\tNuevo nombre de subcategoria: ");
						fflush(stdin);
						scanf(" %[^\n]", &campo);
						if (busca_sub(p, campo, refo))
							printf("\n\tYa existe la subcategoria %s\n\n", campo);
					} while (busca_sub(p, campo, refo));
					strcpy(s->tipo, campo);
					printf("\n\n------------------------------------------------------\n");
					printf("\n\t Subcategoria modificada exitosamente");
					printf("\n\n------------------------------------------------------\n");
					break;
				}
				s = s->abajo;
			}
		}
		t = t->sig;
	}

	while (lt) {  // Cambia nuevo subcategoria en lotes
		if (strcmp(lt->sub, ref) == 0)
			strcpy(lt->sub, campo);
		lt = lt->sig;
	}
}

void eliminar_l(lotes **p) {
	lotes *t = *p;
	lotes *aux;
	int sale = -1;
	char campo[20];
	char ref[10];
	do {
		printf("\n\t Indique numero de lote a eliminar: ");
		scanf(" %[^\n]", &(campo));
		fflush(stdin);
		if (!(busca_l(p, campo)))
			printf("\n\t No existe el lote %s\n", campo);
	} while (!(busca_l(p, campo)));
	strcpy(ref, campo);

	if (strcmp(t->lote, ref) == 0) {
		aux = t;
		t = t->sig;
		delete aux;
		*p = t;
		printf("\n\n------------------------------------------------------\n");
		printf("\n\t Lote eliminado exitosamente");
		printf("\n\n------------------------------------------------------\n");
	}
	while ((t) && (t->sig) && (strcmp(t->sig->lote, ref) != 0))
		t = t->sig;
	if (t->sig) {
		aux = t->sig;
		t->sig = t->sig->sig;
		delete aux;
		printf("\n\n------------------------------------------------------\n");
		printf("\n\t Lote eliminado exitosamente");
		printf("\n\n------------------------------------------------------\n");
	}
}

void eliminar_s(sucursales **p, facturas **f, lotes **l) {
	sucursales *t = *p;
	sucursales *aux;
	int sale = -1;
	char campo[20], sede[20];
	char ref[20];
	printf("\t*** Los lotes de la sucursal eliminada se eliminaran ***\n");
	printf("\t*** Las facturas de la sucursal eliminada se descontaran a cero (0) ***\n");
	do {
		printf("\n\t Indique sucursal a eliminar: ");
		scanf(" %[^\n]", &(campo));
		fflush(stdin);
		if (!(busca_s(p, campo)))
			printf("\n\t No existe sucursal %s\n", campo);
	} while (!(busca_s(p, campo)));
	strcpy(ref, campo);

	if (strcmp(t->sede, ref) == 0) {
		aux = t;
		t = t->sig;
		delete aux;
		*p = t;
		printf("\n\n------------------------------------------------------\n");
		printf("\n\t Sucursal eliminada exitosamente");
		printf("\n\n------------------------------------------------------\n");
	}
	while ((t) && (t->sig) && (strcmp(t->sig->sede, ref) != 0))
		t = t->sig;
	if (t->sig) {
		aux = t->sig;
		t->sig = t->sig->sig;
		delete aux;
		printf("\n\n------------------------------------------------------\n");
		printf("\n\t Sucursal eliminada exitosamente");
		printf("\n\n------------------------------------------------------\n");
	}
	lotes *lt = *l, *aux2;

	if (strcmp(lt->sucursal, ref) == 0) {
		aux2 = lt;

		lt = lt->sig;

		delete aux2;
		*l = lt;
	}
	while ((lt) && (lt->sig)) {
		if (strcmp(lt->sig->sucursal, ref) == 0) {
			aux2 = lt->sig;

			lt->sig = lt->sig->sig;
			delete aux2;
		}
		lt = lt->sig;
	}
	lt = *l;

	if (strcmp(lt->sucursal, ref) == 0) {
		aux2 = lt;

		lt = lt->sig;

		delete aux2;
		*l = lt;
	}
	while ((lt) && (lt->sig)) {
		if (strcmp(lt->sig->sucursal, ref) == 0) {
			aux2 = lt->sig;

			lt->sig = lt->sig->sig;
			delete aux2;
		}
		lt = lt->sig;
	}

	facturas *s = *f;

	while (s) {
		if (strcmp(s->sucursal, ref) == 0) {
			s->total = 0;
			strcpy(s->sucursal, strcat(s->sucursal, " (eliminado)"));
			s->abajo = NULL;
		}
		s = s->sig;
	}
	
}

void eliminar_c(clientes **p, facturas **f) {
	clientes *t = *p;
	clientes *aux;
	int sale = -1;
	char campo[20];
	char ref[20], lote[20];
	printf("\t*** Las facturas del cliente eliminado quedaran en cero(0) ***\n");
	do {
		printf("\n\t Indique cliente a eliminar: ");
		scanf(" %[^\n]", &(campo));
		fflush(stdin);
		if (!(busca_c(p, campo)))
			printf("\n\t No existe el cliente %s \n", campo);
	} while (!(busca_c(p, campo)));
	strcpy(ref, campo);

	if (strcmp(t->nombre, ref) == 0) {
		aux = t;
		t = t->sig;
		delete aux;
		*p = t;
		printf("\n\n------------------------------------------------------\n");
		printf("\n\t Cliente eliminado exitosamente");
		printf("\n\n------------------------------------------------------\n");
	}
	while ((t) && (t->sig) && (strcmp(t->sig->nombre, ref) != 0))
		t = t->sig;
	if (t->sig) {
		aux = t->sig;
		t->sig = t->sig->sig;
		delete aux;
		printf("\n\n------------------------------------------------------\n");
		printf("\n\t Cliente eliminado exitosamente");
		printf("\n\n------------------------------------------------------\n");
	}
	facturas *s = *f;
	
	while (s) {
		if (strcmp(s->cliente, ref) == 0) {
			s->total = 0;
			strcpy(s->cliente, strcat(s->cliente, " (eliminado)"));
			s->abajo = NULL;
		}
		s = s->sig;
	}

}

void eliminar_r(rubros **p, facturas **f, lotes **l) {
	rubros *t = *p;
	rubros *aux;
	int sale = -1;
	char campo[20], lote[20];
	char ref[20];
	printf("\t*** Se descontara el precio en las facturas ***\n");
	printf("\t*** Los lote del rubro eliminado se eliminaran ***\n");
	do {
		printf("\n\t Indique rubro a eliminar: ");
		scanf(" %[^\n]", &(campo));
		fflush(stdin);
		if (!(busca_r(p, campo)))
			printf("\n\t No existe rubro %s", campo);
	} while (!(busca_r(p, campo)));
	strcpy(ref, campo);

	if (strcmp(t->nombre, ref) == 0) {
		aux = t;
		t = t->sig;
		delete aux;
		*p = t;
		printf("\n\n------------------------------------------------------\n");
		printf("\n\t Rubro eliminado exitosamente");
		printf("\n\n------------------------------------------------------\n");
	}
	while ((t) && (t->sig) && (strcmp(t->sig->nombre, ref) != 0))
		t = t->sig;
	if (t->sig) {
		aux = t->sig;
		t->sig = t->sig->sig;
		delete aux;
		printf("\n\n------------------------------------------------------\n");
		printf("\n\t Rubro eliminado exitosamente");
		printf("\n\n------------------------------------------------------\n");
	}
	facturas *s = *f;
	detalle *det, *ad;

	lotes *lt = *l, *aux2;

	if (strcmp(lt->rubro, ref) == 0) {
		aux2 = lt;
		strcpy(lote, lt->lote);
		lt = lt->sig;
		
		delete aux2;
		*l = lt;
	}
	while ((lt) && (lt->sig)){
		if (strcmp(lt->sig->rubro, ref) == 0) {
			aux2 = lt->sig;
			strcpy(lote, lt->sig->lote);
			lt->sig = lt->sig->sig;
			delete aux2;
		}
		lt = lt->sig;
	}

}

void eliminar_sub(rubros **p, lotes **l) {
	rubros *s = *p;
	sub *aux;
	sub *t;
	int sale = -1;
	char campo[20];
	char ref[20], refo[20];
	do {
		printf("\n\t Indique rubro de subcategoria a eliminar: ");
		scanf(" %[^\n]", &(campo));
		fflush(stdin);
		if (!(busca_r(p, campo)))
			printf("\n\t No existe rubro %s", campo);
	} while (!(busca_r(p, campo)));
	strcpy(refo, campo);

	do {
		printf("\n\t Indique subcategoria a eliminar: ");
		scanf(" %[^\n]", &(campo));
		fflush(stdin);
	} while (!(busca_sub(p, campo, refo)));
	strcpy(ref, campo);

	while (s) {
		t = s->abajo;

		if (strcmp(t->tipo, ref) == 0) {
			aux = t;
			t = t->abajo;
			delete aux;
			s->abajo = t;
			printf("\n\n------------------------------------------------------\n");
			printf("\n\t Subcategoria eliminada exitosamente");
			printf("\n\n------------------------------------------------------\n");
			break;
		}
		while ((t) && (t->abajo) && (strcmp(t->abajo->tipo, ref) != 0))
			t = t->abajo;
		if (t->abajo) {
			aux = t->abajo;
			t->abajo = t->abajo->abajo;
			delete aux;
			printf("\n\n------------------------------------------------------\n");
			printf("\n\t Subcategoria eliminada exitosamente");
			printf("\n\n------------------------------------------------------\n");
			break;
		}
		s = s->sig;
	}

	lotes *lt = *l, *aux2;

	if (strcmp(lt->sub, ref) == 0) {
		aux2 = lt;
		
		lt = lt->sig;

		delete aux2;
		*l = lt;
	}
	while ((lt) && (lt->sig)) {
		if (strcmp(lt->sig->sub, ref) == 0) {
			aux2 = lt->sig;
			
			lt->sig = lt->sig->sig;
			delete aux2;
		}
		lt = lt->sig;
	}
}

void mostrar_l(lotes **p) {
	lotes *t = *p;
	printf("\n\t\t Lotes\n");
	while (t) {
		printf("\n\t Lote: %s", t->lote);
		printf("\n\t Sucursal: %s", t->sucursal);
		printf("\n\t Rubro: %s", t->rubro);
		printf("\n\t Subcategoria: %s", t->sub);
		printf("\n\t Total de unidades: %i", t->total);
		printf("\n\t En existencia: %i", t->exist);
		printf("\n\t Peso: %.2f", t->peso);
		printf("\n\t Costo: %i\n", t->costo);
		t = t->sig;
	}
	printf("\n");
}

void mostrar_s(sucursales **p) {
	sucursales *t = *p;
	printf("\n\t\t Sucursales\n");
	while (t) {
		printf("\n\t Sede: %s\n", t->sede);
		t = t->sig;
	}
	printf("\n");
}

void mostrar_c(clientes **p) {
	clientes *t = *p;
	printf("\n\t\t Clintes\n");
	while (t) {
		printf("\n\t Nombre: %s\n", t->nombre);
		t = t->sig;
	}
	printf("\n");
}

void mostrar_r(rubros **p) {
	rubros *t = *p;
	sub *s;
	printf("\n\t\t Rubros\n");
	while (t) {
		s = t->abajo;
		printf("\n\t Rubro: %s", t->nombre);
		printf("\n\t Subcategorias:");
		while (s) {
			printf("\n\t     %s", s->tipo);
			s = s->abajo;
		}
		printf("\n");
		t = t->sig;
	}
	printf("\n");
}
