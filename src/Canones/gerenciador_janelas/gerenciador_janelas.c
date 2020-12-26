int wnd_logger(janelas_info *struct_wnd)
{
  char query[MAX_QUERY_LEN];
  char janela_nome[200];
	int err=1;
	if(primeira_conexao==0){
		if(!mysql_init(&conectar)){
			popup(NULL,"Não foi possivel conectar ao servidor");
			autologger("Não foi possivel conectar ao servidor");
			autologger((char*)mysql_error(&conectar));
			primeira_conexao=0;
			return 1;
		}
		if(!mysql_real_connect(&conectar,server_confs.server_endereco,server_confs.server_user,server_confs.server_senha,server_confs.server_database,0,NULL,0)){
			popup(NULL,"Não foi possivel conectar ao servidor");
			file_logger("Não foi possivel conectar ao servidor");
			file_logger((char*)mysql_error(&conectar));
			primeira_conexao=0;
			return 1;
		}
		if (mysql_set_character_set(&conectar, "utf8")){
			file_logger("Não foi possivel setar novo caracter");
		}
    primeira_conexao=1;
	}
  strcpy(janela_nome,"");

  if(struct_wnd->reg_id <= REG_WIN_QNT)
    strcpy(janela_nome,janelas_nomes[struct_wnd->reg_id]);
  else{
    switch (struct_wnd->reg_id) {
      case REG_PRINC_WIN:
        strcpy(janela_nome,"Janela Principal");
        break;

      case REG_INIT_FUN_WIN:
        strcpy(janela_nome,"Janela de Inicialização");
        break;

      case REG_WIN_ENCERRA:
        strcpy(janela_nome,"Janela de encerramento");
        break;
    }
  }
  sprintf(query,"insert into wnd_logger(id_janela,nome_janela,estado,qnt_aberta,operador,tempo) values(%i,'%s',%i,%i,%i,NOW())",
  struct_wnd->reg_id,
  janela_nome,
  struct_wnd->aberta,
  struct_wnd->qnt_aberta,
  sessao_oper.code);

  err = mysql_query(&conectar,query);
	if(err!=0)
	{
		popup(NULL,"Erro de formato\n");
		if(logging == 0){
			file_logger(query);
			file_logger((char*)mysql_error(&conectar));
		}
		return err;
	}
	return 0;
}

int ger_janela_aberta(GtkWidget *janela, janelas_info *struct_wnd){
  char msg[200];

  struct_wnd->aberta = 1;
  struct_wnd->qnt_aberta++;

  if(struct_wnd->reg_id == REG_PRINC_WIN){
    file_logger("Janela principal aberta\nResetando gerenciador de janelas\n");
    iniciar_gerenciador_janela();
  }

  if(gerenciador_janela())
    return 1;

  if(struct_wnd->reg_id < REG_WIN_QNT){
    sprintf(msg,"Id Janela aberta: %i",struct_wnd->reg_id);
    autologger(msg);
    sprintf(msg,"Nome Janela aberta: %s",janelas_nomes[struct_wnd->reg_id]);
    autologger(msg);
  }
  wnd_logger(struct_wnd);

  return 0;
}

int ger_janela_fechada(GtkWidget *janela, janelas_info *struct_wnd){
  char msg[200];

  struct_wnd->aberta = 0;
  struct_wnd->qnt_aberta--;

  if(struct_wnd->reg_id == REG_PRINC_WIN){
    file_logger("Janela principal fechada\nResetando gerenciador de janelas\n");
    iniciar_gerenciador_janela();
  }

  if(gerenciador_janela())
    return 1;

  if(struct_wnd->reg_id <= REG_WIN_QNT){
    sprintf(msg,"Id Janela aberta: %i",struct_wnd->reg_id);
    autologger(msg);
    sprintf(msg,"Nome Janela aberta: %s",janelas_nomes[struct_wnd->reg_id]);
    autologger(msg);
  }

  wnd_logger(struct_wnd);
  return 0;
}

int iniciar_gerenciador_janela(){

  inativar_debug_fun();
  for(int cont=0;cont<REG_WIN_QNT;cont++){

    if(janelas_gerenciadas.vetor_janelas[cont].aberta){
        g_print("gerenciador finalizando %s ID: %i Contador %i\n",
        janelas_nomes[janelas_gerenciadas.vetor_janelas[cont].reg_id],
        janelas_gerenciadas.vetor_janelas[cont].reg_id,
        cont);

        if(!GTK_IS_WIDGET(janelas_gerenciadas.vetor_janelas[cont].janela_pointer)){
          g_print("Janela '%s' já estava fechada\n",
          janelas_nomes[janelas_gerenciadas.vetor_janelas[cont].reg_id]);
        }
        else
          gtk_widget_destroy(janelas_gerenciadas.vetor_janelas[cont].janela_pointer);
    }

    janelas_gerenciadas.vetor_janelas[cont].qnt_aberta = 0;
    janelas_gerenciadas.vetor_janelas[cont].qnt_fechada = 0;
    janelas_gerenciadas.vetor_janelas[cont].aberta = 0;
    janelas_gerenciadas.vetor_janelas[cont].janela_pointer = NULL;
  }

  janelas_gerenciadas.vetor_janelas[REG_CAD_PROD].fun = cad_prod;
  janelas_gerenciadas.vetor_janelas[REG_CAD_TER].fun = cad_terc;
  janelas_gerenciadas.vetor_janelas[CAD_TIT_PAG_WND].fun = cad_titulos_pagar;
  janelas_gerenciadas.vetor_janelas[CAD_TIT_REC_WND].fun = cad_titulos_receber;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_PROD_WIN].fun = relat_fix_prod;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_VND_WIN].fun = relat_fix_vnd;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_EST_WIN].fun = relat_fix_est;
  janelas_gerenciadas.vetor_janelas[CAD_BX_REC_WND].fun = cad_baixas_receber;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_FINREC_WIN].fun = rel_fix_fin_rec;
  janelas_gerenciadas.vetor_janelas[REG_REL_FIX_FINPAG_WIN].fun = rel_fix_fin_pag;
  janelas_gerenciadas.vetor_janelas[CAD_TRSP_WND].fun = trsp_cad_fun;

  janelas_gerenciadas.principal.aberta = 1;
  janelas_gerenciadas.principal.qnt_aberta = 1;
  janelas_gerenciadas.fundo_inicializacao.aberta = 0;
  janelas_gerenciadas.fundo_inicializacao.qnt_aberta = 0;

  return 0;
}

int gerenciador_janela(){

  for(int cont=0;cont<=REG_WIN_QNT;cont++){
      if(janelas_gerenciadas.vetor_janelas[cont].qnt_aberta>MAX_WND1_ABRT){
        if(janelas_gerenciadas.vetor_janelas[cont].janela_pointer)
          if(GTK_WINDOW(janelas_gerenciadas.vetor_janelas[cont].janela_pointer)){
            janelas_gerenciadas.vetor_janelas[cont].qnt_aberta = MAX_WND1_ABRT;
            gtk_window_present(GTK_WINDOW(janelas_gerenciadas.vetor_janelas[cont].janela_pointer));
            return 1;
          }
      }
  }

  return 0;
}