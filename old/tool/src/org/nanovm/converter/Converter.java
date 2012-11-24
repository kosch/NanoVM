/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.nanovm.converter;

import org.nanovm.NanoVMByteCode;

/**
 *
 * @author nils
 */
public class Converter {

    public static NanoVMByteCode convert(String config, String classpath, String classname) {
        Config.load(config);
        ClassLoader.setClassPath(classpath);
        ClassLoader.load(classname);
        NanoVMByteCode code = new NanoVMByteCode(Config.getMaxSize());        
        Generator gen = new Generator();
        gen.generate(code);
        return code;
    }
}
