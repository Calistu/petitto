GtkWidget *cad_menu_get_icon_view(){

	int N_COLUMNS=3;
	GtkTreeIter iter;
	GtkWidget *icon_view = gtk_icon_view_new();
	cad_icos_model = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING,GDK_TYPE_PIXBUF,G_TYPE_INT);

	gtk_tree_store_append(cad_icos_model,&iter,NULL);
  gtk_tree_store_set(cad_icos_model,
    &iter,
		0,janelas_nomes[REG_CAD_PROD],
		1, gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(PROD_IMG))),
    2,REG_CAD_PROD,-1);

  gtk_tree_store_append(cad_icos_model,&iter,NULL);
  gtk_tree_store_set(cad_icos_model,
    &iter,0,janelas_nomes[REG_CAD_TER],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(TERC_IMG))),
    2,REG_CAD_TER,-1);

  gtk_tree_store_append(cad_icos_model,&iter,NULL);
  gtk_tree_store_set(cad_icos_model,
    &iter,
		0,janelas_nomes[REG_CAD_OPER],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(OPR_IMG))),
    2,REG_CAD_OPER,-1);

  gtk_tree_store_append(cad_icos_model,&iter,NULL);
  gtk_tree_store_set(cad_icos_model,
    &iter,
		0,janelas_nomes[REG_CAD_UND],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(UND_IMG))),
    2,REG_CAD_UND,-1);

	gtk_tree_store_append(cad_icos_model,&iter,NULL);
  gtk_tree_store_set(cad_icos_model,
    &iter,
		0,janelas_nomes[REG_CAD_GRP],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(GRP_IMG))),
    2,REG_CAD_GRP,-1);

  gtk_tree_store_append(cad_icos_model,&iter,NULL);
  gtk_tree_store_set(cad_icos_model,
    &iter,
		0,janelas_nomes[REG_CAD_COND],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(PAG_IMG))),
    2,REG_CAD_COND,-1);

	gtk_tree_store_append(cad_icos_model,&iter,NULL);
  gtk_tree_store_set(cad_icos_model,
    &iter,
		0,janelas_nomes[REG_CAD_RELAT],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(REL_IMG))),
    2,REG_CAD_RELAT,-1);

	gtk_tree_store_append(cad_icos_model,&iter,NULL);
  gtk_tree_store_set(cad_icos_model,
    &iter,
		0,janelas_nomes[REG_CAD_CEP],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(CAD_CEP_IMG))),
    2,REG_CAD_CEP,-1);

	gtk_tree_store_append(cad_icos_model,&iter,NULL);
  gtk_tree_store_set(cad_icos_model,
    &iter,
		0,janelas_nomes[CAD_BANCOS_WND],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(BANCOS_IMG))),
    2,CAD_BANCOS_WND,-1);

  gtk_icon_view_set_model(GTK_ICON_VIEW(icon_view),GTK_TREE_MODEL(cad_icos_model));

	gtk_icon_view_set_columns (GTK_ICON_VIEW(icon_view),3);
  gtk_icon_view_set_text_column(GTK_ICON_VIEW(icon_view),0);
  gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(icon_view),1);
	gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(icon_view),GTK_SELECTION_BROWSE);
	gtk_icon_view_set_margin(GTK_ICON_VIEW(icon_view),10);
	//gtk_icon_view_set_activate_on_single_click(GTK_ICON_VIEW(icon_view),TRUE);

	g_signal_connect(icon_view,"item-activated",G_CALLBACK(icon_view_select_caller), cad_icos_model);
	g_signal_connect(icon_view,"item-activated",G_CALLBACK(menu_icon_view_select), janelas_gerenciadas.vetor_janelas[REG_MENU_WND].janela_pointer);

	return icon_view;
}
