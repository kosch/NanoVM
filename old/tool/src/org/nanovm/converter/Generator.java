package org.nanovm.converter;

//
//  NanoVMTool, Converter and Upload Tool for the NanoVM
//  Copyright (C) 2005 by Till Harbaum <Till@Harbaum.org>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//  Parts of this tool are based on public domain code written by Kimberley
//  Burchett: http://www.kimbly.com/code/classfile/
//

//
// UVMWriter.java
//
import org.nanovm.*;

public class Generator {

    private NanoVMByteCode code;
    static final int MAGIC = 0xBE000000;
    static final int VERSION = 2;
    int cur;

    void updateHeader() throws ConvertException {
        int old_cur = cur;
        cur = 0;
        writeHeader();
        cur = old_cur;
    }

    // write uvm file header
    void writeHeader() throws ConvertException {
        int offset = 15;    // header size: 15 bytes

        code.write32(MAGIC | UsedFeatures.get());
        code.write8(VERSION);
        code.write8(ClassLoader.totalMethods());
        code.write16(ClassLoader.getMainIndex());

        // offset to constant data
        offset += 2 * ClassLoader.totalClasses(); // class header size: 2bytes
        code.write16(offset);

        // offset to string data
        offset += 4 * ClassLoader.totalConstantEntries(); // constant value size: 4bytes
        code.write16(offset);

        // offset to method data
        offset += 2 * ClassLoader.totalStrings(); // string indices
        offset += ClassLoader.totalStringSize();  // string data
        code.write16(offset);
        code.write8(ClassLoader.totalStaticFields());  // static fields
    }

    // write all class headers
    void writeClassHeaders() throws ConvertException {
        for (int i = 0; i < ClassLoader.totalClasses(); i++) {
            ClassInfo classInfo = ClassLoader.getClassInfo(i);

            code.write8(classInfo.getSuperClassIndex());
            code.write8(classInfo.nonStaticFields());
        }
    }

    // write all 32bit constant values
    void writeConstantEntries() throws ConvertException {
        System.out.println("Writing " + ClassLoader.totalConstantEntries() + " constant entries");
        for (int i = 0; i < ClassLoader.totalConstantEntries(); i++) {
            System.out.println("  entry[" + i + "] = 0x" + Integer.toHexString(ClassLoader.getConstantEntry(i)));
            code.write32(ClassLoader.getConstantEntry(i));
        }
    }

    // write all string headers and data
    void writeStrings() throws ConvertException {
        System.out.println("Writing " + ClassLoader.totalStrings() + " strings");

        // write array of string offsets
        int offset = 2 * ClassLoader.totalStrings();
        for (int i = 0; i < ClassLoader.totalStrings(); i++) {
            code.write16(offset);
            offset += ClassLoader.getString(i).length() + 1;
        }

        // write the strings itself
        for (int i = 0; i < ClassLoader.totalStrings(); i++) {
            String str = ClassLoader.getString(i);
            System.out.println("  entry[" + (i + ClassLoader.totalConstantEntries()) + "] = \"" + str + "\"");

            // write zero terminated c strings
            for (int j = 0; j < str.length(); j++) {
                code.write8(str.charAt(j));
            }
            code.write8(0);
        }
    }

    // write all methods
    void writeMethods() throws ConvertException {
        int codeOffset = 0;

        // build the method id table
        MethodIdTable.build();

        // write all Method headers
        for (int i = 0; i < ClassLoader.totalMethods(); i++) {
            MethodInfo methodInfo = ClassLoader.getMethod(i);

            // offset from this header to bytecode (this header is 8 bytes
            // in size)
            code.write16((ClassLoader.totalMethods() - i) * 8 + codeOffset);      // code_index
            code.write16((ClassLoader.getClassIndex(i) << 8) +
                    MethodIdTable.getEntry(i));                        // id
            code.write8(methodInfo.getName().equals("<clinit>") ? 1 : 0);       // flags
            code.write8(methodInfo.getArgs());                              // args
            code.write8(methodInfo.getCodeInfo().getMaxLocals());           // max_locals
            code.write8(methodInfo.getCodeInfo().getMaxStack());            // max_stack

            codeOffset += methodInfo.getCodeInfo().getBytecode().length;
        }

        // write bytecode
        for (int i = 0; i < ClassLoader.totalMethods(); i++) {
            ClassInfo classInfo = ClassLoader.getClassInfoFromMethodIndex(i);
            MethodInfo methodInfo = ClassLoader.getMethod(i);

            System.out.println("Converting " +
                    classInfo.getName() + "." +
                    methodInfo.getName() + ":" +
                    methodInfo.getSignature());

            byte bcode[] = ClassLoader.getMethod(i).getCodeInfo().getBytecode();

            // adjust references etc
            CodeTranslator.translate(classInfo, bcode);

            // and write bytecode
            for (int j = 0; j < bcode.length; j++) {
                code.write8(bcode[j]);
            }

            System.out.println("");
        }
    }

    public Generator() {
    }

    public void generate(NanoVMByteCode code) {
        this.code = code;
        System.out.println("Generating unified class file ...");

        // create output buffer and reset output pointer
        cur = 0;

        try {
            writeHeader();           // write file header
            writeClassHeaders();     // write class headers
            writeConstantEntries();  // write all 32-bit constants
            writeStrings();          // write all string data
            writeMethods();          // write method headers and byte code
            updateHeader();          // update feature values
        } catch (ConvertException e) {
            System.out.println("Conversion failed: " + e.toString());
            System.exit(-1);
        }
    }
}
