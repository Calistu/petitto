int conclui_grupo(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	gchar *nome;
	concluindo_grp=1;
	char query[MAX_QUERY_LEN];
	char mensagem[30];
	if(cod_grp()!=0)
		return 1;
	if(nome_grp()!=0)
		return 1;

	if(alterando_grp==0)
	{
		strcpy(mensagem,"Grupo criado com sucesso");
		sprintf(query,"insert into grupos(code,nome,pai,nivel) values('%s','%s',1,1)",grpcode, grpnome);
	}
	else
	{
		strcpy(mensagem,"Grupo alterado com sucesso");
		sprintf(query,"update grupos set nome = '%s' where code = %s",grpnome,grpcode);
	}
	if(enviar_query(query)!=0)
	{
		return 1;
	}
	cancela_grupo();

	popup(NULL,mensagem);

	return 0;
}
