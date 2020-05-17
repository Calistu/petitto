drop database if exists erp;
create database erp;
use erp;

create table operadores( code int primary key auto_increment,
nome varchar(20) not null,
senha varchar(20) not null,
nivel int not null);

create table empresa( cnpj varchar(20) primary key default 'cnpj',
razao varchar(150) not null,
endereco varchar(200) not null);

create table perfil_desktop(code int primary key auto_increment,
desktop_img int default 0,
cor_barra int default 0,
janela_init bool default 0,
janelas_keep_above bool default 0);

create table criticas(opcao_nome varchar(20) default 0,
campo_nome varchar(20) default 0,
critica bool default 0);

create table terceiros ( code int primary key auto_increment,
razao varchar(300) default '',
doc varchar(20) default '',
	ie varchar(20) default 'IE',
	tipo_doc int default 0,
tipoc varchar(20) default 0,
tipo int default 0,
cep varchar(15) default '',
endereco varchar(400) default '',
cidade varchar(50) default '',
uf varchar(20) default 'UF',
numrua int default 0,
tiporua int default 0,
telefone varchar(15) default '',
contatot varchar(15) default '',
celular varchar(15) default '',
contatoc varchar(15) default '',
email varchar(100) default '',
contatoe varchar(20) default '',

transp_nome varchar(300) default '',
transp_cnpj varchar(20) default '',
transp_ie varchar(20) default '',
transp_logradouro varchar(400) default '',
transp_num int default 0,
transp_cidade varchar(50) default '',
transp_estado varchar(20) default 'UF',
transp_cep varchar(15) default '',
transp_telefone varchar(20) default '',
transp_obs varchar(500) default '',

frete_pago bool default 0,
vlr_frete_pago float default 0,
prazo varchar(20) default '',
obs varchar(500) default '');

create table grupos( code int primary key auto_increment,
pai int not null,
nome varchar(20) not null,
nivel int default 1,
foreign key(pai) references grupos(code));

create table unidades( code int primary key auto_increment,
nome varchar(20) default '',
sigla varchar(10) default '',
multiplo int default 1,
medida int default 0);

create table produtos( code int primary key auto_increment,
nome varchar(150) default 'NOME',
peso float default 0.0,
unidades int default 1,
unidades_atacado int default 1,
fornecedor int default 1,
grupo int default 1,
preco_vista float default 0.0,
preco_faturado float default 0.0,
observacoes varchar(500) default '',
foreign key(unidades) references unidades(code),
foreign key(fornecedor) references terceiros(code),
foreign key(grupo) references grupos(code) );

create table estoques( code int primary key auto_increment,
produto int default 1,
saldo float default 0.0,
entradas int default 0,
saidas int default 1,
resultado float default 0.0,
foreign key(produto) references produtos(code));

create table precos( code int primary key auto_increment,
produto int default 1,
terceiro int default 1,
valor float default 0.0,
foreign key(produto) references produtos(code),
foreign key(terceiro) references terceiros(code));

create table pedidos( code int primary key auto_increment,
vendedor int default 1,
cliente int default 1,
dia date not null,
total float default 0.0,
foreign key(cliente) references terceiros(code));

create table orcamentos( code int primary key auto_increment,
vendedor int default 0,
cliente int default 0,
dia date not null,
total float default 0,
observacoes varchar (500) default '',
foreign key(cliente) references terceiros(code));

create table Produto_Orcamento( code int,
item int default 0,
produto int default 1,
subgrupo int default 1,
unidades float default 0.0,
valor_unit float default 0.0,
valor_orig int default 0,
tipodesc int default 0,
desconto float default 0.0,
total float default 0.0,
foreign key(code) references orcamentos(code));

create table cidade (id_cidade int(11) NOT NULL AUTO_INCREMENT,
descricao varchar(100) DEFAULT NULL,
uf varchar(2) DEFAULT NULL,
codigo_ibge int(11) DEFAULT NULL,
ddd varchar(2) DEFAULT NULL,
PRIMARY KEY (id_cidade),
KEY id (id_cidade) USING BTREE,
KEY cidade (id_cidade,
uf) USING BTREE,
KEY cidade_estado (uf) USING BTREE);


create table logradouro (  CEP varchar(11) NOT NULL,
id_logradouro int(10) unsigned NOT NULL AUTO_INCREMENT,
tipo varchar(50) DEFAULT NULL,
descricao varchar(100) NOT NULL,
id_cidade int(11) NOT NULL,
UF varchar(2) NOT NULL,
complemento varchar(100) DEFAULT NULL,
descricao_sem_numero varchar(100) DEFAULT NULL,
descricao_cidade varchar(100) DEFAULT NULL,
codigo_cidade_ibge int(11) DEFAULT NULL,
descricao_bairro varchar(100) DEFAULT NULL,
PRIMARY KEY (id_logradouro),
KEY cep (CEP) USING BTREE,
KEY cidade (id_cidade,
UF) USING BTREE,
CONSTRAINT FK_cidade_2 FOREIGN KEY (id_cidade) REFERENCES cidade (id_cidade));

create user 'petitto'@'localhost' identified by '1234';
grant all privileges on *.* to 'petitto'@'localhost';
flush privileges;

insert into criticas(opcao_nome,campo_nome,critica) 
values('terceiros','ter_doc',1),
('terceiros','ter_tipo_doc',1),
('terceiros','ter_endereco',1),
('terceiros','ter_cep',1),
('terceiros','ter_tipo',1),
('terceiros','ter_celular',1),
('terceiros','ter_contatoc',1),
('terceiros','ter_telefone',1),
('terceiros','ter_contatot',1),
('terceiros','ter_email',1),
('terceiros','ter_contatoe',1);

insert into operadores 
values(1,'Petitto','',5);

insert into empresa(razao,endereco,cnpj) 
values ( 'Petitto Mat. p/ encadern. e carton.','R. Dna Amelia de Paula,100\nJardim Leonor,Campinas ','---');

insert into perfil_desktop(code,
desktop_img,
cor_barra,
janela_init,
janelas_keep_above) values(1,3,1,0,1);
