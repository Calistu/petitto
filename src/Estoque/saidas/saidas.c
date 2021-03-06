#include "campos/codigo.c"
#include "campos/produto.c"
#include "campos/tipo.c"
#include "campos/data.c"
#include "campos/quantidade.c"
#include "campos/cliente.c"
#include "campos/estoque.c"
#include "campos/pedido.c"
#include "campos/obs.c"


#include "cancelar.c"
#include "confirmar.c"
#include "excluir.c"
#include "alterar.c"

void inicializar_saidas()
{
	est_said_client_gchar = malloc(MAX_CODE_LEN);
	est_said_prod_gchar = malloc(MAX_CODE_LEN);
	est_said_qnt_gchar = malloc(MAX_CODE_LEN);
	est_said_data_gchar	 = malloc(MAX_CODE_LEN);
	find_subgrupos_restrict = malloc(sizeof(struct duo_widget));
}

int est_saidas(){
	mov_said_est_limit =0;
	GtkWidget *janela, *grid;
	char code[MAX_CODE_LEN];
	GtkWidget *est_said_cod_frame, *est_said_cod_fixed;
	GtkWidget *est_said_prod_frame, *est_said_prod_fixed;
	GtkWidget *est_said_qnt_frame, *est_said_qnt_fixed;
	GtkWidget *est_said_tipo_fixed;
	GtkWidget *est_said_data_frame, *est_said_data_fixed;
	GtkWidget *est_said_est_frame, *est_said_est_fixed;
	GtkWidget *est_said_ped_frame, *est_said_ped_fixed;
	GtkWidget *est_said_client_frame, *est_said_client_fixed;
	GtkWidget *est_said_obs_frame, *est_said_obs_fixed, *est_said_obs_scroll;

	GtkWidget *est_said_cod_box;
	GtkWidget *est_said_prod_box;
	GtkWidget *est_said_qnt_box;
	GtkWidget *est_said_tipo_box;
	GtkWidget *est_said_data_box;
	GtkWidget *est_said_client_box;
	GtkWidget *est_said_obs_box;

	GtkWidget *psq_prod_button, *psq_subgrp_button, *psq_client_button, *psq_data_button;
	GtkWidget *produto_box, *subgrupo_box, *cliente_box;

	GtkWidget *caixa_fixed, *caixa_opcoes, *caixa_grande;

	char query[MAX_QUERY_LEN],nome_estoque[MAX_EST_NOME+MAX_CODE_LEN*2];
	MYSQL_RES *res;
	MYSQL_ROW row;
	int cont=0;

	alterando_mov_said_est=0;
	concluindo_mov_said_est=0;

	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Saidas");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"list-remove");

	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));

	inicializar_saidas();

	grid = gtk_grid_new();

	est_said_confirma_button = gtk_button_new_with_label("Concluir");
	gtk_button_set_image(GTK_BUTTON(est_said_confirma_button),gtk_image_new_from_file(IMG_OK));
	est_said_cancela_button = gtk_button_new_with_label("Cancelar");
	gtk_button_set_image(GTK_BUTTON(est_said_cancela_button),gtk_image_new_from_file(IMG_CANCEL));
	est_said_altera_button = gtk_button_new_with_label("Alterar");
	gtk_button_set_image(GTK_BUTTON(est_said_altera_button),gtk_image_new_from_file(IMG_ALTER));
	est_said_exclui_button = gtk_button_new_with_label("Excluir");
	gtk_button_set_image(GTK_BUTTON(est_said_exclui_button),gtk_image_new_from_file(IMG_EXCLUI));

	caixa_opcoes = gtk_box_new(0,0);
	caixa_fixed = gtk_fixed_new();
	caixa_grande = gtk_box_new(1,0);

	gtk_box_pack_start(GTK_BOX(caixa_opcoes),est_said_confirma_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),est_said_cancela_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),est_said_altera_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_opcoes),est_said_exclui_button,0,0,5);
	gtk_fixed_put(GTK_FIXED(caixa_fixed),caixa_opcoes,60,20);

	produto_box = gtk_box_new(0,0);
	subgrupo_box = gtk_box_new(0,0);
	cliente_box = gtk_box_new(0,0);

	est_said_psqcod_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(est_said_psqcod_button),gtk_image_new_from_file(IMG_PESQ));
	psq_data_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(psq_data_button),gtk_image_new_from_file(IMG_PESQ));
	psq_prod_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(psq_prod_button),gtk_image_new_from_file(IMG_PESQ));
	psq_subgrp_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(psq_subgrp_button),gtk_image_new_from_file(IMG_PESQ));
	psq_client_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(psq_client_button),gtk_image_new_from_file(IMG_PESQ));

	est_said_cod_frame = gtk_frame_new("Cód:. Saída");
	est_said_cod_fixed = gtk_fixed_new();
	est_said_cod_box = gtk_box_new(0,0);
	est_said_cod_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(est_said_cod_entry),5);
	gtk_box_pack_start(GTK_BOX(est_said_cod_box),est_said_cod_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(est_said_cod_box),est_said_psqcod_button,0,0,0);
	gtk_container_add(GTK_CONTAINER(est_said_cod_frame),est_said_cod_box);
	gtk_fixed_put(GTK_FIXED(est_said_cod_fixed),est_said_cod_frame,20,5);

	est_said_prod_frame = gtk_frame_new("Produto");
	est_said_prod_fixed = gtk_fixed_new();
	est_said_prod_entry = gtk_entry_new();
	est_said_campo_nome_prod = gtk_entry_new();
	est_said_prod_box = gtk_box_new(1,0);
	gtk_entry_set_placeholder_text(GTK_ENTRY(est_said_campo_nome_prod),"Nome Produto");
	gtk_editable_set_editable(GTK_EDITABLE(est_said_campo_nome_prod),FALSE);
	gtk_box_pack_start(GTK_BOX(produto_box),est_said_prod_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(produto_box),psq_prod_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(produto_box),est_said_campo_nome_prod,0,0,0);
	gtk_container_add(GTK_CONTAINER(est_said_prod_frame),produto_box);
	gtk_fixed_put(GTK_FIXED(est_said_prod_fixed),est_said_prod_frame,20,5);
	gtk_entry_set_width_chars(GTK_ENTRY(est_said_prod_entry),5);

	est_said_est_frame = gtk_frame_new("Estoque");
	est_said_est_fixed = gtk_fixed_new();
	est_said_est_combo = gtk_combo_box_text_new();
	gtk_container_add(GTK_CONTAINER(est_said_est_frame),est_said_est_combo);
	gtk_fixed_put(GTK_FIXED(est_said_est_fixed),est_said_est_frame,60,60);
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(est_said_est_combo),"Escolha o estoque");
	sprintf(query,"select code,nome from estoques");
	cont=1;
	if((res = consultar(query))==NULL){
		popup(NULL,"Erro ao buscar estoques");
		return 1;
	}
	while((row = mysql_fetch_row(res))!=NULL){
		sprintf(nome_estoque,"%s - %s",row[0],row[1]);
		gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(est_said_est_combo),cont+1,row[0],nome_estoque);
		cont++;
	}
	if(cont==1){
		popup(NULL,"Sem nenhum estoque cadastrado");
		return 1;
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(est_said_est_combo),1);


	est_said_qnt_frame = gtk_frame_new("Quantidade");
	est_said_qnt_entry = gtk_spin_button_new_with_range(0,100000000,0.005);
	est_said_qnt_fixed = gtk_fixed_new();
	est_said_qnt_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(est_said_qnt_box),est_said_qnt_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(est_said_qnt_frame),est_said_qnt_box);
	gtk_fixed_put(GTK_FIXED(est_said_qnt_fixed),est_said_qnt_frame,20,20);

	est_said_tipo_combo = gtk_combo_box_text_new();
	est_said_tipo_fixed = gtk_fixed_new();
	est_said_tipo_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(est_said_tipo_box),est_said_tipo_combo,0,0,0);
	gtk_fixed_put(GTK_FIXED(est_said_tipo_fixed),est_said_tipo_box,60,20);
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(est_said_tipo_combo),"Tipo Movimento");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(est_said_tipo_combo),"Venda");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(est_said_tipo_combo),"Devolução Compra");
	gtk_combo_box_set_active(GTK_COMBO_BOX(est_said_tipo_combo),0);

	est_said_data_frame = gtk_frame_new("Data");
	est_said_data_entry = gtk_entry_new();
	est_said_data_fixed = gtk_fixed_new();
	est_said_data_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(est_said_data_box),est_said_data_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(est_said_data_box),psq_data_button,0,0,0);
	gtk_container_add(GTK_CONTAINER(est_said_data_frame),est_said_data_box);
	gtk_fixed_put(GTK_FIXED(est_said_data_fixed),est_said_data_frame,60,20);

	est_said_client_frame = gtk_frame_new("Cliente/Fornecedor");
	est_said_client_fixed = gtk_fixed_new();
	est_said_client_entry = gtk_entry_new();
	est_said_campo_nome_client = gtk_entry_new();
	est_said_client_box = gtk_box_new(1,0);
	gtk_entry_set_placeholder_text(GTK_ENTRY(est_said_campo_nome_client),"Nome Cliente");
	gtk_editable_set_editable(GTK_EDITABLE(est_said_campo_nome_client),FALSE);
	gtk_box_pack_start(GTK_BOX(cliente_box),est_said_client_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(cliente_box),psq_client_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(cliente_box),est_said_campo_nome_client,0,0,0);
	gtk_entry_set_width_chars(GTK_ENTRY(est_said_client_entry),5);
	gtk_container_add(GTK_CONTAINER(est_said_client_frame),cliente_box);
	gtk_fixed_put(GTK_FIXED(est_said_client_fixed),est_said_client_frame,20,20);

	est_said_ped_frame = gtk_frame_new("Vin. Pedido");
	est_said_ped_fixed = gtk_fixed_new();
	est_said_ped_entry = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(est_said_ped_frame),est_said_ped_entry);
	gtk_fixed_put(GTK_FIXED(est_said_ped_fixed),est_said_ped_frame,60,20);
	gtk_entry_set_width_chars(GTK_ENTRY(est_said_ped_entry),15);

	est_said_obs_frame = gtk_frame_new("Observações");
	est_said_obs_fixed = gtk_fixed_new();
	est_said_obs_box = gtk_box_new(0,0);
	est_said_obs_view = gtk_text_view_new();
	est_said_obs_scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_box_pack_start(GTK_BOX(est_said_obs_box),est_said_obs_view,0,0,0);
	gtk_container_add(GTK_CONTAINER(est_said_obs_scroll),est_said_obs_box	);
	gtk_container_add(GTK_CONTAINER(est_said_obs_frame),est_said_obs_scroll	);
	gtk_fixed_put(GTK_FIXED(est_said_obs_fixed),est_said_obs_frame,20,20);
	gtk_widget_set_size_request(est_said_obs_view, 300, 80);
	gtk_widget_set_size_request(est_said_obs_scroll, 300, 80);
	gtk_widget_set_size_request(est_said_obs_box, 300, 80);

	gtk_grid_attach(GTK_GRID(grid),est_said_cod_fixed,0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),est_said_data_fixed,1,0,1,1);

	gtk_grid_attach(GTK_GRID(grid),est_said_client_fixed,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),est_said_tipo_fixed,1,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),est_said_est_fixed,1,1,1,1);

	gtk_grid_attach(GTK_GRID(grid),est_said_prod_fixed,0,2,1,1);

	gtk_grid_attach(GTK_GRID(grid),est_said_qnt_fixed,0,3,1,1);
	gtk_grid_attach(GTK_GRID(grid),est_said_ped_fixed,1,3,1,1);

	gtk_grid_attach(GTK_GRID(grid),est_said_obs_fixed,0,4,1,1);

	g_signal_connect(est_said_cod_entry,"activate",G_CALLBACK(est_said_codigo_fun),NULL);

	g_signal_connect(est_said_data_entry,"activate",G_CALLBACK(est_said_data_fun),NULL);
	g_signal_connect(psq_data_button,"clicked",G_CALLBACK(psq_data),est_said_data_entry);

	g_signal_connect(est_said_client_entry,"activate",G_CALLBACK(est_said_client_fun),NULL);
	g_signal_connect(psq_client_button,"clicked",G_CALLBACK(psq_ter),est_said_client_entry);

	g_signal_connect(est_said_prod_entry,"activate",G_CALLBACK(est_said_produto_fun),NULL);
	g_signal_connect(psq_prod_button,"clicked",G_CALLBACK(psq_prod),est_said_prod_entry);

	g_signal_connect(est_said_tipo_combo,"changed",G_CALLBACK(est_said_tipo_fun),NULL);

	g_signal_connect(est_said_qnt_entry,"activate",G_CALLBACK(est_said_qnt_fun),NULL);

	g_signal_connect(est_said_ped_entry,"activate",G_CALLBACK(est_said_ped_fun),NULL);

	g_signal_connect(est_said_psqcod_button,"clicked",G_CALLBACK(psq_est_said_mov),est_said_cod_entry);

	g_signal_connect(est_said_confirma_button,"clicked",G_CALLBACK(est_said_confirmar_fun),NULL);
	g_signal_connect(est_said_exclui_button,"clicked",G_CALLBACK(est_said_excluir_fun),NULL);
	g_signal_connect(est_said_altera_button,"clicked",G_CALLBACK(est_said_alterar_fun),NULL);
	g_signal_connect(est_said_cancela_button,"clicked",G_CALLBACK(est_said_cancelar_fun),NULL);

	gtk_box_pack_start(GTK_BOX(caixa_grande),grid,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),caixa_fixed,0,0,20);

	est_said_cancelar_fun();

	gtk_container_add(GTK_CONTAINER(janela),caixa_grande);

	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
	gtk_widget_set_size_request(janela,580,400);
	gtk_widget_show_all(janela);

	return 0;
}
