/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.nanovm;

/**
 *
 * @author nils
 */
public class NanoVMByteCode {

    int cur;
    int maxsize;
    byte[] data;

    public NanoVMByteCode(int maxsize) {
        this.maxsize = maxsize;
        data = new byte[maxsize];
    }

    public int getSize() {
        return cur;
    }

    public byte getByte(int pos) {
        return data[pos];
    }


    // write a 8 bit value into buffer and make sure buffer
    // end is not overwritten
    public void write8(int val) throws ConvertException {
        if (cur >= maxsize) {
            throw new ConvertException("Converted data too big");
        }
        data[cur++] = (byte) val;
    }

    // write a 16 bit value little endian into buffer
    public void write16(int val) throws ConvertException {
        write8(val & 0xff);
        write8((val >> 8) & 0xff);
    }

    // write a 32 bit value little endian into buffer
    public void write32(int val) throws ConvertException {
        write8(val & 0xff);
        write8((val >> 8) & 0xff);
        write8((val >> 16) & 0xff);
        write8((val >> 24) & 0xff);
    }
}
