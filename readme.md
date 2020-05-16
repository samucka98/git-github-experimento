# Git comandos básicos
>As { } são para indicar um nome que o usuário irá dar ou variável.

---
## Iniciando e adicionando pontos.
### Este recurso nos da o poder de controlar o tempo durante o processo de desenvolvimento.

* Dentro do diretório devemos iniciar a nossa linha do tempo.
>`git init`

* Dica para criar arquivo com mais facilidade.
> `touch {nome do arquivo com extensão}`

* Adicionar um ponto, prepara arquivo para commit.
> `git add {nome do arquivo com extensão}`

* Adicionar tudo.
> `git add .`

* Efetivar a adição e documentar.
> `git commit -m "mensagem"`

* Efetivar uma modificação e documentar
> `git commit -am "mensagem"`

---
## Monitorar

* Verificar estado do projeto(arquivos).
> `git status`

* Verificar histórico, ou pontos na linha do tempo.
> `git log`

* Analisar os commits, sem o hash ele mostra o ultimo.
> `git show {hash}` ou `git show`

---
## Iniciar uma nova função no projeto sem interferir no projeto principal.
### Poder de controlar universos paralelos - linhas do tempo alternativas.

Utilizando as branch - Significa ramificação, Principal branch é a master.

* Criar.
> `git branch {nome da branch: ex: feature/cart}`

* Alternar entre branch's, manipula linha do tempo.
> `git checkout {nome da branch}`

* Vizualizar todas as branch.
> `git branch` 

* Enviar branch para o repositório remoto
> `git push --set-upstream origin MinhaNovaBrach`

Deletar branch no topico abaixo.

---
## Adicionar as novas funcionalidades no projeto em produção.
### Mesclar a linha do tempo alternativa(branch) com a principal.

* União de linhas do tempo
> `git merge {nome da branch}`

* Quando uma branch é finalizada e a funcionalidade esta pronta, e foi realizada a união então é necessário excluir a branch.
> `git branch -D {nome da branch}`

---
## Criação de repositório remoto

* Adicionar projeto local para o repositório do github.
> `git remote add origin {link}`

* Enviar(Empurrar) o projeto local adicionado ao repositório no github.
> `git push -u origin master` // Como é a primeira vez é necessário utilizar o s parametros: `-u origin master`

---
## Contribuir em algum projeto em andamento.

* Adicionando o repositório
> `git clone {link}`

* Criando uma branch e mudando para ela.
> `git checkout -b {nome da branch}`

---
## Puxar atualizações feitas por outros desenvolvedores.

* Puxa todas as alterações(para realizar esta operação é recomendáve todos devem atualizar o projeto para evitar conflitos).
> `git pull`

---
## Voltando determinado arquivo na linha do tempo

* Recuperando arquivo
> `git checkout {hash} -- {nome do arquivo com extensão}`

---
## Recuperar arquivo deletado.

* Caso a remoção não tenha passado por commits
> `git checkout -- {nome do arquivo com extensão}`

* Se passou por commit
> `git checkout {hash} -- {nome do arquivo com extensão}`
