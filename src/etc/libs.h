#include "tools.h"
#include "impressao.h"
#include "css.c"
#include "vars.h"
#include "stoi.h"

#include "../Canones/gerenciador_janelas.h"
#include "../Canones/cad_ceps/cadastro_ceps.h"
#include "parametros.h"
#include "operadores.h"
#include "../Inicio/pega_data.h"
#include "../Terceiros/pesquisa_cad.h"
#include "../Produtos/grupos/cad_grupo.h"
#include "../Produtos/grupos/reload_nome.h"
#include "../pesquisadores/grupos.h"
#include "../pesquisadores/datas.h"
#include "../pesquisadores/subgrupos.h"
#include "../pesquisadores/subgrupos_todos.h"
#include "../pesquisadores/terceiros.h"
#include "../pesquisadores/unidades.h"
#include "../pesquisadores/produtos.h"
#include "../pesquisadores/orcamentos.h"
#include "../pesquisadores/pedidos.h"
#include "../pesquisadores/ceps.h"
#include "../pesquisadores/movimentos_ent_estoque.h"
#include "../pesquisadores/movimentos_said_estoque.h"
#include "../pesquisadores/relatorios.h"
#include "../pesquisadores/cond_pag.h"
#include "../pesquisadores/operadores.h"
#include "../Unidades/cadastro_unidades.h"
#include "../Estoque/saldos/saldos.h"
#include "../Estoque/entradas/entradas.h"
#include "../Estoque/saidas/saidas.h"
#include "../Estoque/cadastro/estoque.h"
#include "../Vendas/condicoes_pag/cad_pag.h"
#include "../Vendas/condicoes_pag/campos/pag_cod.h"
#include "../Vendas/condicoes_pag/campos/pag_nome.h"
#include "../Vendas/condicoes_pag/campos/pag_init.h"
#include "../Vendas/condicoes_pag/campos/pag_tipo.h"
#include "../Vendas/condicoes_pag/campos/pag_parc_qnt.h"
#include "../Vendas/condicoes_pag/campos/pag_parc.h"
#include "../Vendas/condicoes_pag/campos/pag_datas.h"
#include "../Vendas/condicoes_pag/campos/pag_dia_fixo.h"
#include "../Vendas/condicoes_pag/cancelar.h"
#include "../Vendas/condicoes_pag/concluir.h"
#include "../Vendas/condicoes_pag/alterar.h"
#include "../Vendas/condicoes_pag/excluir.h"
#include "../Vendas/pedidos/pedidos.h"
#include "../Vendas/pedidos/emitir.h"
#include "../Vendas/pedidos/cancelar.h"
#include "../Vendas/pedidos/excluir.h"
#include "../Vendas/orcamentos/orcamentos.h"
#include "../Relatorios/relatorios.h"
#include "../Relatorios/relatorios/produtos/produtos.h"
#include "../Relatorios/relatorios/terceiros/terceiros.h"
#include "../Relatorios/relatorios/movimentos/movimentos.h"
#include "../Relatorios/relatorios/orc_prod/orc_prods.h"
#include "../Relatorios/pesquisar/relat_ptabs.h"
#include "../Suporte/suporte.h"
#include "../Suporte/adicionar.h"
#include "../Suporte/atualiza.h"
#include "../Tecnico/cad_empresa/cad_empresa.h"

#include "../Estoque/cadastro/conclui.h"
#include "../Estoque/cadastro/cancela.h"
#include "../Estoque/cadastro/altera.h"
#include "../Estoque/cadastro/exclui.h"

#include "receber_confs.c"
#include "tools.c"
#include "impressao.c"
#include "criticas.c"
#include "pesquisador.c"
#include "personalizacao.c"
#include "parametros.c"
#include "temas.c"
#include "../Inicio/pega_data.c"

#include "operadores.c"
#include "../pesquisadores/grupos.c"
#include "../pesquisadores/datas.c"
#include "../pesquisadores/subgrupos.c"
#include "../pesquisadores/subgrupos_todos.c"
#include "../pesquisadores/terceiros.c"
#include "../pesquisadores/unidades.c"
#include "../pesquisadores/produtos.c"
#include "../pesquisadores/orcamentos.c"
#include "../pesquisadores/pedidos.c"
#include "../pesquisadores/ceps.c"
#include "../pesquisadores/movimentos_said_estoque.c"
#include "../pesquisadores/movimentos_ent_estoque.c"
#include "../pesquisadores/relatorios.c"
#include "../pesquisadores/cond_pag.c"
#include "../pesquisadores/operadores.c"
#include "../Canones/Cadastro_Operadores.c"
#include "../Canones/cad_ceps/cadastro_ceps.c"
#include "../Canones/Vinculos_Chaves.c"
#include "../Inicio/fechar.c"
#include "../Terceiros/cadastro_terceiros.c"
#include "../Terceiros/pesquisa_cad.c"
#include "../Produtos/cadastro_produtos.c"
#include "../Produtos/grupos/reload_nome.c"
#include "../Unidades/cadastro_unidades.c"
#include "../Compras/cadastro_compras.c"
#include "../Vendas/condicoes_pag/cad_pag.c"
#include "../Vendas/condicoes_pag/campos/pag_cod.c"
#include "../Vendas/condicoes_pag/campos/pag_nome.c"
#include "../Vendas/condicoes_pag/campos/pag_init.c"
#include "../Vendas/condicoes_pag/campos/pag_tipo.c"
#include "../Vendas/condicoes_pag/campos/pag_parc_qnt.c"
#include "../Vendas/condicoes_pag/campos/pag_parc.c"
#include "../Vendas/condicoes_pag/campos/pag_datas.c"
#include "../Vendas/condicoes_pag/campos/pag_dia_fixo.c"
#include "../Vendas/condicoes_pag/cancelar.c"
#include "../Vendas/condicoes_pag/concluir.c"
#include "../Vendas/condicoes_pag/alterar.c"
#include "../Vendas/condicoes_pag/excluir.c"
#include "../Vendas/orcamentos/orcamentos.c"
#include "../Vendas/pedidos/emitir.c"
#include "../Vendas/pedidos/cancelar.c"
#include "../Vendas/pedidos/excluir.c"
#include "../Vendas/pedidos/pedidos.c"

#include "../Estoque/cadastro/codigo.c"
#include "../Estoque/cadastro/nome.c"
#include "../Estoque/saldos/saldos.c"
#include "../Estoque/entradas/entradas.c"
#include "../Estoque/saidas/saidas.c"
#include "../Estoque/cadastro/conclui.c"
#include "../Estoque/cadastro/cancela.c"
#include "../Estoque/cadastro/altera.c"
#include "../Estoque/cadastro/exclui.c"
#include "../Estoque/cadastro/estoque.c"

#include "../Vendas/faturamento.c"
#include "../Relatorios/relatorios.c"
#include "../Relatorios/relatorios/produtos/produtos.c"
#include "../Relatorios/pesquisar/relat_ptabs.c"
#include "../Relatorios/relatorios/terceiros/terceiros.c"
#include "../Relatorios/relatorios/movimentos/movimentos.c"
#include "../Relatorios/relatorios/orc_prod/orc_prods.c"
#include "../Suporte/suporte.c"
#include "../Suporte/adicionar.c"
#include "../Suporte/atualiza.c"

#include "../Tecnico/cad_empresa/cad_empresa.c"

#include "../Canones/gerenciador_janelas.c"
