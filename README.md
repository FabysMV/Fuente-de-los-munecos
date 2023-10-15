# Fuente de los muñecos
<img src="https://github.com/FabysMV/Fuente-de-los-munecos/blob/main/Im%C3%A1genes/Captura%20de%20pantalla%202023-10-14%20234701.png" width="100%"
  height="100%"/>
>[!NOTE]
Estructura que llevará <br>
1.-HISTORIA DE LA LEYENDA (A FONDO AUNQUE NO MUY EXTENSO)<br>
2.- DESCRIPCIÓN DE ANIMATRÓNICO<br>
3.- PROCESO DE ELABORACIÓN----> PONER ALGUNOS CÁLCULOS--->fotos de ensamblaje--->diagramas de circuito--->algoritmos/diagrama de flujo<br>


La bella __ciudad de Puebla__, cuna de múltiples e impresionantes leyendas, alberga entre sus calles, __misterios__ que han acompañado a sus habitantes con el pasar del tiempo: desde la epóca prehispánica, pasando por el México colonial, llegando a los albores del siglo pasado. <br>
Los relatos que sus calles susurran son únicos y se viven aún en <i>tiempos modernos</i>.



## ***La fuente de los muñecos*** 
<img src="https://github.com/FabysMV/Fuente-de-los-munecos/blob/main/Im%C3%A1genes/talavera.png" width="100%"
  height="100%"/>
<p align="justify">
En el que hoy es conocido como barrio de Xonaca, antaño llamado <b><i>"Barrio de los catrines"</i></b>, debido a que la gente adinerada del centro del país construía sus fincas.
Frente a la iglesia de La Candelaria, se encontraba una casona, la cual fue ocupada por la emperatriz Carlota, esposa de Maximiliano de Habsburgo. En dicha casona, Maximinio Ávila Camacho, ex-gobernador de Puebla y hermano del expresidente Manuel Ávila Camacho, construyó su casa de verano.<br> 
  <img src="https://github.com/FabysMV/Fuente-de-los-munecos/blob/main/Im%C3%A1genes/avila.png" width="100%"
  height="100%"/>
<p align="justify">
Este inmueble lo cuidaba un caballerango, cuyo nombre se ha perdido ya entre las bocas de la gente que ha perpetuado esta historia. Dicho caballerango tenía dos hijos, <b>una niña y un niño</b>, de seis y siete años. Ambos niños eran muy queridos y apreciados por él y los habitantes del <i>barrio de los catrines</i>.
Un trágico día de lluvias torrenciales, el par de niños salió con rumbo a la escuela, desafortunadamente nunca lograron llegar a su destino.
Al caer la tarde, y debido a su ausencia el padre dió la noticia, junto con los vecinos salieron en busca de los hermanos.<br>
  
Con un gran pesar se dedujo que habían caído en un pozo de agua cercano a la propiedad del gobernador Ávila Camacho. Los cuerpos de los hermanos <b>nunca fueron encontrados</b>. Al enterarse de la noticia, el gobernador, quien estimaba mucho a su caballerango, mandó a construir una fuente, entre las que hoy son las calles 22 Oriente y 18 Norte, con azulejos de talavera y un pedestal con la figura de dos niños.
La pequeña niña de rostro pálido, con un libro debajo de su brazo derecho, porta un vestido con olanes, en su cabello dos largas trenzas que adornan sus hombros, extiende su brazo izquierdo con delicadeza y rodea al niño, su hermano, vestido con una camisa verde y un overol. 
<br> <br>
<img src="https://github.com/FabysMV/Fuente-de-los-munecos/blob/main/Im%C3%A1genes/pozo.png" width="100%"
  height="100%"/>
<p align="justify">
Desde esa fecha e incluso ahora, los habitantes del barrio de Xonaca cuentan como por las noches,las figuras de los dos hermanitos cobran vida, salen a jugar, divertirse, sus risas llenas de júbilo resuenan por todo el barrio hasta que los primeros rayos que acompañan al amanecer aparecen. Es entonces cuando vuelven a su pedestal, para volver a quedar pretrificados, esperando a que la noche caiga una vez más y así poder volver a jugar una noche más.</p>



  <img src="https://github.com/FabysMV/Fuente-de-los-munecos/blob/7b09bb53ef8141561e2ab438184908cd7aae595c/Im%C3%A1genes/Fuente_mu%C3%B1eco.png">

  <img src="https://github.com/FabysMV/Fuente-de-los-munecos/blob/main/Im%C3%A1genes/tirita.png" width="100%"
  height="100%"/>
## ¿Qué hacen los muñecos?
<p align="justify">
El presente proyecto consiste en el desarrollo de dos animatrónicos, un niño y una niña, los cuales interactuarán con el público. Para esto, se utiliza un control a través de voz que detecta la intensidad con la que se les habla a los muñecos de la fuente. Éstos reaccionarán de diferente forma dependiendo de cómo se realice la comunicación con ellos.

De igual manera, la reacción de los muñecos será a través de movimiento, donde cada frecuencia de voz envía una señal diferente a los servomotores para que estos ejecuten una secuencia de movimientos predeterminados.</p>

En la siguiente tabla se explica las reacciones que tendrán los muñecos para las diferentes intensidades que sean detectadas. </p>

<img src="https://github.com/FabysMV/Fuente-de-los-munecos/blob/main/Im%C3%A1genes/tabla_accion.png" width="100%"
  height="100%"/>

<p align="justify">Si nadie le habla a los muñecos, entrarán en un estado de <i>stand by</i> y harán diferentes acciones predeterminadas como cantar o mover sus cabezas.</p>  <br>  <br>
 <img src="https://github.com/FabysMV/Fuente-de-los-munecos/blob/main/Im%C3%A1genes/tirita.png" width="100%"
  height="100%"/>

  
## PROCESO DE ELABORACIÓN.

**_Parte electrónica_**

<p align="justify">
En este apartado se decriben los circuitos implementados para el funcionamiento de los animatrónicos, asi como las adecuaciones tecnicas pertinentes para adecuerlo a las necesidades requeridas.</p>

<p align="justify">
En primera instancia, se ocuparon de dos circuitos de amplificación con filtrado para la voz de los animatrónicos, ya que necesitábamos que fueran lo más claros y posibles, con potencia suficiente para que se escucharan a cierta distancia. Posterior a ello, se requirió de un circuito que controlara los servomotores y que estos realizaran la labor del movimiento de quijada y cabeza, al mismo tiempo que estos hablaban.</p>

![Circuito amplificador](https://github.com/FabysMV/Fuente-de-los-munecos/assets/147775106/4f598ded-af15-4841-99ba-1e9054e95909)

![2](https://github.com/FabysMV/Fuente-de-los-munecos/assets/147775106/710536d2-34ef-4c8f-bbf4-9ae741a398ac)
>Circuitos amplificadores.

![servos](https://github.com/FabysMV/Fuente-de-los-munecos/assets/147775106/dacdbc3f-c55e-4eed-bd40-7d0c728a11ca)
>Curcuito controlador de servomotores a través de micrófono.




**_Progamación_**




**_Construcción de los muñecos_**


 <img src="https://github.com/FabysMV/Fuente-de-los-munecos/blob/main/Im%C3%A1genes/tirita.png" width="100%"
  height="100%"/>
## EVIDENCIAS.

<p align="justify">
<figure>
  <img src="https://github.com/FabysMV/Fuente-de-los-munecos/assets/147775106/e592b361-e638-42d4-ba4a-2e542bcb2edb"/></p>
  <figcaption> circuito de reproducción de audio.</figcaption>
</figure>


<p align="justify">
<figure>
  <img src="https://github.com/FabysMV/Fuente-de-los-munecos/assets/147775106/961bb3e5-4920-4a95-888d-2b5784c8ca0b"/></p>
  <figcaption> circuito de servomotor controlado por micrófono.</figcaption>
</figure>

  
<p align="justify">
<figure>
  <img src="https://github.com/FabysMV/Fuente-de-los-munecos/assets/147775106/bd59a6ca-a73b-49d9-92c8-8ab126f9c04f"/></p>
 
</figure>

>Impresión de mandibula.


<p align="center">
<figure>
    <img src="https://github.com/FabysMV/Fuente-de-los-munecos/assets/147775106/93f09457-6ce6-49e3-8455-ece9f894928a"/></p>
  <figcaption> Corte de piezas del cuerpo. </figcaption>
</figure>
