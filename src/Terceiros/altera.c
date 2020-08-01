int altera_ter()
{
	char task[10];
	char query[MAX_QUERY_LEN];
	int pos=0;
	gchar *cod;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	GtkTextBuffer *buffer;
	GtkTextIter inicio,fim;
	alterando_ter=1;

	if(code_terc()!=0)
		return 0;

	sprintf(query,"select * from terceiros where code = '%s';",codigos_ter);
	g_print("query: %s\n",query);
	autologger(query);
	estado = consultar(query);
	g_print("verificando estado da alteracao\n");
	campo = mysql_fetch_row(estado);

	if(campo==NULL)
	{
		g_print("terceiro não existe para ser alterado\n");
		popup(NULL,"Terceiro não existe");
		cancelar_ter();
		return 1;
	}

	if(campo[COD_TER_NFE_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(code_ter_nfe_field),campo[COD_TER_NFE_COL]);

	if(campo[RAZ_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(name_ter_field),campo[RAZ_TER_COL]);

	if(campo[DOC_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(doc_ter_field),campo[DOC_TER_COL]);

	if(atoi(campo[TDOC_TER_COL])==1)
	{
		gtk_combo_box_set_active (GTK_COMBO_BOX(doc_combo),1);
	}
	if(atoi(campo[TDOC_TER_COL])==2)
	{
		gtk_combo_box_set_active (GTK_COMBO_BOX(doc_combo),2);
	}
	if(atoi(campo[TDOC_TER_COL])==3)
	{
		gtk_combo_box_set_active (GTK_COMBO_BOX(doc_combo),3);
	}
	if(campo[IE_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(inscr_ter_field),campo[IE_TER_COL]);
	//campo[4] = tipoter string
	if(campo[TIPI_TER_COL]!=NULL)
	{
		if(atoi(campo[TIPI_TER_COL])==0)
		{
			gtk_combo_box_set_active (GTK_COMBO_BOX(type_ter_field),0);
		}
		if(atoi(campo[TIPI_TER_COL])==1)
		{
			gtk_combo_box_set_active (GTK_COMBO_BOX(type_ter_field),1);
		}
		if(atoi(campo[TIPI_TER_COL])==2)
		{
			gtk_combo_box_set_active (GTK_COMBO_BOX(type_ter_field),2);
		}
		if(atoi(campo[TIPI_TER_COL])==3)
		{
			gtk_combo_box_set_active (GTK_COMBO_BOX(type_ter_field),3);
		}
	}

	if(campo[CEP_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(cep_ter_field),campo[CEP_TER_COL]);

	if(campo[END_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(address_ter_field),campo[END_TER_COL]);

	if(campo[BAIR_TER_COL]!=NULL)
			gtk_entry_set_text(GTK_ENTRY(bairro_ter_field),campo[BAIR_TER_COL]);

	if(campo[CID_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(cidade_ter_field),campo[CID_TER_COL]);

	if(campo[UF_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(uf_ter_field),campo[UF_TER_COL]);

	if(campo[REND_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(address_num_field),campo[REND_TER_COL]);

	if(campo[TRUA_TER_COL]!=NULL)
		gtk_combo_box_set_active(GTK_COMBO_BOX(rua_combo),atoi(campo[TRUA_TER_COL]));

	if(campo[TEL_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(telefone_ter_field),campo[TEL_TER_COL]);

	if(campo[CTEL_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(contatot_ter_field),campo[CTEL_TER_COL]);

	if(campo[CEL_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(celular_ter_field),campo[CEL_TER_COL]);

	if(campo[CCEL_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(contatoc_ter_field),campo[CCEL_TER_COL]);

	if(campo[EMAIL_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(email_ter_field),campo[EMAIL_TER_COL]);

	if(campo[CEMAIL_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(contatoe_ter_field),campo[CEMAIL_TER_COL]);

	if(campo[TRSP_COD_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(transp_codigo_entry),campo[TRSP_COD_COL]);
	gtk_widget_activate(transp_codigo_entry);

	if(campo[TRSP_LOGR_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(transp_logradouro_entry),campo[TRSP_LOGR_COL]);

	if(campo[TRSP_NUM_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(transp_num_entry),campo[TRSP_NUM_COL]);

	if(campo[TRSP_CID_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(transp_cidade_entry),campo[TRSP_CID_COL]);

	if(campo[TRSP_BAIR_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(transp_estado_entry),campo[TRSP_BAIR_COL]);

	if(campo[TRSP_UF_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(transp_estado_entry),campo[TRSP_UF_COL]);

	if(campo[TRSP_CEP_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(transp_cep_entry),campo[TRSP_CEP_COL]);

	if(campo[TRSP_TEL_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(transp_telefone_entry),campo[TRSP_TEL_COL]);

	if(campo[PRAZ_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(prazo_ter_field),campo[PRAZ_TER_COL]);

	if(campo[FLAG_MIN_FRT_PAG_COL]!=NULL)
	{
		if(atoi(campo[FLAG_MIN_FRT_PAG_COL])==0)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(frete_pago_flag),FALSE);
		else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(frete_pago_flag),TRUE);
	}

	if(campo[VLR_MIN_FRT_PAG_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(frete_pago_entry),campo[VLR_MIN_FRT_PAG_COL]);

	if(campo[OBS_TER_COL]!=NULL)
		strcpy(observacoes_ter,campo[OBS_TER_COL]);
	else
		strcpy(observacoes_ter,"");

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacoes_ter_field));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),observacoes_ter,strlen(observacoes_ter));

	gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);

	memset(query,0x0,strlen(query));

	gtk_widget_set_sensitive(GTK_WIDGET(code_ter_field),FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(alterar_ter_buttom),FALSE);
	gtk_widget_set_sensitive(psq_ter_button,FALSE);
	gtk_label_set_text(GTK_LABEL(acao_atual2),"Alterando");
	return 0;

}
