int rel_fix_fin_rec_ped1_fun(){
  rel_fix_fin_rec_ped_gchar1 = (gchar *)gtk_entry_get_text(GTK_ENTRY(rel_fix_fin_rec_ped_entry1));

  gtk_widget_grab_focus(rel_fix_fin_rec_ped_entry2);
  return 0;
}

int rel_fix_fin_rec_ped2_fun(){
  rel_fix_fin_rec_ped_gchar2 = (gchar *)gtk_entry_get_text(GTK_ENTRY(rel_fix_fin_rec_ped_entry2));

  if(atoi(rel_fix_fin_rec_ped_gchar2) < atoi(rel_fix_fin_rec_ped_gchar1)){
    char char1[strlen(rel_fix_fin_rec_ped_gchar1)];
    char char2[strlen(rel_fix_fin_rec_ped_gchar2)];

    strcpy(char1,rel_fix_fin_rec_ped_gchar1);
    strcpy(char2,rel_fix_fin_rec_ped_gchar2);

    gtk_entry_set_text(GTK_ENTRY(rel_fix_fin_rec_ped_entry1),char2);
    gtk_entry_set_text(GTK_ENTRY(rel_fix_fin_rec_ped_entry2),char1);
  }
  gtk_widget_grab_focus(rel_fix_fin_rec_tit_entry1);
  return 0;
}
