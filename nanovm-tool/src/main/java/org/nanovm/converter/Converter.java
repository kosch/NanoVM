package org.nanovm.converter;

import java.util.Arrays;

/**
 * Just to create the NVM bytecode
 * todo use logging
 */
public class Converter {

    private static final int MAGIC = 0xBE000000;
    private static final int VERSION = 2;

    private byte[] outputBuffer;
    private int cur;

    private final ClassLoader classLoader;

    public Converter(ClassLoader classLoader, int byteCodeLimit) throws ConvertException, ClassNotFoundException {
        outputBuffer = new byte[byteCodeLimit];
        this.classLoader = classLoader;

        try {
            writeHeader();           // write file header
            writeClassHeaders();     // write class headers
            writeConstantEntries();  // write all 32-bit constants
            writeStrings();          // write all string data
            writeMethods();          // write method headers and byte code
            updateHeader();          // update feature values
        } catch (ArrayIndexOutOfBoundsException ex){
            throw new ConvertException("Converted data too big");
        }
    }

    public byte[] toByteArray(){
        return Arrays.copyOf(outputBuffer, cur);
    }

    // write uvm file header
    private void writeHeader() throws ConvertException {
        int offset = 15;    // header size: 15 bytes

        write32(MAGIC | UsedFeatures.get());
        write8(VERSION);
        write8(classLoader.totalMethods());
        write16(classLoader.getMainIndex());

        // offset to constant data
        offset += 2 * classLoader.totalClasses(); // class header size: 2bytes
        write16(offset);

        // offset to string data
        offset += 4 * classLoader.totalConstantEntries(); // constant value size: 4bytes
        write16(offset);

        // offset to method data
        offset += 2 * classLoader.totalStrings(); // string indices
        offset += classLoader.totalStringSize();  // string data
        write16(offset);
        write8(classLoader.totalStaticFields());  // static fields
    }

    // write all class headers
    private void writeClassHeaders() throws ConvertException {
        for (int i = 0; i < classLoader.totalClasses(); i++) {
            ClassInfo classInfo = classLoader.getClassInfo(i);

            write8(classInfo.getSuperClassIndex());
            write8(classInfo.nonStaticFields());
        }
    }

    // write all 32bit constant values
    private void writeConstantEntries() throws ConvertException {
        System.out.println("Writing " + classLoader.totalConstantEntries() + " constant entries");
        for (int i = 0; i < classLoader.totalConstantEntries(); i++) {
            System.out.println("  entry[" + i + "] = 0x" + Integer.toHexString(classLoader.getConstantEntry(i)));
            write32(classLoader.getConstantEntry(i));
        }
    }

    // write all string headers and data
    private void writeStrings() throws ConvertException {
        System.out.println("Writing " + classLoader.totalStrings() + " strings");

        // write array of string offsets
        int offset = 2 * classLoader.totalStrings();
        for (int i = 0; i < classLoader.totalStrings(); i++) {
            write16(offset);
            offset += classLoader.getString(i).length() + 1;
        }

        // write the strings itself
        for (int i = 0; i < classLoader.totalStrings(); i++) {
            String str = classLoader.getString(i);
            System.out.println("  entry[" + (i + classLoader.totalConstantEntries()) + "] = \"" + str + "\"");

            // write zero terminated c strings
            for (int j = 0; j < str.length(); j++) write8(str.charAt(j));
            write8(0);
        }
    }

    // write all methods
    private void writeMethods() throws ConvertException, ClassNotFoundException {
        int codeOffset = 0;

        // build the method id table
        MethodIdTable mt = new MethodIdTable(classLoader);
        mt.build();

        // write all Method headers
        for (int i = 0; i < classLoader.totalMethods(); i++) {
            MethodInfo methodInfo = classLoader.getMethod(i);

            // offset from this header to bytecode (this header is 8 bytes
            // in size)
            write16((classLoader.totalMethods() - i) * 8 + codeOffset);      // code_index
            write16((classLoader.getClassIndex(i) << 8) + mt.getEntry(i));// id
            write8(methodInfo.getName().equals("<clinit>") ? 1 : 0);       // flags
            write8(methodInfo.getArgs());                              // args
            write8(methodInfo.getCodeInfo().getMaxLocals());           // max_locals
            write8(methodInfo.getCodeInfo().getMaxStack());            // max_stack

            codeOffset += methodInfo.getCodeInfo().getBytecode().length;
        }

        // write bytecode
        for (int i = 0; i < classLoader.totalMethods(); i++) {
            ClassInfo classInfo = classLoader.getClassInfoFromMethodIndex(i);
            MethodInfo methodInfo = classLoader.getMethod(i);

            System.out.println("Converting " +
                    classInfo.getName() + "." +
                    methodInfo.getName() + ":" +
                    methodInfo.getSignature());

            byte code[] = classLoader.getMethod(i).getCodeInfo().getBytecode();

            // adjust references etc
            CodeTranslator.translate(classInfo, code);

            // and write bytecode
            for (int j = 0; j < code.length; j++){
                write8(code[j]);
            }
            System.out.println("");
        }
    }

    private void updateHeader() throws ConvertException {
        int old_cur = cur;
        cur = 0;
        writeHeader();
        cur = old_cur;
    }

    // write a 8 bit value into buffer and make sure buffer
    // end is not overwritten
    private void write8(int val){
        outputBuffer[cur++] = (byte) val;
    }

    // write a 16 bit value little endian into buffer
    private void write16(int val){
        write8(val & 0xff);
        write8((val >> 8) & 0xff);
    }

    // write a 32 bit value little endian into buffer
    private void write32(int val){
        write8(val & 0xff);
        write8((val >> 8) & 0xff);
        write8((val >> 16) & 0xff);
        write8((val >> 24) & 0xff);
    }
}
