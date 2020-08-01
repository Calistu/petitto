#define GTK_RESPONSE_RESTART 3
int init();
static int encerrar_manualmente=0;

int encerrar(GtkWidget *buttton,GtkWindow *parent)
{
	GtkWidget * mensagem;
	GtkWidget *sair_label,*sair_box,*sair_fixed;
	int resultado, handler_id=0;

	if(janelas_gerenciadas.principal.sys_close_wnd == 1)
		return 0;

	mensagem = gtk_dialog_new_with_buttons("Sair?",parent,4,"Sim",GTK_RESPONSE_ACCEPT,"Não",GTK_RESPONSE_REJECT,NULL);

	gtk_window_set_icon_name(GTK_WINDOW(mensagem),"system-log-out");
	gtk_window_set_position(GTK_WINDOW(mensagem),3);

	gtk_window_set_keep_above(GTK_WINDOW(mensagem),TRUE);

	janelas_gerenciadas.encerramento.reg_id = REG_WIN_ENCERRA;
	janelas_gerenciadas.encerramento.aberta = 1;
	if(ger_janela_aberta(mensagem, &janelas_gerenciadas.encerramento))
		return 1;

	janelas_gerenciadas.encerramento.janela_pointer = mensagem;

	handler_id = g_signal_connect(mensagem,"destroy",G_CALLBACK(encerrando),NULL);

	sair_label = gtk_label_new("Você deseja realmente sair ?");
	sair_fixed = gtk_fixed_new();
	sair_box = gtk_bin_get_child(GTK_BIN(mensagem));
	gtk_dialog_set_default_response(GTK_DIALOG(mensagem),GTK_RESPONSE_REJECT);
	gtk_box_pack_start(GTK_BOX(sair_box),sair_label,0,0,10);
	gtk_widget_show_all(mensagem);

	resultado = gtk_dialog_run(GTK_DIALOG(mensagem));

	switch(resultado)
	{
		case GTK_RESPONSE_ACCEPT:
			encerrando();
			break;

		case GTK_RESPONSE_REJECT:
			g_signal_handler_disconnect(mensagem,handler_id);

			if(encerrar_manualmente){
				encerrar_manualmente = 0;
			}
			else
			{
				if(desktop()!=0){
						popup(NULL,"Erro na reinicialização");
						encerrando();
				}
			}
			autologger("Reiniciando janela principal");
			break;
	}

	if(GTK_IS_WIDGET(mensagem))
		gtk_widget_destroy(mensagem);

	return 0;
}

void botao_encerrar(){
	encerrar_manualmente = 1;
	encerrar(NULL,GTK_WINDOW(janelas_gerenciadas.principal.janela_pointer));
}

void fechar_sessao(){
	int err;
	char query[MAX_QUERY_LEN];

	sprintf(query,"insert into wnd_logger(id_janela,nome_janela,estado,qnt_aberta,operador,tempo) values(%i,'%s',%i,%i,%i,NOW())",
  janelas_gerenciadas.principal.reg_id,
  "Reiniciando...",
  0,
  0,
  sessao_oper.code);
	err = mysql_query(&conectar,query);
	if(err!=0)
	{
		popup(NULL,"Não foi possivel salvar status da sessão\n");
		file_logger(query);
		file_logger((char*)mysql_error(&conectar));
		return ;
	}

	//variavel de encerramento ocorrida pelo proprio sistema (logoff)
	janelas_gerenciadas.principal.sys_close_wnd = 1;

	gtk_widget_destroy(janelas_gerenciadas.principal.janela_pointer);
	init();

	janelas_gerenciadas.principal.sys_close_wnd = 0;

}
