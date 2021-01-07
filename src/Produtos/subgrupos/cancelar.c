int cancela_subgrupo()
{
	char code[MAX_CODE_LEN];
	sprintf(code,"%i",tasker("grupos"));
	gtk_entry_set_text(GTK_ENTRY(cod_subgrp_entry),code);
	gtk_entry_set_text(GTK_ENTRY(nome_subgrp_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cod_subgrp_pai_entry),"");
	gtk_entry_set_text(GTK_ENTRY(campo_nome_subgrg_pai),"");
	gtk_widget_grab_focus(nome_subgrp_entry);
	gtk_widget_set_sensitive(cod_subgrp_entry,TRUE);
	gtk_widget_set_sensitive(psq_subgrpo_button,TRUE);
	gtk_widget_set_sensitive(altera_subgrp_button,TRUE);
	alterando_subgrp = 0;
	concluindo_subgrp = 0;

	GtkTreeStore *modelo = GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(cad_grp_treeview)));
	g_object_ref(G_OBJECT(modelo));
  gtk_tree_view_set_model(GTK_TREE_VIEW(cad_grp_treeview),NULL);
  gtk_tree_store_clear(modelo);
  gtk_tree_view_set_model(GTK_TREE_VIEW(cad_grp_treeview),GTK_TREE_MODEL(modelo));

	if(!grp_get_tree(modelo, 1, NULL))
		return 1;

	return 0;
}
