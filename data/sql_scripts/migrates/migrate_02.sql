-- migrate criado com script migrate pedidos

update versao set versao = '1.1', lancamento = '2021-06-17';
insert into migrate values(2, 'Versao 1.1.2', 'migrate_02.sql', '1.1', '2021-06-17');

ALTER TABLE terceiros add column relacionamento_desde datetime after tipo;
