#include "header.c"
#include "assinaturas.c"
#include "fornecedor.c"
#include "itens.c"


#define MM_TO_POINTS(mm)  mm*2
#define WB_TO_RGB(color) color/255.00

#define ORD_CMP_FORN_INFOS_HPOS 50
#define ORD_CMP_FORN_INFOS_VPOS 336.0

#define ORD_CMP_EMP_INFOS_VPOS 100
#define ORD_CMP_EMP_INFOS_HPOS 400.0

#define ASS_ORD_CMP_HPOS 50.0
#define ASS_ORD_CMP_VPOS 526.0

#define ORD_CMP_ENTRGA_HPOS 50.0
#define ORD_CMP_ENTRGA_VPOS 806.0

#define ORD_CMP_ITENS_HPOS 50.0
#define ORD_CMP_ITENS_VPOS 970.0

#define TITLE_TEXT_FONT_SIZE 24
#define DESCR_TEXT_FONT_SIZE 15

int gera_doc_ordcmp(struct _ord_cmp *ordem_cmp){

  PangoLayout *pango_layout;
  PangoFontDescription *pango_desc;

  cairo_surface_t *surface = cairo_pdf_surface_create(ORD_CMP_PDF_FILE, MM_TO_POINTS(594), MM_TO_POINTS(841));
  cairo_t *cairo = cairo_create(surface);

  cairo_rectangle(cairo, MM_TO_POINTS(5), MM_TO_POINTS(5), MM_TO_POINTS(584), MM_TO_POINTS(831));
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(6), MM_TO_POINTS(582), MM_TO_POINTS(132));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(10), MM_TO_POINTS(10), MM_TO_POINTS(582), MM_TO_POINTS(362));
  cairo_surface_t *logo_surface = cairo_image_surface_create_from_png(LOGO_MEDIA);
  cairo_set_source_surface(cairo, logo_surface ,10,10);
  cairo_fill(cairo);

  cairo_move_to(cairo, ORD_CMP_EMP_INFOS_HPOS, ORD_CMP_EMP_INFOS_VPOS );
  cairo_set_font_size(cairo, TITLE_TEXT_FONT_SIZE);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  gchar *nome_empresa = malloc(20 + strlen(cad_emp_strc.xNome));
  sprintf(nome_empresa, "%s", cad_emp_strc.xNome);
  cairo_show_text(cairo, nome_empresa);
  cairo_fill(cairo);

  cairo_move_to(cairo, ORD_CMP_EMP_INFOS_HPOS+450, ORD_CMP_EMP_INFOS_VPOS);
  gchar *num_ord = malloc(30);
  sprintf(num_ord, "Pedido Nº: %i", ordem_cmp->code);
  cairo_show_text(cairo, num_ord);
  cairo_fill(cairo);

  cairo_move_to(cairo, ORD_CMP_EMP_INFOS_HPOS, ORD_CMP_EMP_INFOS_VPOS+30);
  gchar *email = malloc(20 + strlen(cad_emp_strc.email));
  sprintf(email, "Email: %s", cad_emp_strc.email);
  cairo_show_text(cairo, email);
  cairo_fill(cairo);

  cairo_move_to(cairo, ORD_CMP_EMP_INFOS_HPOS+450, ORD_CMP_EMP_INFOS_VPOS+30);
  gchar *data_emissao = malloc(20+strlen(ordem_cmp->data_emissao));
  sprintf(data_emissao, "Data: %s", ordem_cmp->data_emissao);
  cairo_show_text(cairo, data_emissao);
  cairo_fill(cairo);

  cairo_move_to(cairo, ORD_CMP_EMP_INFOS_HPOS, ORD_CMP_EMP_INFOS_VPOS+60);
  cairo_show_text(cairo, "Solicitado por:");
  cairo_fill(cairo);

  cairo_move_to(cairo, ORD_CMP_EMP_INFOS_HPOS+450, ORD_CMP_EMP_INFOS_VPOS+60);
  gchar *data_entrega = malloc(20+strlen(ordem_cmp->data_entrega));
  sprintf(data_entrega, "Data Entrega: %s", ordem_cmp->data_entrega);
  cairo_show_text(cairo, data_entrega);
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(139), MM_TO_POINTS(582), MM_TO_POINTS(22));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_move_to(cairo, 500.0, 310.0);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_show_text(cairo, "Ordem de Compra");
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(162), MM_TO_POINTS(582), MM_TO_POINTS(80));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_move_to(cairo, ORD_CMP_FORN_INFOS_HPOS, ORD_CMP_FORN_INFOS_VPOS + 30);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  gchar *nome_fornecedor = malloc(20+strlen(ordem_cmp->fornecedor->razao));
  sprintf(nome_fornecedor, "Fornecedor: %s", ordem_cmp->fornecedor->razao);
  cairo_show_text(cairo, nome_fornecedor);
  cairo_fill(cairo);

  cairo_move_to(cairo, ORD_CMP_FORN_INFOS_HPOS, ORD_CMP_FORN_INFOS_VPOS + 60);
  gchar *ender_fornecedor = malloc(20+strlen(ordem_cmp->fornecedor->xLgr)+strlen(ordem_cmp->fornecedor->xBairro)+strlen(ordem_cmp->fornecedor->xCpl)+2);
  gchar *cmplt_fornecedor;
  if(strlen(ordem_cmp->fornecedor->xCpl)){
    cmplt_fornecedor = malloc(strlen(ordem_cmp->fornecedor->xCpl)+2);
    sprintf(cmplt_fornecedor, "(%s)", ordem_cmp->fornecedor->xCpl);
  }else{
    cmplt_fornecedor = strdup("");
  }
  sprintf(ender_fornecedor, "Endereço: %s, %s - %s %s", ordem_cmp->fornecedor->xLgr, ordem_cmp->fornecedor->c_nro ,ordem_cmp->fornecedor->xBairro, cmplt_fornecedor);
  cairo_show_text(cairo, ender_fornecedor);
  cairo_fill(cairo);

  cairo_move_to(cairo, ORD_CMP_FORN_INFOS_HPOS + 650, ORD_CMP_FORN_INFOS_VPOS + 60);
  gchar *cidade_fornecedor = malloc(20+strlen(ordem_cmp->fornecedor->xMun)+strlen(ordem_cmp->fornecedor->UF));
  sprintf(cidade_fornecedor, "Cidade: %s/%s", ordem_cmp->fornecedor->xMun, ordem_cmp->fornecedor->UF);
  cairo_show_text(cairo, cidade_fornecedor);
  cairo_fill(cairo);

  cairo_move_to(cairo, ORD_CMP_FORN_INFOS_HPOS, ORD_CMP_FORN_INFOS_VPOS + 90);
  gchar *telefone_fornecedor;
  if(ordem_cmp->fornecedor->contatos_qnt){
    telefone_fornecedor = malloc(20+strlen(ordem_cmp->fornecedor->contatos[0].telefone));
    sprintf(telefone_fornecedor, "Fone: %s", ordem_cmp->fornecedor->contatos[0].telefone);
  }else{
    telefone_fornecedor = strdup("Fone: Não possui");
  }
  cairo_show_text(cairo, telefone_fornecedor);
  cairo_fill(cairo);

  cairo_move_to(cairo, ORD_CMP_FORN_INFOS_HPOS, ORD_CMP_FORN_INFOS_VPOS + 120);
  gchar *contato_fornecedor;
  if(ordem_cmp->fornecedor->contatos_qnt){
    contato_fornecedor = malloc(20+strlen(ordem_cmp->fornecedor->contatos[0].nome));
    sprintf(contato_fornecedor, "Contato: %s", ordem_cmp->fornecedor->contatos[0].nome);
  }else{
    contato_fornecedor = strdup("Contato: Não possui");
  }
  cairo_show_text(cairo, contato_fornecedor);
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(243), MM_TO_POINTS(582), MM_TO_POINTS(60));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORD_CMP_HPOS, ASS_ORD_CMP_VPOS);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_show_text(cairo, "Autorizado por:");
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORD_CMP_HPOS+500, ASS_ORD_CMP_VPOS);
  cairo_show_text(cairo, "Conferido por:");
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(304), MM_TO_POINTS(582), MM_TO_POINTS(80));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORD_CMP_HPOS, ASS_ORD_CMP_VPOS+100);
  cairo_set_font_size(cairo, DESCR_TEXT_FONT_SIZE);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_show_text(cairo, "Preecher no recebimento dos materiais:");
  cairo_fill(cairo);

  cairo_set_font_size(cairo, TITLE_TEXT_FONT_SIZE);

  cairo_move_to(cairo, ASS_ORD_CMP_HPOS, ASS_ORD_CMP_VPOS+140);
  cairo_show_text(cairo, "NF Nº: __________");
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORD_CMP_HPOS+300, ASS_ORD_CMP_VPOS+140);
  cairo_show_text(cairo, "Data Entrada: __/__/____");
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORD_CMP_HPOS+700, ASS_ORD_CMP_VPOS+140);
  cairo_show_text(cairo, "Data Vencimento: __/__/____");
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORD_CMP_HPOS, ASS_ORD_CMP_VPOS+200);
  cairo_show_text(cairo, "NF Nº: __________");
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORD_CMP_HPOS+300, ASS_ORD_CMP_VPOS+200);
  cairo_show_text(cairo, "Data Entrada: __/__/____");
  cairo_fill(cairo);

  cairo_move_to(cairo, ASS_ORD_CMP_HPOS+700, ASS_ORD_CMP_VPOS+200);
  cairo_show_text(cairo, "Data Vencimento: __/__/____");
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(385), MM_TO_POINTS(582), MM_TO_POINTS(80));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_move_to(cairo, ORD_CMP_ENTRGA_HPOS, ORD_CMP_ENTRGA_VPOS);
  cairo_set_font_size(cairo, TITLE_TEXT_FONT_SIZE);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_show_text(cairo, "Condições de Entrega:");
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(466), MM_TO_POINTS(582), MM_TO_POINTS(200));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_move_to(cairo, ORD_CMP_ITENS_HPOS, ORD_CMP_ITENS_VPOS);
  cairo_set_font_size(cairo, TITLE_TEXT_FONT_SIZE);
  cairo_set_source_rgb(cairo, WB_TO_RGB(0), WB_TO_RGB(0), WB_TO_RGB(0));
  cairo_show_text(cairo, "Itens Solicitados:");
  cairo_fill(cairo);

  cairo_rectangle(cairo, MM_TO_POINTS(6), MM_TO_POINTS(667), MM_TO_POINTS(582), MM_TO_POINTS(80));
  cairo_set_source_rgb(cairo, WB_TO_RGB(255), WB_TO_RGB(255), WB_TO_RGB(255));
  cairo_fill(cairo);

  cairo_show_page(cairo);
  cairo_destroy(cairo);


  cairo_surface_flush(surface);
  cairo_surface_destroy(surface);
  return 0;
}
