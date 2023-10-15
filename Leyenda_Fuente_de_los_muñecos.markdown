# Leyenda de la fuente de los muñecos
Lo primero que se hace es el control de estado de los muñecos, esto se logra con dos botones que los despiertan o los ponen a dormir.
```ruby
if(digitalRead(Up) == HIGH)//si se presionó el botón, despertarán los muñecos
  {Up = true;}
 
  if(digitalRead(Sleep) == HIGH && digitalRead(Up)== LOW)//si se presionó el botón de dormir
  { delta_sec = 0;
    Up = false;
    Serial.println("dormido");
    do{ //vemos que no se haya dado la indicación de que despierten
        if(digitalRead(Up) == HIGH)
        {Up = true; Serial.println("despertando...");
        delay(100);}//si es así, cambiamos el estado de Up a activo
      }while(Up == false); //cuando Up esté activo, salimos del ciclo
    }
```
Después se revisan las primeras condiciones mostradas en la tabla anterior. 
```ruby
if(bajo<analogRead(A0)<alto) //el microfono de la nene tiene ruido?
    {//---------------------------------------------------------------------------------- 
          if(bajo<analogRead(A1)<alto) //tiene ruido la nena?
          {//// COMIENZO O SIGO EL CONTEO//////////
            if(flag == false){in = 0;}
            if(in == 0){tiempo_set = millis();}
            delta_sec = millis() - tiempo_set;
            in ++;
            if(delta_sec >= 60000){flag = true;
                                   tiempo_set = 0;}
            ////// NADA ////////////////////////////
            }//end if ruido nena
          else if(0 < analogRead(A1) < bajo) // le hablan bajo EXCLUSIVAMENTE a la nena
          { flag = false;
            nenes.g_bajo();}//end if bajo a nena
          else if(alto < analogRead(A1)< max)
          { flag = false;
            nenes.g_alto();}//end if alto a nena  
      }//end if ruido a nene-----
```

Si ninguna de las condiciones se cumplen, se revisa el segundo bloque de la tabla. 
```ruby
else if(bajo<analogRead(A1)<alto) //el microfono de la nena tiene ruido?
    {//---------------------------------------------------------------------------------- 
          if(0 < analogRead(A0) < bajo) // le hablan bajo EXCLUSIVAMENTE a nene
          { flag = false;
            nenes.b_bajo();}//end if bajo a nene
          else if(alto < analogRead(A0)< max) // le hablan alto EXCLUSIVAMENTE a nene 
          {   flag = false;
              nenes.b_alto();}//end if alto a nene
      }//end if ruido a nena----
```
Por último, si ninguno de los dos bloques coincide con el evento, se procede con el siguiente código en donde le hablan a los dos muñecos.
```ruby
///      CUANDO NO HAY RUIDO --> LE HABLAN A LOS DOS    ///
      //¿a la nena le hablan alto?
      else if(alto < analogRead(A1)< max)
      {   flag = false;
          if(alto < analogRead(A0)< max)
          {//acciones AMBOS alto
            nenes.ambos_alto();}//le hablan alto al nene?
          else if(0 < analogRead(A0) < bajo)
          {nenes.ambos_g();//le hablan más alto a la nena, el se quiere incluir
            } // le hablan bajo al nene? 
        }//end if nena alta 
        //¿a nena le hablan bajo?
      else if(0 < analogRead(A1) < bajo)
      { flag = false;
        if(alto < analogRead(A0)< max)
          { nenes.ambos_b();}//le hablan alto al nene?  
        else if(0 < analogRead(A0) < bajo)
          {nenes.ambos_bajo();} // le hablan bajo al nene?
       }//end if hablan bajo a nena
```

Si los muñecos entran en stand by, se ejecutan las acciones predeterminadas. Se cancelará esta ejecución en cuanto se vuelva a detectar un sonido en los micrófonos.

```ruby
if(flag == true)
      {
          //cálculos para el timer
          tiempo_prev = tiempo;
          tiempo = millis();
          cont_s = cont_s + tiempo - tiempo_prev; //incrementa el conteo en delta 
          if(last_s != s)
          { switch(s){case 0: nenes.baile();   break;
                      case 1: nenes.lamento(); break;
                      case 2: nenes.canto();   break;}//end switch s
            }// end if last_s

          if(cont_s >= 30000)//el límite debe de ser la duración del audio + 30 segundos
          {//ahora se cambia la secuencia
            Serial.println("cambio de secuencia");
            s = random(0,2);//elegir una secuencia 1.-baile  2.-lamento  3.-canto 
            Serial.println(s);
            cont_s = 0;}
          last_s = s;
       }//end if flag true --> que el contador ya llegó al limite
```
