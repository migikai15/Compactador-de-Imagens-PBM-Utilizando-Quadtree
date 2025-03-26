# Compactador-de-Imagens-PBM-Utilizando-Quadtree

Este programa em C implementa um algoritmo de **compressão de imagens PBM** utilizando a técnica de **quadtree**. Ele analisa uma imagem binária e a converte em uma representação compacta baseada em regiões uniformes.

## **Como Funciona**
1. O programa recebe um arquivo de imagem no formato **PBM (Portable Bitmap - P1)**.
2. Lê os dados da imagem e os armazena em uma matriz.
3. O algoritmo **divide a imagem em regiões** e verifica se cada região possui pixels uniformes.
4. Caso uma região contenha apenas pixels `1`, imprime `'P'`.
5. Caso contenha apenas pixels `0`, imprime `'B'`.
6. Se houver mistura de pixels, imprime `'X'` e continua dividindo a região em quatro partes.
7. O resultado é um código compactado que representa a estrutura da imagem.


## **Formato do Arquivo PBM (P1)**
O programa aceita imagens no formato **PBM ASCII (P1)**, que segue a estrutura:

### **Exemplo de entrada:**
```plaintext
P1
# Exemplo de imagem 4x4
4 4
1 1 0 0
1 1 0 0
0 0 1 1
0 0 1 1
```

### **Saída esperada:**
```plaintext
Dimensões da imagem: 4 x 4
Matriz da imagem:
1 1 0 0
1 1 0 0
0 0 1 1
0 0 1 1

Código resultante: XXPBPB
```

## **Estrutura do Código**

### **Principais Funções:**
- `Uniforme(...)`: Verifica se uma região da imagem é completamente uniforme.
- `codificarImagem(...)`: Aplica o algoritmo de compressão com quadtree.
- `processarArquivo(...)`: Lê o arquivo PBM e prepara a imagem para compressão.


