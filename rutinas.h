
struct lotes {
	// Info de lotes
	char lote[10];
	char sucursal[15];
	char rubro[10];
	char sub[20];
	int total;
	int exist;
	float peso;
	long costo;
	lotes *sig;
};

struct detalle {
	// Info de detalle de factura

	char lote[20];
	int unidades;
	long int  precio;
	detalle *abajo;
};

struct facturas {
	// Info de facturas
	char num[10];
	char sucursal[30];
	char cliente[30];
	char fecha[30];
	long int total;
//	int cantotal;
	facturas *sig;
	detalle *abajo;
};

struct sucursales {
	// Info de sucursales
	char sede[10];
	sucursales *sig;
};

struct clientes {
	// Info de clientes
	char nombre[10];
	clientes *sig;
};

struct sub {
	char tipo[20];
	sub *abajo;
};

struct rubros {
	// Info de rubros
	char nombre[20];
	rubros *sig;
	sub *abajo;
};

void leerLotes(lotes **p) {
	// Lee de archivo y guarda en lista lotes
	FILE *M;
	M = fopen("lotes.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo");
		fclose(M);
		exit(1);
	}
	else {
		char campo[25];
		lotes *t = *p;
		t = new lotes;

		fscanf(M, " %[^\n]", &(campo));
		fflush(stdin);
		strcpy(t->lote, campo);
		fscanf(M, " %[^\n]", &(campo));
		fflush(stdin);
		strcpy(t->sucursal, campo);
		fscanf(M, " %[^\n]", &(campo));
		fflush(stdin);
		strcpy(t->rubro, campo);
		fscanf(M, " %[^\n]", &(campo));
		fflush(stdin);
		strcpy(t->sub, campo);
		fscanf(M, "%i", &(t->total));
		fscanf(M, "%i", &(t->exist));
		fscanf(M, "%f", &(t->peso));
		fscanf(M, "%i", &(t->costo));

		t->sig = NULL;
		*p = t;

		while (!(feof(M))) {
			lotes *s = *p;

			while (s->sig)
				s = s->sig;
			s->sig = new lotes;
			t = s->sig;

			fscanf(M, " %[^\n]", &(campo));
			fflush(stdin);
			strcpy(t->lote, campo);
			fscanf(M, " %[^\n]", &(campo));
			fflush(stdin);
			strcpy(t->sucursal, campo);
			fscanf(M, " %[^\n]", &(campo));
			fflush(stdin);
			strcpy(t->rubro, campo);
			fscanf(M, " %[^\n]", &(campo));
			fflush(stdin);
			strcpy(t->sub, campo);
			fscanf(M, "%i", &(t->total));
			fscanf(M, "%i", &(t->exist));
			fscanf(M, "%f", &(t->peso));
			fscanf(M, "%i", &(t->costo));

			s->sig->sig = NULL;


		}
		fclose(M);
	}

};

void leerFacturas(facturas **p) {
	// Lee datos de archivo de alumnos
	FILE* M;
	M = fopen("facturas.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo");
		fclose(M);
		exit(1);
	}
	else {			//Lee primer registro
		char campo[30];
		facturas *t = *p;
		t = new facturas;

		fscanf(M, " %[^\n]", &(campo));
		fflush(stdin);
		strcpy(t->num, campo);
		fscanf(M, " %[^\n]", &(campo));
		fflush(stdin);
		strcpy(t->sucursal, campo);
		fscanf(M, " %[^\n]", &(campo));
		fflush(stdin);
		strcpy(t->fecha, campo);
		fscanf(M, " %[^\n]", &(campo));
		fflush(stdin);
		strcpy(t->cliente, campo);
		fscanf(M, "%ld", &(t->total));


		t->abajo = NULL;
		t->sig = NULL;
		*p = t;

		while (!(feof(M))) {		//Lee los demas registros
			facturas *s = *p;

			while (s->sig)
				s = s->sig;

			s->sig = new facturas;
			t = s->sig;

			fscanf(M, " %[^\n]", &(campo));
			fflush(stdin);
			strcpy(t->num, campo);
			fscanf(M, " %[^\n]", &(campo));
			fflush(stdin);
			strcpy(t->sucursal, campo);
			fscanf(M, " %[^\n]", &(campo));
			fflush(stdin);
			strcpy(t->fecha, campo);
			fscanf(M, " %[^\n]", &(campo));
			fflush(stdin);
			strcpy(t->cliente, campo);
			fscanf(M, "%ld", &(t->total));

			t->abajo = NULL;
			s->sig->sig = NULL;
		}
		fclose(M);
	}
};

void leerDetalles(facturas **p) {
	//Lee detalles de facturas
	FILE* M;
	M = fopen("detalle.txt", "r");
	if (M == NULL) {
		printf("error al abrir el archivo");
		fclose(M);
		exit(1);
	}
	else {
		char campo[30];
		while (!(feof(M))) {
			facturas *t = *p;
			if (t != NULL) {
				char fg[10];
				fscanf(M, " %[^\n]", &(campo));
				fflush(stdin);
				strcpy(fg, campo);

				while ((strcmp((t->num), fg) != 0) && (t->sig != NULL)) {
					t = t->sig;
				}
				if ((strcmp((t->num), fg) == 0) && (t->abajo == NULL)) {					// Lee primer registro de sublista
					detalle *c = new detalle;


					fscanf(M, " %[^\n]", &(campo));
					fflush(stdin);
					strcpy(c->lote, campo);
					fscanf(M, "%i", &(c->unidades));
					fscanf(M, "%ld", &(c->precio));

					c->abajo = t->abajo;
					t->abajo = c;
				}
				else if ((strcmp((t->num), fg) == 0) && (t->abajo != NULL)) {			// Lee los demas
					detalle *s = t->abajo;
					while (s->abajo)
						s = s->abajo;
					detalle *c = new detalle;

					fscanf(M, " %[^\n]", &(campo));
					fflush(stdin);
					strcpy(c->lote, campo);
					fscanf(M, "%i", &(c->unidades));
					fscanf(M, "%ld", &(c->precio));

					s->abajo = c;
					c->abajo = NULL;

				}
			}
		}
		fclose(M);
	}
};

void leerSucursales(sucursales **p) {
	// Lee de archivo y guarda en lista sucursales
	FILE *M;
	M = fopen("sucursales.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo");
		fclose(M);
		exit(1);
	}
	else {
		char campo[25];
		sucursales *t = *p;
		t = new sucursales;

		fscanf(M, " %[^\n]", &(campo));
		fflush(stdin);
		strcpy(t->sede, campo);

		t->sig = NULL;
		*p = t;

		while (!(feof(M))) {
			sucursales *s = *p;

			while (s->sig)
				s = s->sig;
			s->sig = new sucursales;
			t = s->sig;

			fscanf(M, " %[^\n]", &(campo));
			fflush(stdin);
			strcpy(t->sede, campo);

			s->sig->sig = NULL;

		}
		fclose(M);
	}

};

void leerClientes(clientes **p) {
	// Lee de archivo y guarda en lista clientes
	FILE *M;
	M = fopen("clientes.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo");
		fclose(M);
		exit(1);
	}
	else {
		char campo[25];
		clientes *t = *p;
		t = new clientes;

		fscanf(M, " %[^\n]", &(campo));
		fflush(stdin);
		strcpy(t->nombre, campo);

		t->sig = NULL;
		*p = t;

		while (!(feof(M))) {
			clientes *s = *p;

			while (s->sig)
				s = s->sig;
			s->sig = new clientes;
			t = s->sig;

			fscanf(M, " %[^\n]", &(campo));
			fflush(stdin);
			strcpy(t->nombre, campo);

			s->sig->sig = NULL;

		}
		fclose(M);
	}

};

void leerRubros(rubros **p) {
	// Lee de archivo y guarda en lista clientes
	FILE *M;
	M = fopen("rubros.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo");
		fclose(M);
		exit(1);
	}
	else {
		char campo[25];
		rubros *t = *p;
		t = new rubros;

		fscanf(M, " %[^\n]", &(campo));
		fflush(stdin);
		strcpy(t->nombre, campo);

		t->abajo = NULL;
		t->sig = NULL;
		*p = t;

		while (!(feof(M))) {
			rubros *s = *p;

			while (s->sig)
				s = s->sig;
			s->sig = new rubros;
			t = s->sig;

			fscanf(M, " %[^\n]", &(campo));
			fflush(stdin);
			strcpy(t->nombre, campo);

			t->abajo = NULL;
			s->sig->sig = NULL;

		}
		fclose(M);
	}
};

void leerSubrubros(rubros **a) {
	//Lee alumnos en cursos
	FILE* GH;
	GH = fopen("sub.txt", "r");
	if (GH == NULL) {
		printf("error al abrir el archivo");
		fclose(GH);
		exit(1);
	}
	else {
		char campo[30];
		while (!(feof(GH))) {
			rubros *t = *a;
			if (t != NULL) {
				char fg[20];
				fscanf(GH, "%s", &fg);
				while ((strcmp((t->nombre), fg) != 0) && (t->sig != NULL)) {
					t = t->sig;
				}
				if ((strcmp((t->nombre), fg) == 0) && (t->abajo == NULL)) {					// Lee primer registro de sublista
					sub *c = new sub;

					fscanf(GH, " %[^\n]", &(campo));
					fflush(stdin);
					strcpy(c->tipo, campo);

					c->abajo = t->abajo;
					t->abajo = c;
				}
				else if ((strcmp((t->nombre), fg) == 0) && (t->abajo != NULL)) {			// Lee los demas
					sub *s = t->abajo;
					while (s->abajo)
						s = s->abajo;
					sub *c = new sub;

					fscanf(GH, " %[^\n]", &(campo));
					fflush(stdin);
					strcpy(c->tipo, campo);
					s->abajo = c;
					c->abajo = NULL;

				}
			}
		}
		fclose(GH);
	}
};

int busca_l(lotes **p, char cod[]) {
	lotes *t = *p;
	while (t) {
		if (strcmp(t->lote, cod) == 0)
			return 1;
		t = t->sig;
	}
	return 0;
}

int busca_s(sucursales **p, char cod[]) {
	sucursales *t = *p;
	while (t) {
		if (strcmp(t->sede, cod) == 0)
			return 1;
		t = t->sig;
	}
	return 0;
}

int busca_r(rubros **p, char cod[]) {
	rubros *t = *p;
	while (t) {
		if (strcmp(t->nombre, cod) == 0)
			return 1;
		t = t->sig;
	}
	return 0;
}

int busca_c(clientes **p, char cod[]) {
	clientes *t = *p;
	while (t) {
		if (strcmp(t->nombre, cod) == 0)
			return 1;
		t = t->sig;
	}
	return 0;
}

int busca_sub(rubros **p, char cod[], char rub[]) {
	rubros *t = *p;
	sub *s;
	while (t) {
		if (strcmp(t->nombre, rub) == 0) {
			s = t->abajo;
			while (s) {
				if (strcmp(s->tipo, cod) == 0)
					return 1;
				s = s->abajo;
			}
		}
		t = t->sig;
	}
	return 0;
}