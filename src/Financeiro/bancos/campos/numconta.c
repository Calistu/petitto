int cad_bancos_conta_fun(){

  cad_bancos_conta_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cad_bancos_conta_entry));


  if( strlen(cad_bancos_conta_gchar) <= 0 ){
    popup(NULL,"O número deve ser preenchido");
    return 1;
  }

  gtk_widget_grab_focus(cad_bancos_agencia_entry);
  return 0;
}
