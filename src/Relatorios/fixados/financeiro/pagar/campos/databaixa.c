int rel_fix_fin_pag_databaixa1_fun(){
  rel_fix_fin_pag_databaixa_gchar1 = (gchar *)gtk_entry_get_text(GTK_ENTRY(rel_fix_fin_pag_databaixa_entry1));

  gtk_widget_grab_focus(rel_fix_fin_pag_databaixa_entry2);
  return 0;
}

int rel_fix_fin_pag_databaixa2_fun(){
  rel_fix_fin_pag_databaixa_gchar2 = (gchar *)gtk_entry_get_text(GTK_ENTRY(rel_fix_fin_pag_databaixa_entry2));

  gtk_widget_grab_focus(rel_fix_fin_pag_datavencimento_entry1);
  return 0;
}
