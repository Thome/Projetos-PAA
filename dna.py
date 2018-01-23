def calcular_tabela(P):
    m = len(P)
    j = -1
    i = 1
    tabela = [-1] * m
    
    while i < m:
        while j >= 0 and P[j+1] != P[i]:
            j = tabela[j]
        if P[j+1] == P[i]:
            j += 1
        tabela[i] = j

        i += 1
    
    return tabela

def kmp(T, P, tam):
    n = len(T)
    m = len(P)
    j = -1
    i = 0
    temp = 0 
    su_m = 0 
    tab = calcular_tabela(P)
    P = P+'$'
    while i < n and len(P) >= tam:
        while j >= 0 and P[j+1] != T[i]:
            j = tab[j]
        if P[j+1] == T[i]:
            j += 1
            temp += 1 
        else:
            if temp >= tam: #add
                su_m += temp#temp
                P = P[tam:] #add
                tab = calcular_tabela(P) #add
                j = - 1   #add
        temp = j + 1 #add


        if j == m - 1:
            su_m += j + 1
            P = P[j:] #add
            j = tab[j]
            break #add
            
        i += 1

    if su_m / m >= 0.9:
        return 1
    else:
        return 0

if __name__ == "__main__":

    f1 = open('input.txt', 'r')
    f2 = open('output.txt', 'w')

    tam = int((f1.readline()).replace("\n",""))
    T = (f1.readline()).replace("\n","")
    n_diseases = int((f1.readline()).replace("\n",""))
    d = dict()

    while n_diseases > 0:
        next_line = f1.readline().split(' ')
        disease = next_line[0]
        n_genes = int(next_line[1])
        genes_ativos = 0
        contador = 0
        
        while contador < n_genes:
            gene = next_line[contador + 2]
            if kmp(T, gene, tam):
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
        f2.write('\n')

    f1.close()
    f2.close()
    print("done")
