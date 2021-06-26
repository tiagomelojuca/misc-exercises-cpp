#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// THIRD PARTY CODE - DO NOT TOUCH!
// CREDITS: WIKIPEDIA <https://en.wikipedia.org/wiki/LU_decomposition>

/* INPUT: A - array of pointers to rows of a square matrix having dimension N
 *        Tol - small tolerance number to detect failure when the matrix is near degenerate
 * OUTPUT: Matrix A is changed, it contains a copy of both matrices L-E and U as A=(L-E)+U such that P*A=L*U.
 *        The permutation matrix is not stored as a matrix, but in an integer vector P of size N+1 
 *        containing column indexes where the permutation matrix has "1". The last element P[N]=S+N, 
 *        where S is the number of row exchanges needed for determinant computation, det(P)=(-1)^S    
 */
int LUPDecompose(double **A, int N, double Tol, int *P) {

    int i, j, k, imax; 
    double maxA, *ptr, absA;

    for (i = 0; i <= N; i++)
        P[i] = i; //Unit permutation matrix, P[N] initialized with N

    for (i = 0; i < N; i++) {
        maxA = 0.0;
        imax = i;

        for (k = i; k < N; k++)
            if ((absA = fabs(A[k][i])) > maxA) { 
                maxA = absA;
                imax = k;
            }

        if (maxA < Tol) return 0; //failure, matrix is degenerate

        if (imax != i) {
            //pivoting P
            j = P[i];
            P[i] = P[imax];
            P[imax] = j;

            //pivoting rows of A
            ptr = A[i];
            A[i] = A[imax];
            A[imax] = ptr;

            //counting pivots starting from N (for determinant)
            P[N]++;
        }

        for (j = i + 1; j < N; j++) {
            A[j][i] /= A[i][i];

            for (k = i + 1; k < N; k++)
                A[j][k] -= A[j][i] * A[i][k];
        }
    }

    return 1;  //decomposition done 
}

/* INPUT: A,P filled in LUPDecompose; b - rhs vector; N - dimension
 * OUTPUT: x - solution vector of A*x=b
 */
void LUPSolve(double **A, int *P, double *b, int N, double *x) {

    for (int i = 0; i < N; i++) {
        x[i] = b[P[i]];

        for (int k = 0; k < i; k++)
            x[i] -= A[i][k] * x[k];
    }

    for (int i = N - 1; i >= 0; i--) {
        for (int k = i + 1; k < N; k++)
            x[i] -= A[i][k] * x[k];

        x[i] = x[i] / A[i][i];
    }
}

/* INPUT: A,P filled in LUPDecompose; N - dimension
 * OUTPUT: IA is the inverse of the initial matrix
 */
void LUPInvert(double **A, int *P, int N, double **IA) {
  
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            if (P[i] == j) 
                IA[i][j] = 1.0;
            else
                IA[i][j] = 0.0;

            for (int k = 0; k < i; k++)
                IA[i][j] -= A[i][k] * IA[k][j];
        }

        for (int i = N - 1; i >= 0; i--) {
            for (int k = i + 1; k < N; k++)
                IA[i][j] -= A[i][k] * IA[k][j];

            IA[i][j] = IA[i][j] / A[i][i];
        }
    }
}

/* INPUT: A,P filled in LUPDecompose; N - dimension. 
 * OUTPUT: Function returns the determinant of the initial matrix
 */
double LUPDeterminant(double **A, int *P, int N) {

    double det = A[0][0];

    for (int i = 1; i < N; i++)
        det *= A[i][i];

    if ((P[N] - N) % 2 == 0)
        return det; 
    else
        return -det;
}

// END OF THIRD PARTY CODE

void multiplicaMatriz(double **a, double **b, double **mult,int r1,int c1,int r2,int c2) {
    int i,j,k;
    
    for(i=0; i<r1; ++i)
        for(j=0; j<c2; ++j)
        {
            mult[i][j]=0;
        }
    
    for(i=0; i<r1; ++i)
        for(j=0; j<c2; ++j)
            for(k=0; k<c1; ++k)
            {
                mult[i][j]+=a[i][k]*b[k][j];
            }
}

int main() {
	
	
// ####################################
// ###### DEFINICAO DE VARIAVEIS ######
// ####################################
	
	
	// Controle
	int tmp = 0;																// Variavel para valores temporarios (swap)
	int tmpx = 0;																// Variavel para valores temporarios (swap)
	int i = 1;																	// Variavel para controle de iteracoes
	int j = 1;																	// Variavel para controle de iteracoes
	int k = 1;																	// Variavel para controle de iteracoes
	char confirma = 'n';														// Variavel para confirmaçaoo de opçoes
	int r, c, p;																// Variaveis de Controle para Alocacaoo Dinamica
	
	// Nodais
	int qtdnodes;																// Quantidade de nos especificada pelo usuario
	float nodepos[501][3];														// Identifica as posicoes X (0), Y (1) e Z (2) do no
	int nodeliberdadex[501][2];													// Graus de Liberdade em X, translacao (0) e rotacao (1)
	int nodeliberdadey[501][2];													// Graus de Liberdade em Y, translacao (0) e rotacao (1)
	int nodeliberdadez[501][2];													// Graus de Liberdade em Z, translacao (0) e rotacao (1)
	float carganodal[501][6];													// Identifica as componentes de carga para cada no definido
	
	// Barras
	int qtdbarras;																// Quantidade de barras especificada pelo usuario
	int barra[501][2];															// Identifica no inicial (0) e no final (1) da barra
	float barraprops[501][7];													// Caracteristicas da barra: E (0), G (1), A (2), Iy (3), Iz (4), J (5) e L (6)
	float barravetoraux[501][3];												// Vetor Auxiliar de Cada Barra
	
	// Matriz de Rigidez
	double kblocal[251][12][12];												// Matriz de Rigidez Padrao da barra no Sistema Local
	double kbrotred[251][3][3];													// Matriz de Rotacao Reduzida da Barra
	double kbrot[251][12][12];													// Matriz de Rotacao da Barra
	double kbrotinversa[251][12][12];											// Inversa da Matriz de Rotacao da Barra
	double produto[251][12][12];												// Produto da Matriz de Rotacao Inversa pela Matriz de Rigidez Local
	double kbglobal[251][12][12];												// Matriz de Rigidez Padrao da barra no Sistema Global
	double pontoauxiliar[4];													// Coordenadas X, Y e Z do ponto auxiliar K, bem como comprimento L do vetor jK
	double cosauxiliar[3];														// Cossenos diretores do vetor jK
	double coefc;																// Coeficiente c do vetor cZ
	double det;																	// Determinante da Matriz de Rigidez Reduzida
	
	// Processamento
	int nnos;																	// Variavel para controle do numero de nos
	int neq;																	// Quantidade de equacoes (numero de nos * graus de liberdade por no)
	int neqlivre = 0;															// Numero de equacoes referentes a deslocabilidades livres
	int neqfixo = 0;															// Numero de equacoes referentes a deslocabilidades fixas
	int countL = 0;																// Contagem das desloc livres para ordenacao da matriz de deslocabilidades
	int countR = 0;																// Contagem das desloc livres para ordenacao da matriz de deslocabilidades
	int ll = 0;
	int cl = 0;
	int lg = 0;
	int cg = 0;
	
	
// ################################################
// ###### INDETIFICACAO DOS NOS PELO USUARIO ######
// ################################################
	
	
	// Determinacao da Quantidade de Nos
	printf("Digite a quantidade de nos da estrutura: ");
	scanf("%i",&qtdnodes);
	nnos = qtdnodes;
	neq = nnos * 6;
	system("cls");

	// Requisicao dos Dados de Entrada	
	while(i <= qtdnodes) {
		printf("-----------------------------\n");
		printf("DADOS DE ENTRADA DO NO %i\n", i);
		printf("-----------------------------\n\n");
		
		// Coordenadas
		printf("X: ");
		scanf("%f", &nodepos[i][0]);
		printf("Y: ");
		scanf("%f", &nodepos[i][1]);
		printf("Z: ");
		scanf("%f", &nodepos[i][2]);
		
		// Graus de Liberdade
		printf("Fixa traslado em X? ");
		scanf(" %c", &confirma);
		if(confirma == 's' || confirma == 'S') {nodeliberdadex[i][0] = 1;} else {nodeliberdadex[i][0] = 0;}
		
		printf("Fixa traslado em Y? ");
		scanf(" %c", &confirma);
		if(confirma == 's' || confirma == 'S') {nodeliberdadey[i][0] = 1;} else {nodeliberdadey[i][0] = 0;}
		
		printf("Fixa traslado em Z? ");
		scanf(" %c", &confirma);
		if(confirma == 's' || confirma == 'S') {nodeliberdadez[i][0] = 1;} else {nodeliberdadez[i][0] = 0;}
		
		printf("Fixa rotacao em X? ");
		scanf(" %c", &confirma);
		if(confirma == 's' || confirma == 'S') {nodeliberdadex[i][1] = 1;} else {nodeliberdadex[i][1] = 0;}
		
		
		printf("Fixa rotacao em Y? ");
		scanf(" %c", &confirma);
		if(confirma == 's' || confirma == 'S') {nodeliberdadey[i][1] = 1;} else {nodeliberdadey[i][1] = 0;}
		
		printf("Fixa rotacao em Z? ");
		scanf(" %c", &confirma);
		if(confirma == 's' || confirma == 'S') {nodeliberdadez[i][1] = 1;} else {nodeliberdadez[i][1] = 0;}
		
		// Confirmacao de Dados
		printf("\nDADOS: X(%.2f), Y(%.2f), Z(%.2f), Fixa TX(%i), Fixa RX(%i), Fixa TY(%i), Fixa RY(%i), Fixa TZ(%i), Fixa RZ(%i)\n", nodepos[i][0], nodepos[i][1], nodepos[i][2], nodeliberdadex[i][0], nodeliberdadex[i][1], nodeliberdadey[i][0], nodeliberdadey[i][1], nodeliberdadez[i][0], nodeliberdadez[i][1]);
		
		printf("\nCONFIRMA DADOS DO NO? ");
		scanf(" %c", &confirma);
		
		if(confirma == 's' || confirma == 'S') {
			
			tmp = 0;
			
			// Vetor de Carga Nodal
			printf("\nDeseja inserir carga nodal? ");
			scanf(" %c", &confirma);
			
			if(confirma == 's' || confirma == 'S') {
				tmp = 0;
				while(tmp == 0) {
					printf("\nFx: ");
					scanf("%f", &carganodal[i][0]);
					printf("Fy: ");
					scanf("%f", &carganodal[i][1]);
					printf("Fz: ");
					scanf("%f", &carganodal[i][2]);
					printf("Mx: ");
					scanf("%f", &carganodal[i][3]);
					printf("My: ");
					scanf("%f", &carganodal[i][4]);
					printf("Mz: ");
					scanf("%f", &carganodal[i][5]);
					
					// Confirmacao de Dados
					printf("\nDADOS: Fx(%.2f), Fy(%.2f), Fz(%.2f), Mx(%.2f), My(%.2f), Mz(%.2f)\n", carganodal[i][0], carganodal[i][1], carganodal[i][2], carganodal[i][3], carganodal[i][4], carganodal[i][5]);
		
					printf("\nCONFIRMA DADOS DA CARGA NODAL? ");
					scanf(" %c", &confirma);
					if(confirma == 's' || confirma == 'S') {tmp = 1;}
					printf("\nPor favor, digite novamente os dados de carga\n");
				}
				tmp = 0;
				
			}
			i++;
		}
		system("cls");
	}
	i = 1;
	j = 1;
	tmp = 0;
	confirma = 'n';
	
	
// ###################################################
// ###### IDENTIFICACAO DAS BARRAS PELO USUARIO ######
// ###################################################
	
	
	// Determinacao da Quantidade de Barras
	printf("Digite a quantidade de barras da estrutura: ");
	scanf("%i",&qtdbarras);
	system("cls");
	
	// Requisicao dos Dados de Entrada
	while(i <= qtdbarras) {
		printf("-----------------------------\n");
		printf("DADOS DE ENTRADA DA BARRA %i\n", i);
		printf("-----------------------------\n\n");
		
		// Extremidades
		printf("No Inicial: ");
		scanf("%i", &barra[i][0]);
		printf("No Final: ");
		scanf("%i", &barra[i][1]);
		
		// Vetor Auxiliar
		printf("vX: ");
		scanf("%f", &barravetoraux[i][0]);
		printf("vY: ");
		scanf("%f", &barravetoraux[i][1]);
		printf("vZ: ");
		scanf("%f", &barravetoraux[i][2]);
		
		// Propriedades da Barra
		printf("E: ");
		scanf("%f", &barraprops[i][0]);
		printf("G: ");
		scanf("%f", &barraprops[i][1]);
		printf("A: ");
		scanf("%f", &barraprops[i][2]);
		printf("Iy: ");
		scanf("%f", &barraprops[i][3]);
		printf("Iz: ");
		scanf("%f", &barraprops[i][4]);
		printf("J:  ");
		scanf("%f", &barraprops[i][5]);
		
		// Confirmacao de Dados
		printf("\nDADOS: NOi(%i), NOf(%i), E(%.2f), G(%.2f), A(%.2f), Iy(%.2f), Iz(%.2f), J(%.2f)\n", barra[i][0], barra[i][1], barraprops[i][0], barraprops[i][1], barraprops[i][2], barraprops[i][3], barraprops[i][4], barraprops[i][5]);
		
		printf("\nCONFIRMA DADOS DA BARRA? ");
		scanf(" %c", &confirma);
		
		if(confirma == 's' || confirma == 'S') {
			i++;
		}
		
		system("cls");
	}
	i = 1;
	confirma = 'n';
	
	// CALCULO DO COMPRIMENTO DAS BARRAS
	
	// Precisamos resgatar os valores armazenados em vetores anteriormente
	// Legenda
	// Xi = nodepos[barra[i][0]][0]
	// Xf = nodepos[barra[i][1]][0]
	// Yi = nodepos[barra[i][0]][1]
	// Yf = nodepos[barra[i][1]][1]
	// Zi = nodepos[barra[i][0]][2]
	// Zf = nodepos[barra[i][1]][2]
	// L = sqrt( pow((Xi - Xf),2) + pow((Yi - Yf),2) + pow((Zi - Zf),2) )
	
	while(i <= qtdbarras) {
		barraprops[i][6] = sqrt(pow((nodepos[barra[i][0]][0]-nodepos[barra[i][1]][0]),2)+pow((nodepos[barra[i][0]][1]-nodepos[barra[i][1]][1]),2)+pow((nodepos[barra[i][0]][2]-nodepos[barra[i][1]][2]),2));
		i++;
	}
	i = 1;
	
	
// #############################################################################
// ###### MONTAGEM DAS MATRIZES DE RIGIDEZ DE CADA BARRA NO SISTEMA LOCAL ######
// #############################################################################

	
	while(i <= qtdbarras) {
		
		// E  - barraprops[i][0]
		// G  - barraprops[i][1]
		// A  - barraprops[i][2]
		// Iy - barraprops[i][3]
		// Iz - barraprops[i][4]
		// J  - barraprops[i][5]
		// L  - barraprops[i][6]
		
		// Coluna 1
		kblocal[i][0][0] = ((barraprops[i][0]*barraprops[i][2])/barraprops[i][6]);
		kblocal[i][1][0] = 0;
		kblocal[i][2][0] = 0;
		kblocal[i][3][0] = 0;
		kblocal[i][4][0] = 0;
		kblocal[i][5][0] = 0;
		kblocal[i][6][0] = (-1)*((barraprops[i][0]*barraprops[i][2])/barraprops[i][6]);
		kblocal[i][7][0] = 0;
		kblocal[i][8][0] = 0;
		kblocal[i][9][0] = 0;
		kblocal[i][10][0] = 0;
		kblocal[i][11][0] = 0;
		
		// Coluna 2
		kblocal[i][0][1] = 0;
		kblocal[i][1][1] = (12*barraprops[i][0]*barraprops[i][4]/pow(barraprops[i][6],3));
		kblocal[i][2][1] = 0;
		kblocal[i][3][1] = 0;
		kblocal[i][4][1] = 0;
		kblocal[i][5][1] = (6*barraprops[i][0]*barraprops[i][4]/pow(barraprops[i][6],2));
		kblocal[i][6][1] = 0;
		kblocal[i][7][1] = (-1)*(12*barraprops[i][0]*barraprops[i][4]/pow(barraprops[i][6],3));
		kblocal[i][8][1] = 0;
		kblocal[i][9][1] = 0;
		kblocal[i][10][1] = 0;
		kblocal[i][11][1] = (6*barraprops[i][0]*barraprops[i][4]/pow(barraprops[i][6],2));
		
		// Coluna 3
		kblocal[i][0][2] = 0;
		kblocal[i][1][2] = 0;
		kblocal[i][2][2] = ((12*barraprops[i][0]*barraprops[i][3])/pow(barraprops[i][6],3));
		kblocal[i][3][2] = 0;
		kblocal[i][4][2] = (-1)*((6*barraprops[i][0]*barraprops[i][3])/pow(barraprops[i][6],2));
		kblocal[i][5][2] = 0;
		kblocal[i][6][2] = 0;
		kblocal[i][7][2] = 0;
		kblocal[i][8][2] = (-1)*((12*barraprops[i][0]*barraprops[i][3])/pow(barraprops[i][6],3));
		kblocal[i][9][2] = 0;
		kblocal[i][10][2] = (-1)*((6*barraprops[i][0]*barraprops[i][3])/pow(barraprops[i][6],2));
		kblocal[i][11][2] = 0;
		
		// Coluna 4
		kblocal[i][0][3] = 0;
		kblocal[i][1][3] = 0;
		kblocal[i][2][3] = 0;
		kblocal[i][3][3] = (barraprops[i][1]*barraprops[i][5]/barraprops[i][6]);
		kblocal[i][4][3] = 0;
		kblocal[i][5][3] = 0;
		kblocal[i][6][3] = 0;
		kblocal[i][7][3] = 0;
		kblocal[i][8][3] = 0;
		kblocal[i][9][3] = (-1)*(barraprops[i][1]*barraprops[i][5]/barraprops[i][6]);
		kblocal[i][10][3] = 0;
		kblocal[i][11][3] = 0;
		
		// Coluna 5
		kblocal[i][0][4] = 0;
		kblocal[i][1][4] = 0;
		kblocal[i][2][4] = (-1)*((6*barraprops[i][0]*barraprops[i][3])/pow(barraprops[i][6],2));
		kblocal[i][3][4] = 0;
		kblocal[i][4][4] = ((4*barraprops[i][0]*barraprops[i][3])/barraprops[i][6]);
		kblocal[i][5][4] = 0;
		kblocal[i][6][4] = 0;
		kblocal[i][7][4] = 0;
		kblocal[i][8][4] = ((6*barraprops[i][0]*barraprops[i][3])/pow(barraprops[i][6],2));
		kblocal[i][9][4] = 0;
		kblocal[i][10][4] = ((2*barraprops[i][0]*barraprops[i][3])/barraprops[i][6]);
		kblocal[i][11][4] = 0;
		
		// Coluna 6
		kblocal[i][0][5] = 0;
		kblocal[i][1][5] = (6*barraprops[i][0]*barraprops[i][4]/pow(barraprops[i][6],2));
		kblocal[i][2][5] = 0;
		kblocal[i][3][5] = 0;
		kblocal[i][4][5] = 0;
		kblocal[i][5][5] = ((4*barraprops[i][0]*barraprops[i][4])/barraprops[i][6]);
		kblocal[i][6][5] = 0;
		kblocal[i][7][5] = (-1)*(6*barraprops[i][0]*barraprops[i][4]/pow(barraprops[i][6],2));
		kblocal[i][8][5] = 0;
		kblocal[i][9][5] = 0;
		kblocal[i][10][5] = 0;
		kblocal[i][11][5] = ((2*barraprops[i][0]*barraprops[i][4])/barraprops[i][6]);
		
		// Coluna 7
		kblocal[i][0][6] = (-1)*((barraprops[i][0]*barraprops[i][2])/barraprops[i][6]);
		kblocal[i][1][6] = 0;
		kblocal[i][2][6] = 0;
		kblocal[i][3][6] = 0;
		kblocal[i][4][6] = 0;
		kblocal[i][5][6] = 0;
		kblocal[i][6][6] = ((barraprops[i][0]*barraprops[i][2])/barraprops[i][6]);
		kblocal[i][7][6] = 0;
		kblocal[i][8][6] = 0;
		kblocal[i][9][6] = 0;
		kblocal[i][10][6] = 0;
		kblocal[i][11][6] = 0;
		
		// Coluna 8
		kblocal[i][0][7] = 0;
		kblocal[i][1][7] = (-1)*(12*barraprops[i][0]*barraprops[i][4]/pow(barraprops[i][6],3));
		kblocal[i][2][7] = 0;
		kblocal[i][3][7] = 0;
		kblocal[i][4][7] = 0;
		kblocal[i][5][7] = (-1)*(6*barraprops[i][0]*barraprops[i][4]/pow(barraprops[i][6],2));
		kblocal[i][6][7] = 0;
		kblocal[i][7][7] = (12*barraprops[i][0]*barraprops[i][4]/pow(barraprops[i][6],3));
		kblocal[i][8][7] = 0;
		kblocal[i][9][7] = 0;
		kblocal[i][10][7] = 0;
		kblocal[i][11][7] = (-1)*(6*barraprops[i][0]*barraprops[i][4]/pow(barraprops[i][6],2));
		
		// Coluna 9
		kblocal[i][0][8] = 0;
		kblocal[i][1][8] = 0;
		kblocal[i][2][8] = (-1)*((12*barraprops[i][0]*barraprops[i][3])/pow(barraprops[i][6],3));
		kblocal[i][3][8] = 0;
		kblocal[i][4][8] = ((6*barraprops[i][0]*barraprops[i][3])/pow(barraprops[i][6],2));
		kblocal[i][5][8] = 0;
		kblocal[i][6][8] = 0;
		kblocal[i][7][8] = 0;
		kblocal[i][8][8] = ((12*barraprops[i][0]*barraprops[i][3])/pow(barraprops[i][6],3));
		kblocal[i][9][8] = 0;
		kblocal[i][10][8] = ((6*barraprops[i][0]*barraprops[i][3])/pow(barraprops[i][6],2));
		kblocal[i][11][8] = 0;
		
		// Coluna 10
		kblocal[i][0][9] = 0;
		kblocal[i][1][9] = 0;
		kblocal[i][2][9] = 0;
		kblocal[i][3][9] = (-1)*(barraprops[i][1]*barraprops[i][5]/barraprops[i][6]);
		kblocal[i][4][9] = 0;
		kblocal[i][5][9] = 0;
		kblocal[i][6][9] = 0;
		kblocal[i][7][9] = 0;
		kblocal[i][8][9] = 0;
		kblocal[i][9][9] = (barraprops[i][1]*barraprops[i][5]/barraprops[i][6]);
		kblocal[i][10][9] = 0;
		kblocal[i][11][9] = 0;
		
		// Coluna 11
		kblocal[i][0][10] = 0;
		kblocal[i][1][10] = 0;
		kblocal[i][2][10] = (-1)*((6*barraprops[i][0]*barraprops[i][3])/pow(barraprops[i][6],2));
		kblocal[i][3][10] = 0;
		kblocal[i][4][10] = ((2*barraprops[i][0]*barraprops[i][3])/barraprops[i][6]);
		kblocal[i][5][10] = 0;
		kblocal[i][6][10] = 0;
		kblocal[i][7][10] = 0;
		kblocal[i][8][10] = ((6*barraprops[i][0]*barraprops[i][3])/pow(barraprops[i][6],2));
		kblocal[i][9][10] = 0;
		kblocal[i][10][10] = ((4*barraprops[i][0]*barraprops[i][3])/barraprops[i][6]);
		kblocal[i][11][10] = 0;
		
		// Coluna 12
		kblocal[i][0][11] = 0;
		kblocal[i][1][11] = (6*barraprops[i][0]*barraprops[i][4]/pow(barraprops[i][6],2));
		kblocal[i][2][11] = 0;
		kblocal[i][3][11] = 0;
		kblocal[i][4][11] = 0;
		kblocal[i][5][11] = ((2*barraprops[i][0]*barraprops[i][4])/barraprops[i][6]);
		kblocal[i][6][11] = 0;
		kblocal[i][7][11] = (-1)*(6*barraprops[i][0]*barraprops[i][4]/pow(barraprops[i][6],2));
		kblocal[i][8][11] = 0;
		kblocal[i][9][11] = 0;
		kblocal[i][10][11] = 0;
		kblocal[i][11][11] = ((4*barraprops[i][0]*barraprops[i][4])/barraprops[i][6]);
		
		i++;
	}
	i = 1;
	
	
// ##############################################################################
// ###### MONTAGEM DAS MATRIZES DE RIGIDEZ DE CADA BARRA NO SISTEMA GLOBAL ######
// ##############################################################################

	
	// Montagem da Matriz de Rotacao Reduzida para cada barra
	while(i <= qtdbarras) {
		
		// Na direcao do vetor X
		kbrotred[i][0][0] = (nodepos[barra[i][1]][0] - nodepos[barra[i][0]][0])/(barraprops[i][6]);
		kbrotred[i][0][1] = (nodepos[barra[i][1]][1] - nodepos[barra[i][0]][1])/(barraprops[i][6]);
		kbrotred[i][0][2] = (nodepos[barra[i][1]][2] - nodepos[barra[i][0]][2])/(barraprops[i][6]);
		
		// Determinacao do ponto auxiliar K
		pontoauxiliar[0] = barravetoraux[i][0];
		pontoauxiliar[1] = barravetoraux[i][1];
		pontoauxiliar[2] = barravetoraux[i][2];
		
		// Calculo dos cossenos diretores do vetor iK
		// 0 - Alfa;		1 - Beta;		2 - Gama
		pontoauxiliar[3] = sqrt( pow((pontoauxiliar[0] - nodepos[barra[i][0]][0]),2) + pow((pontoauxiliar[1] - nodepos[barra[i][0]][1]),2) + pow((pontoauxiliar[2] - nodepos[barra[i][0]][2]),2) );
		cosauxiliar[0] = (pontoauxiliar[0] - nodepos[barra[i][0]][0])/pontoauxiliar[3];
		cosauxiliar[1] = (pontoauxiliar[1] - nodepos[barra[i][0]][1])/pontoauxiliar[3];
		cosauxiliar[2] = (pontoauxiliar[2] - nodepos[barra[i][0]][2])/pontoauxiliar[3];
		
		// Na direcao do vetor Z
		coefc = sqrt( pow((kbrotred[i][0][1]*cosauxiliar[2]-kbrotred[i][0][2]*cosauxiliar[1]),2) + pow((kbrotred[i][0][2]*cosauxiliar[0]-kbrotred[i][0][0]*cosauxiliar[2]),2) + pow((kbrotred[i][0][0]*cosauxiliar[1]-kbrotred[i][0][1]*cosauxiliar[0]),2) );
		kbrotred[i][2][0] = (kbrotred[i][0][1]*cosauxiliar[2] - kbrotred[i][0][2]*cosauxiliar[1])/coefc;
		kbrotred[i][2][1] = (kbrotred[i][0][2]*cosauxiliar[0] - kbrotred[i][0][0]*cosauxiliar[2])/coefc;
		kbrotred[i][2][2] = (kbrotred[i][0][0]*cosauxiliar[1] - kbrotred[i][0][1]*cosauxiliar[0])/coefc;
		
		// Na direcao do vetor Y
		kbrotred[i][1][0] = kbrotred[i][0][2]*kbrotred[i][2][1] - kbrotred[i][0][1]*kbrotred[i][2][2];
		kbrotred[i][1][1] = kbrotred[i][0][0]*kbrotred[i][2][2] - kbrotred[i][0][2]*kbrotred[i][2][0];
		kbrotred[i][1][2] = kbrotred[i][0][1]*kbrotred[i][2][0] - kbrotred[i][0][0]*kbrotred[i][2][1];
		
		i++;
	}
	i = 1;
	
	// Transformacao das Matrizes de Rotacao das Barras em Nulas
	while(i <= qtdbarras) {
		while(j <= 12) {
			while(k <= 12) {
				kbrot[i][j-1][k-1] = 0;
				k++;
			}
			k = 1;
			j++;
		}
		j = 1;
		
		i++;
	}
	i = 1;
	j = 1;
	k = 1;
	
	// Montagem da Matriz de Rotacao de cada Barra ( kbrot[i][a][b] )
	while(i <= qtdbarras) {
		
		// Elementos que recebem a11 da matriz reduzida
		kbrot[i][0][0] = kbrotred[i][0][0];
		kbrot[i][3][3] = kbrotred[i][0][0];
		kbrot[i][6][6] = kbrotred[i][0][0];
		kbrot[i][9][9] = kbrotred[i][0][0];
		
		// Elementos que recebem a12 da matriz reduzida
		kbrot[i][0][1] = kbrotred[i][0][1];
		kbrot[i][3][4] = kbrotred[i][0][1];
		kbrot[i][6][7] = kbrotred[i][0][1];
		kbrot[i][9][10] = kbrotred[i][0][1];
		
		// Elementos que recebem a13 da matriz reduzida
		kbrot[i][0][2] = kbrotred[i][0][2];
		kbrot[i][3][5] = kbrotred[i][0][2];
		kbrot[i][6][8] = kbrotred[i][0][2];
		kbrot[i][9][11] = kbrotred[i][0][2];
		
		// Elementos que recebem a21 da matriz reduzida
		kbrot[i][1][0] = kbrotred[i][1][0];
		kbrot[i][4][3] = kbrotred[i][1][0];
		kbrot[i][7][6] = kbrotred[i][1][0];
		kbrot[i][10][9] = kbrotred[i][1][0];
		
		// Elementos que recebem a22 da matriz reduzida
		kbrot[i][1][1] = kbrotred[i][1][1];
		kbrot[i][4][4] = kbrotred[i][1][1];
		kbrot[i][7][7] = kbrotred[i][1][1];
		kbrot[i][10][10] = kbrotred[i][1][1];
		
		// Elementos que recebem a23 da matriz reduzida
		kbrot[i][1][2] = kbrotred[i][1][2];
		kbrot[i][4][5] = kbrotred[i][1][2];
		kbrot[i][7][8] = kbrotred[i][1][2];
		kbrot[i][10][11] = kbrotred[i][1][2];
		
		// Elementos que recebem a31 da matriz reduzida
		kbrot[i][2][0] = kbrotred[i][2][0];
		kbrot[i][5][3] = kbrotred[i][2][0];
		kbrot[i][8][6] = kbrotred[i][2][0];
		kbrot[i][11][9] = kbrotred[i][2][0];
		
		// Elementos que recebem a32 da matriz reduzida
		kbrot[i][2][1] = kbrotred[i][2][1];
		kbrot[i][5][4] = kbrotred[i][2][1];
		kbrot[i][8][7] = kbrotred[i][2][1];
		kbrot[i][11][10] = kbrotred[i][2][1];
		
		// Elementos que recebem a33 da matriz reduzida
		kbrot[i][2][2] = kbrotred[i][2][2];
		kbrot[i][5][5] = kbrotred[i][2][2];
		kbrot[i][8][8] = kbrotred[i][2][2];
		kbrot[i][11][11] = kbrotred[i][2][2];
		
		i++;
	}
	i = 1;
	
	// Montagem da Matriz Transposta ( kbrotinversa[i][a][b] )
	while (i <= qtdbarras) {
		while(j <= 12) {
			while(k <= 12) {
				kbrotinversa[i][j-1][k-1] = kbrot[i][k-1][j-1];
				k++;
			}
			k = 1;
			j++;
		}
		j = 1;
		i++;
	}
	i = 1;
	j = 1;
	k = 1;
	
	// Calculo do Produto da Matriz Rotacao Transposta pela Matriz de Rigidez Local
	r = 12; c = 12;
	double *produtotmp[r];
	for (p=0; p<r; p++)
		produtotmp[p] = (double *)malloc(c * sizeof(double));
		
	r = 12; c = 12;
	double *produtotmp2[r];
	for (p=0; p<r; p++)
		produtotmp2[p] = (double *)malloc(c * sizeof(double));
		
	r = 12; c = 12;
	double *produtotmp3[r];
	for (p=0; p<r; p++)
		produtotmp3[p] = (double *)malloc(c * sizeof(double));
		
	while (i <= qtdbarras) {
		while(j <= 12) {
			while(k <= 12) {
				produtotmp[j-1][k-1] = kbrotinversa[i][j-1][k-1];
				k++;
			}
			k = 1;
			j++;
		}
		j = 1;
		
		while(j <= 12) {
			while(k <= 12) {
				produtotmp2[j-1][k-1] = kblocal[i][j-1][k-1];
				k++;
			}
			k = 1;
			j++;
		}
		j = 1;
		
		multiplicaMatriz(produtotmp, produtotmp2, produtotmp3, 12, 12, 12, 12);
		
		while(j <= 12) {
			while(k <= 12) {
				produto[i][j-1][k-1] = produtotmp3[j-1][k-1];
				k++;
			}
			k = 1;
			j++;
		}
		j = 1;
		
		i++;
	}
	i = 1;
	
	// Calculo da Matriz de Rigidez Global da Barra
	
	while (i <= qtdbarras) {
		while(j <= 12) {
			while(k <= 12) {
				produtotmp[j-1][k-1] = produto[i][j-1][k-1];
				k++;
			}
			k = 1;
			j++;
		}
		j = 1;
		
		while(j <= 12) {
			while(k <= 12) {
				produtotmp2[j-1][k-1] = kbrot[i][j-1][k-1];
				k++;
			}
			k = 1;
			j++;
		}
		j = 1;
		
		multiplicaMatriz(produtotmp, produtotmp2, produtotmp3, 12, 12, 12, 12);
		
		while(j <= 12) {
			while(k <= 12) {
				kbglobal[i][j-1][k-1] = produtotmp3[j-1][k-1];
				k++;
			}
			k = 1;
			j++;
		}
		j = 1;
		
		i++;
	}
	i = 1;
	
	
// #####################################################
// ###### MONTAGEM DO SISTEMA GLOBAL DA ESTRUTURA ######
// #####################################################

	
	// Inicializacao da Matriz de Rigidez Global
	r = neq;
	c = neq;
	double *matrizrigidez[r];
	for (p=0; p<r; p++)
		matrizrigidez[p] = (double *)malloc(c * sizeof(double));
	
	i = 0;
	j = 0;
	while(i < neq){
		while(j < neq) {
			matrizrigidez[i][j] = 0;
			j++;
		}
		j = 0;
		i++;
	}
	i = 1;
	j = 1;
		
	// Inicializacao do Vetor de Carga Nodal
	r = neq;
	c = 1;
	double *vetorcarganodal[r];
	for (p=0; p<r; p++)
		vetorcarganodal[p] = (double *)malloc(c * sizeof(double));
		
	i = 0;
	while(i < neq){
		vetorcarganodal[i][0] = 0;
		i++;
	}
	i = 1;
	
	//	Inicializacao do Vetor de Deslocamentos
	r = neq;
	c = 1;
	double *vetordesloc[r];
	for (p=0; p<r; p++)
		vetordesloc[p] = (double *)malloc(c * sizeof(double));
		
	i = 0;
	while(i < neq){
		vetordesloc[i][0] = 0;
		i++;
	}
	i = 1;
		
	// Inicializacao da Matriz de Deslocabilidades
	r = 6;
	c = nnos;
	int *matrizgdl[r];
	for (p=0; p<r; p++)
		matrizgdl[p] = (int *)malloc(c * sizeof(int));
		
	i = 0;
	j = 0;
	while(i < 6){
		while(j < nnos) {
			matrizgdl[i][j] = 0;
			j++;
		}
		j = 0;
		i++;
	}
	i = 1;
	j = 1;
		
	// Inicializacao dos Vetores de Espalhamento
	r = qtdbarras;
	c = 12;
	int *vetorespalhamento[r];
	for (p=0; p<r; p++)
		vetorespalhamento[p] = (int *)malloc(c * sizeof(int));
		
	i = 0;
	j = 0;
	while(i < qtdbarras){
		while(j < 12) {
			vetorespalhamento[i][j] = 5;
			j++;
		}
		j = 0;
		i++;
	}
	i = 1;
	j = 1;
	
	// Montagem da Matriz Global de Deslocabilidades
	neqfixo = 0;
	
	i = 0;
	j = 0;
	while(i < nnos) {
		
		// Verifica Translacao em X
		if(nodeliberdadex[i+1][0] == 1) {
			neqfixo++;
			matrizgdl[0][i] = 1;
		}
		
		// Verifica Translacao em Y
		if(nodeliberdadey[i+1][0] == 1) {
			neqfixo++;
			matrizgdl[1][i] = 1;
		}
		
		// Verifica Translacao em Z
		if(nodeliberdadez[i+1][0] == 1) {
			neqfixo++;
			matrizgdl[2][i] = 1;
		}
		
		// Verifica Rotacao em X
		if(nodeliberdadex[i+1][1] == 1) {
			neqfixo++;
			matrizgdl[3][i] = 1;
		}
		
		// Verifica Rotacao em Y
		if(nodeliberdadey[i+1][1] == 1) {
			neqfixo++;
			matrizgdl[4][i] = 1;
		}
		
		// Verifica Rotacao em Z
		if(nodeliberdadez[i+1][1] == 1) {
			neqfixo++;
			matrizgdl[5][i] = 1;
		}
		
		i++;
	}
	i = 1;
	j = 1;
	neqlivre = neq - neqfixo;
	
	printf("MATRIZ DE RESTRICOES:\n");
	for(i = 0; i < 6; i++) {
		for(j = 0; j < nnos; j++) {
			printf("%i\t", matrizgdl[i][j]);
		}
		printf("\n");
	}
	
	// Preenchimento da Matriz Global de Deslocabilidades
	countL = 0;
	countR = neqlivre;
	
	i = 0;
	j = 0;
	while(i < nnos) {
		while(j < 6) {
			if(matrizgdl[j][i] == 0) {
				countL++;
				matrizgdl[j][i] = countL;
			} else {
				countR++;
				matrizgdl[j][i] = countR;
			}
			j++;
		}
		j = 0;
		i++;
	}
	i = 1;
	j = 1;
	
	// Montagem do Vetor de Espalhamento para cada Barra a partir da Matriz Global de Deslocabilidades
	i = 0;
	j = 0;
	k = 0;
	while(i < qtdbarras) {
		
		j = 0;
		
		k = barra[i+1][0] - 1;
		while(j < 6) {
			vetorespalhamento[i][j] = matrizgdl[j][k];
			j++;
		}
		
		k = barra[i+1][1] - 1;
		while(j < 12) {
			vetorespalhamento[i][j] = matrizgdl[j-6][k];
			j++;
		}
		
		i++;
	}
	i = 1;
	j = 1;
	k = 1;
	
	// Montagem da Matriz de Rigidez Global
	i = 0;
	while(i < qtdbarras) {
		
		ll = 0;
		cl = 0;
		
		while(ll < 12) {
			lg = vetorespalhamento[i][ll] - 1;
			while(cl < 12) {
				
				cg = vetorespalhamento[i][cl] - 1;
				matrizrigidez[lg][cg] = matrizrigidez[lg][cg] + kbglobal[i+1][ll][cl];
				
				cl++;
			}
			cl = 0;
			ll++;
		}
		ll = 0;
		
		i++;
	}
	i = 1;
	
	// Montagem do Vetor de Carregamentos Nodais
	i = 0;
	while (i < nnos) {
		
		j = matrizgdl[0][i]-1;
		vetorcarganodal[j][0] = vetorcarganodal[j][0] + carganodal[i+1][0];
		
		j = matrizgdl[1][i]-1;
		vetorcarganodal[j][0] = vetorcarganodal[j][0] + carganodal[i+1][1];
		
		j = matrizgdl[2][i]-1;
		vetorcarganodal[j][0] = vetorcarganodal[j][0] + carganodal[i+1][2];
		
		j = matrizgdl[3][i]-1;
		vetorcarganodal[j][0] = vetorcarganodal[j][0] + carganodal[i+1][3];
		
		j = matrizgdl[4][i]-1;
		vetorcarganodal[j][0] = vetorcarganodal[j][0] + carganodal[i+1][4];
		
		j = matrizgdl[5][i]-1;
		vetorcarganodal[j][0] = vetorcarganodal[j][0] + carganodal[i+1][5];
		
		i++;
	}
	i = 1;
	j = 1;
	
	
// ###########################################################################
// ###### PARTICIONAMENTO DO SISTEMA GLOBAL PARA RESOLUCAO DAS EQUACOES ######
// ###########################################################################
	
	
	// Inicializacao e Montagem da Matriz dos Graus de Liberdade Livres
	r = neqlivre;
	c = neqlivre;
	double *matrizlivre[r];
	for (p=0; p<r; p++)
		matrizlivre[p] = (double *)malloc(c * sizeof(double));
	
	i = 0;
	j = 0;
	while(i < neqlivre){
		while(j < neqlivre) {
			matrizlivre[i][j] = matrizrigidez[i][j];
			j++;
		}
		j = 0;
		i++;
	}
	i = 1;
	j = 1;
	
	// Inicializacao e Montagem da Matriz Particionada Superior
	r = neqlivre;
	c = neqfixo;
	double *matrizsuperior[r];
	for (p=0; p<r; p++)
		matrizsuperior[p] = (double *)malloc(c * sizeof(double));
	
	i = 0;
	j = 0;
	while(i < neqlivre){
		while(j < neqfixo) {
			matrizsuperior[i][j] = matrizrigidez[i][j+neqlivre];
			j++;
		}
		j = 0;
		i++;
	}
	i = 1;
	j = 1;
	
	// Inicializacao e Montagem da Matriz Particionada Inferior
	r = neqfixo;
	c = neqlivre;
	double *matrizinferior[r];
	for (p=0; p<r; p++)
		matrizinferior[p] = (double *)malloc(c * sizeof(double));
	
	i = 0;
	j = 0;
	while(i < neqfixo){
		while(j < neqlivre) {
			matrizinferior[i][j] = matrizrigidez[i+neqlivre][j];
			j++;
		}
		j = 0;
		i++;
	}
	i = 1;
	j = 1;
	
	// Inicializacao e Montagem da Matriz dos Graus de Liberdade Restritos
	r = neqfixo;
	c = neqfixo;
	double *matrizrestrita[r];
	for (p=0; p<r; p++)
		matrizrestrita[p] = (double *)malloc(c * sizeof(double));
	
	i = 0;
	j = 0;
	while(i < neqfixo){
		while(j < neqfixo) {
			matrizrestrita[i][j] = matrizrigidez[i+neqlivre][j+neqlivre];
			j++;
		}
		j = 0;
		i++;
	}
	i = 1;
	j = 1;
	
	//	Inicializacao e Montagem do Vetor de Forcas Referentes aos Graus de Liberdade Livres
	r = neqlivre;
	c = 1;
	double *vetorforcaslivre[r];
	for (p=0; p<r; p++)
		vetorforcaslivre[p] = (double *)malloc(c * sizeof(double));
		
	i = 0;
	while(i < neqlivre){
		vetorforcaslivre[i][0] = vetorcarganodal[i][0];
		i++;
	}
	i = 1;
	
	//	Inicializacao do Vetor de Forcas Referentes aos Graus de Liberdade Restritos
	r = neqfixo;
	c = 1;
	double *vetorforcasrestritos[r];
	for (p=0; p<r; p++)
		vetorforcasrestritos[p] = (double *)malloc(c * sizeof(double));
		
	i = 0;
	while(i < neqfixo){
		vetorforcasrestritos[i][0] = vetorcarganodal[i+neqlivre][0];
		i++;
	}
	i = 1;
	
	//	Inicializacao do Vetor de Deslocamentos Restritos
	r = neqfixo;
	c = 1;
	double *vetordeslocsrestritos[r];
	for (p=0; p<r; p++)
		vetordeslocsrestritos[p] = (double *)malloc(c * sizeof(double));
		
	i = 0;
	while(i < neqfixo){
		vetordeslocsrestritos[i][0] = 0;
		i++;
	}
	i = 1;
	
	//	Inicializacao do Vetor de Deslocamentos Livres (Incognitas) e Preenchimento Temporario com Zeros
	r = neqlivre;
	c = 1;
	double *vetordeslocslivres[r];
	for (p=0; p<r; p++)
		vetordeslocslivres[p] = (double *)malloc(c * sizeof(double));
		
	i = 0;
	while(i < neqlivre){
		vetordeslocslivres[i][0] = 0;
		i++;
	}
	i = 1;
	
	
// #############################################
// ###### PROCESSAMENTO DO SISTEMA GLOBAL ######
// #############################################


	//	Copia temporaria do vetor de forcas referente aos nos fixados
	r = neqfixo;
	c = 1;
	double *bakvetorforcasrestrito[r];
	for (p=0; p<r; p++)
		bakvetorforcasrestrito[p] = (double *)malloc(c * sizeof(double));
		
	i = 0;
	while(i < neqfixo){
		bakvetorforcasrestrito[i][0] = vetorforcasrestritos[i][0];
		i++;
	}
	i = 1;

	// Inicializacao da Matriz Inversa dos Graus de Liberdade Livres
	r = neqlivre;
	c = neqlivre;
	double *matrizlivreinversa[r];
	for (p=0; p<r; p++)
		matrizlivreinversa[p] = (double *)malloc(c * sizeof(double));
	
	i = 0;
	j = 0;
	while(i < neqlivre){
		while(j < neqlivre) {
			matrizlivreinversa[i][j] = matrizrigidez[i][j];
			j++;
		}
		j = 0;
		i++;
	}
	i = 1;
	j = 1;

	// Inicializacao do Vetor Permutacao para Decomposicao LU
	r = neqlivre + 1; int* permut = malloc(r * sizeof(int));
	
	// Inicializacao da Matriz Auxiliar para Decomposicao LU
	r = neqlivre;
	c = neqlivre;
	double *matrizlivreauxiliar[r];
	for (p=0; p<r; p++)
		matrizlivreauxiliar[p] = (double *)malloc(c * sizeof(double));
	
	i = 0;
	j = 0;
	while(i < neqlivre){
		while(j < neqlivre) {
			matrizlivreauxiliar[i][j] = matrizlivreinversa[i][j];
			j++;
		}
		j = 0;
		i++;
	}
	i = 1;
	j = 1;
	
	// Calculo do Determinante da Matriz Inversa dos GDL-L (que, no momento, ainda e a propria Matriz GDL-L)
	// Verifica a singularidade da matriz de rigidez global da estrutura
	LUPDecompose(matrizlivreauxiliar, neqlivre, 0.00001, permut);
	det = LUPDeterminant(matrizlivreauxiliar, permut, neqlivre);
	
	if(det == 0) {
		printf("ESTRUTURA INSTAVEL! VERIFIQUE\n\n");
		system("pause");
		return 0;
		}
		
	// Calculo das Reaoees de Apoio
	LUPInvert(matrizlivreauxiliar, permut, neqlivre, matrizlivreinversa);
	multiplicaMatriz(matrizlivreinversa, vetorforcaslivre, vetordeslocslivres, neqlivre, neqlivre, neqlivre, 1);	
	multiplicaMatriz(matrizinferior, vetordeslocslivres, vetorforcasrestritos, neqfixo, neqlivre, neqfixo, 1);
	for(i=0;i<neqfixo;i++){
		vetorforcasrestritos[i][0] = vetorforcasrestritos[i][0] - bakvetorforcasrestrito[i][0];
	}


// ###########################################
// ###### SAIDA DE DADOS PARA O USUARIO ######
// ###########################################

	
	printf("DESLOCAMENTOS LIVRES:\n");
	for(i = 0; i < neqlivre; i++) {
		printf("%.6f\n", vetordeslocslivres[i][0]);
	}
	
	printf("REACOES DE APOIO:\n");
	for(i = 0; i < neqfixo; i++) {
		printf("%.2f\n", vetorforcasrestritos[i][0]);
	}
	
	// 	FIM DO PROGRAMA
	
	system("pause");
	return 0;
	
}
