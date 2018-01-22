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


def busca_kmp(T, P):
    pos = []
    tab = []
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

    # > 90%? return 1, else return 0  


if __name__ == "__main__":

    f1 = open('input.txt', 'r')
    f2 = open('output', 'w')

    tam = int((f1.readline()).replace("\n",""))
    T = (f1.readline()).replace("\n","")
    n_diseases = int((f1.readline()).replace("\n",""))
    d = dict()

    while n_diseases > 0:
        next_line = f1.readline().split(' ')
        disease = next_line[0]
        n_genes = next_line[1]
        genes_ativos = 0
        contador = 0
        
        while contador < n_genes:
            gene = next_line[contador + 2]
            if kmp(T, gene):
                genes_ativos += 1
            contador += 1

        
        percent = round(genes_ativos / n_genes)
        d[percent] = disease
        n_diseases -= 1


    # código
    # ordena-se diseases e %s, imprime
    porcentagems = sorted(d)
    porcentagems.reverse()
    for pcent in porcentagems:
        text = "%s: %s" % (d[pcent], str(pcent)) + "%"
        f2.write(text)
        #f2.write('\n') talvez necessário

    f1.close()
    f2.close()
    """done"""
