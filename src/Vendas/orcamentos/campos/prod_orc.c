int orc_prod_calc_saldo(int posicao, int prod_code){

	char query[MAX_QUERY_LEN];
	MYSQL_RES *vetor;
	MYSQL_ROW campos;

	if(!orc_estoque.produtos[prod_code])
		orc_estoque.produtos[prod_code] = malloc(sizeof(struct _orc_estoque));

	operacao_orc_orc();

	sprintf(query,"select SUM(entradas) - SUM(saidas) %c %i from movimento_estoque where produto = %i and estoque = %i",
	sinal_operacao_int,
	atoi(qnt_prod_orc_gchar),
	prod_code,
	orc_params.est_orc_padrao);

	if(!(vetor = consultar(query))){
		popup(NULL,"Erro ao consultar saldo do estoque");
		return 1;
	}

	orc_estoque.produtos[prod_code]->mov_qnt = mysql_num_rows(vetor);

	if((campos = mysql_fetch_row(vetor))){

		orc_estoque.produtos[prod_code]->saldo = atof(campos[0]);

		for(int cont=1;cont<MAX_PROD_ORC;cont++){
			if(ativos[cont].id)
				if(ativos[cont].produto == prod_code)
					if(produto_inserido[cont])
						orc_estoque.produtos[prod_code]->saldo_usado = 0;
		}

		for(int cont=1;cont<MAX_PROD_ORC;cont++){
			if(ativos[cont].id)
				if(produto_inserido[cont])
					if(ativos[cont].produto == prod_code){
						orc_estoque.produtos[prod_code]->saldo_usado += ativos[cont].qnt_f;
					}
		}

		orc_estoque.produtos[prod_code]->saldo_usado = orc_estoque.produtos[prod_code]->saldo_usado + orc_estoque.produtos[prod_code]->saldo;
		orc_estoque.produtos[prod_code]->saldo_liquido = orc_estoque.produtos[prod_code]->saldo_usado;

		sprintf(query,"select saldo_min from saldo_min where produto = %i and estoque = %i",
		prod_code,
		orc_params.est_orc_padrao);

		if(!(vetor = consultar(query))){
			popup(NULL,"Não foi possivel verificar saldo mínimo do produto");
			return 1;
		}

		if((campos = mysql_fetch_row(vetor))!=NULL){
			orc_estoque.produtos[prod_code]->saldo_min = atof(campos[0]);
		}
	}

	char saldo[MAX_PRECO_LEN];
	sprintf(saldo,"%.2f",orc_estoque.produtos[prod_code]->saldo_usado);
	gtk_entry_set_text(GTK_ENTRY(saldo_prod_orc_entry[posicao]),saldo);
	return 0;
}

int ha_prods(){
	for(int cont=1;cont<=MAX_PROD_ORC;cont++){
		if(produto_inserido[cont] == 1)
			return 1;
	}
	return 0;
}

int codigo_prod_orc(GtkWidget *widget,int posicao)
{
	char query[MAX_QUERY_LEN];
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	codigo_prod_orc_gchar = malloc(MAX_CODE_LEN);
	codigo_prod_orc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(codigo_prod_orc_entry[posicao]));
	ativos[posicao].produto = 0;

	orc_estoque.produtos[atoi(codigo_prod_orc_gchar)] = malloc(sizeof(struct _orc_estoque_prods));

	if(adicionando_linha_ignore == 1){
		gtk_entry_set_text(GTK_ENTRY(codigo_prod_orc_entry[posicao]),"");
		gtk_widget_grab_focus(codigo_prod_orc_entry[posicao]);
		return 0;
	}

	if(strlen(codigo_prod_orc_gchar)<=0)
	{
		produto_inserido[posicao] = 0;
		if(posicao>1){
			gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
			gtk_widget_grab_focus(orc_transp_codigo_entry);
			return 0;
		}

		popup(NULL,"O código do produto deve ser inserido");
		gtk_widget_grab_focus(codigo_prod_orc_entry[posicao]);
		return 1;
	}
	if(stoi(codigo_prod_orc_gchar)==-1)
	{
		popup(NULL,"O código do produto deve ser numérico");
		gtk_widget_grab_focus(codigo_prod_orc_entry[posicao]);
		return 1;
	}
	sprintf(query,"select p.nome, u.nome, p.grupo from produtos as p inner join unidades as u on p.unidades= u.code where p.code = %s",codigo_prod_orc_gchar);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		autologger("Erro na query de produtos no orcamento\n");
		gtk_widget_grab_focus(codigo_prod_orc_entry[posicao]);
		return 1;
	}

	if(!(campos = mysql_fetch_row(vetor)))
	{
		popup(NULL,"Produto não existente");
		gtk_widget_grab_focus(codigo_prod_orc_entry[posicao]);
		gtk_widget_grab_focus(codigo_prod_orc_entry[posicao]);
		return 1;
	}

	ativos[posicao].produto = atoi(codigo_prod_orc_gchar);

	if(campos[0])
		strcpy(ativos[posicao].produto_nome,campos[0]);

	gtk_entry_set_text(GTK_ENTRY(descricao_prod_orc_entry[posicao]),campos[0]);
	if(strlen(campos[1])>15)
	{
		campos[1][15] = '.';
		campos[1][15] = '\0';
	}

	produto_inserido[posicao] = 1;
	gtk_label_set_text(GTK_LABEL(qnt_prod_orc_label[posicao]),campos[1]);

	int prod_code = atoi(codigo_prod_orc_gchar);

	if(orc_prod_calc_saldo(posicao, prod_code))
		return 1;

	gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
	return 0;
}
