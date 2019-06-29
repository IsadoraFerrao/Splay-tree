/*Trabalho 2 - v1: BST for categories of products.
Implementar uma BST para catalogar categorias de produtos de uma loja online (e.g., Submarino, Amazon).
Cada categoria tem um código e um nome. O código é um número sequencial. Para cada categoria há um conjunto
de produtos (e.g, 5000 diferentes smartphones). Cada produto é identificado por um código, um nome, um
fabricante, um modelo, um ano de lançamento e um preço. Cada categoria de produtos deverá ser representada,
também, como uma BST. Em outras palavras, o valor do nó da árvore de categoria irá apontar para uma BST que
contém os produtos da respectiva categoria.
O arquivo de entrada, para carregar as BSTs, é um arquivo CSV. O separador padrão do CSV é um ponto-e-vírgula(;).
Entretanto, o usuário deverá poder definir um separador qualquer para cada arquivo CSV, como "#" e "@".
Exemplo de arquivo CSV de entrada:
Laptop; 12345; Lenovo; 12346; IBM; Modelo X51; 2014; 1200.00
Laptop; 12347; Latitude; 12348; Dell; Modelo 21; 2015; 1811.00
Tablet; 12349; iPad; 12350; Apple; II; 2014; 2200.00
Smartphone; 12351; iPhone; 12352; Apple; V; 2014; 3200.00
Scripts para gerar arquivos de entrada de tamanhos quaisquer:
Exemplo de código: geração de categorias e produtos Arquivo
Exemplo de arquivo de entrada com 200 categorias e 300 produtos por categoria:
Trabalho 1: exemplo de arquivo CSV (200 categorias com 300 produtos cada)
Implementar as seguintes funções para as BSTs:
- put (inserir novo elemento na árvore)
- get (retornar um ponteiro para o nó da árvore que contém a chave procurada)
- delete (apagar um elemento da árvore)
- contains (verificar se a árvore contém, ou não, uma chave X)
- size (retornar o tamanho de uma árvore, i.e., número de elementos abaixo da chave X)
- min (retornar a chave de menor valor)
- max (retornar a chave de maior valor)
- rank (retornar o número de elementos cuja chave é menor que a chave X)
- height (retornar a altura da árvore)
- floor (retornar o elemento menor mais próximo da chave X)
- ceiling (retornar o elemento maior mais próximo da chave X)
- inorder traversal (percorrer a árvore na ordem "inorder", i.e., listar os elementos da árvore em ordem crescente)
O que entregar: uma versão completa do trabalho. Em outras palavras, a primeira versão de todas as funções acima.
O usuário deverá poder escolher a função através de um parâmetro de execução do programa. Eis o formato dos parâmetros de entrada:
put: -p <entrada_put.csv>
get: -g <entrada_get.csv>
delete: -d <entrada_delete.csv>
contains: -c <entrada_contains.csv>
size: -s (imprime o tamanho de todas as árvores)
min: -m (imprimir o mínimo de todas as árvores)
max: -M (retornar a chave de maior valor)
rank: -R <entrada_rank.csv>
height: -H (retornar a altura de todas as árvores)
floor: -F <entrada_floor.csv>
ceiling: -C <entrada_ceiling.csv>
opts_sequence: -S <sequência_de_execução_das_operações. exemplo: pgdcM>
inorder traversal: -i (percorrer todas as árvores na ordem "inorder", i.e., listar os elementos da árvore em ordem crescente)
Formato dos arquivos entrada_get.csv, entrada_delete.csv, entrada_contains.csv, entrada_rank.csv, entrada_floor.csv, entrada_ceiling.csv:
Uma lista contendo um "tipo" e uma "chave" por linha. O tipo (categoria ou produto) e a chave são separados por ";". No caso de produto,
a linha contém a informação da categoria e do produto. Portanto, são dois tipos de linhas. Linhas que apenas identificam uma categoria
e linhas que identificam uma categoria e um produto.
Exemplo de conteúdo dos arquivos entrada_contains.csv, entrada_delete.csv, entrada_contains.csv, entrada_rank.csv, entrada_floor.csv, entrada_ceiling.csv:
categoria; 12345
categoria; 12345; produto; 12346
categoria; 12349
categoria; 12351
categoria; 12351; produto; 12352
categoria; 12351; produto; 12354
categoria; 12359; produto; 12355
categoria; 12359; produto; 12399
categoria; 12359; produto; 12101
categoria; 12366
categoria; 12377
categoria; 12359; produto; 12203

Nome: Isadora Garcia Ferrão
Matrícula: 151151387

Nome: Sherlon Almeida da Silva
Matrícula: 151150179*/

//#include <unistd.h>
//#include <ctype.h>
//#include <conio.h>
//#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <getopt.h>

//------------------------------------------------TIPOS ESTRUTURADOS--------------------------------------------------------------------
typedef struct no_prod {
    char nome_produto[128];
    unsigned int key;
    char fabricante[128];
    char modelo[128];
    unsigned int ano;
    float valor;
    struct no_prod *esq, *dir;
} no_prod_t;

typedef struct no_cat {
    char nome_categoria[128];
    unsigned int key;
    no_prod_t *prods;
    struct no_cat *esq, *dir;
} no_cat_t;

//--------------------------------------------------------PUT---------------------------------------------------------------------------
no_prod_t *inserir_produtos(no_prod_t *no,  unsigned int key, char nome_produto[128], char fabricante[128], char modelo[128], int ano, float valor){
    if(no == NULL){
        no = (no_prod_t*)malloc(sizeof(no_prod_t));
        no->key = key;
        strcpy(no->nome_produto, nome_produto);
        strcpy(no->fabricante, fabricante);
        strcpy(no->modelo, modelo);
        no->ano = ano;
        no->valor = valor;
        no->esq = NULL;
        no->dir = NULL;
        printf("\nProduto cadastrado com sucesso! Produto:%d\n ", key);
    }
    else if(key > no->key){
        no->dir = inserir_produtos(no->dir, key, nome_produto, fabricante, modelo, ano, valor);
    }
    else if(key < no->key){ 
		no->esq = inserir_produtos(no->esq, key, nome_produto, fabricante, modelo, ano, valor);
    }else{		
		printf("Produto %d ja existente\n", key);
	}
    return no;
}

no_cat_t* inserir_categoria(no_cat_t *no, unsigned int key_cat, char nome_categoria[128], int key_prod, char nome_produto[128], char fabricante[128], char modelo[128], int ano, float valor){
    if(no == NULL){
        no = (no_cat_t*)malloc(sizeof(no_cat_t));
        no->key = key_cat;
        strcpy(no->nome_categoria, nome_categoria);
        no->esq = NULL;
        no->dir = NULL;
        no->prods = NULL;
		no->prods = inserir_produtos(no->prods, key_prod, nome_produto, fabricante, modelo, ano, valor);
    }
    else if(key_cat > no->key){
        no->dir = inserir_categoria(no->dir,key_cat, nome_categoria, key_prod, nome_produto, fabricante, modelo, ano, valor);
    }
    else if(key_cat < no->key){
		no->esq = inserir_categoria(no->esq,key_cat, nome_categoria, key_prod, nome_produto, fabricante, modelo, ano, valor);
    }else {	
    	no->prods = inserir_produtos(no->prods, key_prod, nome_produto, fabricante, modelo, ano, valor);
	}
    return no;
}
//---------------------------------------------------------GET---------------------------------------------------------------------
void busca_produto (no_prod_t *no, unsigned int key_prod){
    if(no == NULL){
        printf("\nPRODUTO NAO ENCONTRADO!\n");
        return;
    }
    else if(no->key == key_prod){
    	printf("\nPRODUTO ENCONTRADO!\n");
        printf("Nome: %s\n", no->nome_produto);
        printf("Chave: %d\n", no->key);
        printf("Fabricante: %s\n", no->fabricante);
        printf("Modelo: %s\n", no->modelo);
        printf("Ano: %d\n", no->ano);
        printf("Valor: %f\n", no->valor);
        return;
    }
    else{
        if(key_prod > no->key){
            busca_produto(no->dir, key_prod);
        }
        else if(key_prod < no->key){
            busca_produto(no->esq, key_prod);
        }
    }
}

void busca_categoria (no_cat_t *no, unsigned int key_cat, unsigned int key_prod){
    if(no == NULL){
        printf("\nCATEGORIA NAO ENCONTRADA!\n");
        //return ;
    }
    else if(no->key == key_cat){
    	printf("\nCATEGORIA ENCONTRADA!\n");
        printf("Nome: %s\n", no->nome_categoria);
        printf("Codigo: %d\n", no->key);
        busca_produto(no->prods, key_prod);
        //return;
    }
    else{
        if(key_cat > no->key){
            busca_categoria(no->dir, key_cat, key_prod);
        }
        else if(key_cat < no->key){
            busca_categoria(no->esq, key_cat, key_prod);
        }
    }
}

//----------------------------------------------------DELETE--------------------------------------------------------
no_prod_t* delete_produto(no_prod_t* no, unsigned int key_prod){
    if(no==NULL){
    	printf("\nPRODUTO NAO ENCONTRADO!\n");
        //return;
        return NULL;
	}
	else if(key_prod > no->key){
		no->dir=delete_produto(no->dir, key_prod);
	}
	else if(key_prod < no->key){
		no->esq=delete_produto(no->esq, key_prod);
	}
	else if(key_prod == no->key){ //achou o produto
		//elemento sem filhos
		if(no->esq == NULL && no->dir == NULL){
			free(no);
			no=NULL;
		}
		//so tem filhos a direita
		else if (no->esq == NULL){
			no_prod_t* t = no;
			no=no->dir;
			free(t);
		}
		//so tem filhos a esquerda
		else if (no->dir == NULL){
			no_prod_t* t = no;
			no=no->esq;
			free(t);
		}
		//tem os dois filhos
		else {
			no_prod_t* f = no->esq;
			while (f->dir != NULL){
				f=f->dir;
			}
			no->key = f->key;
			f->key = key_prod;
			no->esq = delete_produto(no->esq, key_prod);
		}
	}
	return no;
}

no_cat_t* delete_categoria(no_cat_t *no, unsigned int key_cat, unsigned int key_prod){
    if(no==NULL){
    	printf("\nCATEGORIA NAO ENCONTRADA!\n");
        //return;
        return NULL;
	}
	else if(key_cat > no->key){
		no->dir=delete_categoria(no->dir, key_cat, key_prod);
	}
	else if(key_cat < no->key){
		no->esq=delete_categoria(no->esq, key_cat, key_prod);
	}
	else if(key_cat == no->key){ //achou a categoria
		no->prods=delete_produto(no->prods, key_prod);
	}
	return no;
}
//------------------------------------------------------------CONTAINS----------------------------------------------------------------
int contains_produto(no_prod_t* no, unsigned int key_prod){
	if (no==NULL){
		printf("\nPRODUTO NAO ENCONTRADO - NAO ESTA CONTIDO NA ARVORE!\n");
		//return;
		return -1;
	}
	else if (key_prod > no->key){
		contains_produto(no->dir, key_prod);
	}
	else if (key_prod < no->key){
		contains_produto(no->esq, key_prod);
	}
	else if (key_prod == no->key){
		printf("\nPRODUTO ENCONTRADO - ESTA CONTIDO NA ARVORE!\n");
		//return;
		return 1;
	}
	return 0;
}

int contains_categoria(no_cat_t* no, unsigned int key_cat, unsigned int key_prod){
	if (no==NULL){
		printf("\nCATEGORIA NAO ENCONTRADA!\n");
		//return;
		return -1;
	}
	else if (key_cat > no->key){
		contains_categoria(no->dir, key_cat, key_prod);
	}
	else if (key_cat < no->key){
		contains_categoria(no->esq, key_cat, key_prod);
	}
	else if (key_cat == no->key){
		printf("\nCATEGORIA ENCONTRADA - ESTA CONTIDA NA ARVORE!\n");
		contains_produto(no->prods, key_prod);
		//return;
		return 1;
	}
	return 0;
}

//---------------------------------------------- SIZE ----------------------------------------------------------------
int cat_size(no_cat_t *no){
	if(no != NULL){
		cat_size(no->esq);
		printf("Categoria[%d] possui %d produtos\n", no->key, prod_size(no->prods));
		cat_size(no->dir);
	}
}

int prod_size(no_prod_t* no){
	if (no!=NULL){
		return 1 + prod_size(no->esq) + prod_size(no->dir);
	}
}

//-----------------------------------------------------MIN----------------------------------------------------------------
int cat_minimo(no_cat_t* no){
	if(no != NULL){
		cat_minimo(no->esq);
    		printf("CATEGORIA:%s - Chave[%d]\nELEMENTO MINIMO: %d\n\n", no->nome_categoria, no->key, prod_minimo(no->prods));
    		cat_minimo(no->dir);
	}
}

int prod_minimo(no_prod_t* no){
	if(no->esq == NULL){
		return no->key;
	}
	else{
		return prod_minimo(no->esq);
	}
}

//-----------------------------------------------------MAX----------------------------------------------------------------
int cat_maximo(no_cat_t* no){
	if(no != NULL){
		cat_maximo(no->esq);
    		printf("CATEGORIA:%s - Chave[%d]\nELEMENTO MAXIMO: %d\n\n", no->nome_categoria, no->key, prod_maximo(no->prods));
    		cat_maximo(no->dir);
	}
}

int prod_maximo(no_prod_t* no){
	if(no!=NULL){
		while( no->dir != NULL){
			no = no->dir;
		}
	}
	return no->key;
}

//-----------------------------------------------------RANK---------------------------------------------------------------
int rank_categoria(no_cat_t *no, int key){
	int soma=0;
	if(no != NULL){
	    	cat_size(no->esq);
		soma+=prod_size(no->prods, key);
		cat_size(no->dir);
	}
	else{
		printf("A soma e: %d\n",soma);
	}
}

int rank_produto(no_prod_t* no, int key){
	if (no!=NULL){
		if(no->key == key){
			return 1 + prod_size(no->esq) + prod_size(no->dir);
		}
		else {
			return 0 + prod_size(no->esq) + prod_size(no->dir);
		}
	}
}

/*int rank_categoria(no_cat_t* no, int key){
	int soma=0;
	if(no != NULL){
    	rank_categoria(no->esq, key);
    	soma+=rank_produto(no->prods, key);
        rank_categoria(no->dir, key);
    }
    if(soma==key-1){
    	printf("Ha %d elementos antes da chave %d!\n\n", soma-1, key);
	}
}

int rank_produto(no_prod_t* no, int key){
	if (no!=NULL){
		if(no->key < key){	
			return 1 + rank_produto(no->esq, key) + rank_produto(no->dir, key);
		}
		else{
			return 0;
		}
	}
}*/

//----------------------------------------------------------- HEIGHT --------------------------------------------------------------------------
int c_height(no_cat_t *no) {
	if (no != NULL) {
		c_height(no->esq);
        printf("Categoria[%d] possui Altura %d\n", no->key, p_height(no->prods));
        c_height(no->dir);
	}
}

int p_height(no_prod_t *no) {
	if (no == NULL){
		return -1;
	} 
	else {
		int he = p_height(no->esq);
		int hd = p_height(no->dir);
		if (he < hd){
			return hd + 1;
		}
		else{
			return he + 1;
		}
	}
}

// ------------------------------------------  FLOOR  -------------------------------------------
no_cat_t* c_floor(no_cat_t* no, int key){
	no_cat_t* i;
	if(no == NULL)
		return NULL;
	if(no->key == key)
		return no;
	if(no->key<key)
		return  c_floor(no->esq, key);
	i=c_floor(no->dir, key);
	
	if(i != NULL){
		return i;
	}else
		return no;
}

// -----------------------------------------  CEILLING  ------------------------------------------
no_cat_t* ceilling(no_cat_t* no, int key){
	no_cat_t* i;
	if(no == NULL)
		return NULL;
	if(no->key == key)
		return no;
	if(no->key>key)
		return  ceilling(no->dir, key);
	i=ceilling(no->esq, key);
	
	if(i != NULL){
		return i;
	}else
		return no;
}

// -----------------------------------------  INORDER TRAVERSAL  ------------------------------------------
int inorder_traversal (no_cat_t *no){
    if(no != NULL){
        inorder_traversal(no->esq);
        inorder_busca_produto (no->prods);
        inorder_traversal(no->dir);
    }
}

int inorder_busca_produto (no_prod_t *no){
    if(no != NULL){
    	inorder_busca_produto(no->esq);
    	printf("\nPRODUTO ENCONTRADO!\n");
        printf("Nome: %s\n", no->nome_produto);
        printf("Chave: %d\n", no->key);
        printf("Fabricante: %s\n", no->fabricante);
        printf("Modelo: %s\n", no->modelo);
        printf("Ano: %d\n", no->ano);
        printf("Valor: %f\n", no->valor);
        inorder_busca_produto(no->dir);
    }
}

//------------------------------------------------OPTS SEQUENCE - HELP------------------------------------------------------------
void print_usage() {
	system("clear");
    printf("Usage: <option1> <option2> ... <optionN>\n"
        "\t-p <entrada_put.csv> [Inserir Elementos]\n"
        "\t-g <entrada_get.csv> [Encontrar Nos da Arvore]\n"
        "\t-d <entrada_delete.csv> [Deletar Nos da Arvore]\n"
        "\t-c <entrada_contains.csv> [Buscar Nos da Arvore]\n"
        "\t-s [Imprime o tamanho das Arvores]\n"
        "\t-m [Imprime o menor No da Arvore]\n"
        "\t-M [Imprime o maior No da Arvore]\n"
        "\t-R <entrada_rank.csv> [Imprime o numero de Nos antes da Chave X]\n"
        "\t-H [Imprime a altura das Arvores]\n"
        "\t-F <entrada_floor.csv> [Encontrar o elemento mais proximo da chave X pela Esquerda]\n"
        "\t-C <entrada_ceiling.csv> [Encontrar o elemento mais proximo da chave X pela Direita]\n"
        "\t-I => [Imprime os elementos da arvore na forma Inorder]\n"
        "\t-S <op_exec_seq> [Definir Sequencia de Execucao]\n"
        "\t   => Operacoes Validas:\n" 
        "\t   => Exemplo: -S pgdcRC\n" 
    	"\t-Q => Sair do programa\n"
    	"\t-h => Ajuda (Menu)\n");
}

//----------------------------------------------------------FUNÇÃO MAIN---------------------------------------------------------
int main(int argc, char **argv){
	no_cat_t* raiz = NULL;
    char fabricante[128], nome_produto[128], modelo[128], nome_categoria[128];
    char option;
    float valor;
    int key_prod, key_cat, ano;
    int chave_cat, chave_prod, inorder, rank_val;;
    int del_cat, del_prod, contem_cat, contem_prod;
    int sair=1, elem_floor, elem_ceilling;
    FILE *entrada, *saida;
	
	if(argc<2){
		printf("Argumentos insuficientes!\n");
		printf("Digite para executar:\n %s <-p -g -d -c -s -m -M -R -H -F -C -I -S -h>\n", argv[0]);
		exit(-1);
	}
	entrada= fopen(argv[1], "r");
	if (entrada == NULL) {
		printf("ERRO na abertura do arquivo %s!\n", argv[1]);
		exit(-1);
	}
	//while((option=getopt(argc,argv,"p:g:d:c:smMR:HF:C:I:S:h"))!=-1){
	while(sair!=0){
		printf("\n\nDIGITE A OPERACAO!");
		__fpurge(stdin);
		scanf("%c",&option);
		switch (option){
			case 'p':
				while(fscanf(entrada, "%[^;]; %u; %[^;]; %u; %[^;]; %[^;]; %u; %f[^\n]",nome_categoria, &key_cat, nome_produto, &key_prod, fabricante, modelo, &ano, &valor)!=EOF){
					raiz=inserir_categoria(raiz, key_cat, nome_categoria, key_prod, nome_produto, fabricante, modelo, ano, valor);
				}
				break;
				
			case 'g':
				//PARA TESTAR A INSERÇÃO E BUSCA
	 			printf("\n\nDigite um elemento para buscar <categoria produto>: ");
		 		scanf("%d %d", &chave_cat, &chave_prod);
		 		busca_categoria(raiz, chave_cat, chave_prod);
				break;
				
			case 'd':
				//PARA TESTAR A DELETE
				printf("\n\nDigite um elemento para deletar <categoria produto>: ");
				scanf("%d %d", &del_cat, &del_prod);
	 			raiz=delete_categoria(raiz, del_cat, del_prod);
	 			break;
				
			case 'c':
				//PARA TESTAR A CONTAINS
	 			printf("\n\nDigite um elemento para buscar <categoria produto>: ");
	 			scanf("%d %d", &contem_cat, &contem_prod);
	 			contains_categoria(raiz, contem_cat, contem_prod);
				break;
				
			case 's':
				//PARA TESTAR SIZE 
				cat_size(raiz);
				break;
				
			case 'm':
				//PARA TESTAR MINIMO
				cat_minimo(raiz);
				break;
				
			case 'M':
				//PARA TESTAR MÁXIMO
				cat_maximo(raiz);	
				break;
				
			case 'R':
				//PARA TESTAR A RANK
				printf("Insira a chave para a funcao RANK <Produto>: ");
				scanf("%d", &rank_val);
				rank_categoria(raiz, rank_val);
				break;
				
			case 'H':
				//PARA TESTAR HEIGHT
				c_height(raiz);	
				break;
				
			case 'F':
				//PARA TESTAR FLOOR
				printf("Insira o elemento para FLOOR:");
				scanf("%d",&elem_floor);
				c_floor(raiz, elem_floor);
				break;
			
			case 'C':
				//PARA TESTAR CEILING
				printf("Insira o elemento para CEILLING:");
				scanf("%d",&elem_ceilling);
				ceilling(raiz, elem_ceilling);
				break;
			
			case 'I':
				//PARA TESTAR INORDER
				inorder_traversal(raiz);
				break;
				
			case 'S':
				//PARA MOSTRAR SEQUENCIA
				printf("Digite uma sequencia para execucao:\n");
				break;
				
			case 'h':
				//PARA MOSTRAR AJUDA
				print_usage();
				break;
			
			case 'Q':
				//PARA SAIR DO PROGRAMA
				sair=0;
				system("clear");
				break;
				
			default:
				printf("OPERACAO INVALIDA!\n\n ");
		}
	}
}

