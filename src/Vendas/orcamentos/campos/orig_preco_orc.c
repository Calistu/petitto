int orig_preco_prod_orc(GtkWidget *widget,int posicao){
	valor_orig[posicao] = gtk_combo_box_get_active(GTK_COMBO_BOX(orig_preco_prod_orc_combo[posicao]));

	gtk_widget_grab_focus(preco_prod_orc_entry[posicao]);
	return 0;
}
