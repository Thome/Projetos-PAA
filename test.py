def inicializar(tabela, tamanho):
    i = 0
    while i < tamanho:
        tabela.append(-1)
        i += 1
     

def calcular_tabela(tabela, P):
    m = len(P)
    j = -1
    i = 1
    inicializar(tabela, m)
    
    while i < m:
        while j >= 0 and P[j+1] != P[i]:
            j = tabela[j]
        if P[j+1] == P[i]:
            j += 1
        tabela[i] = j

        i += 1
    
    print("Done!")


def busca_kmp(pos, tab, T, P):
    n = len(T)
    m = len(P)
    j = -1
    calcular_tabela(tab, P)

    for i in range(n):
        while j >= 0 and P[j+1] != T[i]:
            j = tab[j]
        if P[j+1] == T[i]:
            j += 1
        if j == m - 1:
            pos.append(i - m + 1)
            j = tab[j]

    """done"""  


if __name__ == "__main__":
    tab = []
    pos = []
    pLista = "ara"
    tLista = "araradearacaju"
    busca_kmp(pos, tab, tLista, pLista)
    print("Tabela:")
    print(tab)
    print("Posições:")
    print(pos)
