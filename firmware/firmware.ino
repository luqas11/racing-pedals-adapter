#include <Joystick.h>

/*
 * Resumen:
 * El Arduino Pro Micro que corre este sketch recibe las señales de los dos potenciómetros logarítmicos que están ubicados en la pedalera.
 * Las señales son linealizadas y enviadas a la pc como ejes de joystick.
 * La constante MODO_DEBUG permite desactivar la salida de joystick y activar logs que muestran el valor actual de las señales antes y después de linealizar.
 *
 * Detalle de la fórmula para linealizar la señal:
 * valorLinealizado = log(valorRaw - valorMinimo) * pendiente
 *
 * Donde:
 * -  valorLinealizado es el valor después de la linealización
 * -  valorRaw es la lectura que llega desde el potenciómetro
 * -  valorMinimo es el valor que tiene el potenciómetro cuando está en la posición mínima (sin presionar el pedal)
 * -  pendiente es la pendiente que tiene la recta linealizada (a mayor valor, mayor resolución de señal recibe la pc, y a menor valor, menos error relativo tiene la linealización)
 *
 * Curva aproximada de los potenciómetros:
 * f(x) = 3e^x + 50
 * Basada en 8 mediciones del pedal, desde f(0) hasta f(8) siendo 0 el pedal sin presionar y 8 el pedal presionado al máximo.
 */

// Joystick object
Joystick_ Joystick;
// If true, disables the joystick and sends the input data to the serial monitor instead
const bool DEBUG_MODE = false;

void setup()
{
  // Initialize objects
  if (DEBUG_MODE)
  {
    Serial.begin(9600);
  }
  else
  {
    Joystick.begin();
  }
}

void loop()
{
  // Read the analog inputs and map the raw values to acceptable values for the Joystick object
  int accelerator = analogRead(A0);
  accelerator = log(accelerator - 45) * 50;
  accelerator = constrain(accelerator, 120, 330);
  accelerator = map(accelerator, 120, 330, 0, 1023);

  int brake = analogRead(A2);
  brake = log(brake - 45) * 50;
  brake = constrain(brake, 120, 330);
  brake = map(brake, 120, 330, 0, 1023);

  if (DEBUG_MODE)
  {
    // Print the raw input values in the serial monitor
    Serial.println();
    Serial.println("Raw analog inputs values:");
    Serial.println("Accelerator: " + (String)(analogRead(A0)));
    Serial.println("Brake: " + (String)(analogRead(A2)));
    delay(200);
  }
  else
  {
    // Set the mapped input values to the Joystick axes
    Joystick.setRxAxis(accelerator);
    Joystick.setRyAxis(brake);
  }
}
