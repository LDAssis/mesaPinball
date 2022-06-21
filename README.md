# Mesa de pinball autonoma
## Objetivo / Ideia
Esse foi um projeto desenvolvido pelo Laboratório de automação (Univates) em conjuto com o professor Alexandre Wolf.
A ideia é desenvolver duas mesas de pinball que podem jogar sozinhas, ou de forma manual. As duas mesas serão colocadas frente a frente, tendo o objetivo de lançar a bolinha para o outro lado e ir pontuando conforme a bolinha for batendo nos cantos. </br>
A automação da mesa será feita através de uma câmera apontada em direção a mesa que será responsavel por "enxergar" a bolinha e algumas marcações da mesa para localizar onde a bolinha se encontra, a area na qual os batedores atuam e a area de lançamento da bolinha. </br>
Para seu funcionamento autonomo se tem 2 formas de funcionamento:
- Algoritimo: 
- IA:

## Execução
### Mesa:
As mesas foram construidas toda em mdf e seus componentes eletronicos são (cada uma):
- 3 Push buttons com led, utilizado para os comandos
- 8 Botões de fim de curso, utilizado para capturar o impacto da bolinha em alguns cantos
- 3 Solenoides, utilizadas para os comandos do braço esquerdo, direito e lançamento da bolinha
- 1 módulo relé, utilizado para alimentar as solenoides
- 8 leds RGB
- 1 arduino mega, utilizado para controlar todos os componentes e se comunicar com o PC (explicação a frente)
- 1 Fonte de computador 400W+ utilizada para ambas as mesas
As mesas são espelhadas e identicas, todos os conectores e comandos serão iguais em ambos os lados

### Pc:
O PC será responsavel por controlar as mesas e utilizará comunicação serial para conversar com os arduinos.

### Automação:
