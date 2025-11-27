import os
VOLTOU = 69
SAIR = 67

def desenha(oq):
    os.system('clear')
    if oq == 'menu':
        print("estou no menu")
        print("1 - Opção 1")
        print("2 - Opção 2")
        print("3 - Sair")
    elif oq == 'opcao1':
        print("Você escolheu a Opção 1")
        print("voltar: 1")
        print("sair: 2")
        print("opcao1_2: 3")
    elif oq == 'opcao2':
        print("Você escolheu a Opção 2")
        print("voltar: 1")
        print("sair: 2")
    elif oq == 'opcao1_2':
        print("Você está na Opção 1.2")
        print("voltar: 1")
        print("sair: 2")
    return input()

def opcao1():
    escolha = desenha('opcao1')
    r = 0
    if escolha == '1':
        return VOLTOU
    elif escolha == '2':
        return SAIR
    elif escolha == '3':
        r = opcao1_2()
    else:
        opcao1()

    if r == VOLTOU:
        return opcao1()
    if r == SAIR:
        return SAIR

def opcao2():
    escolha = desenha('opcao2')
    if escolha == '1':
        return VOLTOU
    elif escolha == '2':
        return SAIR
    else:
        opcao2()

def opcao1_2():
    escolha = desenha('opcao1_2')
    if escolha == '1':
        return VOLTOU
    elif escolha == '2':
        return SAIR
    else:
        opcao1_2()


def menu():
    opcao = desenha('menu')
    r = 0
    if opcao == '1':
        r = opcao1()
    elif opcao == '2':
        r = opcao2()
    elif opcao == '3':
        r = SAIR
    else:
        menu()

    if r == VOLTOU:
        menu()
    if r == SAIR:
        os.system('clear')
        print("Saindo...")
        exit()

menu()
