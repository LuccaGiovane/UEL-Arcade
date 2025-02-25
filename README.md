<div align="center">
  <h1><b>Pew-Pew</b></h1><br><br>
  
  <a href="LICENSE" target="_blank">![C++](https://img.shields.io/badge/C++-11%2B-blue.svg)</a>
  ![OpenGL](https://img.shields.io/badge/OpenGL-Utility-yellowgreen.svg)
  ![GLUT](https://img.shields.io/badge/GLUT-3.x-blueviolet)
  

</div>

<div>
  <h2>📖 Descrição</h2>
  <p>
    <b>Pew-Pew</b> é um jogo de tiro em 3D desenvolvido como projeto final da disciplina de Computação Gráfica da Universidade Estadual de Londrina (UEL). O jogo conta com interação via teclado, projeção 3D com definição de janela de recorte e câmera, modelo de iluminação e animação contínua.
  </p>
</div>

<div>
  <h2>🎯 Funcionalidades</h2>
  <ul>
    <li><b>Interação com o Usuário:</b> Controle do jogador via teclado (movimentação, rotação, disparo e comandos para reiniciar/sair em game over).</li>
    <li><b>Projeção 3D:</b> Uso de perspectiva com definição de janela de recorte e câmera dinâmica, que segue o jogador.</li>
    <li><b>Iluminação:</b> Implementação de modelo de iluminação com luz ambiente para o ambiente e luz dinâmica para o efeito de tiro.</li>
    <li><b>Animação:</b> Movimento contínuo dos inimigos, que perseguem o jogador, além de animações do HUD e da tela de game over.</li>
    <li><b>Sistema de Colisão:</b> Detecção de colisões tanto com o ambiente (paredes da sala) quanto entre os inimigos e o jogador.</li>
    <li><b>Sistema de Disparo:</b> Implementação do disparo do jogador, que diminui a saúde dos inimigos e atualiza a pontuação.</li>
  </ul>
</div>

<div>
  <h2>👨🏻‍💻 Tecnologias Utilizadas</h2>
  <ul>
    <li><b>C++</b></li>
    <li><b>OpenGL</b> – API gráfica para renderização 3D.</li>
    <li><b>GLUT/FreeGLUT</b> – Biblioteca para gerenciamento de janelas e entrada do usuário.</li>
  </ul>
</div>

<div>
  <h2>💾 Instalação e Configuração</h2>
  <p>
    Para compilar e executar o jogo, siga os passos abaixo:
  </p>
  
  <b>Clone o repositório</b>
  ```bash
  git clone https://github.com/LuccaGiovane/UEL-Arcade
  cd Pew-Pew-Arcade-Shooter
  ```
  <b>Compile o projeto</b><br>
  Se você possuir um <i>Makefile</i> configurado, basta executar:
  ```bash
  make
  ```
  Caso contrário, compile manualmente com:
  ```bash
  g++ -std=c++11 -o PewPew main.cpp menu.cpp player.cpp enemy.cpp map.cpp -lGL -lGLU -lglut
  ```

  <b>Execute o jogo</b>
  ```bash
  ./PewPew
  ```
    
</div>

<div>
  <h2>📁 Estrutura do Projeto</h2>
  <pre>
.
├── LICENSE
├── Makefile
├── main.cpp
├── menu.cpp
├── menu.h
├── player.cpp
├── player.h
├── enemy.cpp
├── enemy.h
├── map.cpp
└── map.h
  </pre>
</div>

<div>
  <h2>🔎 Funcionalidades Detalhadas</h2>
  <h3>1. Interface e HUD</h3>
  <p>
    - Desenha a mira (crosshair) central na tela utilizando uma projeção 2D sobre o cenário 3D.<br>
    - Exibe informações de status do jogador, como HP e pontuação, no canto superior.
  </p>
  
  <h3>2. Movimentação e Controle</h3>
  <p>
    - O jogador pode se mover para frente, trás e realizar movimentos laterais.<br>
    - Rotaciona a direção do jogador com as teclas de giro.<br>
    - A posição da câmera é atualizada constantemente para seguir o jogador.
  </p>
  
  <h3>3. Sistema de Disparo</h3>
  <p>
    - Ao pressionar a tecla de disparo (espaço), o jogador atira e ativa uma luz temporária que simula o efeito do tiro.<br>
    - A função de disparo verifica se os inimigos estão alinhados com a mira e, se acertados, diminui sua saúde.
  </p>
  
  <h3>4. Inimigos e Inteligência Artificial</h3>
  <p>
    - Inimigos (monstros) são gerados periodicamente com diferentes tipos (básico, rápido, forte).<br>
    - Cada inimigo possui comportamento específico, movendo-se em direção ao jogador e causando dano ao colidir.<br>
    - A pontuação do jogador é atualizada conforme o tipo de inimigo eliminado.
  </p>
  
  <h3>5. Ambiente e Colisões</h3>
  <p>
    - A cena se passa em uma sala 3D com chão, teto e paredes, definida por constantes (ex.: <code>ROOM_SIZE</code>).<br>
    - A função de colisão impede que o jogador e inimigos saiam dos limites da sala.
  </p>
  
  <h3>6. Tela de Game Over</h3>
  <p>
    - Ao zerar a vida do jogador, é exibida uma tela de game over com a pontuação final e instruções para reiniciar ou sair.
  </p>
</div>

<div>
  <h2>🤝 Contribuições</h2>
  <p>
    Contribuições são bem-vindas! Se você deseja ajudar a melhorar o projeto, sinta-se à vontade para abrir uma issue ou enviar um pull request.
  </p>
</div>
