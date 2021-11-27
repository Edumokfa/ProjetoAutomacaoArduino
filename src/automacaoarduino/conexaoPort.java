/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package automacaoarduino;

import conexaoArduino.conexaoArduino;

/**
 *
 * @author juanw
 */
public interface conexaoPort {
    static conexaoArduino con = new conexaoArduino("COM4");
    boolean iniciado = false;
}
