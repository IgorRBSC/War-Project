# War-like Game Base (C)

Projeto em C que implementa a base de um jogo estilo **War** com:
- Estruturas (`struct`) para territórios.
- Cadastro de territórios (nome, cor, tropas) usando vetor dinâmico.
- Lógica de ataque entre territórios usando alocação dinâmica e ponteiros.
- Sistema de missões estratégicas com verificação de vitória.
- Código modularizado em múltiplos arquivos `.c` / `.h`.

## Como compilar
```bash
make
```

## Como executar
```bash
./war_game
```

## Arquivos
- `main.c` - interface de menu e fluxo principal.
- `territory.h/.c` - definição e funções de territórios.
- `attack.h/.c` - lógica de ataque (usa ponteiros, malloc/free).
- `mission.h/.c` - criação e verificação de missões (dinâmico).
- `utils.h/.c` - funções utilitárias.
- `Makefile` - para compilar.

## Observações
- Projeto educacional com foco em organização, modularização e uso de ponteiros.
- É possível estender para salvar/ler de arquivo, IA, rede, etc.
